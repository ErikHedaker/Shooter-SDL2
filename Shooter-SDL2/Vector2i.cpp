#include "Vector2i.h"

Vector2i::Vector2i( ) :
    x( 0 ),
    y( 0 )
{
}
Vector2i::Vector2i( int x, int y ) :
    x( x ),
    y( y )
{
}

bool operator==( const Vector2i& lhs, const Vector2i& rhs )
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=( const Vector2i& lhs, const Vector2i& rhs )
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}
bool operator<=( const Vector2i& lhs, const Vector2i& rhs )
{
    return lhs.x <= rhs.x && lhs.y <= rhs.y;
}
bool operator>=( const Vector2i& lhs, const Vector2i& rhs )
{
    return lhs.x >= rhs.x && lhs.y >= rhs.y;
}
bool operator<( const Vector2i& lhs, const Vector2i& rhs )
{
    return lhs.x < rhs.x && lhs.y < rhs.y;
}
bool operator>( const Vector2i& lhs, const Vector2i& rhs )
{
    return lhs.x > rhs.x && lhs.y > rhs.y;
}
const Vector2i operator+( const Vector2i& lhs, const Vector2i& rhs )
{
    Vector2i result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    return result;
}
const Vector2i operator+( const Vector2i& lhs, int rhs )
{
    Vector2i result;
    result.x = lhs.x + rhs;
    result.y = lhs.y + rhs;
    return result;
}
const Vector2i operator-( const Vector2i& lhs, const Vector2i& rhs )
{
    Vector2i result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    return result;
}
const Vector2i operator-( const Vector2i& lhs, int rhs )
{
    Vector2i result;
    result.x = lhs.x - rhs;
    result.y = lhs.y - rhs;
    return result;
}
const Vector2i operator*( const Vector2i& lhs, const Vector2i& rhs )
{
    Vector2i result;
    result.x = lhs.x * rhs.x;
    result.y = lhs.y * rhs.y;
    return result;
}
const Vector2i operator*( const Vector2i& lhs, int rhs )
{
    Vector2i result;
    result.x = lhs.x * rhs;
    result.y = lhs.y * rhs;
    return result;
}
const Vector2i operator/( const Vector2i& lhs, const Vector2i& rhs )
{
    Vector2i result;
    result.x = lhs.x / rhs.x;
    result.y = lhs.y / rhs.y;
    return result;
}
const Vector2i operator/( const Vector2i& lhs, int rhs )
{
    Vector2i result;
    result.x = lhs.x / rhs;
    result.y = lhs.y / rhs;
    return result;
}

void Vector2iHasher::HashCombine( std::size_t& seed, int value )
{
    /*
    https://www.quora.com/How-can-I-declare-an-unordered-set-of-pair-of-int-int-in-C++11
    Function implementation is based on the source
    */

    std::hash<int> hasher;

    seed ^= hasher( value ) + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 );
}
std::size_t Vector2iHasher::operator()( const Vector2i& key ) const
{
    size_t seed = 0;

    HashCombine( seed, key.x );
    HashCombine( seed, key.y );

    return seed;
}