// ------------------------------------------------------------------------------------------------
#include "Handle/Document.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
void DocumentRef::Validate() const
{
    if (!m_Ptr)
    {
        STHROWF("Invalid XML document reference");
    }
}

} // Namespace:: SqMod