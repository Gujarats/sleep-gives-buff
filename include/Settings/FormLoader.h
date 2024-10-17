#pragma once
#include "Utility.h"
#include "Buffs/Awake.h"

class FormLoader
{
public:
  
    static FormLoader* GetSingleton()
    {
        static FormLoader formLoader;
        return &formLoader;
    }

    void LoadAllForms() { 
        logger::info("load all SleepGivesBuffs started");
        /* The ID is using ability however the type is still SpellItem
        */
        auto Awaken              = Awake::GetSingleton();
        Awaken->HealthRegen = RE::TESForm::LookupByEditorID("SGBHealthRegenAbility")->As<RE::SpellItem>();
        Awaken->MagicRegen = RE::TESForm::LookupByEditorID("SGBMagicRegenAbility")->As<RE::SpellItem>();
        Awaken->StaminaIncreased = RE::TESForm::LookupByEditorID("SGBStaminaIncreasedAbility")->As<RE::SpellItem>();
        Awaken->HealthIncreased = RE::TESForm::LookupByEditorID("SGBHealthIncreasedAbility")->As<RE::SpellItem>();
        Awaken->MagicIncreased = RE::TESForm::LookupByEditorID("SGBMagicIncreasedAbility")->As<RE::SpellItem>();
        
        logger::info("load all SleepGivesBuffs success");
    }

    // Cache commonly called addresses to avoid address lib overhead
    void CacheGameAddresses()
    {
        auto utility = Utility::GetSingleton();
        // Cache player singleton address
        utility->PlayerSingletonAddress       = RELOCATION_ID(517014, 403521).address(); // what in the world ?? where does the number coming from ??
    }

};
