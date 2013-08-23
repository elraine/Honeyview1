#include "stdafx.h"
#include "Gutil.h"
#include <windowsx.h>
#include <io.h>


//##################################################################################################################
//##	CRC ����
//##################################################################################################################

const DWORD CRC32[256] = {
      0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,      0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,      0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,      0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,      0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,      0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,      0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,      0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
      0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,      0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,      0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,      0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,      0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,      0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,      0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,      0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
      0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,      0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,      0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,      0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,      0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,      0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,      0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,      0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
      0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,      0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,      0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,      0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,      0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,      0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,      0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,      0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
      0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,      0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,      0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,      0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,      0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,      0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,      0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,      0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
      0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,      0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,      0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d };

#define DO1(buf) crc = CRC32[((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8);
#define DO2(buf)  DO1(buf); DO1(buf);
#define DO4(buf)  DO2(buf); DO2(buf);
#define DO8(buf)  DO4(buf); DO4(buf);

/* ========================================================================= */
DWORD crc32( DWORD crc, const BYTE *buf, UINT len)
{
    if (buf == NULL) return 0L;
    crc = crc ^ 0xffffffffL;
    while (len >= 8)
    {
      DO8(buf);
      len -= 8;
    }
    if(len) do {
      DO1(buf);
    } while (--len);
    return crc ^ 0xffffffffL;
}

#define FILEBUFSIZE 4096
/* ������ CRC �� üũ�ϰ� �����Ѵ�. */
bool CheckFileCRC(const char* szFileName, DWORD &dwResult,int nStartPos)
{
	HANDLE hf;
	int		m_uhCRCBytes = 0;
	DWORD dwRead;
	BYTE dwBuffer[FILEBUFSIZE];
	DWORD dwCRC;

	memset(dwBuffer,0,sizeof(dwBuffer));
	hf = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
	FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(hf==INVALID_HANDLE_VALUE) return false;

	SetFilePointer(hf, nStartPos, (PLONG) NULL, FILE_BEGIN);

	dwCRC = 0;
	while(ReadFile(hf, &dwBuffer, sizeof(dwBuffer), &dwRead, NULL))
	{
		if(dwRead==0) break;
		dwCRC = crc32(dwCRC, dwBuffer, dwRead);
	}
	CloseHandle(hf);

	dwResult = dwCRC;
	return true;
}


#define MAX_PASSENCKEY_SIZE		13
const char szPassEncKey[MAX_PASSENCKEY_SIZE] = "�̷�������";

// sPassWord �� sDest[MAX_PASSENCDEC_BUFSIZE] �� ��ũ���� ��Ų��.
void EncPass(char* sDest,const char* sPassWord)
{
	int i,j;
	memset(sDest,0,MAX_PASSENCDEC_BUFSIZE);
	strcpy(sDest,sPassWord);

	for(i=0;i<MAX_PASSENCDEC_BUFSIZE;i++)
	{
		for(j=i;j<i+MAX_PASSENCDEC_BUFSIZE;j++)
		{
			sDest[(j+1)%MAX_PASSENCDEC_BUFSIZE] ^= sDest[j%MAX_PASSENCDEC_BUFSIZE];
			sDest[(j)%MAX_PASSENCDEC_BUFSIZE] ^= szPassEncKey[j%MAX_PASSENCKEY_SIZE];
		}
	}
}

// ��ũ���ǵ� binary ����Ÿ�� ���������ش�.
char* DecPass(char* sSrc)
{
	int i,j;
	static char sDest[MAX_PASSENCDEC_BUFSIZE];
	memset(sDest,0,MAX_PASSENCDEC_BUFSIZE);
	memcpy(sDest, sSrc, MAX_PASSENCDEC_BUFSIZE);

	for(i=MAX_PASSENCDEC_BUFSIZE-1;i>=0;i--)
	{
		for(j=i+MAX_PASSENCDEC_BUFSIZE-1;j>=i;j--)
		{
			sDest[(j)%MAX_PASSENCDEC_BUFSIZE] ^= szPassEncKey[j%MAX_PASSENCKEY_SIZE];
			sDest[(j+1)%MAX_PASSENCDEC_BUFSIZE] ^= sDest[j%MAX_PASSENCDEC_BUFSIZE];
		}
	}
	return sDest;
}

//##################################################################################################################
//##	���� ����
//##################################################################################################################
#include <AFXINET.H>
// URL ���� ���� �̸��� �̾Ƴ���.
bool		GetFileNameFromURL(const CString& sURL, CString& sResult)
{
	DWORD			dwServerType;
	CString			sServer, sObject;
	INTERNET_PORT	nPort;
	// ���� �̸��� ��� �´�. -- sObject ���� "/dir/dir/objec.ext" �������� �� �ִ�..
	if(AfxParseURL(sURL,dwServerType, sServer, sObject, nPort)==FALSE)
	{
		sResult = "";
		return false;
	}
	// ��¥ ��Į ���� �̸��� ��� �´�. 
	sResult = GetFileNameFromPath(sObject);
	return true;
}

// PATH ���� ���� �̸��� �̴´�.
char* GetFileNameFromPath( const char* szPathName )
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];
   static char ret[_MAX_FNAME];
   _splitpath( szPathName, drive, dir, fname, ext );
   strcpy(ret,fname);
   strcat(ret,ext);
   return ret;
}

// PATH ���� Ȯ���ڸ� ������ ���ϸ��� �̴´�.
char* GetFileNameFromPathWithOutExt( const char* szPathName )
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];
   static char ret[_MAX_FNAME];
   _splitpath( szPathName, drive, dir, fname, ext );
   strcpy(ret,fname);
   return ret;
}

// PATH ���� Ȯ���� ���� �̾Ƴ���.
char*	GetExtFromPath(const char* szPathName)
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];
   static char ret[_MAX_FNAME];
   _splitpath( szPathName, drive, dir, fname, ext );
   strcpy(ret,ext);
   return ret;
}

// PATH ���� ����̺� (EX) "C:") �� �̾Ƴ���.
char*	GetDriveNameFromPath(const char* szPathName)
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];
   static char ret[_MAX_DRIVE];
   _splitpath( szPathName, drive, dir, fname, ext );
   strcpy(ret,drive);
   return ret;
}

// PATH ���� ���丮�� �̾Ƴ���.
char*	GetDirNameFromPath(const char* szPathName)
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];
   static char ret[_MAX_DIR];
   _splitpath( szPathName, drive, dir, fname, ext );
   strcpy(ret,dir);
   return ret;
}

// ��ü ������ ������ ���丮 �̸� ���ϱ�
CString GetLastDirFromPath(const CString& sPathName)
{
	CString sRet;
	sRet = GetDirNameFromPath(sPathName);
	sRet = sRet.Left(sRet.GetLength()-1);			// ���� \\ ���� 
	sRet = sRet.Mid(sRet.ReverseFind('\\')+1);
	return sRet;
}

// PARENT ���� ���ϱ� - ��Ʈ(EX) C:\)�� PARENT �� ���� ""�� �����Ѵ� 
CString GetParentPath(const CString& sPathName)
{
	CString sRet;
	sRet = sPathName;
	if(sRet.Right(1)=="\\")
		sRet = sRet.Left(sRet.GetLength()-1);			// ���� \\ ���� 
	sRet = sRet.Left(sRet.ReverseFind('\\')+1);
	return sRet;
}

// ���� ������ ���ϱ�
int GetFileSize(const CString& sPathName)
{
	HANDLE	hFile;
	int		nSize;
	hFile = ::CreateFile(sPathName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(hFile==INVALID_HANDLE_VALUE) return -1;
	nSize = ::GetFileSize(hFile, NULL);
	CloseHandle(hFile);
	return nSize;


	// 2000(Ȥ�� NT) ���� �� �Լ��� ������ close �� ���� �ʴ� ������ �߻��Ѵ�. 
	/*
	struct _finddata_t c_file;
	HFILE		hFile;
    if( hFile = _findfirst( sPathName, &c_file ) == -1L ) return -1;
	_findclose(hFile);
	return c_file.size;
	*/
}

// ���� ���� �Ǵ�
bool IsFolder(const char* szPathName)
{
	DWORD dwRet;
	dwRet = GetFileAttributes(szPathName);
	if(dwRet==-1) return false;					// ���� �߻�
	if(dwRet & FILE_ATTRIBUTE_DIRECTORY) return true;
	return false;
}
// ���� ���� �Ǵ�
bool IsFile(const char* szPathName)
{
	DWORD dwRet;
	dwRet = GetFileAttributes(szPathName);
	if(dwRet==-1) return false;					// ���� �߻�
	if(dwRet & FILE_ATTRIBUTE_DIRECTORY) return false;
//	if(dwRet & FILE_ATTRIBUTE_NORMAL) return true;
	return true;
}

CString  g_sGetDirectoryDir;
int CALLBACK BrowseCallbackProc(HWND hwnd,UINT msg,LPARAM lp, LPARAM pData)
{
	TCHAR buf[MAX_PATH];
	switch(msg) 
	{
	// when dialog is first initialized, change directory to one chosen above
		case BFFM_INITIALIZED: 
			strcpy(buf,g_sGetDirectoryDir);
			::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)buf);
			break;
	// if you picked BIF_STATUSTEXT above, you can fill status here
		case BFFM_SELCHANGED:
			if (::SHGetPathFromIDList((LPITEMIDLIST) lp ,buf)) 
				SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)buf);
			break;
	}
	return 0;
}

