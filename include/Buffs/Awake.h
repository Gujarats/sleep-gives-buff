#pragma once
#include "Utility.h"

class Awake {
public:
    RE::SpellItem* HealthRegen;
    RE::SpellItem* MagicRegen;
    RE::SpellItem* HealthIncreased;
    RE::SpellItem* StaminaIncreased;
    RE::SpellItem* MagicIncreased;

    std::mutex update_mutex;

    static Awake* GetSingleton()
	{
			static Awake singleton;
			return &singleton;
	}

    void GiveBuffs(){
        Utility::GetPlayer()->AddSpell(MagicRegen);
        Utility::GetPlayer()->AddSpell(HealthIncreased);
        Utility::GetPlayer()->AddSpell(StaminaIncreased);
        Utility::GetPlayer()->AddSpell(MagicIncreased);
    } 
};
