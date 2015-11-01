#ifndef _LIBRARY_FORMAT_HPP_
#define _LIBRARY_FORMAT_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
String GetFormatStr(HSQUIRRELVM vm, SQInteger arg, SQInteger args);
String GetFormatStr(HSQUIRRELVM vm, const String & fstr,  SQInteger arg, SQInteger args);

} // Namespace:: SqMod

#endif // _LIBRARY_FORMAT_HPP_