/*****************************************************************************
File name: string_to_double.cpp
Description: change type string to type double
*****************************************************************************/

#include "string_to_double.h"
#include <sstream>


double string_to_double( const std::string& s )
{
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}
