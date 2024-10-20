#pragma once
#include "Buffs/Awake.h"
#include "Utility.h"

namespace Events
{
    class OnSleepStopEventHandler : public RE::BSTEventSink<RE::TESSleepStopEvent>
    {
    public:
        static OnSleepStopEventHandler* GetSingleton()
        {
            static OnSleepStopEventHandler singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::TESSleepStopEvent* a_event, RE::BSTEventSource<RE::TESSleepStopEvent>*) override
        {
            if (!a_event) {
                logger::info("invalid event found");
                return RE::BSEventNotifyControl::kContinue;
            }

            logger::info("player has awaken from sleep");
            // auto player = Utility::GetPlayer();
            // auto SGBRegen = RE::TESForm::LookupByEditorID("SGBHealthRegenate");
            // player->AddSpell(SGBRegen->As<RE::SpellItem>());
            auto awake = Awake::GetSingleton();
            awake->GiveBuffs();
            logger::info("player has been given new effect");

            return RE::BSEventNotifyControl::kContinue;
        }

        static void Register()
        {
            RE::ScriptEventSourceHolder* eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
            eventHolder->AddEventSink(OnSleepStopEventHandler::GetSingleton());
        }
    };

    class WaitStopEventHandler : public RE::BSTEventSink<RE::TESWaitStopEvent>
    {
    public:
        static WaitStopEventHandler* GetSingleton()
        {
            static WaitStopEventHandler singleton;
            return &singleton;
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::TESWaitStopEvent* a_event, RE::BSTEventSource<RE::TESWaitStopEvent>*) override
        {
            if(a_event->interrupted){
                logger::info("[MENU] :: interrupted");
            } else {
                logger::info("[MENU] :: finish");
            }

            RE::BSSimpleList<RE::ActiveEffect*>* activeEffectList = Utility::GetPlayer()->AsMagicTarget()->GetActiveEffectList();
         
            for (RE::BSSimpleList<RE::ActiveEffect*>::iterator activeEffectIterator = activeEffectList->begin(); activeEffectIterator != activeEffectList->end();
                 ++activeEffectIterator)
            {
                RE::EffectSetting* es= (*activeEffectIterator)->GetBaseObject();
                logger::info("looping : effect setting = {}",es->GetFullName());
             

            }
            return RE::BSEventNotifyControl::kContinue;
        }
        

        static void Register()
        {
            RE::ScriptEventSourceHolder* eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
            eventHolder->AddEventSink(WaitStopEventHandler::GetSingleton());
        }
    };

    inline static void Register()
    {
        OnSleepStopEventHandler::Register();
        WaitStopEventHandler::Register();
    }
}
