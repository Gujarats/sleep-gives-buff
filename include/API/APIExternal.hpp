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
    
    void CustomWidgetLoad()
    {
        logger::info("TrueHUD : create custome bar started");
        if (!ersh_TrueHUD) {
            logger::info("...aborted: TrueHUD API not acquired.");
            return;
        }
    
        ersh_TrueHUD->LoadCustomWidgets(SKSE::GetPluginHandle(), "TrueHUD_Widgets.swf", [](TRUEHUD_API::APIResult a_Res) {
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


    void CustomWidgetLoadStep2() {
        std::string actionScript = "swf/Widgets/TrueHUD_InfoBar.as";
        std::shared_ptr<WidgetBase> myWidget     = TRUEHUD_API::GetSingleton();

         ersh_TrueHUD->AddWidget(SKSE::GetPluginHandle(), TRUEHUD_API::MyCustomWidgetType::SleepIndicator, 12345, actionScript, myWidget);
    }    
};
