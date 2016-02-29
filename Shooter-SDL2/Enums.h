#pragma once

struct Attributes
{
    enum AttributesType
    {
        Renderable    = 1 << 0,
        Collision     = 1 << 1,
        Collide       = 1 << 2,
        Friction      = 1 << 3,
        Gravity       = 1 << 4,
        VelocityLimit = 1 << 5,
        Decay         = 1 << 6
    };
};

struct States
{
    enum StatesType
    {
        Falling = 1 << 0
    };
};

struct Guns
{
    enum GunsType
    {
        Pistol     = 1 << 0,
        Shotgun    = 1 << 1,
        Machinegun = 1 << 2,
        Framegun   = 1 << 3
    };
};