// ����ڷκ��� ������ �Է� �޴´�.
CString GetDirectory(HWND hWndParent, const char* szRoot, const char* szTitle)
{
	CString str;
	BROWSEINFO bi;
    bi.hwndOwner=hWndParent;		//owner of created dialog box
    bi.pidlRoot=0;					//unused
    bi.pszDisplayName=0;			//buffer to receive name displayed by folder (not a valid path)
    bi.lpszTitle=szTitle;			//title is "Browse for Folder", this is an instruction
	bi.lpfn = BrowseCallbackProc;	//callback routine called when dialog has been initialized
    bi.lParam=0;					//passed to callback routine
    bi.ulFlags=
		BIF_RETURNONLYFSDIRS |		//only allow user to select a directory
		BIF_STATUSTEXT |			//create status text field we will be writing to in callback
//		BIF_BROWSEFORCOMPUTER|		//only allow user to select a computer
//		BIF_BROWSEFORPRINTER |		//only allow user to select a printer
//		BIF_BROWSEINCLUDEFILES|		//displays files too which user can pick
//		BIF_DONTGOBELOWDOMAIN|		//when user is exploring the "Entire Network" they
									// are not allowed into any domain
		0; 
	g_sGetDirectoryDir = szRoot;

	LPITEMIDLIST lpItemId=::SHBrowseForFolder(&bi); 
	if (lpItemId)
	{
		LPTSTR szBuf=str.GetBuffer(MAX_PATH);
		::SHGetPathFromIDList(lpItemId, szBuf);
		::GlobalFree(lpItemId);
		str.ReleaseBuffer();
	}
	return str;
}

// ������ �����.
void	DeleteFolder(CString sFolder)
{
	if(sFolder.Right(1)!="\\") sFolder+= "\\";

	CFileFind	FileFind;
	BOOL		bResult;

	bResult = FileFind.FindFile(sFolder+"*.*");

	while (bResult)
	{
		bResult = FileFind.FindNextFile();
		DeleteFile(FileFind.GetFilePath());
	}

	RemoveDirectory(sFolder);
}

// �ΰ��� ����(Ȥ�� ����+����)�� ���Ѵ�.
CString AddPath(CString sLeft, CString sRight)
{
	CString sRet;
	sRight = 
		sRight.GetLength()==0 ? "" : 
		(sRight.GetLength()==1 && sRight.Left(1)=="\\") ? "" :  
		sRight.Left(1)=="\\" ? sRight.Mid(1) : 
		sRight;

	sRet = (sLeft.Right(1)=="\\") ?
				sLeft + sRight :
				sLeft + "\\" + sRight;
	return sRet;
}

// ������ �մ´�.
bool	DigPath(CString sFolderPath)
{
	if(IsFolder(sFolderPath)) return true;						// ���� �ʿ� ����.


	CString	sSubPath;
	int		nFrom, nTo;

	nFrom = 0;
	nTo = 0;
	nFrom = sFolderPath.Find("\\", 0)+1;
	for(;;)
	{
		nTo = sFolderPath.Find("\\", nFrom);
		if(nTo==-1) break;
		sSubPath = sFolderPath.Left(nTo);
		::CreateDirectory(sSubPath, NULL);
		nFrom = nTo+1;
	}

	::CreateDirectory(sFolderPath, NULL);
	return IsFolder(sFolderPath);
}

//##################################################################################################################
//##	INI / REGISTRY
//##################################################################################################################

// ������Ʈ�� �а� ���µ� ���Ǵ� APP �̸�.
/*
CString			g_sRegAppName;
void SetPrivateRegAppName(const CString& sAppName)
{
	g_sRegAppName = sAppName;
}

// REGISTRY �� INT �� ����
void SetPrivateRegInt(CString sKeyName, DWORD nValue)
{
	if(g_sRegAppName=="") g_sRegAppName = AfxGetAppName();
	HKEY		hKey;
	HKEY		hkRoot, hSubKey;

	RegOpenKey(HKEY_LOCAL_MACHINE,NULL, &hkRoot);
	RegOpenKey(hkRoot,"SOFTWARE",&hKey);
    if(RegOpenKey(hKey,g_sRegAppName,&hSubKey)!=ERROR_SUCCESS)
    {
    	RegCreateKey(hKey,g_sRegAppName,&hSubKey);
    }
	::RegSetValueEx(hSubKey,sKeyName,NULL,REG_DWORD,(CONST BYTE*)&nValue,sizeof(DWORD));

	RegCloseKey(hSubKey);
	RegCloseKey(hKey);
	RegCloseKey(hkRoot);
	return ;
}

// REGISTRY ���� INT �� �б�
DWORD GetPrivateRegInt(CString sKeyName, DWORD nDefaultValue)
{
	if(g_sRegAppName=="") g_sRegAppName = AfxGetAppName();
	HKEY		hKey;
	DWORD		dwDispotion;
    DWORD		ret=0;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE,										// ������Ʈ�� ����.
    	"SOFTWARE\\"+g_sRegAppName,
		NULL,
		"Class??",															// ????
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDispotion);
	// ���� ������Ʈ���� �������� ������, ��� ������ �ʱ�ȭ �Ѵ�. 
	if(dwDispotion==REG_CREATED_NEW_KEY) 
	{
        ret = nDefaultValue;
	}
	else 
	{
		DWORD	size;
		size = sizeof(ret);
		int result = RegQueryValueEx(
			hKey,sKeyName,NULL,NULL,
			(unsigned char *)&ret,
			&size);
		if(ERROR_SUCCESS!=result) 
		{ // if ���н�.
        	ret = nDefaultValue;
        }
	}
    RegCloseKey(hKey);
    return ret;
}

// REGISTRY �� BINARY �� ����
void SetPrivateRegBin(CString sKeyName, void* pData, int nSize)
{
	if(g_sRegAppName=="") g_sRegAppName = AfxGetAppName();
	HKEY		hKey;
	HKEY		hkRoot, hSubKey;

	RegOpenKey(HKEY_LOCAL_MACHINE,NULL, &hkRoot);
	RegOpenKey(hkRoot,"SOFTWARE",&hKey);
    if(RegOpenKey(hKey,g_sRegAppName,&hSubKey)!=ERROR_SUCCESS)
    	RegCreateKey(hKey,g_sRegAppName,&hSubKey);
	::RegSetValueEx(hSubKey,sKeyName,NULL,REG_BINARY,(const unsigned char*)pData,nSize);
	RegCloseKey(hSubKey);
	RegCloseKey(hKey);
	RegCloseKey(hkRoot);
}

// REGISTRY ���� BINARY �� �б�
bool GetPrivateRegBin(CString sKeyName, void* pData, int nSize)
{
	if(g_sRegAppName=="") g_sRegAppName = AfxGetAppName();
	HKEY		hKey;
	DWORD		dwDispotion;

	RegCreateKeyEx(HKEY_LOCAL_MACHINE,				// ������Ʈ�� ����.
    	"SOFTWARE\\"+g_sRegAppName,
		NULL,
		"Class??",							
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDispotion);

	// ���� ������Ʈ���� �������� ������, ��� ������ �ʱ�ȭ �Ѵ�. 
	if(dwDispotion==REG_CREATED_NEW_KEY) 
	{
		memset(pData,0,nSize);
	    RegCloseKey(hKey);
        return false;
	}
	else 
	{
		int result = RegQueryValueEx(
			hKey,sKeyName,NULL,NULL,
			(unsigned char *)pData,
			(unsigned long*)(&nSize));
		if(ERROR_SUCCESS!=result) 
		{ 
			memset(pData,0,nSize);
		    RegCloseKey(hKey);
            return false;
        }
	}
    RegCloseKey(hKey);
    return true;
}
*/
// INI ���Ͽ��� STRING �� �б�
CString GetIniStr(const char* szSection, const char* szKey, CString sIniFileName, CString sDefaultValue)
{
    char  szBuf[10000];
	if(sIniFileName.Find(':')==-1 && sIniFileName.Left(2)!="\\\\")
		sIniFileName = GetThisPath() + sIniFileName;
    GetPrivateProfileString(szSection,szKey,sDefaultValue,szBuf,9999,sIniFileName);
    return CString(szBuf);
}
// INI ���Ͽ� STRING �� ����
void SetIniStr(const char* szSection, const char* szKey, const char* szValue, CString sIniFileName)
{
	if(sIniFileName.Find(':')==-1)
	    sIniFileName = GetThisPath() + sIniFileName;
	WritePrivateProfileString(szSection, szKey, szValue, sIniFileName);
}
// INI ���Ͽ��� INT �� �б�
int	GetIniInt(const char* szSection, const char* szKey, int nDefault, CString sIniFileName)
{
	int		nRet;
	if(sIniFileName.Find(':')==-1)
	    sIniFileName = GetThisPath() + sIniFileName;
    nRet = GetPrivateProfileInt(szSection, szKey, nDefault, sIniFileName);
	return nRet;
}
// INI ���Ͽ� INT �� ����
void SetIniInt(const char* szSection, const char* szKey, int nValue, CString sIniFileName)
{
	CString sValue;
	sValue.Format("%d", nValue);
	SetIniStr(szSection, szKey, sValue, sIniFileName);
}
// INI ������ SECTION �� ��� KEY �� ����Ʈ�� ���
void GetIniKeyList(CStringList& slKey, CString sSection, CString sIniFileName)
{
	char szBuf[32*1024];
	char* p;

	slKey.RemoveAll();
	if(sIniFileName.Find(':')==-1) sIniFileName = GetThisPath() + sIniFileName;
	memset(szBuf, 0, sizeof(szBuf));
	GetPrivateProfileString(sSection,NULL,"",szBuf,sizeof(szBuf),sIniFileName);
	p = szBuf;
	while(*p)
	{
		slKey.AddTail(p);
		p = p + strlen(p) + 1;
	}
}


