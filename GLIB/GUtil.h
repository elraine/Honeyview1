/*//////////////////////////////////////////////////////////////////////////////////////////////////////

	HISTROY
		- 2000/03/17 : ���� ����..

//////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once

//##################################################################################################################
//##	��ũ�ε�
//##################################################################################################################
#define	ZERO_MEMORY(x)			memset(&x,0,sizeof(x))
#define OPEN_URL(xxxx)			ShellExecute(NULL, "open", xxxx, NULL, NULL, SW_SHOW);
inline	void SET_EVENT(HANDLE hEvent) { if(hEvent) SetEvent(hEvent); }
#define SETICON() 				{HICON hIcon;hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);SetIcon(hIcon, FALSE);}
#define SETICONX(x) 			{HICON hIcon;hIcon = AfxGetApp()->LoadIcon(x);SetIcon(hIcon, FALSE);}
#define BEEP()					MessageBeep(MB_ICONASTERISK);

//##################################################################################################################
//##	CRC + ENC&DEC ����
//##################################################################################################################
DWORD	crc32( DWORD crc, const BYTE *buf, UINT len);
bool	CheckFileCRC(const char* szFileName, DWORD &dwResult,int nStartPos=0);		// ������ CRC �� üũ�ϰ� �����Ѵ�.
#define MAX_PASSENCDEC_BUFSIZE	100													// ��ȣȭ�� �н������� ��� ���� ������
void	EncPass(char* sDest,const char* sPassWord);									// sPassWord �� sDest[MAX_PASSENCDEC_BUFSIZE] �� ��ũ���� ��Ų��.
char*	DecPass(char* sSrc);														// ��ũ���ǵ� binary ����Ÿ�� ���������ش�.

//##################################################################################################################
//##	���� ����
//##################################################################################################################
bool	GetFileNameFromURL(const CString& sURL, CString& sResult);					// URL ���� ���� �̸��� �̾Ƴ���.
char* 	GetFileNameFromPath(const char* szPathName );								// PATH ���� ���� �̸��� �̴´�.
char*	GetDriveNameFromPath(const char* szPathName);								// PATH ���� ����̺� (EX) "C:") �� �̾Ƴ���.
char*	GetDirNameFromPath(const char* szPathName);									// PATH ���� ���丮�� �̾Ƴ���.
CString GetLastDirFromPath(const CString& sPathName);								// ��ü ������ ������ ���丮 �̸� ���ϱ�
CString GetParentPath(const CString& sPathName);									// PARENT ���� ���ϱ� - ��Ʈ(EX) C:\)�� PARENT �� ���� ""�� �����Ѵ� 
char* 	GetFileNameFromPathWithOutExt(const char* szPathName );						// PATH ���� Ȯ���ڸ� ������ ���ϸ��� �̴´�.
char*	GetExtFromPath(const char* szPathName);										// PATH ���� Ȯ���� ���� �̾Ƴ���.
int		GetFileSize(const CString& sPathName);										// ���� ������ ���ϱ�
bool	IsFolder(const char* szPathName);											// ���� ���� �Ǵ�
bool	IsFile(const char* szPathName);												// ���� ���� �Ǵ� 
CString GetDirectory(HWND hWndParent, const char* szRoot, const char* szTitle);		// ����ڷκ��� ������ �Է� �޴´�.
void	DeleteFolder(CString sFolder);												// ������ �����.
CString AddPath(CString sLeft, CString sRight);										// �ΰ��� ����(Ȥ�� ����+����)�� ���Ѵ�.
bool	DigPath(CString sFolderPath);												// ������ �մ´�.

//##################################################################################################################
//##	INI / REGISTRY
//##################################################################################################################
#define	DEFAULT_INI_FILE_NAME	"SETTING.INI"										// �⺻ INI ���� �̸�
/*		�� �ڵ���� ������ ��ȸ�� ���� �����..
void	SetPrivateRegAppName(const CString& sAppName);
void 	SetPrivateRegInt(CString sKeyName, DWORD nValue);							// REGISTRY �� INT �� ����
DWORD 	GetPrivateRegInt(CString sKeyName, DWORD nDefaultValue=0);					// REGISTRY ���� INT �� �б�
void 	SetPrivateRegBin(CString sKeyName, void* pData, int nSize);					// REGISTRY �� BINARY �� ����
bool 	GetPrivateRegBin(CString sKeyName, void* pData, int nSize);					// REGISTRY ���� BINARY �� �б�
*/
CString	GetIniStr(const char* szSection, const char* szKey, 						// INI ���Ͽ��� STRING �� �б�
				CString sIniFileName=DEFAULT_INI_FILE_NAME,
				CString sDefaultValue="");										
