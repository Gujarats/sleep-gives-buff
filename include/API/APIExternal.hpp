#pragma once
#include "TrueHUDAPI.h"

class APIExternal
{
public:
    TRUEHUD_API::IVTrueHUD4* ersh_TrueHUD = nullptr;

    static APIExternal* GetSingleton()
    {
        static APIExternal singleton;
        return std::addressof(singleton);
    }
    
    void createCustomeWidgetBar()
    {
        logger::info("TrueHUD : create custome bar started");
        if (!ersh_TrueHUD) {
            logger::info("...aborted: TrueHUD API not acquired.");
            return;
        }
    
        ersh_TrueHUD->LoadCustomWidgets(SKSE::GetPluginHandle(), "somePath", [](TRUEHUD_API::APIResult a_Res) {
            switch (a_Res) {
            case TRUEHUD_API::APIResult::OK:
                logger::info("TrueHUD : callbac result ok");
            case TRUEHUD_API::APIResult::AlreadyGiven:
                logger::info("TrueHUD: callbac result AlreadyGiven");
                break;
            case TRUEHUD_API::APIResult::AlreadyTaken:
                logger::info("TrueHUD: callbac result Taken");
                break;
            }
        });
    }
};