// ����Ʈ ���� ������ ������Ʈ������ ��Ʈ���� �о� ���δ�.
bool  GetRegStr(HKEY hKeyRoot, const CString& sKeySub, const CString& sValue, CString& sResult, CString sDefaultValue)
{
	if(GetRegStr(hKeyRoot, sKeySub, sValue, sResult)) return true;
	sResult = sDefaultValue;
	return false;
}

// ������Ʈ������ ��Ʈ���� �о� ���δ� //
bool  GetRegStr(HKEY hKeyRoot, const CString& sKeySub, const CString& sValue, CString& sResult)
{
	LONG		lResult;
	BYTE*		pBuf=NULL;
	DWORD		dwBufSize = 0;
	DWORD		dwType = REG_SZ;
	HKEY		hKeySub=NULL;

	// ������Ʈ���� ����.
	lResult = RegOpenKeyEx(hKeyRoot, sKeySub, 0, KEY_ALL_ACCESS, &hKeySub);
	if(lResult!=ERROR_SUCCESS) 
		goto FAIL;

	// ��Ʈ���� ����� ���� �´�.
	lResult = RegQueryValueEx(hKeySub, sValue, NULL, &dwType, pBuf, &dwBufSize);
	if(dwBufSize==0) goto FAIL;
	pBuf = (BYTE*)malloc(dwBufSize);
	if(pBuf==NULL) goto FAIL;

	// �ٽ� �о� �´�.
	lResult = RegQueryValueEx(hKeySub, sValue, NULL, &dwType, pBuf, &dwBufSize);
	if(lResult!=ERROR_SUCCESS) goto FAIL;

	sResult = (char*)pBuf;
	free(pBuf);

	if(hKeySub)
		RegCloseKey (hKeySub);
	return true;

FAIL :
	if(hKeySub)
		RegCloseKey (hKeySub);
	return false;

}

// ������Ʈ������ ��Ʈ���� �о� ���δ� //
bool  GetRegStr(const CString& sKeyRoot, const CString& sKeySub, const CString& sValue, CString& sResult)
{
	HKEY		hKeyRoot;

	// ��Ʈ������ root Ű�� ã�´�.
	if(sKeyRoot=="HKEY_CLASSES_ROOT")			hKeyRoot = HKEY_CLASSES_ROOT;
	else if(sKeyRoot=="HKEY_CURRENT_USER")		hKeyRoot = HKEY_CURRENT_USER;
	else if(sKeyRoot=="HKEY_LOCAL_MACHINE")		hKeyRoot = HKEY_LOCAL_MACHINE;
	else if(sKeyRoot=="HKEY_USERS")				hKeyRoot = HKEY_USERS;
	else if(sKeyRoot=="HKEY_PERFORMANCE_DATA")	hKeyRoot = HKEY_PERFORMANCE_DATA;
	else if(sKeyRoot=="HKEY_CURRENT_CONFIG")	hKeyRoot = HKEY_CURRENT_CONFIG;
	else if(sKeyRoot=="HKEY_DYN_DATA")			hKeyRoot = HKEY_DYN_DATA;
	else return false;

	return GetRegStr(hKeyRoot, sKeySub, sValue, sResult);
}


// ��¥�� ������Ʈ������ ��Ʈ���� �о� ���δ�. ��:"HKEY_LOCAL_MACHINE\\SOFTWARE\\Blizzard Entertainment\\Starcraft\\Program"
bool  GetRegStr(const CString& sKey, CString& sResult)
{
	CString		sKeyRoot;
	CString		sKeySub;
	CString		sValue;

	// ��ƮŰ, ����Ű, �� �� �����Ѵ�. 
	int nPosFrom = sKey.Find('\\', 0);
	int nPosTo   = sKey.ReverseFind('\\');
	if(nPosFrom==-1 || nPosTo==-1) return false;

	sKeyRoot = sKey.Left(nPosFrom);
	sKeySub  = sKey.Mid(nPosFrom+1, nPosTo-nPosFrom );
	sValue   = sKey.Mid(nPosTo+1);

	return GetRegStr(sKeyRoot, sKeySub, sValue, sResult);
}

// ������Ʈ���� ��Ʈ���� �����Ѵ� //
bool  SetRegStr(HKEY hKeyRoot, const CString& sKeySub, const CString& sValueName, const CString& sValue)
{
	LONG		lResult;
	HKEY		hKeySub=NULL;

	// ������Ʈ���� ����.
	lResult = RegOpenKeyEx(hKeyRoot, sKeySub, 0, KEY_ALL_ACCESS, &hKeySub);
	if(lResult!=ERROR_SUCCESS)												// ������Ʈ���� �������� ������ �����.
	{
		if(	RegCreateKey(hKeyRoot,sKeySub,&hKeySub)!=ERROR_SUCCESS)
			goto FAIL;
	}
	if(::RegSetValueEx(hKeySub,sValueName,NULL,REG_SZ,(const unsigned char*)(const char*)sValue,sValue.GetLength())!=ERROR_SUCCESS)
		goto FAIL;


	if(hKeySub)	RegCloseKey (hKeySub);
	return true;

FAIL :
	if(hKeySub)	RegCloseKey (hKeySub);
	return false;

}

// ������Ʈ���� ��Ʈ���� �����Ѵ� //
bool  SetRegStr(const CString& sKeyRoot, const CString& sKeySub, const CString& sValueName, const CString& sValue)
{
	HKEY		hKeyRoot;

	// ��Ʈ������ root Ű�� ã�´�.
	if(sKeyRoot=="HKEY_CLASSES_ROOT")			hKeyRoot = HKEY_CLASSES_ROOT;
	else if(sKeyRoot=="HKEY_CURRENT_USER")		hKeyRoot = HKEY_CURRENT_USER;
	else if(sKeyRoot=="HKEY_LOCAL_MACHINE")		hKeyRoot = HKEY_LOCAL_MACHINE;
	else if(sKeyRoot=="HKEY_USERS")				hKeyRoot = HKEY_USERS;
	else if(sKeyRoot=="HKEY_PERFORMANCE_DATA")	hKeyRoot = HKEY_PERFORMANCE_DATA;
	else if(sKeyRoot=="HKEY_CURRENT_CONFIG")	hKeyRoot = HKEY_CURRENT_CONFIG;
	else if(sKeyRoot=="HKEY_DYN_DATA")			hKeyRoot = HKEY_DYN_DATA;
	else return false;

	return SetRegStr(hKeyRoot, sKeySub, sValueName, sValue);
}

// ��¥�� ������Ʈ���� ��Ʈ���� �����Ѵ� ��:"HKEY_LOCAL_MACHINE\\SOFTWARE\\Blizzard Entertainment\\Starcraft\\Program"
bool  SetRegStr(const CString& sKey, const CString& sValue)
{
	CString		sKeyRoot;
	CString		sKeySub;
	CString		sValueName;

	// ��ƮŰ, ����Ű, �� �� �����Ѵ�. 
	int nPosFrom = sKey.Find('\\', 0);
	int nPosTo   = sKey.ReverseFind('\\');
	if(nPosFrom==-1 || nPosTo==-1) return false;

	sKeyRoot	= sKey.Left(nPosFrom);
	sKeySub		= sKey.Mid(nPosFrom+1, nPosTo-nPosFrom );
	sValueName  = sKey.Mid(nPosTo+1);

	return SetRegStr(sKeyRoot, sKeySub, sValueName, sValue);
}

// ������Ʈ���� DWORD�� �����Ѵ� //
bool  SetRegDWORD(HKEY hKeyRoot, const CString& sKeySub, const CString& sValueName, DWORD dwValue)
{
	LONG		lResult;
	HKEY		hKeySub=NULL;

	// ������Ʈ���� ����.
	lResult = RegOpenKeyEx(hKeyRoot, sKeySub, 0, KEY_ALL_ACCESS, &hKeySub);
	if(lResult!=ERROR_SUCCESS)												// ������Ʈ���� �������� ������ �����.
	{
		if(	RegCreateKey(hKeyRoot,sKeySub,&hKeySub)!=ERROR_SUCCESS) 
			goto FAIL;
	}
	if(::RegSetValueEx(hKeySub,sValueName,NULL,REG_DWORD,(const unsigned char*)&dwValue,sizeof(DWORD)))
		goto FAIL;


	if(hKeySub)	RegCloseKey (hKeySub);
	return true;

FAIL :
	if(hKeySub)	RegCloseKey (hKeySub);
	return false;
}

