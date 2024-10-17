#include <spdlog/sinks/basic_file_sink.h>
#include <algorithm>
#include "Events.h"
#include "Settings/FormLoader.h"


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

void GetSpellData() {
    auto someSpell = RE::TESForm::LookupByID(RE::FormID(0x0001CEA6));
    // logger::info("This is the Spell Name : {}",someSpell->GetFormDetailedString());
    logger::info("This is the Spell Type : {}", someSpell->GetFormType());
    logger::info("This is the Spell Name : {}", someSpell->GetName());

    // well rested
    auto wellRested = RE::TESForm::LookupByID(RE::FormID(0x000FB984))->As<RE::SpellItem>();
    logger::info("This is well rested type :{}",wellRested->GetFormType());
    logger::info("This is well rested name :{}", wellRested->GetName());

    // healing spell
    auto healingSpell = RE::TESForm::LookupByID(RE::FormID(0x00012FCC));
    logger::info("This is healing  type :{}", healingSpell->GetFormType());
    logger::info("This is healing name :{}", healingSpell->GetName());

    // created spell from esp file
    auto SGBRegen = RE::TESForm::LookupByEditorID("SGBHealthRegenate");
    logger::info("This is SGBRegen  type :{}", healingSpell->GetFormType());
    logger::info("This is SGBRegen name :{}", healingSpell->GetName());
}

void CreateSpellData() {
    /*RE::SpellItem* WellRested = RE::TESForm::LookupByID(RE::FormID(0x000FB984))->As<RE::SpellItem>();
    RE::SpellItem* NewSpellItem1 = RE::SpellItem(); 
    NewSpellItem1->CopyMagicItemData(WellRested);
    logger::info("WellRested form ID : {}", WellRested->GetFormID());
    logger::info("NewSPellItem form ID : {}", NewSpellItem1->GetFormID());
    logger::info("NewSPellItem data size : {}", NewSpellItem1->GetDataSize());*/
}

void InitListener(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case SKSE::MessagingInterface::kDataLoaded:
        Events::Register();
        GetSpellData();
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
