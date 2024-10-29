#pragma once
#include "Buffs/Awake.h"
#include "Utility.h"
#include "API/APIExternal.hpp"

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

        void DrawLineTest()
        {
            auto apiExternal = APIExternal::GetSingleton();

            // draw connected lines
            RE::NiPoint3 start;
            RE::NiPoint3 end;
            float        duration  = 90000.f;
            uint32_t     color     = 0xcc0808;
            float        thickness = 10.f;

            start =  RE::NiPoint3(10.f, 10.f, 10.f);
            end   = RE::NiPoint3(100.f, 10.f, -10.f);
            logger::info("TrueHUD : starting to draw line");
            apiExternal->ersh_TrueHUD->DrawLine(start, end, duration, color, thickness);

            RE::NiQuaternion rotation;
            rotation.w = 10.f;
            rotation.x = 0.f;
            rotation.y = 0.f;
            rotation.z = -100.f;
            start = RE::NiPoint3(150.f, 150.f, 0.f);
            end   = RE::NiPoint3(0.f, 0.f, -100.f);
            logger::info("TrueHUD : starting to draw box");
            apiExternal->ersh_TrueHUD->DrawBox(start, end, rotation, duration,color, thickness);
        }

        RE::BSEventNotifyControl ProcessEvent(const RE::TESWaitStopEvent* a_event, RE::BSTEventSource<RE::TESWaitStopEvent>*) override
        {
            if(a_event->interrupted){
                logger::info("[MENU] :: interrupted");
            } else {
                logger::info("[MENU] :: finish");
            }

            DrawLineTest();

            RE::BSSimpleList<RE::ActiveEffect*>* activeEffectList = Utility::GetPlayer()->AsMagicTarget()->GetActiveEffectList();
         
            for (RE::BSSimpleList<RE::ActiveEffect*>::iterator activeEffectIterator = activeEffectList->begin(); activeEffectIterator != activeEffectList->end();
                 ++activeEffectIterator)
            {
                RE::EffectSetting* es= (*activeEffectIterator)->GetBaseObject();
                RE::MagicItem*          mg       = (*activeEffectIterator)->spell;
                const char*  fullname = mg->GetFullName();
                //logger::info("looping : effect setting = {}",es->GetFullName());
                //logger::info("spell getFullName = {}", fullname);
                logger::info("spell = {}  active effect duration = {} , elapsed second = {}", fullname, (*activeEffectIterator)->duration, (*activeEffectIterator)->elapsedSeconds);

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