void	SetIniStr(const char* szSection, const char* szKey, const char* szValue,	// INI ���Ͽ� STRING �� ����
				CString sIniFileName=DEFAULT_INI_FILE_NAME);	
int		GetIniInt(const char* szSection, const char* szKey, int nDefault,			// INI ���Ͽ��� INT �� �б�
				CString sIniFileName=DEFAULT_INI_FILE_NAME);	
void	SetIniInt(const char* szSection, const char* szKey, int nValue,				// INI ���Ͽ� INT �� ����
				CString sIniFileName=DEFAULT_INI_FILE_NAME);	
void	GetIniKeyList(CStringList& slKey, CString sSection,							// INI ������ SECTION �� ��� KEY �� ����Ʈ�� ���
				CString sIniFileName=DEFAULT_INI_FILE_NAME);

bool	GetRegStr(HKEY hKeyRoot, const CString& sKeySub, const CString& sValue,		// ����Ʈ ���� ������ ������Ʈ������ ��Ʈ���� �о� ���δ�.
				  CString& sResult, CString sDefaultValue);
bool	GetRegStr(HKEY hKeyRoot, const CString& sKeySub,							// ������Ʈ������ ��Ʈ���� �о� ���δ� //
				const CString& sValue, CString& sResult);	
bool	GetRegStr(const CString& sKeyRoot, const CString& sKeySub,					// ������Ʈ������ ��Ʈ���� �о� ���δ� //
				const CString& sValue, CString& sResult);
bool	GetRegStr(const CString& sKey, CString& sResult);							// ��¥�� ������Ʈ������ ��Ʈ���� �о� ���δ�. ��:"HKEY_LOCAL_MACHINE\\SOFTWARE\\Blizzard Entertainment\\Starcraft\\Program"
bool	SetRegStr(HKEY hKeyRoot, const CString& sKeySub,							// ������Ʈ���� ��Ʈ���� �����Ѵ� //
				const CString& sValueName, const CString& sValue);
bool	SetRegStr(const CString& sKeyRoot, const CString& sKeySub,					// ������Ʈ���� ��Ʈ���� �����Ѵ� //
				const CString& sValueName, const CString& sValue);
bool	SetRegStr(const CString& sKey, const CString& sValue);						// ��¥�� ������Ʈ���� ��Ʈ���� �����Ѵ� ��:"HKEY_LOCAL_MACHINE\\SOFTWARE\\Blizzard Entertainment\\Starcraft\\Program"
bool	SetRegDWORD(HKEY hKeyRoot, const CString& sKeySub,							// ������Ʈ���� DWORD�� �����Ѵ� //
				const CString& sValueName, DWORD dwValue);
bool	GetRegDWORD(HKEY hKeyRoot, const CString& sKeySub,							// ������Ʈ������ DWORD�� �о� ���δ� //
				const CString& sValue, DWORD& dwResult, DWORD dwDefaultValue=0);
bool	SetRegBin(HKEY hKeyRoot, const CString& sKeySub,							// ������Ʈ���� BINARY�� �����Ѵ� //
				const CString& sValueName, void* pData, int nDataSize);
bool	GetRegBin(HKEY hKeyRoot, const CString& sKeySub, const CString& sValue,		// ������Ʈ������ BINARY�� �о� ���δ� - �ݵ�� free() �� ������ �־�� �Ѵ�.. //
				BYTE** pRetBuf, int& nBufSize);
bool	SetRegInt(HKEY hKeyRoot, const CString& sKeySub,							// ������Ʈ���� INT�� �����Ѵ� //
				const CString& sValueName, int nValue);
bool	GetRegInt(HKEY hKeyRoot, const CString& sKeySub,							// ������Ʈ������ INT�� �о� ���δ� //
				const CString& sValue, int& nResult, int nDefaultValue=0);
bool	RegDeleteValue(HKEY hKeyRoot, const CString& sKeySub, 
				const CString& sValueName);											// ������Ʈ�� ��(Value) �����.
