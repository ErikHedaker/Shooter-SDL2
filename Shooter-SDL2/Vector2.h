#pragma once

template<class T> struct Vector2
{
    T x;
    T y;

    Vector2& operator+=( const Vector2& rhs )
    {
        x = x + rhs.x;
        y = y + rhs.y;
        return *this;
    }
    Vector2& operator-=( const Vector2& rhs )
    {
        x = x - rhs.x;
        y = y - rhs.y;
        return *this;
    }
    template<class Y> operator Vector2<Y>( )
    {
        return { static_cast<Y>( x ), static_cast<Y>( y ) };
    }
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