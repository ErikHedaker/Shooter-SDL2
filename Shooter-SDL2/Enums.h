#pragma once

struct Attributes
{
    enum AttributesType
    {
        Renderable    = 1 << 0,
        Deletable     = 1 << 1,
        Collide       = 1 << 2,
        Collision     = 1 << 3,
        Friction      = 1 << 4,
        Gravity       = 1 << 5
    };
};

struct States
{
    enum StatesType
    {
        Falling = 1 << 0
    };
};

struct Projectiles
{
    enum ProjectilesType
    {
        None       = 0,
        Pistol     = 1 << 0,
        Shotgun    = 1 << 1,
        Machinegun = 1 << 2,
        Framegun   = 1 << 3
    };
};

enum class Representation
{
    None,
    Lifetime,
    Projectile
};