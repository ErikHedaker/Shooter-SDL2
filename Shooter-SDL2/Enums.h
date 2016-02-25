#pragma once

struct Attributes
{
    enum AttributesType
    {
        Renderable = 1 << 0,
        Collision  = 1 << 2,
        Gravity    = 1 << 3
    };
};

struct States
{
    enum StatesType
    {
        Falling = 1 << 0
    };
};