// ------------------------------------------------------------------------------------------------
#include "Library/Worker.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
SQMODE_DECL_TYPENAME(SqWorker, _SC("SqWorker"))

// ------------------------------------------------------------------------------------------------
Worker::Container Worker::sm_Workers{};

// ------------------------------------------------------------------------------------------------
Thread::Thread( Worker * worker)
    : mWorker(worker)
    , mObject(worker)
    , mThread(&Worker::Start, worker)
{
}
// ------------------------------------------------------------------------------------------------
Thread::Thread(Thread && o) noexcept
    : mWorker(o.mWorker)
    , mObject(std::forward< LightObj >(o.mObject))
    , mThread(std::forward< std::thread >(o.mThread))
{
    o.mWorker = nullptr;
}
// ------------------------------------------------------------------------------------------------
Worker::Worker(SQInteger stack, String && str, size_t h)
    : m_PendingJobs(4096), m_FinishedJobs(4096)
    , m_Running()
    , m_VM(nullptr)
    , m_Mutex()
    , m_Hash(h)
    , m_Name(std::forward< String >(str))
    , m_StackSize(stack)
{
}
// ------------------------------------------------------------------------------------------------
Worker::~Worker()
{
    // Instruct the thread to stop whenever possible
    Stop();
    // Locate our self in the list
    std::unique_ptr< Thread > & t = sm_Workers[m_Hash];
    // Wait for the thread to finish
    if (t->mThread.joinable())
    {
        t->mThread.join();
    }
    // Remove ourselves from the list
    sm_Workers.erase(m_Hash);
}

// ------------------------------------------------------------------------------------------------
void Worker::Terminate()
{
    // Attempt to stop workers
    for (auto & t : sm_Workers)
    {
        // Tell the thread to stop as soon as it can
        t.second->mWorker->Stop();
        // Wait for it to stop
        if (t.second->mThread.joinable())
        {
            t.second->mThread.join();
        }
    }
    // Simply get rid of them
    sm_Workers.clear();
}
// ------------------------------------------------------------------------------------------------
void Worker::Process(size_t jobs)
{
    std::vector< Worker * > workers;
    workers.reserve(sm_Workers.size());
    for (auto & t : sm_Workers)
    {
        workers.push_back(t.second->mWorker);
    }
    for (auto & t : workers)
    {
        for (size_t n = 0; n < jobs; ++n)
        {
            std::unique_ptr< BaseJob > job;
            // Try to get a job from the queue
            if (t->m_FinishedJobs.try_dequeue(job))
            {
                // Allow the job to finish
                job->Finish(t->m_VM, *t);
            }
        }
    }
}
// ------------------------------------------------------------------------------------------------
LightObj Worker::Create(SQInteger stack, StackStrF & str)
{
    HSQUIRRELVM vm = SqVM();
	// Make sure there's a name
	if (str.mLen <= 0)
	{
		STHROWF("Invalid or empty worker name");
	}
	// Extract the worker name
    String name(str.mPtr, static_cast< size_t >(str.mLen));
    // Create the name hash
    size_t name_hash = std::hash< String >{}(name);
    // Make sure this worker doesn't exist
    if (sm_Workers.exists(name_hash))
    {
        STHROWF("Worker already exists");
    }
    // Attempt to create a routine instance
    DeleteGuard< Worker > dg(new Worker(stack, std::move(name), name_hash));
    ClassType< Worker >::PushInstance(vm, dg.Get());
    Worker * worker = dg.Grab();
    // Create the worker thread
    std::unique_ptr< Thread > & th = sm_Workers.emplace_back(name_hash, new Thread{worker});
    // Return the worker object
    return th->mObject;
}
// ------------------------------------------------------------------------------------------------
void Worker::Start()
{
    // Initialize
    {
        // Acquire exclusive access to this instance
        std::lock_guard< std::mutex > lg(m_Mutex);
        // This should never be the case but why not
        if (m_VM)
        {
            STHROWF("Worker was already started.");
        }
        // Create the JS state
        m_VM = sq_open(m_StackSize);
        // Associate with this VM
        sq_setforeignptr(m_VM, this);
        // Tell the VM to use these functions to output user on error messages
        sq_setprintfunc(m_VM, PrintFunc, ErrorFunc);
        // Tell the VM to trigger this function on compile time errors
        sq_setcompilererrorhandler(m_VM, CompilerErrorHandler);
        // Push the runtime error handler on the stack and create a closure
        sq_newclosure(m_VM, RuntimeErrorHandler, 0);
        // Tell the VM to trigger this function on runtime errors
        sq_seterrorhandler(m_VM);
        // This is now running
        m_Running.test_and_set();
    }
    // Process
    while (m_Running.test_and_set())
    {
        // Acquire exclusive access to this instance
        std::lock_guard< std::mutex > lg(m_Mutex);
        // Do the actual processing
        Work();
    }
    // Cleanup
    {
        // Acquire exclusive access to this instance
        std::lock_guard< std::mutex > lg(m_Mutex);
        // We're out of the process loop
        sq_close(m_VM);
    }
}
// ------------------------------------------------------------------------------------------------
void Worker::Work()
{
    std::unique_ptr< BaseJob > job;
    // Try to get a job from the queue
    if (!m_PendingJobs.try_dequeue(job))
    {
        using namespace std::chrono_literals;
        // Do not hammer the CPU if there are no jobs
        std::this_thread::sleep_for(50ms);
    }
    else
    {
        // Do the job
        job->Start(m_VM, *this);
        // This job was finished
        m_FinishedJobs.enqueue(std::move(job));
    }
}
// ------------------------------------------------------------------------------------------------
void Worker::PrintFunc(HSQUIRRELVM /*vm*/, CSStr msg, ...)
{
    // Initialize the variable argument list
    va_list args;
    va_start(args, msg);
    // Forward the message to the logger
    Logger::Get().SendFv(LOGL_USR, false, msg, args);
    // Finalize the variable argument list
    va_end(args);
}

