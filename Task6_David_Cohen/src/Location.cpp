#include "Location.h"

bool Location::CompareX::operator()(const Location& lhs, const Location& rhs) const
{
    return lhs < rhs;
}

bool Location::CompareY::operator()(const Location& lhs, const Location& rhs) const
{
    if (lhs.y != rhs.y)
        return lhs.y < rhs.y;
    return lhs.x < rhs.x;
}

bool Location::operator!=(const Location& other) const
{
    return x != other.x || y != other.y;
}

bool Location::operator==(const Location& other) const
{
    return !(operator!=(other));
}

bool Location::operator<(const Location& other) const
{
    if (x != other.x)
        return x < other.x;
    return y < other.y;
}