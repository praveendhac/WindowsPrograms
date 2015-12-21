#include <windows.h>
#include<string.h>
#define MAX_KEY_NAME 255
#define MAX_STR 32

int main()
{
    HKEY hKey_ptr = NULL;
    DWORD status;
    char data[MAX_STR-1] = "Praveen Darshanam";
    char sKey[MAX_KEY_NAME] = "disects\\Tutorial";
    DWORD createdornot;
        
    printf("\nAdding new Registry Information\n");
    /*
     * http://msdn.microsoft.com/en-us/library/windows/desktop/ms724844%28v=vs.85%29.aspx
     */
    status = RegCreateKeyEx(HKEY_CURRENT_USER, /* hKey */
                          sKey, /* lpSubKey */
                          0, NULL, /* Reserved, lpClass */
                          REG_OPTION_NON_VOLATILE, /* dwOptions */
                          KEY_ALL_ACCESS, /* samDesired */
                          NULL, /* lpSecurityAttributes */
                          &hKey_ptr, /* phkResult */
                          &createdornot /* lpdwDisposition */
                          );
    if (status != ERROR_SUCCESS) {
               printf("Error RegCreateKeyEx(%d), lpdwDisposition=%u\n", 
                      status, createdornot);
               return 0;
    }
 
    status = RegSetValueEx(hKey_ptr, "Name", /* hKey, lpValueName*/
                           0, REG_SZ, /* Reserved, dwType */
                           data,  strlen(data)/* *lpData, cbData */
                           );    
    if (status != ERROR_SUCCESS) {  
       printf("Error RegSetValueEx(%d)\n", status);
       return 0;         
    }
    printf("Value of createdornot(lpdwDisposition)=%u\n", createdornot);
    printf("Successfully created registry HKEY_CURRENT_USER\\%s\n", sKey);
    
    return 0;   
}