// ------------------------------------------------------------------------------------------------
void Worker::ErrorFunc(HSQUIRRELVM vm, CSStr msg, ...)
{
    // Initialize the variable argument list
    va_list args;
    va_start(args, msg);
    // Tell the logger to display debugging information
    Logger::Get().DebugFv(vm, msg, args);
    // Finalize the variable argument list
    va_end(args);
}
// ------------------------------------------------------------------------------------------------
SQInteger Worker::RuntimeErrorHandler(HSQUIRRELVM vm)
{
    // Was there a value thrown?
    if (sq_gettop(vm) < 1)
    {
        return SQ_OK; // No error to display!
    }
    // Attempt to generate the string value
    StackStrF val(vm, 2);
    // Have we failed to retrieve the string?
    if (SQ_FAILED(val.Proc(false)))
    {
        Logger::Get().DebugF(vm, _SC("Unknown runtime error has occurred"));
    }
    else
    {
        Logger::Get().DebugF(vm, _SC("%s"), val.mPtr);
    }
    // We handled the error
    return SQ_OK;
}

// ------------------------------------------------------------------------------------------------
void Worker::CompilerErrorHandler(HSQUIRRELVM /*vm*/, CSStr desc, CSStr src, SQInteger line, SQInteger column)
{
    LogFtl("Message: %s\n[\n=>Location: %s\n=>Line: %" PRINT_INT_FMT "\n=>Column: %" PRINT_INT_FMT "\n]", desc, src, line, column);
}

// ------------------------------------------------------------------------------------------------
void TerminateWorkers()
{
    Worker::Terminate();
}
// ================================================================================================
void Register_Worker(HSQUIRRELVM vm)
{
    Table thns(vm);

    thns.Bind(_SC("Worker"),
        Class< Worker, NoConstructor< Worker > >(vm, SqWorker::Str)
        // Meta-methods
        .SquirrelFunc(_SC("_typename"), &SqWorker::Fn)
        // Properties
        .Prop(_SC("Name"), &Worker::GetName)
        // Core Methods
        .Func(_SC("Enqueue"), &Worker::Enqueue)
        // Static Member Methods
    );

    thns.FmtFunc(_SC("Process"), &Worker::Process);
    thns.FmtFunc(_SC("Create"), &Worker::Create);

    RootTable(vm).Bind(_SC("SqThread"), thns);
}

} // Namespace:: SqMod