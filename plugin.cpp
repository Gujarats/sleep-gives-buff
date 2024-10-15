#include <spdlog/sinks/basic_file_sink.h>
#include <algorithm>
#include "Events.h"


namespace logger = SKSE::log;

void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) {
        SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
        return;
    }
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::info);
}

void InitListener(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
        Events::Register();
		break;
	}
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SetupLog();

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto version{ plugin->GetVersion() };
    auto runtimcompat = plugin->GetRuntimeCompatibility();

    logger::info("{} {} loading...", plugin->GetName(), version);

    SKSE::Init(skse);

    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener(InitListener)) {
        logger::info("Plugin listener failed to register");
        return false;
    }else {
        logger::info("Plugin listener success to register");
    }

    logger::info("Plugin loaded successfully");
    return true;
}
