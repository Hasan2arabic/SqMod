#ifndef _LIBRARY_LONGINT_HPP_
#define _LIBRARY_LONGINT_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
#include <stdexcept>

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
template <typename T> class LongInt
{
public:
    // --------------------------------------------------------------------------------------------
    static_assert(std::is_integral<T>::value, "LongInt type is not an integral type");

	// --------------------------------------------------------------------------------------------
	typedef T Value;

	// --------------------------------------------------------------------------------------------
	LongInt() noexcept
		: m_Data(0), m_Text()
	{

	}

	template <typename U>
	LongInt(U data) noexcept
	{
		*this = data;
	}

	// --------------------------------------------------------------------------------------------
    LongInt(const SQChar * text) noexcept
    {
        *this = text;
    }

    LongInt(const SQChar * text, SQInteger overload = 0) noexcept
    {
        *this = text;
    }

    // --------------------------------------------------------------------------------------------
	LongInt(const LongInt<T> & i) noexcept
        : m_Data(i.m_Data), m_Text(i.m_Text)
    {

    }

    LongInt(LongInt<T> && i) noexcept
        : m_Data(i.m_Data), m_Text(std::move(i.m_Text))
    {

    }

	// --------------------------------------------------------------------------------------------
	~LongInt()
    {

    }

	// --------------------------------------------------------------------------------------------
	LongInt & operator = (const LongInt<T> & i) noexcept
    {
        m_Data = i.m_Data;
        m_Text = i.m_Text;

        return *this;
    }

    LongInt & operator = (LongInt<T> && i) noexcept
    {
        m_Data = i.m_Data;
        m_Text = std::move(i.m_Text);

        return *this;
    }

	// --------------------------------------------------------------------------------------------
	template <typename U, typename std::enable_if<std::is_integral<U>::value>::type* = nullptr>
	LongInt & operator = (U data) noexcept
	{
		m_Data = static_cast<Value>(data);
		m_Text = std::to_string(m_Data);
		return *this;
	}

	LongInt & operator = (const SQChar * text) noexcept
	{
		m_Text = text;
        try
        {
            m_Data = SToI<T>(text, 0, 10);
        }
        catch (const std::invalid_argument & e)
        {
            LogErr("Unable to extract number: %s", e.what());
        }
        return *this;
	}

	// --------------------------------------------------------------------------------------------
	bool operator == (const LongInt<T> & x) const noexcept
	{
		return (m_Data == x.m_Data);
	}

	bool operator != (const LongInt<T> & x) const noexcept
	{
		return (m_Data != x.m_Data);
	}

	bool operator < (const LongInt<T> & x) const noexcept
	{
		return (m_Data < x.m_Data);
	}

	bool operator > (const LongInt<T> & x) const noexcept
	{
		return (m_Data > x.m_Data);
	}

	bool operator <= (const LongInt<T> & x) const noexcept
	{
		return (m_Data <= x.m_Data);
	}

	bool operator >= (const LongInt<T> & x) const noexcept
	{
		return (m_Data >= x.m_Data);
	}

	// --------------------------------------------------------------------------------------------
	inline operator T () const noexcept
    {
        return m_Data;
    }

    // --------------------------------------------------------------------------------------------
    LongInt<T> operator + (const LongInt<T> & x) const noexcept
    {
        return LongInt<T>(m_Data + x.m_Data);
    }

    LongInt<T> operator - (const LongInt<T> & x) const noexcept
    {
        return LongInt<T>(m_Data - x.m_Data);
    }

    LongInt<T> operator * (const LongInt<T> & x) const noexcept
    {
        return LongInt<T>(m_Data * x.m_Data);
    }

    LongInt<T> operator / (const LongInt<T> & x) const noexcept
    {
        return LongInt<T>(m_Data / x.m_Data);
    }

    LongInt<T> operator % (const LongInt<T> & x) const noexcept
    {
        return LongInt<T>(m_Data % x.m_Data);
    }

    // --------------------------------------------------------------------------------------------
    LongInt<T> operator - () const noexcept
    {
        return LongInt<T>(-m_Data);
    }

    // --------------------------------------------------------------------------------------------
    SQInteger Cmp(const LongInt<T> & x) const noexcept
    {
        return m_Data == x.m_Data ? 0 : (m_Data > x.m_Data ? 1 : -1);
    }

    const SQChar * ToString() const noexcept
    {
        return m_Text.c_str();
    }

	// --------------------------------------------------------------------------------------------
	void SetNum(T data) noexcept
	{
		*this = data;
	}

    T GetNum() const noexcept
    {
        return m_Data;
    }

    SQInteger GetSNum() const noexcept
    {
        return static_cast<SQInteger>(m_Data);
    }

    // --------------------------------------------------------------------------------------------
	void SetStr(const SQChar * text) noexcept
	{
		*this = text;
	}

	const String & GetStr() const noexcept
	{
		return m_Text;
	}

	const SQChar * GetCStr() const noexcept
	{
		return m_Text.c_str();
	}

    // --------------------------------------------------------------------------------------------
    void Random() noexcept
    {
        m_Data = RandomVal<T>::Get();
        m_Text = std::to_string(m_Data);
    }

    void Random(T min, T max) noexcept
    {
        m_Data = RandomVal<T>::Get(min, max);
        m_Text = std::to_string(m_Data);
    }

private:
	// --------------------------------------------------------------------------------------------
	T      m_Data;
	String m_Text;
};

// ------------------------------------------------------------------------------------------------
typedef LongInt<Int64> SLongInt;
typedef LongInt<Uint64> ULongInt;

} // Namespace:: SqMod

#endif // _LIBRARY_LONGINT_HPP_
