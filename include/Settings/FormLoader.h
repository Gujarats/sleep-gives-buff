#pragma once

#include "Utility.h"

#undef AddForm

class FormLoader
{
public:
  
    static FormLoader* GetSingleton()
    {
        static FormLoader formLoader;
        return &formLoader;
    }

    // Cache commonly called addresses to avoid address lib overhead
    void CacheGameAddresses()
    {
        auto utility = Utility::GetSingleton();
        // Cache player singleton address
        utility->PlayerSingletonAddress       = RELOCATION_ID(517014, 403521).address(); // what in the world ?? where does the number coming from ??
    }

};
