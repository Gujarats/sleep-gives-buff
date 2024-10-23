#pragma once
#include "Utility.h"

class Rewards
{
public:
    RE::SpellItem* HealthRegen;
    RE::SpellItem* MagicRegen;
    RE::SpellItem* HealthIncreased;
    RE::SpellItem* StaminaIncreased;
    RE::SpellItem* MagicIncreased;


    static Awake* GetSingleton()
    {
        static Awake singleton;
        return &singleton;
    }

    vector<RE::SpellItem*> GetSleepRewards()
    {
        vector<RE::SpellItem*> listBuff;
        listBuff.push_back(MagicRegen);
        return listBuff;
    }

    vector<RE::SpellItem*> GetEatRewards()
    {
        vector<RE::SpellItem*> listBuff;
        listBuff.push_back(MagicRegen);
        return listBuff;
    }
};