// ������Ʈ������ DWORD�� �о� ���δ� //
bool  GetRegDWORD(HKEY hKeyRoot, const CString& sKeySub, const CString& sValue, DWORD& dwResult, DWORD dwDefaultValue)
{
	LONG		lResult;
	BYTE		pBuf[4];
	DWORD		dwBufSize = sizeof(DWORD);
	DWORD		dwType = REG_DWORD;
	HKEY		hKeySub=NULL;

	dwResult = dwDefaultValue;

	// ������Ʈ���� ����.
	lResult = RegOpenKeyEx(hKeyRoot, sKeySub, 0, KEY_ALL_ACCESS, &hKeySub);
	if(lResult!=ERROR_SUCCESS) goto FAIL;

	// �о� �´�.
	lResult = RegQueryValueEx(hKeySub, sValue, NULL, &dwType, pBuf, &dwBufSize);
	if(lResult!=ERROR_SUCCESS) goto FAIL;

	dwResult = *((DWORD*)pBuf);

	if(hKeySub)	RegCloseKey (hKeySub);
	return true;

FAIL :
	if(hKeySub)	RegCloseKey (hKeySub);
	return false;
}

// ������Ʈ���� BINARY�� �����Ѵ� //
bool  SetRegBin(HKEY hKeyRoot, const CString& sKeySub, const CString& sValueName, void* pData, int nDataSize)
{
	LONG		lResult;
	HKEY		hKeySub=NULL;

	// ������Ʈ���� ����.
	lResult = RegOpenKeyEx(hKeyRoot, sKeySub, 0, KEY_ALL_ACCESS, &hKeySub);
	if(lResult!=ERROR_SUCCESS)												// ������Ʈ���� �������� ������ �����.
	{
		if(	RegCreateKey(hKeyRoot,sKeySub,&hKeySub)!=ERROR_SUCCESS)
			goto FAIL;
	}
	if(::RegSetValueEx(hKeySub,sValueName,NULL,REG_BINARY,(const unsigned char*)pData,nDataSize))
		goto FAIL;

	if(hKeySub)	RegCloseKey (hKeySub);
	return true;

FAIL :
	if(hKeySub)	RegCloseKey (hKeySub);
	return false;
}

// ������Ʈ������ BINARY�� �о� ���δ� - �ݵ�� free() �� ������ �־�� �Ѵ�.. //
bool  GetRegBin(HKEY hKeyRoot, const CString& sKeySub, const CString& sValue, BYTE** pRetBuf, int& nBufSize)
{
	LONG		lResult;
	DWORD		dwBufSize = nBufSize;
	DWORD		dwType = REG_BINARY;
	HKEY		hKeySub=NULL;

	// ������Ʈ���� ����.
	lResult = RegOpenKeyEx(hKeyRoot, sKeySub, 0, KEY_ALL_ACCESS, &hKeySub);
	if(lResult!=ERROR_SUCCESS) goto FAIL;

	// ���̳ʸ��� ����� ���� �´�.
	lResult = RegQueryValueEx(hKeySub, sValue, NULL, &dwType, (unsigned char*)*pRetBuf, &dwBufSize);
	if(dwBufSize==0) goto FAIL;
	*pRetBuf = (BYTE*)malloc(dwBufSize);
	if(*pRetBuf==NULL) goto FAIL;

	// �о� �´�.
	lResult = RegQueryValueEx(hKeySub, sValue, NULL, &dwType,(unsigned char*) *pRetBuf, &dwBufSize);
	if(lResult!=ERROR_SUCCESS) goto FAIL;
	nBufSize = dwBufSize;

	if(hKeySub)	RegCloseKey (hKeySub);
	return true;

FAIL :
	if(hKeySub)	RegCloseKey (hKeySub);
	return false;


}
// ������Ʈ���� INT�� �����Ѵ� //
bool SetRegInt(HKEY hKeyRoot, const CString& sKeySub, const CString& sValueName, int nValue)
{
	return SetRegDWORD(hKeyRoot, sKeySub, sValueName, (DWORD)nValue);
}
// ������Ʈ������ INT�� �о� ���δ� //				
bool GetRegInt(HKEY hKeyRoot, const CString& sKeySub,const CString& sValue, int& nResult, int nDefaultValue)
{
	return GetRegDWORD(hKeyRoot, sKeySub, sValue, (DWORD&) nResult, (DWORD)nDefaultValue);
}

// ������Ʈ�� �����.
bool  RegDeleteValue(HKEY hKeyRoot, const CString& sKeySub, const CString& sValueName)
{
	LONG		lResult;
	HKEY		hKeySub=NULL;

	lResult = RegOpenKeyEx(hKeyRoot, sKeySub, 0, KEY_ALL_ACCESS, &hKeySub);			// ������Ʈ���� ����.
	if(lResult!=ERROR_SUCCESS)	goto FAIL;											// ������Ʈ���� �������� ������..
	lResult = RegDeleteValue(hKeySub, sValueName);									// ������Ʈ���� �����.
	if(lResult!=ERROR_SUCCESS) goto FAIL;

	if(hKeySub)	RegCloseKey (hKeySub);
	return true;

FAIL :
	if(hKeySub)	RegCloseKey (hKeySub);
	return false;
}

#define	REG_AUTORUN "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
// �ý��� ���۽� ������ ���� �̸��� �����Ѵ�. 
bool RegistAutoRun(const CString& sValueName, const CString &sFileName)
{
	if(sFileName=="")
	{
		LONG ret;
		ret = RegDeleteValue(HKEY_CURRENT_USER, CString(REG_AUTORUN), sValueName);
		if(ret==ERROR_SUCCESS) return true;
		return false;
	}
	return SetRegStr(HKEY_CURRENT_USER, REG_AUTORUN, sValueName, sFileName);
}
// �ڵ������� ���� �̸��� ���Ѵ�.
CString	GetAutoRun(const CString& sKeyName)
{
	CString sResult;
	GetRegStr(HKEY_CURRENT_USER, REG_AUTORUN, sKeyName, sResult);
	return sResult;
}

//##################################################################################################################
//##	�ý��� ���� ���
//##################################################################################################################

// ���α׷��� ���۵� ���丮..��
CString  GetThisPath()
{
	char szFileName[MAX_PATH];
	char szPathName[MAX_PATH];
	char szDrive[_MAX_DRIVE];
	::GetModuleFileName(NULL,szFileName,MAX_PATH);
	_splitpath(szFileName,szDrive,szPathName,NULL,NULL);
	return CString(szDrive)+szPathName;
}
// �� �ڽ��� ���� �̸�
CString	GetThisFileName()
{
	char szFileName[MAX_PATH];
	::GetModuleFileName(NULL,szFileName,MAX_PATH);
	return szFileName;
}

// ����� �Ķ���� ���ϱ�.
int GetCommandLineList(CStringArray &sa)
{
	CString				sCmd = GetCommandLine();
	CString				sToken;
	int					nFrom=0, nTo=0;

	sa.RemoveAll();


	if(sCmd[0]=='\"')
	{
		nTo=sCmd.Find("\"", 1);
		if(nTo!=-1)
		{
			sToken = sCmd.Mid(nFrom+1, nTo-nFrom-1);
			sa.Add(sToken);
			nFrom = nTo+1;
		}
	}

	for(;;)
	{
		nTo = sCmd.Find(" ", nFrom);
		if(nTo==-1)
			sToken = sCmd.Mid(nFrom);
		else
			sToken = sCmd.Mid(nFrom, nTo-nFrom);
		if(sToken!="")
			sa.Add(sToken);
		nFrom = nTo+1;
		if(nTo==-1) break;
	}

	return sa.GetSize();
}


// ��ũ�� �� ���
int		GetScreenWidth()  { return GetSystemMetrics(SM_CXFULLSCREEN); }

// ��ũ�� ���� ��� 
int		GetScreenHeight() { return GetSystemMetrics(SM_CYFULLSCREEN); }

// �۾� ���� ���
void GetWorkArea(CRect& r)
{
	SystemParametersInfo(SPI_GETWORKAREA,NULL,&r,0);
}

// �ؽ�Ʈ ���ڿ��� �� ���
int TextWidth (HDC hDC, const char* szText)
{
	SIZE	size ;
	if(szText==NULL) return 0;
    GetTextExtentPoint32 (hDC, szText, lstrlen (szText), &size) ;
    return  size.cx ;
}

// �ؽ�Ʈ ������ ���� ���
int FontHeight (HDC hDC,	BOOL bIncludeLeading)
{
	TEXTMETRIC     tm ;
    GetTextMetrics (hDC, &tm) ;
    if (bIncludeLeading)
    	return (tm.tmHeight + tm.tmExternalLeading) ;
    else
    	return (tm.tmHeight) ;
}

// ������ ���̸� ���� ( ���� : \n ���� LF �� ���� )
int ParagraphHeight(HDC hDC, BOOL bIncludeLeading, const char* pText)
{
	int nCount=1;
	int i;
	for(i=0;i<(int)strlen(pText);i++)
	{
		if(pText[i]=='\n') nCount++;
	}

	return FontHeight(hDC, bIncludeLeading)*nCount;
}

// ������ ���� �����Ѵ� ( ���� : \n ���� LF �� ���� )
int ParagraphWidth(HDC hDC, const char* szText)
{
	char* strTmp;
	char* token;
	char seps[]   = "\n";
	int		nMaxWidth=0;
	int		nWidth;

	// �ҽ� ��Ʈ���� �����Ѵ�..
	strTmp = new char[strlen(szText)+1];
	memcpy(strTmp, szText, strlen(szText)+1);

	// ���κ��� ���̸� ����Ѵ�.
	token = strtok( strTmp, seps );
	while( token != NULL )
	{
		nWidth = TextWidth(hDC, token);
		nMaxWidth = max(nWidth, nMaxWidth);		// ���� ���� ���� ������ ã�´�.
		token = strtok( NULL, seps );
	}

	// �޸� ����..
	delete strTmp;
	return nMaxWidth;
}

