#pragma once
#include "Utility.h"

namespace logger = SKSE::log;

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
			auto player = Utility::GetPlayer();
			RE::SpellItem* healingSpell = RE::TESForm::LookupByID(RE::FormID(0x00012FCC))->As<RE::SpellItem>();
			player->AddSpell(healingSpell);
            logger::info("player has been given new effect");

			return RE::BSEventNotifyControl::kContinue;
		}

		static void Register()
		{
			RE::ScriptEventSourceHolder* eventHolder = RE::ScriptEventSourceHolder::GetSingleton();
			eventHolder->AddEventSink(OnSleepStopEventHandler::GetSingleton());
		}
	};

	inline static void Register()
	{
		OnSleepStopEventHandler::Register();
	}
}