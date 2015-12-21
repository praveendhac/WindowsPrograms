#include"windows.h"

int main(int argc, char *argv[])
{
     HINSTANCE handle;
     LPWSTR procAddr;
          
     //handle = LoadLibrary(TEXT("C:\\WINDOWS\\system32\\kernel32.dll"));
     handle = LoadLibrary(argv[1]);
     
     if(handle != NULL) {
         procAddr = (LPWSTR)GetProcAddress(handle,argv[2]);
         if(procAddr != NULL) {
             printf("In %s API \"%s\" is located at %#x\n", 
                    argv[1], argv[2], procAddr);
         } else {
             printf("Address not found\n");
         }
     } else {
       printf("NULL handle");
     }
     
     //Free DLL Module
     FreeLibrary(handle);
     return 0;
}
