#pragma once

// ------------------------------------------------------------------------------------------------
#include "Base/Shared.hpp"
#include "Base/VecMap.hpp"
#include "Library/Worker/Job.hpp"
#include "Logger.hpp"

// ------------------------------------------------------------------------------------------------
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <chrono>
#include <condition_variable>

// ------------------------------------------------------------------------------------------------
#include <concurrentqueue.h>

// ------------------------------------------------------------------------------------------------
namespace SqMod {

using namespace moodycamel;

// ------------------------------------------------------------------------------------------------
struct Worker;

/* ------------------------------------------------------------------------------------------------
 * Thread.
*/
struct Thread
{
    // --------------------------------------------------------------------------------------------
    Worker *    mWorker; // Worker pointer.
    LightObj    mObject; // Worker object.
    std::thread mThread; // Worker thread.
    /* --------------------------------------------------------------------------------------------
     * Default constructor.
    */
    Thread()
        : mWorker(nullptr), mObject(), mThread()
    {
    }
    /* --------------------------------------------------------------------------------------------
     * Base constructor.
    */
    Thread(Worker * worker);
    /* --------------------------------------------------------------------------------------------
     * Copy constructor (disabled).
    */
    Thread(const Thread & o) = delete;
    /* --------------------------------------------------------------------------------------------
     * Move constructor (disabled).
    */
    Thread(Thread && o) noexcept;
    /* --------------------------------------------------------------------------------------------
     * Destructor.
    */
    ~Thread()
    {
        End();
    }
    /* --------------------------------------------------------------------------------------------
     * Copy assignment (disabled).
    */
    Thread & operator = (const Thread & o) = delete;
    /* --------------------------------------------------------------------------------------------
     * Move assignment (disabled).
    */
    Thread & operator = (Thread && o) = delete;
    /* --------------------------------------------------------------------------------------------
     *
    */
    void End()
    {

    }
};
/* ------------------------------------------------------------------------------------------------
*
*/
struct Worker
{
    /* --------------------------------------------------------------------------------------------
     * Default constructor.
    */
    Worker(SQInteger stack, String && str, size_t h);
    /* --------------------------------------------------------------------------------------------
     * Copy constructor (disabled).
    */
    Worker(const Worker & o) = delete;
    /* --------------------------------------------------------------------------------------------
     * Move constructor (disabled).
    */
    Worker(Worker && o) = delete;
    /* --------------------------------------------------------------------------------------------
     * Destructor.
    */
    ~Worker();
    /* --------------------------------------------------------------------------------------------
     * Copy assignment operator (disabled).
    */
    Worker & operator = (const Worker & o) = delete;
    /* --------------------------------------------------------------------------------------------
     * Move assignment operator (disabled).
    */
    Worker & operator = (Worker && o) = delete;
    /* --------------------------------------------------------------------------------------------
     *
    */
    static void Terminate();
    /* --------------------------------------------------------------------------------------------
     *
    */
    static void Process(size_t jobs);
    /* --------------------------------------------------------------------------------------------
     *
    */
    static LightObj Create(SQInteger stack, StackStrF & str);
    /* --------------------------------------------------------------------------------------------
     * Invoke the actual process loop only if the worker was not requested to stop.
    */
    void Start();
    /* --------------------------------------------------------------------------------------------
     * Stop the worker but do not remove from container.
    */
    void Kill()
    {
        std::lock_guard< std::mutex > lg(m_Mutex);
    }
    /* --------------------------------------------------------------------------------------------
     * Stop the worker and remove from container.
    */
    void Stop()
    {
        m_Running.clear(); // Stop running as soon as you finish what you're doing
    }
    /* --------------------------------------------------------------------------------------------
     * Retrieve the worker name.
    */
    const String & GetName() const
    {
        return m_Name;
    }
    /* --------------------------------------------------------------------------------------------
     *
    */
    void Enqueue(JobWrapperBase & job)
    {
        m_PendingJobs.enqueue(job.Grab());
    }
private:

    /* --------------------------------------------------------------------------------------------
     * Worker thread container.
    */
    using Container = VecMap< size_t, std::unique_ptr< Thread > >;
    /* --------------------------------------------------------------------------------------------
     * List of active worker threads.
    */
    static Container sm_Workers;
    /* --------------------------------------------------------------------------------------------
     *
    */
    using Jobs = ConcurrentQueue< std::unique_ptr< BaseJob > >;
    /* --------------------------------------------------------------------------------------------
     * Pending job queue.
    */
    Jobs                        m_PendingJobs;
    /* --------------------------------------------------------------------------------------------
     * Finished job queue.
    */
    Jobs                        m_FinishedJobs;
    /* --------------------------------------------------------------------------------------------
     * Loop state.
    */
    std::atomic_flag            m_Running;
    /* --------------------------------------------------------------------------------------------
     * Script state.
    */
    HSQUIRRELVM                 m_VM;
    /* --------------------------------------------------------------------------------------------
     * Instance mutex.
    */
    std::mutex                  m_Mutex;
    /* --------------------------------------------------------------------------------------------
     * Cached name hash.
    */
    size_t                      m_Hash;
    /* --------------------------------------------------------------------------------------------
     * Worker name string.
    */
    String                      m_Name;
    /* --------------------------------------------------------------------------------------------
     * Cached name hash.
    */
    SQInteger                   m_StackSize;
    /* --------------------------------------------------------------------------------------------
     * Take jobs from the queue and perform them.
    */
    void Work();
    /* --------------------------------------------------------------------------------------------
     * Script output handlers.
    */
    static void PrintFunc(HSQUIRRELVM vm, CSStr msg, ...);
    static void ErrorFunc(HSQUIRRELVM vm, CSStr msg, ...);

    /* --------------------------------------------------------------------------------------------
     * Script error handlers.
    */
    static SQInteger RuntimeErrorHandler(HSQUIRRELVM vm);
    static void CompilerErrorHandler(HSQUIRRELVM vm, CSStr desc, CSStr src,
                                     SQInteger line, SQInteger column);

};

} // Namespace:: SqMod
