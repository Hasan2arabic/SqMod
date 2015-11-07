#ifndef _BASE_BUFFER_HPP_
#define _BASE_BUFFER_HPP_

// ------------------------------------------------------------------------------------------------
#include "Config.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
class Buffer
{
public:

    // --------------------------------------------------------------------------------------------
    typedef SQChar          Value;

    // --------------------------------------------------------------------------------------------
    typedef Value &         Reference;
    typedef const Value &   ConstRef;

    // --------------------------------------------------------------------------------------------
    typedef Value *         Pointer;
    typedef const Value *   ConstPtr;

    // --------------------------------------------------------------------------------------------
    typedef SQUint32        SzType;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Buffer();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Buffer(SzType sz);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Buffer(const Buffer &) = delete;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Buffer(Buffer && o);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    ~Buffer();

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Buffer & operator = (const Buffer &) = delete;

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Buffer & operator = (Buffer && o);
    
    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool operator == (const Buffer & o) const
    {
        return (m_Size == o.m_Size);
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool operator != (const Buffer & o) const
    {
        return (m_Size != o.m_Size);
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool operator < (const Buffer & o) const
    {
        return (m_Size < o.m_Size);
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool operator > (const Buffer & o) const
    {
        return (m_Size > o.m_Size);
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool operator <= (const Buffer & o) const
    {
        return (m_Size <= o.m_Size);
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    bool operator >= (const Buffer & o) const
    {
        return (m_Size >= o.m_Size);
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    operator bool () const
    {
        return (m_Data != nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    operator ! () const
    {
        return (m_Data == nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Pointer Begin()
    {
        return m_Data;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    ConstPtr Begin() const
    {
        return m_Data;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Pointer End()
    {
        return m_Data + m_Size;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    ConstPtr End() const
    {
        return m_Data + m_Size;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    Pointer Data()
    {
        return m_Data;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    ConstPtr Data() const
    {
        return m_Data;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    SzType Size() const
    {
        return m_Size;
    }

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void Resize(SzType sz);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void Reserve(SzType sz);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void Increase(SzType sz)
    {
        Reserve(m_Size + sz);
    }

protected:

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    void Copy(ConstPtr buf, SzType sz);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static Pointer Alloc(SzType sz);

    /* --------------------------------------------------------------------------------------------
     * ...
    */
    static void Free(Pointer buf);

private:

    // --------------------------------------------------------------------------------------------
    Pointer m_Data;
    SzType  m_Size;
};

} // Namespace:: SqMod

#endif // _BASE_BUFFER_HPP_