#pragma comment(lib,"version.lib")
// ������ ���� ������ ����.
bool GetFileVersion(char *szFileName, DWORD* verMS, DWORD* verLS)
{
   DWORD   dwVerInfoSize;
   LPSTR   lpVersion;
   DWORD   dwVerHnd = 0;
   BOOL    bRetCode;
   bool    bResult;

   bResult = false;
   dwVerInfoSize = GetFileVersionInfoSize(szFileName, &dwVerHnd);
   if (dwVerInfoSize)
   {
      LPSTR   lpstrVffInfo;
      UINT    uVersionLen;

      lpstrVffInfo  = (char *)GlobalAllocPtr(GMEM_MOVEABLE, dwVerInfoSize);
      GetFileVersionInfo(szFileName, dwVerHnd, dwVerInfoSize, lpstrVffInfo);

      bRetCode = VerQueryValue((LPVOID)lpstrVffInfo, TEXT("\\"), (LPVOID *)&lpVersion, &uVersionLen);
      if (bRetCode)
      {
         VS_FIXEDFILEINFO *pfi;
         pfi = (VS_FIXEDFILEINFO*)lpVersion;
         *verMS = pfi->dwFileVersionMS;
         *verLS = pfi->dwFileVersionLS;
         bResult = true;
      }
      GlobalFreePtr(lpstrVffInfo);
   }
   return bResult;
}

// ������ ���� ������ ����.
bool GetFileVersion(CString sFileName, CString& sFileVersion)
{
	//__int64 ver;
	DWORD	verMS, verLS;
	if(GetFileVersion((char*)(const char*)sFileName, &verMS, &verLS)==false) return false;
	sFileVersion.Format("%d, %d, %d, %d", 
		//ver>>48, (ver>>32)&0xff, (ver>>16)&0xff, (ver)&0xff);
		verMS >> 16, verMS&0xffff,
		verLS >> 16, verLS&0xffff);
	return true;
}

// �ϵ� �������� �������ϱ�(KB)
BOOL GetDiskFreeSpace(char cDrive, int& nResult)
{
	CString s;
	s.Format("%c:\\", cDrive);
	return GetDiskFreeSpace(s, nResult);
}
// �ϵ� �������� �������ϱ�(KB)
BOOL GetDiskFreeSpace(const char* s, int& nResult)
{
    DWORD spc,bps,fc,tc;
    if (GetDiskFreeSpace(s,&spc,&bps,&fc,&tc))
    {
      DWORD r;
      DWORD v=0x7fffffff;
      r=bps*spc*(fc>>10);
      if (!r) r=(bps*spc*fc)>>10;
      if (r > v) r=v;
      nResult=(int)r;
	  return TRUE;
    }
	return FALSE;
}

// OS VERSION ������
OS_VERSION CheckOSVerion(CString* psServiceRelease)
{
	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osv))
	{
		if(psServiceRelease)
			*psServiceRelease = osv.szCSDVersion;	// note: szCSDVersion =  service pack  release  
		switch(osv.dwPlatformId)
		{
		case VER_PLATFORM_WIN32s:					//Win32s on Windows 3.1.
			return OSVER_31;
			
		case VER_PLATFORM_WIN32_WINDOWS:			//WIN32 on 95 or 98
			if (osv.dwMinorVersion == 0)			return OSVER_95;
			else if(osv.dwMinorVersion == 10)		return OSVER_98;
			else if(osv.dwMinorVersion == 90)		return OSVER_ME;
			break;

		case VER_PLATFORM_WIN32_NT:					//Win32 on Windows NT.
			if(osv.dwMajorVersion == 3) 			return OSVER_NT351;
			else if(osv.dwMajorVersion == 4) 		return OSVER_NT4;
			else if(osv.dwMajorVersion == 5)
			{
				if(osv.dwMinorVersion == 0)			return OSVER_2000;
				else if(osv.dwMinorVersion == 1)	return OSVER_XP;
			}
		}
		return OSVER_UNKNOWN;
	}
	return OSVER_ERROR;
}

// OS VERSION �� ��Ʈ������ �ٲٱ�
CString OSVer2Str(OS_VERSION nOS)
{
	switch(nOS)
	{
	case OSVER_UNKNOWN	: return "Unknown OS";
	case OSVER_31		: return "Windows 3.1";
	case OSVER_95		: return "Windows 95";
	case OSVER_98		: return "Windows 98";
	case OSVER_ME		: return "Windows ME";
	case OSVER_NT351	: return "Windows NT 3.51";
	case OSVER_NT4		: return "Windows NT 4";
	case OSVER_2000		: return "Windows 2000";
	case OSVER_XP		: return "Windows XP";
	};
	ASSERT(0);
	return "";
}

//##################################################################################################################
//##	���ڿ� ó�� �Լ�
//##################################################################################################################

// ������ ��Ʈ�� ī�� �Լ�.
void	StringCopy(char* szDst, const char* szSrc, int nCount)
{
	if(szDst==NULL) {ASSERT(0);return;}					// ���� �߻�.
	if(szSrc==NULL) {memset(szDst,0,nCount);return;}
//	memcpy(szDst, szSrc, nCount-1);
	strncpy(szDst, szSrc, nCount-1);
	szDst[nCount-1] = NULL;
}
void	StringCopy(BYTE* szDst, const char* szSrc, int nCount)
{
	StringCopy((char*)szDst, (const char*)szSrc, nCount);
}
void	StringCopy(char* szDst, const BYTE* szSrc, int nCount)
{
	StringCopy((char*)szDst, (const char*)szSrc, nCount);
}
void	StringCopy(BYTE* szDst, const BYTE* szSrc, int nCount)
{
	StringCopy((char*)szDst, (const char*)szSrc, nCount);
}
void	StringCopy(CString& sDst,BYTE* szSrc, int nCount)
{
	*(szSrc + nCount-1) = NULL;
	sDst = (const char*)szSrc;
}
// ������ Ȯ���ڸ� �ٲ۴�.
CString	ChangeFileExtString(const CString& sFileName, const CString& sNewExt)
{
	return CString(GetFileNameFromPathWithOutExt(sFileName))+"."+sNewExt;
}

// URL�� Ȯ���ڸ� �ٲ۴�.
CString	ChangeURLExtString(const CString& sPathName, const CString& sNewExt)
{
	int				nPos;
	CString			sResult;
	nPos= sPathName.ReverseFind('.');
	if(nPos==-1) return sResult;						// .�� ã�� �� ����..
	sResult = sPathName.Left(nPos)+"."+sNewExt;
	return sResult;
}

// �̸��� �ּҸ� id�� ���� �ּҷ� �и��Ѵ� 
bool SplitEmailAddress(const char* szEmail, CString &sID, CString &sAddress)
{
	CString sEmail = szEmail;
	int			nPos;
	nPos = sEmail.Find('@',0);
	if(nPos<0) return false;							// @ ���� ���ڿ��� ���
	if(nPos==0) return false;							// @ �� ���۵Ǵ� ���ڿ��� ���
	if(nPos==sEmail.GetLength()-1) return false;		// @ �� ������ ���ڿ��� ���

	sID = sEmail.Left(nPos);
	sAddress = sEmail.Right(sEmail.GetLength()-nPos);
	return true;
}


//##################################################################################################################
//##	�ð� ó�� �Լ�
//##################################################################################################################

// ���� �ð��� ������ ���ؼ� ��������
CString	GetTimeString(const CString& sFormat )
{
	CTime			t = CTime::GetCurrentTime();
	CString	sTime;
	sTime = t.Format(sFormat);
	return sTime;
}

// ���� �ð��� �ʱ��� ���ڿ��� ����
CString GetCurrentTimeString()
{
	CTime			t = CTime::GetCurrentTime();
	CString	sTime;
	sTime = t.Format("%Y��%m��%d�� %H��%M��%S��");
	return sTime;
}

// ��¥&�ð��� ���ڿ��� ����
CString GetCurrentHourString()
{
	CTime			t = CTime::GetCurrentTime();
	CString	sTime;
	sTime = t.Format("%Y��%m��%d�� %H��");
	return sTime;
}

// ���� �ð��� �б��� ���ڿ��� ����
CString GetCurrentMinString()
{
	CTime			t = CTime::GetCurrentTime();
	CString	sTime;
	sTime = t.Format("%Y��%m��%d�� %H��%M��");
	return sTime;
}

// ���� ��¥�� ���ڿ��� ����
CString GetCurrentDayString()
{
	CTime			t = CTime::GetCurrentTime();
	CString	sTime;
	sTime = t.Format("%Y��%m��%d��");
	return sTime;
}

// ���� ������ �⵵ 
int		GetThisYear()
{
	CTime			t = CTime::GetCurrentTime();
	return t.GetYear();
}


//##################################################################################################################
//##	�����
//##################################################################################################################

#define MAX_MSGBUFFER_SIZE		(4096*16)
// �����쿡 ��Ʈ�� �޽��� ������ �Լ� - �����Լ� 
void SendStringMessageToDebugWindow(const char* szWndNameToRecv, const char* szMessage)
{
#ifndef _FINAL_RELEASE
    HWND    hWndRecv;
    hWndRecv = FindWindow(NULL,szWndNameToRecv);
    if(hWndRecv==NULL) return;

    COPYDATASTRUCT cd;
    cd.dwData = 0;
    cd.cbData = strlen(szMessage)+1;
    cd.lpData = (void*)szMessage;

    SendMessage(hWndRecv,WM_COPYDATA, NULL, (LPARAM) (PCOPYDATASTRUCT)&cd);
#endif
}

