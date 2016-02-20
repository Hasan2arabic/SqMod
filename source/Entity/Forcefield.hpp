#ifndef _ENTITY_FORCEFIELD_HPP_
#define _ENTITY_FORCEFIELD_HPP_

// ------------------------------------------------------------------------------------------------
#include "Base/Shared.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * Manages Forcefield instances.
*/
class CForcefield
{
    // --------------------------------------------------------------------------------------------
    friend class Core;

private:

    // --------------------------------------------------------------------------------------------
    static Color3       s_Color3;
    static Vector3      s_Vector3;

    // --------------------------------------------------------------------------------------------
    static Uint32       s_ColorR, s_ColorG, s_ColorB;

    /* --------------------------------------------------------------------------------------------
     * Cached identifiers for fast integer to string conversion.
    */
    static SQChar s_StrID[SQMOD_FORCEFIELD_POOL][8];

    /* --------------------------------------------------------------------------------------------
     * Identifier of the managed entity.
    */
    Int32   m_ID;

    /* --------------------------------------------------------------------------------------------
     * User tag and data associated with this instance.
    */
    String  m_Tag;
    Object  m_Data;

    /* --------------------------------------------------------------------------------------------
     * Base constructor.
    */
    CForcefield(Int32 id);

    /* --------------------------------------------------------------------------------------------
     * Copy constructor. (disabled)
    */
    CForcefield(const CForcefield &);

    /* --------------------------------------------------------------------------------------------
     * Copy assignment operator. (disabled)
    */
    CForcefield & operator = (const CForcefield &);

public:

    // --------------------------------------------------------------------------------------------
    static const Int32 Max;

    /* --------------------------------------------------------------------------------------------
     * Destructor.
    */
    ~CForcefield();

    /* --------------------------------------------------------------------------------------------
     * See whether this instance manages a valid entity.
    */
    bool Validate() const
    {
        if (VALID_ENTITY(m_ID))
            return true;
        SqThrow("Invalid forcefield reference [%s]", m_Tag.c_str());
        return false;
    }

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to compare two instances of this type.
    */
    Int32 Cmp(const CForcefield & o) const;

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to convert an instance of this type to a string.
    */
    CSStr ToString() const;

    /* --------------------------------------------------------------------------------------------
     * Retrieve the identifier of the entity managed by this instance.
    */
    Int32 GetID() const { return m_ID; }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the maximum possible identifier to an entity of this type.
    */
    Int32 GetMaxID() const { return SQMOD_FORCEFIELD_POOL; }

    /* --------------------------------------------------------------------------------------------
     * Check whether this instance manages a valid entity.
    */
    bool IsActive() const { return VALID_ENTITY(m_ID); }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the associated user tag.
    */
    CSStr GetTag() const;

    /* --------------------------------------------------------------------------------------------
     * Modify the associated user tag.
    */
    void SetTag(CSStr tag);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the associated user data.
    */
    Object & GetData();

    /* --------------------------------------------------------------------------------------------
     * Modify the associated user data.
    */
    void SetData(Object & data);

    // --------------------------------------------------------------------------------------------
    bool Destroy(Int32 header, Object & payload);
    bool Destroy() { return Destroy(0, NullObject()); }
    bool Destroy(Int32 header) { return Destroy(header, NullObject()); }

    // --------------------------------------------------------------------------------------------
    bool BindEvent(Int32 evid, Object & env, Function & func) const;

    // --------------------------------------------------------------------------------------------
    bool IsStreamedFor(CPlayer & player) const;
    Int32 GetWorld() const;
    void SetWorld(Int32 world) const;
    const Color3 & GetColor() const;
    void SetColor(const Color3 & col) const;
    void SetColorEx(Uint8 r, Uint8 g, Uint8 b) const;
    const Vector3 & GetPosition() const;
    void SetPosition(const Vector3 & pos) const;
    void SetPositionEx(Float32 x, Float32 y, Float32 z) const;
    Float32 GetRadius() const;
    void SetRadius(Float32 radius) const;
    Object & GetOwner() const;
    Int32 GetOwnerID() const;

    // --------------------------------------------------------------------------------------------
    Float32 GetPosX() const;
    Float32 GetPosY() const;
    Float32 GetPosZ() const;
    void SetPosX(Float32 x) const;
    void SetPosY(Float32 y) const;
    void SetPosZ(Float32 z) const;

    // --------------------------------------------------------------------------------------------
    Uint32 GetColR() const;
    Uint32 GetColG() const;
    Uint32 GetColB() const;
    void SetColR(Uint32 r) const;
    void SetColG(Uint32 g) const;
    void SetColB(Uint32 b) const;
};

} // Namespace:: SqMod

#endif // _ENTITY_FORCEFIELD_HPP_