#pragma once

#include <utility>

template<class T> struct Vector2
{
    T x;
    T y;
};

template<class T> bool operator==( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
template<class T> bool operator!=( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}
template<class T> bool operator<=( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return lhs.x <= rhs.x && lhs.y <= rhs.y;
}
template<class T> bool operator>=( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return lhs.x >= rhs.x && lhs.y >= rhs.y;
}
template<class T> bool operator<( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return lhs.x < rhs.x && lhs.y < rhs.y;
}
template<class T> bool operator>( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return lhs.x > rhs.x && lhs.y > rhs.y;
}
template<class T> const Vector2<T> operator+( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}
template<class T> const Vector2<T> operator+( const Vector2<T>& lhs, T rhs )
{
    return { lhs.x + rhs, lhs.y + rhs };
}
template<class T> const Vector2<T> operator-( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}
template<class T> const Vector2<T> operator-( const Vector2<T>& lhs, T rhs )
{
    return { lhs.x - rhs, lhs.y - rhs };
}
template<class T> const Vector2<T> operator*( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return { lhs.x * rhs.x, lhs.y * rhs.y };
}
template<class T> const Vector2<T> operator*( const Vector2<T>& lhs, T rhs )
{
    return { lhs.x * rhs, lhs.y * rhs };
}
template<class T> const Vector2<T> operator/( const Vector2<T>& lhs, const Vector2<T>& rhs )
{
    return { lhs.x / rhs.x, lhs.y / rhs.y };
}
template<class T> const Vector2<T> operator/( const Vector2<T>& lhs, T rhs )
{
    return { lhs.x / rhs, lhs.y / rhs };
}