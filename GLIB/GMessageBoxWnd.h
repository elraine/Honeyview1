#pragma once


#define		GMB_TIMER		0x00000001									// Ÿ�̸� ���̾˷α� �ڽ�.
#define		GMB_ALARM		0x00000002									// �˶� �ڽ�..


class GDocker;
class GDib;
class GMessageBoxWnd;

int GMessageBox(CWnd* pParentWnd, CString sMsg, CString sCaption="~~", UINT uType=MB_OK, UINT uTypeEx=0, int nExParam=0);
int GAlaramBox(CWnd* pParentWnd, CString sMsg, CString sCaption="~~", UINT uType=MB_OK, int nExParam=0);


HWND 	GShowAlarmBox(CWnd* pParentWnd, CString sMsg, CString sCaption, int nDuration=0);
void	GHideAlarmBox(HWND hWnd);


class GMessageBoxWnd : public CWnd
{
public:
	GMessageBoxWnd();
	BOOL		Create(CWnd* pParentWnd, CString sMsg, CString sCaption="~~", UINT uType=MB_OK, UINT uTypeEx=0, int nExParam=0);
	int			DoModal();

public :															// ����� ���� ���� �Ӽ� 
	static int		m_nIconResourceID;								// ������ ���ҽ� id
	static COLORREF m_clrCaption;									// ĸ�� �ؽ�Ʈ �� 
	static COLORREF m_clrCaptionStart;								// ĸ�� �׶��̼� ����
	static COLORREF m_clrCaptionEnd;								// ĸ�� �׶��̼� ��
	static COLORREF m_clrCaption_p;
	static COLORREF m_clrCaptionStart_p;
	static COLORREF m_clrCaptionEnd_p;
	static CString	m_sDefaultCaption;
	static void		ChangeCaptionColorToPurple();					// ĸ�ǻ� �ٲٱ�

private :
	HWND		m_hWndParent;
	CString		m_sCaption;
	CString		m_sMsg;
	UINT		m_uType;
	UINT		m_uTypeEx;
	GDocker*	m_pDocker;
	GDib*		m_pDibTitle;
	CFont		m_font;
	int			m_nCount;

private :
	CButton		m_btnOK;
	CButton		m_btnCancel;
	CButton		m_stFrm;
	CStatic		m_stIcn;
	CStatic		m_stMsg;
	CStatic		m_stTtl;

private :
	void		CreateTltleBar();
	void		ResizeWnd();
	void		CreateControl();
	int			RunModalLoop();
	void		SetMessageText();

private :
	void		OnOK();
	void		OnCancel();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GMessageBoxWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~GMessageBoxWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(GMessageBoxWnd)
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnGMessageBoxClose(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

