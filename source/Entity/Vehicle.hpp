#ifndef _ENTITY_VEHICLE_HPP_
#define _ENTITY_VEHICLE_HPP_

// ------------------------------------------------------------------------------------------------
#include "Entity.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * ...
*/
class CVehicle : public Reference< CVehicle >
{
public:
    // --------------------------------------------------------------------------------------------
    using RefType::Reference;
};

} // Namespace:: SqMod

#endif // _ENTITY_VEHICLE_HPP_