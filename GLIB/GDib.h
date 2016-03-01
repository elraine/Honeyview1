///////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GDib Ŭ����
//	- ��Ʈ�� ó���� ���������� ���̱� ���� ������� Ŭ����
//	- MSJ 1997/07(??) ȣ �ҽ��� ����� ��.
//	- ���� �ۼ��� : 1999/12/29 BY HONG
//	- ���� ��Ʈ 
//		. 1999/12/29 ; �Ķ���� �ణ ����
//		. 2000/01/03 : GetScanLine, MakeGray, MakeHalftone, FindNearestPalColor, FindExactPalColor �߰�.
//		. 2000/01/07 : DrawTransTo �߰�, DrawTo �Ķ���� ���� �ٲ�..
//		. 2000/01/10 : GetAddrOfPos(), ChangeBkColor() �߰�.
//		. 2000/01/14 : �̹��� Create �� CDC �Ķ���� ���� ����. - �ʿ� ���.. ���߿� �ٽ� �ʿ����...
//		. 2000/01/23 : DrawAlphaTo(), DrawAlphaTransTo() �߰� 
//		. 2000/01/26 : GetAddrOfPos()�� ���� ����
//		. 2000/03/18 : DrawHSplitAlphaTransTo() �߰�.
//		. 2000/06/16 : DrawStretchTo(), DrawStretchToInterpolation() �ϼ�
//		. 2000/06/26 : GDibExt.cpp �и�, DrawWarpingTo() �߰�.
//
//	- �߰� �ؾ��� ���׵�
//		. 256 �÷� ��Ʈ�ʿ��� �ȷ�Ʈ ó�� 
//		. CreateNullImage ���� 256 �÷��� ������ ��� �ȷ�Ʈ ó�� �κ� �ʿ�
//		. ����/���/Ȯ��/���� �׸���
//		. ��Ÿ..
//		. 
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DIB_H_
#define _DIB_H_

enum			PIXEL_FORMAT { PF_UNKNOWN, PF_4BIT, PF_8BIT, PF_24BIT };
const	int		nBitCount[4]  = { 0, 4, 8, 24 };					// �ȼ��� ��Ʈ��
const	int		nByteCount[4] = { 0, 0, 1, 3  };					// �ȼ��� ����Ʈ��

#define			GDIB_TRANS_COLOR	RGB(255,0,255)					// ���� �÷�(��ȫ��)
#define			BYTE_PER_PIXEL_24BIT	3
#define			BIT_PER_PIXEL_24BIT		24

// CALL BACK FUNCTIONS
typedef void GDibProgressFunc(int nCur, int nRange, void* param);


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define			WIDTHBYTES(bits) ((((bits) + 31) / 32) * 4)			// �� ������ �����ϴ� ����Ʈ ��..(4����Ʈ ����)

class GDib  {

protected:
/*
	DECLARE_DYNAMIC(GDib)
	CPalette			m_pal;										// palette
	HDRAWDIB			m_hdd;										// for DrawDib
*/
	CDC					m_dcMem;
	HGDIOBJ				m_hGdiObj;

	BYTE*				m_pDIBits;									// �ȼ��� ���� �����ϱ� ���� ������ 
	bool				m_bOK;										// �̹����� ���� �Ǿ��� ����
	PIXEL_FORMAT		m_nPixelFormat;								// ���� �̹����� pixel format;
	CSize				m_size;										// �̹����� ũ��..
	static BYTE			AlphaTable[256][256];						// ���� ���� ���̺�
	static bool			m_bInitAlphaTable;							// ���� ���̺��� �ʱ�ȭ �Ǿ���?

public:					/* ���� & �Ҹ��� */
	GDib();
	~GDib();

public :				/* �������� �Լ��� */
	
	BOOL				Draw(CDC& dc, const CRect* rcDst=NULL, const CRect* rcSrc=NULL,		
							BOOL bUseDrawDib=TRUE, CPalette* pPal=NULL, BOOL bForeground=FALSE);	// ���� �ִ� DRAW ���.. �̳��� 256 �÷������� �ȷ�Ʈ ó���� ����� �Ѵ� //
	//CPalette*			GetPalette()  { return &m_pal; }

private :				/* ���� �Լ��� */
	BOOL				Attach(HGDIOBJ hbm);
	BOOL				CreatePalette(CPalette& pal);
	UINT				GetColorTable(RGBQUAD* colorTab, UINT nColors);
	BOOL				DeleteObject();

public :				/* ��ƿ �Լ��� */
	CSize				GetSize() { return m_size; }
	CDC*				GetMemDC() { return &m_dcMem; }
	BYTE*				SetDIBits();
	BYTE*				GetDIBits() { return m_pDIBits;}
	const GDib&			operator=(GDib& dibSrc) ;
	operator			CDC*(){return GetMemDC();};
	BYTE*				GetScanLine(int nLine);
	BYTE*				GetAddrOfPos(int nX, int nY);
	int					Get8BitPixel(int nX, int nY);
	bool				Set8BitPixel(int nX, int nY, int value);
	bool				FindNearestPalColor(COLORREF cl, int& nRet);
	bool				FindExactPalColor(COLORREF cl, int& nRet);
	BOOL				CalcAndCheckParamWhenDrawDibToDib(GDib *pDib, int &dx, int &dy, int &sx, int &sy, int &sw, int &sh);
	void				InitAlphaTable();
	PIXEL_FORMAT		GetPixelFormat() { return m_nPixelFormat; }
	UINT				GetPixel(int x, int y);
	UINT				GetPixel24Fast(int x, int y);
	COLORREF			GetRGBPixel(int x, int y);
	void				SetPixel(int x, int y, UINT clr);
	void				SetRGBPixel(int x, int y, COLORREF clr);
	void				Clear(COLORREF clr);

