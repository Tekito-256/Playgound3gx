#include <3ds.h>
#include <CTRPluginFramework.hpp>

#include "csvc.h"
#include "Patches.hpp"
#include "Debug.hpp"

namespace CTRPluginFramework
{
    void    ProcessEventCallback(Process::Event event)
    {
        if(event == Process::Event::EXIT)
        {
            socExit();

            // Free allocated memory
            u32 temp;
            svcControlMemoryUnsafe((u32 *)&temp, SHAREDMEM_ADDR, SERVICE_SHAREDMEM_SIZE * SERVICE_COUNT, (MemOp)MEMOP_FREE, (MemPerm)0);
        }
    }

    void    PatchProcess(FwkSettings &settings)
    {
        Process::SetProcessEventCallback(ProcessEventCallback);

        if(System::IsCitra())
        {
            Result res;
            
            res = socInit((u32 *)0, SERVICE_SHAREDMEM_SIZE);
            DEBUG_NOTIFY(Utils::Format("Soc Init: %08lX", res));
        }
        else
        {
            u32 temp;
            Result res;

            if(R_FAILED(res = svcControlMemoryUnsafe((u32 *)&temp, SHAREDMEM_ADDR, SERVICE_SHAREDMEM_SIZE * SERVICE_COUNT, MemOp(MEMOP_REGION_SYSTEM | MEMOP_ALLOC), MemPerm(MEMPERM_READ | MEMPERM_WRITE))))
            {
                MessageBox(Utils::Format("Failed to allocate memory. (Error code: %08lX)\nWe are going to abort.", res));
                abort();
            }

            res = socInit((u32 *)SHAREDMEM_ADDR, SERVICE_SHAREDMEM_SIZE);
            DEBUG_NOTIFY(Utils::Format("socInit: %08lX", res));
        }

        if(!InstallSocketHooks())
        {
            OSD::Notify("Failed to install socket hooks", Color::Red);
        }
    }

    void    InitMenu(PluginMenu &menu)
    {

    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("Playground 3gx", 0, 7, 4, "Created by Tekito_256");

        menu->SynchronizeWithFrame(true);
        InitMenu(*menu);
        menu->Run();
        delete menu;
        return 0;
    }
}