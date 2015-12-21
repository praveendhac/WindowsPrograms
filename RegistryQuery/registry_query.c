#include <windows.h>

int main()
{
    HKEY hKey;
    DWORD status;
    DWORD type = REG_SZ;
    char sKey[255] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    PPERF_DATA_BLOCK data = (PPERF_DATA_BLOCK) malloc(1024);
    DWORD dsize = 1024;
  
    status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, /**/
                          sKey, 0, /* lpSubKey, ulOptions */
                          KEY_READ, &hKey /* samDesired, phkResult */
                          );
    if (status != ERROR_SUCCESS) {
               printf("Error RegOpenKeyEx\n");
               return 0;
    } 
    status = RegQueryValueEx(hKey, "VBoxTray", /* hKey, lpValueName */
                             NULL, &type, /* lpReserved, lpType */
                             (LPBYTE)data, &dsize /* lpData, lpcbData*/
                             );    
    if (status != ERROR_SUCCESS) {
       MessageBox(0, "Error querying Registry", "Error", 0);  
       return 0;         
    }
    /* Using RegEnumKeyEx, RegEnumValue we can enumerate through 
     * subkeys and value names*/
    printf("\nQuerying Registry Information HKEY_LOCAL_MACHINE\\%s\n", sKey);
    printf("VBoxTray executes from %s\n", data);
    
    return 0;   
}