bool	RegistAutoRun(const CString& sValueName, const CString &sFileName);			// �ý��� ���۽� ������ ���� �̸��� �����Ѵ�. 
CString	GetAutoRun(const CString& sKeyName);										// �ڵ������� ���� �̸��� ���Ѵ�.


//##################################################################################################################
//##	�ý��� ���� ���
//##################################################################################################################
CString	GetThisPath();															// ���α׷��� ���۵� ���丮..��
CString	GetThisFileName();														// �� �ڽ�..
int		GetCommandLineList(CStringArray &sa);									// ����� �Ķ���� ���ϱ�.
int		GetScreenWidth() ;														// ��ũ�� �� ���
int		GetScreenHeight() ;														// ��ũ�� ���� ��� 
void	GetWorkArea(CRect& r);													// �۾� ���� ���
int		TextWidth (HDC hDC, const char* szText);								// �ؽ�Ʈ ���ڿ��� �� ���
int 	FontHeight (HDC hDC,      BOOL bIncludeLeading=TRUE);					// �ؽ�Ʈ ������ ���� ���
int		ParagraphHeight(HDC hDC, BOOL bIncludeLeading, const char* pText);		// ������ ���̸� ���� ( ���� : \n ���� LF �� ���� )
int		ParagraphWidth(HDC hdC, const char* szText);							// ������ ���� �����Ѵ� ( ���� : \n ���� LF �� ���� )
bool	GetFileVersion(char *szFileName, DWORD* verMS, DWORD* verLS);			// ������ ���� ������ ����.
bool	GetFileVersion(CString sFileName, CString& sFileVersion);				// ������ ���� ������ ����.
BOOL	GetDiskFreeSpace(char cDrive, int& nResult);							// �ϵ� �������� �������ϱ�(KB)
BOOL	GetDiskFreeSpace(const char* szDrive, int& nResult);					// �ϵ� �������� �������ϱ�(KB)
enum OS_VERSION
{
	OSVER_ERROR,	OSVER_UNKNOWN,
	OSVER_31,		OSVER_95,	OSVER_98,	OSVER_ME,
	OSVER_NT351,	OSVER_NT4,	OSVER_2000,	OSVER_XP,
};
OS_VERSION	CheckOSVerion(CString* psServiceRelease=NULL);						// OS VERSION ������
CString		OSVer2Str(OS_VERSION nOS);											// OS VERSION �� ��Ʈ������ �ٲٱ�


//##################################################################################################################
//##	���ڿ� ó�� �Լ�
//##################################################################################################################
void	StringCopy(char* szDst, const char* szSrc, int nCount);
void	StringCopy(BYTE* szDst, const char* szSrc, int nCount);
void	StringCopy(char* szDst, const BYTE* szSrc, int nCount);
void	StringCopy(BYTE* szDst, const BYTE* szSrc, int nCount);
void	StringCopy(CString& sDst,BYTE* szSrc, int nCount);
CString	ChangeFileExtString(const CString& sFileName, const CString& sNewExt);		// ������ Ȯ���ڸ� �ٲ۴�.
CString	ChangeURLExtString(const CString& sPathName, const CString& sNewExt);		// URL�� Ȯ���ڸ� �ٲ۴�.
bool	SplitEmailAddress(const char* szEmail, CString &sID, CString &sAddress);	// �̸��� �ּҸ� id�� ���� �ּҷ� �и��Ѵ� 

//##################################################################################################################
//##	�ð� ó�� �Լ�
//##################################################################################################################
CString	GetTimeString(const CString& sFormat );										// ���� �ð��� ������ ���ؼ� ��������
CString	GetCurrentTimeString();														// ���� �ð��� �ʱ��� ���ڿ��� ����
CString	GetCurrentHourString();														// ��¥&�ð��� ���ڿ��� ����
CString	GetCurrentMinString();														// ���� �ð��� �б��� ���ڿ��� ����
CString	GetCurrentDayString();														// ���� ��¥�� ���ڿ��� ����
int		GetThisYear();																// ���� ������ �⵵ 

