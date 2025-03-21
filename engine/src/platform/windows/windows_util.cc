#include "tlpch.hh"
#include "windows_util.hh"

namespace triangl {

    system_theme windows_platform_util::get_system_theme() const
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
            TL_CORE_WARN("windows_platform_util::get_system_theme() error: reg key AppsUseLightTheme doesn't exist, assuming that the system is using light theme.");
            return system_theme::light;
        }

        int result = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
        return result == 0 ? system_theme::dark : system_theme::light;
    }

}
