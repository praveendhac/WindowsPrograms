#include<windows.h>

int main()
{
    HANDLE fH, hFind;
    WIN32_FIND_DATA fileData;
    LPCTSTR fileName = "testfile.txt";
    char buff_in[512] = "Creating test file using windows API's";
    int bytes_written = 0;
    int status, ftype, fsize, fsh, binary_type;
    char dir_path[80]="C:\\Documents and Settings\\praveen \
                       \\My Documents\\mal_files\\";
    char file_ext[8] = "*.exe";
    char filepath[128];
    
    strcpy(filepath, dir_path);
    strcat(filepath, file_ext);    
    /* relative path did not work*/
    hFind = FindFirstFile(filepath, /* lpFileName, */
                       &fileData /* lpFindFileData */ );
    while (hFind != INVALID_HANDLE_VALUE) {
        printf("fileName=%s(%d)\n", fileData.cFileName, GetLastError());
        strcpy(filepath, dir_path);
        strcat(filepath, fileData.cFileName);
        fH = CreateFile(filepath, /*lpFileName*/
                        GENERIC_READ|GENERIC_WRITE, /* dwDesiredAccess */
                        FILE_SHARE_WRITE, /* dwShareMode */
                        NULL, /* lpSecurityAttributes */
                        OPEN_EXISTING, /* dwCreationDisposition, Creates a 
                         new file, only if it does not already exist.*/
                         SECURITY_SQOS_PRESENT|FILE_ATTRIBUTE_HIDDEN, 
                         /* dwFlagsAndAttributes */
                         NULL        /* hTemplateFile */);
        if (fH == INVALID_HANDLE_VALUE) {
            if (ERROR_FILE_EXISTS == GetLastError())
                printf("file exists(%d)\n", GetLastError());
            else
                printf("Invalid file handle (%d)\n", GetLastError());
            return -1;    
        }
        printf("Stats of file=\"%s\"\n", filepath);
        ftype = GetFileType(fH);
        fsize = GetFileSize(fH, &fsh);
        GetBinaryType(filepath, &binary_type);
        printf("file type =%d(1=Disk File)\n", ftype);
        printf("file size=%d(%d) bytes\n", fsize, fsh);
        printf("binary_type=%d, error=%d\n", binary_type, GetLastError());
        printf("We can print file attributes from fileData\n");
        printf("*****************************************\n");   
        
        if(!FindNextFile(hFind, &fileData)) {
            FindClose(hFind);
            hFind = INVALID_HANDLE_VALUE;
        }
    }
    return 0;
}
