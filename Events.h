#pragma once

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

			//ProcessSleepStopEvent();
			logger::info("player has awaken from sleep");

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