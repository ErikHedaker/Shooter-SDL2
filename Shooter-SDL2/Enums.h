#pragma once

struct Attributes
{
    enum AttributesType
    {
        Renderable = 1 << 0,
        Collision  = 1 << 2,
        Friction   = 1 << 3,
        Gravity    = 1 << 4,
        Decay      = 1 << 5
    };
};

struct States
{
    enum StatesType
    {
        Falling = 1 << 0
    };
};