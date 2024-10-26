#pragma once
#include "TrueHUDAPI.h"

static enum class  MyCustomWidgetType{
    SleepIndicator
};

class MyCustomWidget : TRUEHUD_API::WidgetBase
{
    public:
    static MyCustomWidget* GetSingleton()
    {
        static MyCustomWidget singleton;
        return std::addressof(singleton);
    }

}

