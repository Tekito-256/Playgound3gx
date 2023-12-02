#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>

#include <vector>

namespace CTRPluginFramework
{    
    void    PatchProcess(FwkSettings &settings)
    {
        
    }

    void    OnProcessExit(void)
    {
        
    }

    void    InitMenu(PluginMenu &menu)
    {
        
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("Action Replay", 0, 7, 4,
                                            "A blank template plugin.\nGives you access to the ActionReplay and others tools.");

        menu->SynchronizeWithFrame(true);
        InitMenu(*menu);
        menu->Run();
        delete menu;
        return 0;
    }
}