	bool				IsCreated() { return m_bOK; };

public :				/* �ν��Ͻ� ���� */
	static HINSTANCE	m_hAppInst;									// APP INSTANCE;
	static void			SetInstance(HINSTANCE hInst) { m_hAppInst = hInst; };

public :				/* DIB ���� �Լ��� */
	BOOL				LoadFromFile(const char* szFileName);
	BOOL				LoadFromResource(const char* szResourceName);
	BOOL				LoadFromResource(UINT uID) { return LoadFromResource(MAKEINTRESOURCE(uID)); }
	BOOL				CreateNullImage(int w, int h, PIXEL_FORMAT pf=PF_24BIT, COLORREF clrBkgnd=RGB(255,255,255));

public :				/* DIB ���� �Լ��� */
	bool				MakeGray();
	bool				MakeHalftone(COLORREF cl=RGB(0,0,0));
	bool				ChangeBkColor(COLORREF cl);
	bool				MakeBright(int nDegree);
	bool				MakeMono(BYTE nDegree=127, BYTE nResult=0);
	bool				Gradation(COLORREF clrFrom, COLORREF clrTo, bool bHorizontal);
	bool				Gradation(COLORREF clrFrom, COLORREF clrTo, bool bHorizontal, CRect r);
	bool				Gradation3(COLORREF clrFrom, COLORREF clrOver, COLORREF clrTo, bool bHorizontal, CRect r);


public :				/* ȭ�鿡 �׸��� �Լ��� */
	BOOL				DrawTo(CDC *pDC, int dx=0, int dy=0);
	BOOL				DrawTo(CDC *pDC, int dx, int dy, int sx, int sy, int sw, int sh);
	BOOL				DrawTo(CWnd *pWnd, int dx=0, int dy=0);
	BOOL				DrawTo(CWnd *pWnd, int dx, int dy, int sx, int sy, int sw, int sh);
	BOOL				DrawSplitTo(CWnd *pWnd, int dx, int dy, int nPos, int nSplit, bool bHsplit=true);
	BOOL				DrawSplitTo(CDC  *pDC,  int dx, int dy, int nPos, int nSplit, bool bHsplit=true);

public :				/* DIB ���� �׸��� �Լ��� */
	BOOL				DrawTo(GDib *pDib, int dx=0, int dy=0);
	BOOL				DrawTo(GDib *pDib, int dx, int dy, int sx, int sy, int sw, int sh);
	BOOL				DrawTransTo(GDib *pDib, int dx=0, int dy=0, COLORREF clrTrans=GDIB_TRANS_COLOR);
	BOOL				DrawTransTo(GDib *pDib, int dx, int dy, int sx, int sy, int sw, int sh, COLORREF clrTrans=GDIB_TRANS_COLOR);
	BOOL				DrawAlphaTo(GDib *pDib, int dx, int dy, int sx, int sy, int sw, int sh, int nAlpha);
	BOOL				DrawAlphaTransTo(GDib *pDib, int dx, int dy, int sx, int sy, int sw, int sh, int nAlpha, COLORREF clrTrans=GDIB_TRANS_COLOR);
	BOOL				DrawSplitAlphaTo(GDib *pDib, int dx, int dy, int nPos, int nSplit, int nAlpha, bool bHsplit=true);
	BOOL				DrawSplitTransTo(GDib *pDib, int dx, int dy, int nPos, int nSplit, COLORREF clrTrans=GDIB_TRANS_COLOR, bool bHsplit=true);
	BOOL				DrawSplitAlphaTransTo(GDib *pDib, int dx, int dy, int nPos, int nSplit, int nAlpha,  COLORREF clrTrans=GDIB_TRANS_COLOR, bool bHsplit=true);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// GDibExt
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public :				/* Ȯ�� �׸��� */
	BOOL				DrawStretchTo(GDib* pDib, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh);
	BOOL				DrawStretchAlphaTo(GDib* pDib, int _dx1, int _dy1, int _dx2, int _dy2, int _sx1, int _sy1, int _sx2, int _sy2, int nAlpha);
	BOOL				DrawStretchInterpolationTo(GDib* pDib, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh);
	BOOL				DrawStretchInterpolationAlphaTo(GDib* pDib, int _dx1, int _dy1, int _dx2, int _dy2, int _sx1, int _sy1, int _sx2, int _sy2, int nAlpha);

public :				/* ���� */
	BOOL				DrawWarpingTo(GDib* pDib,  int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int sx1, int sy1, int sx2, int sy2, int sx3, int sy3, int nAlpha=-1);
	BOOL				DrawWarpingRectTo(GDib* pDib,  int dx1, int dy1, int dx2, int dy2, int dx3, int dy3, int dx4, int dy4, int sx1, int sy1, int sx2, int sy2, int sx3, int sy3, int sx4, int sy4, int nAlpha=-1);

public :				/* OLE PICTURE ��� */
	bool				OLELoadFromFile(CString sFileName);
	bool				OLELoadFromBuffer(BYTE* pBuff, int nSize);
	bool				OLELoadFromResource(CString sResourceType, CString sResource);
private :
	bool				OLEGetResource(LPSTR lpName, LPSTR lpType, void* pResource, int& nBufSize);


public :				/* PNG ���� */
	bool				PNGLoadFromFile(CString sFileName);
private :
	void				PNGCopyRow(BYTE* pSrc, BYTE* pDest, int nWidth, int nBitperPixel);

public :				/* DIB ���� �Լ��� */
	bool				Sharpen();

public :				/* CALL BACK ���� */
	void				SetProgressFunc(GDibProgressFunc* pFunc, void* param=NULL);
private :
	GDibProgressFunc*	m_pProgressFunc;
	void*				m_pProgressParam;


};

#endif