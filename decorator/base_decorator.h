#pragma once
#include <cinttypes>

namespace deco
{
    class BaseDecorator
    {
    protected:
        BaseDecorator();

    public:
        static const uint16_t DECO_ID;
    };

} // namespace deco