//##################################################################################################################
//##	�����
//##################################################################################################################
#define		DEFAULT_GEBUG_FILENAME	"GEBUG.txt"										// �⺻ �α� ���� �̸�
void _cdecl gebug(const char* str, ...);											// ����� ������ RECV ���� ������.
void _cdecl gebugto(const char* szWndNameToRecv, const char* str, ...);				// ����� ������ ���� ��븦 �����ؼ� ������.
void		SetDefaultGEBUGFileName(const char* sFIleName);							// ����� �޽��� ���� �̸� �����ϱ�
void _cdecl fgebug(const char* str, ...);											// ����� �޽����� ���Ϸ� ����
void _cdecl fgebugto(const char* szFileName, const char* str, ...);					// Ư�� ���Ͽ� �޽��� �����
void _cdecl flog(const char* str, ...);												// �α����Ͽ� ����ϱ�
#define		err(x)	gebug("$$ERROR$$ : [%s,%d] - %s",__FILE__,__LINE__,x);			// ���� ��ũ��
#define		ferr(x)	flog ("$$ERROR$$ : [%s,%d] - %s",__FILE__,__LINE__,x);			// ���� ��ũ��

//##################################################################################################################
//##	�� ����
//##################################################################################################################
HRESULT		CreateShortcut(LPCSTR pszShortcutFile, LPCTSTR pszLink, LPSTR pszDesc);	// ���� �������� �����.
HRESULT		SHCreateSystemShortcut(LPCTSTR szLnkFile, int nFolder, LPCTSTR szFile);	// ���� ������ �����..
BOOL		QueryShellFolders(char *name, char *out);

//##################################################################################################################
//##	�޴� ����
//##################################################################################################################
bool		MergeMenu(CMenu * pMenuDestination, 
				const CMenu * pMenuAdd, bool bTopLevel = false);					// �ΰ��� �޴��� ��ģ��.

//##################################################################################################################
//##	Ʈ���� ����
//##################################################################################################################
extern UINT WM_TRAY_NOTIFY;
void		Tray_NotifyDelete(HWND hWnd, UINT uID);
void		Tray_NotifyAdd(HWND hWnd, UINT uID, HICON hIcon, LPSTR lpszTip);
void		Tray_NotifyModify(HWND hWnd, UINT uID, HICON hIcon, LPSTR lpszTip);

//##################################################################################################################
//##	��Ʈ��  ����
//##################################################################################################################
#ifdef _GUTIL_NETWORK
CString		GetIP(bool bHexType=false, bool bUseDot=true);							// ���� ��ǻ���� ������ ���ϱ� 
int			GetIPList(CStringArray& ipList, bool bHexType=false, bool bUseDot=true);
#endif

//##################################################################################################################
//##	�������� �Ľ� ����
//##################################################################################################################
#define		DELIM_PACKET					'\n'
#define		DELIM_RECORD					','
int			ParsingMessage(CString sMsg, CStringArray& msgArray, bool bUsingWhiteSpace=false);	// DELIM���� �������� STRING ARRAY ���ϱ�
CString		Escaping(CString sStr);													// DELIM�� ESCAPING
CString		DeEscaping(CString sStr);												// DELIM�� DEESCAPING

//##################################################################################################################
//##	��Ÿ
//##################################################################################################################
void PumpUntilEmpty(HWND hWnd=NULL);												// �޽��� ����
bool PumpUntilMessage(UINT nMessage);												// Ư�� �޽����� �ö����� ����
UINT GetWindowShowState(HWND hWnd);													// �������� �����ֱ� ���� 
bool StrRetToBuf(LPSTRRET pstr, LPITEMIDLIST pidl, LPTSTR* ppszBuf);				// STRRET�� ��Ʈ������ ��ȯ

//##################################################################################################################
//##	�Ľ� ��ƿ Ŭ���� ����
//##################################################################################################################
class GrowBuf
{
public:
    GrowBuf();
    ~GrowBuf();
    int Add(void *data, int len);
    void Resize(int newlen);
    int Getlen();
    void *Get();
private:
    void *m_s;
    int m_alloc;
    int m_used;
};

class StringList
{
public:
	StringList();
	~StringList();
	int Add(char *str, int case_sensitive);
	// use 2 for case sensitive end-of-string matches too
	int Find(char *str, int case_sensitive); // returns -1 if not found
	char *Get();
	int Getlen();
private:
	GrowBuf gr;
};

class LineParser {
public:
    LineParser();
    ~LineParser();
    int Parse(char *line);
    int Parse2(char *line);
    int GetNumTokens();
    void EatToken();
    char* GetTokenStr(int token);
private:
    void FreeTokens();
    int Doline(char *line);
    int Doline2(char *line);
	bool IsWhiteSpace(char c);
    int m_eat;
    int m_nTokenNum;
    char **m_tokens;
};