// ����� ������ RECV ���� ������.
void _cdecl gebug(const char* str, ...)
{
#ifndef _FINAL_RELEASE
	CString sBuffer;
	va_list args;

	va_start(args, str);
    sBuffer.FormatV(str, args);
	va_end(args);
	SendStringMessageToDebugWindow("XXXXXXXXXX", sBuffer);
/*	static TCHAR szBuffer[MAX_MSGBUFFER_SIZE];
	va_list args;

	va_start(args, str);
	memset(szBuffer,0,sizeof(szBuffer));
    vsprintf(szBuffer, str, args);
	va_end(args);
	SendStringMessageToDebugWindow("RECV", szBuffer);*/
#endif
}
// ����� ������ ���� ��븦 �����ؼ� ������.
void _cdecl gebugto(const char* szWndNameToRecv, const char* str, ...)
{
#ifndef _FINAL_RELEASE
	static TCHAR szBuffer[MAX_MSGBUFFER_SIZE];
	va_list args;

	va_start(args, str);
	memset(szBuffer,0,sizeof(szBuffer));
    vsprintf(szBuffer, str, args);
	va_end(args);
	SendStringMessageToDebugWindow(szWndNameToRecv, szBuffer);
#endif
}

// �⺻ �޽��� ���� �̸�.
CString g_sGEBUGFileName = DEFAULT_GEBUG_FILENAME;

// �޽��� ���� �̸� �����ϱ�
void SetDefaultGEBUGFileName(const char* sFIleName)						
{
	g_sGEBUGFileName = sFIleName;
}

// ����� �޽����� ���Ϸ� ����
void _cdecl fgebug(const char* str, ...)
{
#ifndef _FINAL_RELEASE
	static TCHAR szBuffer[MAX_MSGBUFFER_SIZE];
	va_list args;
	va_start(args, str);
	memset(szBuffer,0,sizeof(szBuffer));
    vsprintf(szBuffer, str, args);
	va_end(args);
	fgebugto(g_sGEBUGFileName,szBuffer);
#endif
}

// Ư�� ���Ͽ� �޽��� �����
void _cdecl fgebugto(const char* szFileName, const char* str, ...)
{
#ifndef _FINAL_RELEASE
	FILE*	fp;
	fp = fopen(GetThisPath()+szFileName,"a+");
	if(fp==NULL)
	{
		gebug("���� ���� ����:%s", szFileName);
		return;
	}

	static TCHAR szBuffer[MAX_MSGBUFFER_SIZE];
	va_list args;

	va_start(args, str);
	memset(szBuffer,0,sizeof(szBuffer));
    vsprintf(szBuffer, str, args);
	va_end(args);

	fprintf(fp, GetCurrentTimeString()+" : ");
	strcat(szBuffer,"\n");
	fprintf(fp,szBuffer);
	fclose(fp);
#endif
}

// �α����Ͽ� ����ϱ�
void _cdecl flog(const char* str, ...)
{

#ifndef _FINAL_RELEASE
	CString sLogFileName;
	CString	sStr;
	sLogFileName = GetCurrentDayString()+".log";

	static TCHAR szBuffer[MAX_MSGBUFFER_SIZE];
	va_list args;
	va_start(args, str);
	memset(szBuffer,0,sizeof(szBuffer));
    vsprintf(szBuffer, str, args);
	va_end(args);
	sStr = GetCurrentTimeString()+" : "+szBuffer;

	FILE* fp;
	fp = fopen(GetThisPath()+sLogFileName, "a+");
	if(fp==NULL) return;
	fprintf(fp,"%s\n", sStr);
	fclose(fp);
#endif
}

