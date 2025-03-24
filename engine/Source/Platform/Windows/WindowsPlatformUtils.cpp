#include "TrianglPCH.h"
#include "WindowsPlatformUtils.h"

namespace Triangl
{
    SystemTheme WindowsPlatformUtils::GetSystemTheme() const
    {
        std::vector<char> data(4);
        DWORD dwSize = sizeof(DWORD);

        LSTATUS lStatus = RegGetValue(
            HKEY_CURRENT_USER,
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize"),
            TEXT("AppsUseLightTheme"),
            RRF_RT_REG_DWORD,
            nullptr,
            data.data(),
            &dwSize
        );
        
        if (lStatus != ERROR_SUCCESS)
        {
            TL_CORE_WARN("WindowsPlatformUtils::GetSystemTheme() error: Registry key AppsUseLightTheme does not exist, assuming that the system is using light theme.");
            return SystemTheme::Light;
        }

        int result = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
        return result == 0 ? SystemTheme::Dark : SystemTheme::Light;
    }
}
