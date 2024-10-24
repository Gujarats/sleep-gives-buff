#include "Events.h"
#include "Settings/FormLoader.h"
#include "API/APIExternal.hpp"

void initTrueHUDAPI() {
	auto val = APIExternal::GetSingleton();
	val->ersh_TrueHUD = reinterpret_cast<TRUEHUD_API::IVTrueHUD4*>(TRUEHUD_API::RequestPluginAPI(TRUEHUD_API::InterfaceVersion::V4));
	if (val->ersh_TrueHUD) {
		logger::info("Obtained TruehudAPI - {0:x}", (uintptr_t)val->ersh_TrueHUD);	
	} else {
		logger::info("TrueHUD API not found.");
	}
}

void SetupLog() {
    auto path{ SKSE::log::log_directory() };
    if (!path)
        stl::report_and_fail("Unable to lookup SKSE logs directory.");
    *path /= SKSE::PluginDeclaration::GetSingleton()->GetName();
    *path += L".log";

    std::shared_ptr<spdlog::logger> log;
    if (IsDebuggerPresent())
        log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
    else
        log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));

    log->set_level(spdlog::level::level_enum::info);
    log->flush_on(spdlog::level::level_enum::trace);

    set_default_logger(std::move(log));

    spdlog::set_pattern("[%T.%e UTC%z] [%L] [%=5t] %v");
}

void InitListener(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
        FormLoader::GetSingleton()->LoadAllForms();
        Events::Register();
        break;
    case SKSE::MessagingInterface::kPostLoad:
        initTrueHUDAPI();
		break;
	}
}

extern "C" DLLEXPORT constexpr auto SKSEPlugin_Version = []() {
    SKSE::PluginVersionData v{};
    v.PluginVersion(REL::Version{ Version::MAJOR, Version::MINOR, Version::PATCH, 0 });
    v.PluginName("SleepGivesBuff"sv);
    v.AuthorName("GujaratSantana"sv);
    v.UsesAddressLibrary(true);
    v.HasNoStructUse(true);
    v.UsesStructsPost629(false);
    return v;
}();

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SetupLog();

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto version{ plugin->GetVersion() };

    logger::info("{} {} loading...", plugin->GetName(), version);

    SKSE::Init(skse);
    /**
     * init global variable for utility
     */
    FormLoader::GetSingleton()->CacheGameAddresses(); 

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