BOOL QueryShellFolders(char *name, char *out)
{
	HKEY hKey;
	if ( RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",0,KEY_READ,&hKey) == ERROR_SUCCESS)
	{
		ULONG l = 1024;
		ULONG t=REG_SZ;
		RegQueryValueEx(hKey,name,NULL,&t,(BYTE*)out,&l );
		RegCloseKey(hKey);
		return TRUE;
	}
	return FALSE;
}



//##################################################################################################################
//##	�޴� ����
//##################################################################################################################
//----�ڵ屸�翡�� ������-------------------------------------------------------
// Function: MergeMenu
// @func		Merges two menus
// @rdesc	bool: false = error occured
// @parm	CMenu * 			|	pMenuDestination		|	[in, retval] destination menu handle    
// @parm	const CMenu *	|	pMenuAdd					|	[in]	menu to merge
// @parmopt bool			|	bTopLevel	|	false	|	[in]	indicator for special top level behavior
//	@comm	This function calles itself recursivley. If bTopLevel is set to true,
//			we append popups at top level or we insert before "Window" or "Help".
//------------------------------------------------------------------------------
bool MergeMenu(CMenu * pMenuDestination, const CMenu * pMenuAdd, bool bTopLevel /* =false */)
{
	int iMenuAddItemCount	= pMenuAdd->GetMenuItemCount();					// get the number menu items in the menus
	int iMenuDestItemCount	= pMenuDestination->GetMenuItemCount();
	
	if (iMenuAddItemCount == 0)	return true;								// if there are no items return
	
	// if we are not at top level and the destination menu is not empty
	// -> we append a seperator
	if (!bTopLevel && iMenuDestItemCount > 0) pMenuDestination->AppendMenu(MF_SEPARATOR);
	
	for(int iLoop = 0; iLoop < iMenuAddItemCount; iLoop++)					// iterate through the top level of <pMenuAdd>
	{
		CString sMenuAddString;												// get the menu string from the add menu
		pMenuAdd->GetMenuString(iLoop, sMenuAddString, MF_BYPOSITION);

		CMenu* pSubMenu = pMenuAdd->GetSubMenu(iLoop);						// try to get the submenu of the current menu item
		
		if (!pSubMenu)														// check if we have a sub menu
		{
			// normal menu item
			// read the source and append at the destination
			UINT nState	 = pMenuAdd->GetMenuState(iLoop, MF_BYPOSITION);
			UINT nItemID = pMenuAdd->GetMenuItemID(iLoop);
			if (pMenuDestination->AppendMenu(nState, nItemID, sMenuAddString))
			{
				iMenuDestItemCount++;										// menu item added, don't forget to correct the item count
			}
			else
			{
				TRACE("MergeMenu: AppendMenu failed!\n");
				return false;
			}
		}
		else																// create or insert a new popup menu item
		{	
			int iInsertPosDefault = -1;										// default insert pos is like ap
			if(bTopLevel)													// if we are at top level merge into existing popups rather than creating new ones
			{
				ASSERT(sMenuAddString != "&?" && sMenuAddString != "?");
				CString csAdd(sMenuAddString);
				csAdd.Remove('&');	// for comparison of menu items supress '&'
				bool bAdded = false;

				for( int iLoop1 = 0; iLoop1 < iMenuDestItemCount; iLoop1++ )	// try to find existing popup
				{
					CString sDest;												// get the menu string from the destination menu
					pMenuDestination->GetMenuString(iLoop1, sDest, MF_BYPOSITION);
					sDest.Remove('&'); // for a better compare (s.a.)
					
					if (csAdd == sDest)
					{
						// we got a hit -> merge the two popups
						// try to get the submenu of the desired destination menu item
						CMenu* pSubMenuDest = pMenuDestination->GetSubMenu(iLoop1);
						
						if (pSubMenuDest)
						{
							// merge the popup recursivly and continue with outer for loop
							if (!MergeMenu(pSubMenuDest, pSubMenu))
								return false;
							bAdded = true;
							break;
						}
					}

					// alternativ insert before <Window> or <Help>
					if (iInsertPosDefault == -1 && (sDest == "Window" || sDest == "?" || sDest == "Help"))
					{
						iInsertPosDefault = iLoop1;
					}
				} // for (iLoop1)
				if (bAdded)
				{
					continue;											// menu added, so go on with loop over pMenuAdd's top level
				}
			} // if (bTopLevel)

			if( iInsertPosDefault == -1 )								// if the top level search did not find a position append the menu
			{
				iInsertPosDefault = pMenuDestination->GetMenuItemCount();
			}
			
			CMenu NewPopupMenu;											// create a new popup and insert before <Window> or <Help>
			if (!NewPopupMenu.CreatePopupMenu())
			{
				TRACE("MergeMenu: CreatePopupMenu failed!\n");
				return false;
			}
			
			if (!MergeMenu(&NewPopupMenu, pSubMenu)) return false;		// merge the new popup recursivly
			
			HMENU hNewMenu = NewPopupMenu.GetSafeHmenu();				// insert the new popup menu into the destination menu
			if (pMenuDestination->InsertMenu(iInsertPosDefault,
				MF_BYPOSITION | MF_POPUP | MF_ENABLED, 
				(UINT)hNewMenu, sMenuAddString ))
			{
				iMenuDestItemCount++;									// don't forget to correct the item count
			}
			else
			{
				TRACE("MergeMenu: InsertMenu failed!\n");
				return false;
			}

			// don't destroy the new menu		
			NewPopupMenu.Detach();
		} // if (pSubMenu)
	} // for (iLoop)
	return true;
}

//##################################################################################################################
//##	Ʈ���� ����
//##################################################################################################################
UINT	WM_TRAY_NOTIFY	= ::RegisterWindowMessage("WM_TRAY_NOTIFY");
BOOL TrayMessage(HWND hWnd, DWORD dwMessage, UINT uID, HICON hIcon, LPSTR lpszTip)
{
   BOOL res;
   NOTIFYICONDATA tnd;
   
   tnd.cbSize      = sizeof(NOTIFYICONDATA);
   tnd.hWnd        = hWnd;
   tnd.uID         = uID;
   tnd.uFlags      = NIF_MESSAGE|NIF_ICON|NIF_TIP;
   tnd.uCallbackMessage   = WM_TRAY_NOTIFY;
   tnd.hIcon       = hIcon;

   if (lpszTip)
      lstrcpyn(tnd.szTip, lpszTip, sizeof(tnd.szTip));
   else
      tnd.szTip[0] = '\0';
   
   res = Shell_NotifyIcon(dwMessage, &tnd);
   
   if (hIcon)
      DestroyIcon(hIcon);
   
   return res;
}

void Tray_NotifyDelete(HWND hWnd, UINT uID)
{
   TrayMessage(hWnd, NIM_DELETE, uID, NULL, NULL);
}

void Tray_NotifyAdd(HWND hWnd, UINT uID, HICON hIcon, LPSTR lpszTip)
{
   TrayMessage(hWnd, NIM_ADD, uID, hIcon, lpszTip);
}

void Tray_NotifyModify(HWND hWnd, UINT uID, HICON hIcon, LPSTR lpszTip)
{
   TrayMessage(hWnd, NIM_MODIFY, uID, hIcon, lpszTip);
}


//##################################################################################################################
//##	��Ʈ��  ����
//##################################################################################################################

// ���� �� ��ǻ���� �����Ǹ� ��´� 
#ifdef _GUTIL_NETWORK
#include "winsock.h"
CString GetIP(bool bHexType, bool bUseDot)
{
	char	szHostName[1024];
	CString	strHostName;
	CString	strIPAddr = "";

	if (! ::gethostname(szHostName, 1024))
	{
		strHostName = szHostName;
		struct hostent*	pHost;

		pHost = gethostbyname(szHostName);
		if (pHost != NULL)
		{
			if (pHost->h_addr_list[0])
			{
				BYTE				bAddr[4];
				CString				strIP;
				bAddr[0] = (BYTE) pHost->h_addr_list[0][0];
				bAddr[1] = (BYTE) pHost->h_addr_list[0][1];
				bAddr[2] = (BYTE) pHost->h_addr_list[0][2];
				bAddr[3] = (BYTE) pHost->h_addr_list[0][3];

				if(bHexType)
				{
					if(bUseDot)
					{
						strIPAddr.Format("%02x.%02x.%02x.%02x", bAddr[0], bAddr[1], bAddr[2], bAddr[3]);
					}
					else
					{
						strIPAddr.Format("%02x%02x%02x%02x", bAddr[0], bAddr[1], bAddr[2], bAddr[3]);
					}
				}
				else
				{
					strIPAddr.Format("%d.%d.%d.%d", bAddr[0], bAddr[1], bAddr[2], bAddr[3]);
				}
			}
		}
	}
	return strIPAddr;
}
int	GetIPList(CStringArray& ipList, bool bHexType, bool bUseDot)
{
	char	szHostName[1024];
	CString	strHostName;
	CString	strIPAddr = "";
	int		i;

	if (! ::gethostname(szHostName, 1024))
	{
		strHostName = szHostName;
		struct hostent*	pHost;

		pHost = gethostbyname(szHostName);
		if (pHost != NULL)
		{
			for(i=0;i<255;i++)
			{
				if (pHost->h_addr_list[i])
				{
					BYTE				bAddr[4];
					CString				strIP;
					bAddr[0] = (BYTE) pHost->h_addr_list[i][0];
					bAddr[1] = (BYTE) pHost->h_addr_list[i][1];
					bAddr[2] = (BYTE) pHost->h_addr_list[i][2];
					bAddr[3] = (BYTE) pHost->h_addr_list[i][3];

					if(bHexType)
					{
						if(bUseDot)
							strIPAddr.Format("%02x.%02x.%02x.%02x", bAddr[0], bAddr[1], bAddr[2], bAddr[3]);
						else
							strIPAddr.Format("%02x%02x%02x%02x", bAddr[0], bAddr[1], bAddr[2], bAddr[3]);
					}
					else
						strIPAddr.Format("%d.%d.%d.%d", bAddr[0], bAddr[1], bAddr[2], bAddr[3]);
					ipList.Add(strIPAddr);
				}
				else
					break;
			}
		}
	}
	return ipList.GetSize();
}
#endif

//##################################################################################################################
//##	�������� �Ľ� ����
//##################################################################################################################
// ESCAPING �ϱ� - �������� 
CString Escaping(CString sStr)
{
	/*
	CString sRet = sStr;
	sRet.Replace("`","``");	sRet.Replace(",","`.");	sRet.Replace("\n","`n");	sRet.Replace("\r","`r");
	return sRet;
	*/
	if(sStr.Find(DELIM_RECORD)>=0||sStr.Find(DELIM_PACKET)>=0||sStr.Find('\r')>=0||sStr.Find('\"')==0)				// ���ο� DELIMITER �� ���� ���.
	{
		sStr.Replace("\\","\\\\");			/* \       -> \\   */
		sStr.Replace("\"","\\\"");			/* "       -> \"   */
		sStr.Replace("\n","\\n");			/* cr      -> \n   */
		sStr.Replace("\r","\\r");			/* lf      -> \r   */

		sStr = "\"" + sStr + "\"";			// ����ǥ�� ���� 
	}
	return sStr;
}

// DEESCAPING �ϱ� - ������
CString DeEscaping(CString sStr)
{
	CString		sMsg;
	LineParser	parser;
	int			ret;

	ret = parser.Parse(sStr.GetBuffer(0));
	if(ret<0) { ASSERT(0); return "";}
	if(ret>1) { ASSERT(0); return "";}

	return parser.GetTokenStr(0);
}

// �޽��� �Ľ��ϱ� - ���н� <0 ���� 
int ParsingMessage(CString sMsg, CStringArray& msgArray, bool bUsingWhiteSpace)
{
	LineParser	parser;
	int			ret,i;
	if(bUsingWhiteSpace)
		ret = parser.Parse2(sMsg.GetBuffer(0));	// white space �� �̿��� parsing..
	else
		ret = parser.Parse(sMsg.GetBuffer(0));
	if(ret<0) { ASSERT(0); msgArray.RemoveAll(); return ret;}
	msgArray.SetSize(parser.GetNumTokens());
	for(i=0;i<parser.GetNumTokens();i++)
	{
		msgArray[i] = parser.GetTokenStr(i);
	}
	return parser.GetNumTokens();
}

//##################################################################################################################
//##	�Ľ� ��ƿ Ŭ���� ����
//##################################################################################################################
GrowBuf::GrowBuf()	{ m_alloc=m_used=0; m_s=NULL; }
GrowBuf::~GrowBuf() { free(m_s); }
int GrowBuf::Add(void *data, int len) 
{ 
	if (len<=0) return 0;Resize(m_used+len);memcpy((char*)m_s+m_used-len,data,len);return m_used-len;
}
void GrowBuf::Resize(int newlen)
{
	m_used=newlen;
	if (newlen > m_alloc)
	{
		m_alloc = newlen + 32768;
		m_s = realloc(m_s, m_alloc);
		if (!m_s)
		{
			flog("Internal compiler error #12345: GrowBuf realloc(%d) failed.\n",m_alloc);
			ASSERT(0); return;
		}
	}
	if (!m_used && m_alloc > 65535) // only free if you resize to 0 and we're > 64k
	{
		m_alloc=0;free(m_s);m_s=NULL;
	}
}
int GrowBuf::Getlen() { return m_used; }
void* GrowBuf::Get() { return m_s; }
////////////////////////////////////////////////////////////////////////////////
StringList::StringList() { }
StringList::~StringList() { }

int StringList::Add(char *str, int case_sensitive)
{
	int a=Find(str,case_sensitive);
	if (a >= 0 && case_sensitive!=-1) return a;
	return gr.Add(str,strlen(str)+1);
}
// use 2 for case sensitive end-of-string matches too
int StringList::Find(char *str, int case_sensitive) // returns -1 if not found
{
	char *s=(char*)gr.Get();
	int ml=gr.Getlen();
	int offs=0;
	while (offs < ml)
	{
		if ((case_sensitive && !strcmp(s+offs,str)) ||(!case_sensitive && !stricmp(s+offs,str)))
		{
			return offs;
		}
		if (case_sensitive==2 && 
			strlen(str) < strlen(s+offs) &&  // check for end of string
			!strcmp(s+offs+strlen(s+offs)-strlen(str),str))
		{
			return offs+strlen(s+offs)-strlen(str);
		}
		offs+=strlen(s+offs)+1;
	}
	return -1;
}
char* StringList::Get() { return (char*)gr.Get(); }
int StringList::Getlen() { return gr.Getlen(); }
////////////////////////////////////////////////////////////////////////////////
LineParser::LineParser()   {m_nTokenNum=m_eat=0;m_tokens=0;}
LineParser::~LineParser()  {FreeTokens();}
int LineParser::Parse(char *line) // returns -1 on error, ',' �� �и��Ͽ� �Ľ�..
{
	m_eat = 0;
	FreeTokens();
	int n;
	n = Doline(line);
	if (n) return n;
	if (m_nTokenNum) 
	{
		m_tokens=(char**)malloc(sizeof(char*)*m_nTokenNum);
		n = Doline(line);
		if (n) {FreeTokens();return -1;}
	}
	return 0;
}
int LineParser::Parse2(char *line) // returns -1 on error   white space �� �и��Ͽ� �Ľ�.
{
	m_eat = 0;
	FreeTokens();
	int n;
	n = Doline2(line);
	if (n) return n;
	if (m_nTokenNum) 
	{
		m_tokens=(char**)malloc(sizeof(char*)*m_nTokenNum);
		n = Doline2(line);
		if (n) {FreeTokens();return -1;}
	}
	return 0;
}
int LineParser::GetNumTokens() 
{ 
	return m_nTokenNum-m_eat; 
}
void LineParser::EatToken() 
{ 
	m_eat++; 
}
char* LineParser::GetTokenStr(int token) 
{ 
	token+=m_eat;
	if (token < 0 || token >= m_nTokenNum) return "";
	return m_tokens[token]; 
}
void LineParser::FreeTokens()
{
	if (m_tokens)
	{
		int x;
		for (x = 0; x < m_nTokenNum; x ++)
			free(m_tokens[x]);
		free(m_tokens);
	}
	m_tokens=0;
	m_nTokenNum=0;
}
int LineParser::Doline(char *line)
{
	int		state=0;
	int		count=0;
	int		size=0;
	bool	escaping=false;
	m_nTokenNum=0;
	while(*line)
	{
		if(m_nTokenNum && *line == ',')line++;			// ��ó���� �ƴϰ�, ��ǥ�θ� ������ ������.. ��) hello,,,

		count = 0;
		state = 0;
		size = 0;
		escaping=false;
		if(*line=='\"') state=1;
		if(state) line++;
		while(*line)
		{
			if(state==1)								// ����ǥ�� ���� ��츸 escaping ó���� �Ѵ�.
			{
				if(*line=='\\'&&*(line+1)=='\"') { line+=2; count+=2; size++; escaping=true; continue; }	// \" ó��
				if(*line=='\\'&&*(line+1)=='\\') { line+=2; count+=2; size++; escaping=true; continue; }	// \\ ó�� 
				if(*line=='\\'&&*(line+1)=='r')  { line+=2; count+=2; size++; escaping=true; continue; }	// \r ó�� 
				if(*line=='\\'&&*(line+1)=='n')  { line+=2; count+=2; size++; escaping=true; continue; }	// \n ó�� 
			}
			if(state==1&&*line=='\"') 
			{
				if(*(line+1)!=NULL &&*(line+1)!=',') 
					return -1;			// ����ǥ ������ ������ �������� �ƴϰ�, ��ǥ�� �ƴҰ��..
				break;
			}
			if(state==0&&*line==',') break;
			line++;
			count++;
			size++;
		}
		if(m_tokens)
		{
			if(escaping)
			{
				char* s;
				char* d;
				int	i;
				m_tokens[m_nTokenNum] = (char*)malloc(size+1);
				d = m_tokens[m_nTokenNum];
				s = line-count;
				for(i=0;i<size;i++)
				{
					if(*s=='\\' && *(s+1)=='\\') { *d = '\\'; s+=2; d++; continue; }
					if(*s=='\\' && *(s+1)=='r')  { *d = '\r'; s+=2; d++; continue; }
					if(*s=='\\' && *(s+1)=='n')  { *d = '\n'; s+=2; d++; continue; }
					if(*s=='\\' && *(s+1)=='\"') { *d = '\"'; s+=2; d++; continue; }
					*d = *s;
					s++; d++;
				}
				*d = 0;
			}
			else
			{
				m_tokens[m_nTokenNum] = (char*)malloc(count+1);
				strncpy(m_tokens[m_nTokenNum], line-count,count);
				m_tokens[m_nTokenNum][count]=0;
			}
		}
		m_nTokenNum++;
		if(state)							// ��ȣ�� ����ä�� ������ ������ ���..
		{
			if(*line) line++;				// �̷� ���̽��� ����..
			else return -1;					// ����..
		}
	}
	return 0;
}
bool LineParser::IsWhiteSpace(char c)
{
	if(c==' '||c=='\t'||c=='\n'||c=='\r') return true;
	return false;
}
int LineParser::Doline2(char *line)
{
	int		state=0;
	int		count=0;
	int		size=0;
	bool	escaping=false;
	m_nTokenNum=0;
	while(*line)
	{
		while (IsWhiteSpace(*line)) line++;	// white space ����.

		count = 0;
		state = 0;
		size = 0;
		escaping=false;
		if(*line=='\"') state=1;
		if(state) line++;
		while(*line)
		{
			if(state==1)								// ����ǥ�� ���� ��츸 escaping ó���� �Ѵ�.
			{
				if(*line=='\\'&&*(line+1)=='\"') { line+=2; count+=2; size++; escaping=true; continue; }	// \" ó��
				if(*line=='\\'&&*(line+1)=='\\') { line+=2; count+=2; size++; escaping=true; continue; }	// \\ ó�� 
				if(*line=='\\'&&*(line+1)=='r')  { line+=2; count+=2; size++; escaping=true; continue; }	// \r ó�� 
				if(*line=='\\'&&*(line+1)=='n')  { line+=2; count+=2; size++; escaping=true; continue; }	// \n ó�� 
			}
			if(state==1&&*line=='\"') 
			{
				//if(*(line+1)!=NULL &&*(line+1)!=',') 
				//	return -1;			// ����ǥ ������ ������ �������� �ƴϰ�, ��ǥ�� �ƴҰ��..
				break;
			}
			if(state==0&& (IsWhiteSpace(*line))) break;
			line++;
			count++;
			size++;
		}
		if(m_tokens)
		{
			if(escaping)
			{
				char* s;
				char* d;
				int	i;
				m_tokens[m_nTokenNum] = (char*)malloc(size+1);
				d = m_tokens[m_nTokenNum];
				s = line-count;
				for(i=0;i<size;i++)
				{
					if(*s=='\\' && *(s+1)=='\\') { *d = '\\'; s+=2; d++; continue; }
					if(*s=='\\' && *(s+1)=='r')  { *d = '\r'; s+=2; d++; continue; }
					if(*s=='\\' && *(s+1)=='n')  { *d = '\n'; s+=2; d++; continue; }
					if(*s=='\\' && *(s+1)=='\"') { *d = '\"'; s+=2; d++; continue; }
					*d = *s;
					s++; d++;
				}
				*d = 0;
			}
			else
			{
				m_tokens[m_nTokenNum] = (char*)malloc(count+1);
				strncpy(m_tokens[m_nTokenNum], line-count,count);
				m_tokens[m_nTokenNum][count]=0;
			}
		}
		m_nTokenNum++;
		if(state)							// ��ȣ�� ����ä�� ������ ������ ���..
		{
			if(*line) line++;				// �̷� ���̽��� ����..
			else return -1;					// ����..
		}
		while (IsWhiteSpace(*line)) line++;	// white space ����.
	}
	return 0;
}

//##################################################################################################################
//##	��Ÿ
//##################################################################################################################
// �޽��� ����
void PumpUntilEmpty(HWND hWnd)
{
	MSG msg;
	while(::PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}

// Ư�� �޽����� �ö����� ����
bool PumpUntilMessage(UINT nMessage)
{
	MSG msg;
	while(::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if(msg.message==nMessage) return true;
		::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return false;
}

// �������� �����ֱ� ���� 
UINT GetWindowShowState(HWND hWnd)
{
	WINDOWPLACEMENT wndpl;
	wndpl.length = sizeof(WINDOWPLACEMENT);
	if(GetWindowPlacement(hWnd, &wndpl)==FALSE) {ASSERT(0); return SW_HIDE;}
	return wndpl.showCmd;
}

bool StrRetToBuf(STRRET* pstr, LPITEMIDLIST pidl, LPTSTR* ppszBuf)
{
    LPMALLOC pMalloc = NULL;
	HRESULT hr = S_OK;
	int cch;
	LPSTR strOffset;
	bool bRet = true;

    SHGetMalloc(&pMalloc);

	*ppszBuf = NULL;  // Assume failure

	switch (pstr->uType)
	{
		case STRRET_WSTR: 
			cch = WideCharToMultiByte(CP_OEMCP, 0, pstr->pOleStr, -1, NULL, 0, NULL, NULL); 
			*ppszBuf = (LPTSTR)pMalloc->Alloc(cch * sizeof(TCHAR));

			if (*ppszBuf != NULL)
				WideCharToMultiByte(CP_OEMCP, 0, pstr->pOleStr, -1, *ppszBuf, cch, NULL, NULL); 
			else
				bRet = false;
			break;

		case STRRET_OFFSET: 
			strOffset = (((char *) pidl) + pstr->uOffset);

			cch = strlen(strOffset) + 1; // NULL terminator
			*ppszBuf = (LPTSTR)pMalloc->Alloc(cch * sizeof(TCHAR));

			if (*ppszBuf != NULL)
				strcpy(*ppszBuf, strOffset);
			else
				bRet = false;
			break;

		case STRRET_CSTR: 
			cch = strlen(pstr->cStr) + 1; // NULL terminator
			*ppszBuf = (LPTSTR)pMalloc->Alloc(cch * sizeof(TCHAR));

			if (*ppszBuf != NULL)
				strcpy(*ppszBuf, pstr->cStr);
			else
				bRet = false;

			break;
	}

	pMalloc->Release();

	return bRet;
}
