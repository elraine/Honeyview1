#include "stdafx.h"
#include "GDocker.h"
#include "Gutil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define		DEFAULT_DOCKING_GAP			15					// �鷯 ���� �Ÿ�.
#define		TIMERID_DOCKER				9999				// Ÿ�̸� ó����.
#define		TIMERELAPSE_DOCKER			10

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GDocker::GDocker()
{
	m_bCaptured = false;
	m_pWndToDock = NULL;
	m_pWnd = NULL;
	m_bDockedToWindow = false;
	m_nDockingGap = DEFAULT_DOCKING_GAP;
	m_bInit = false;
}

GDocker::~GDocker()
{

}

//////////////////////////////////////////////////////////////////////
//
//	PUBLIC CLASSES
//
//////////////////////////////////////////////////////////////////////

/* �ʱ�ȭ */
void GDocker::Create(CWnd *pWnd, CWnd *pWndToDock)
{
	m_pWndToDock = pWndToDock;
	m_pWnd = pWnd;
	m_bInit = true;

	if(m_pWndToDock) 
	{
		pWnd->SetTimer(TIMERID_DOCKER,TIMERELAPSE_DOCKER,NULL);
		CheckDockAtStart();
	}
}

/* Ŭ���̾�Ʈ ���� ���콺 ó���� */
void GDocker::OnLButtonDown()
{
	if(m_bInit==false) ASSERT(0);
	CPoint	point;
	GetCursorPos(&point);
	m_bCaptured = true;
	m_pntOld = point;
	m_pWnd->GetWindowRect(m_rWindow);
	m_pWnd->SetCapture();
}


bool IsMaxmized(HWND hWnd)
{
	WINDOWPLACEMENT wndpl;
	wndpl.length = sizeof(WINDOWPLACEMENT);
	if(GetWindowPlacement(hWnd, &wndpl)==FALSE) return false;
	if(wndpl.showCmd==SW_SHOWMAXIMIZED) return true;
	return false;
}

/* ĸ�� ���� ���콺 Ŭ���� ó���� */
void GDocker::OnNcLButtonDown(UINT nHitTest)
{
	if(m_bInit==false) ASSERT(0);

	if(IsMaxmized(m_pWnd->m_hWnd)) return;
	
	if(nHitTest!=HTCAPTION) return;
	CPoint	point;
	GetCursorPos(&point);
	m_bCaptured = true;
	m_pntOld = point;
	m_pWnd->GetWindowRect(m_rWindow);
	m_pWnd->SetCapture();
}

/* ���콺 �����϶� ��� */
void GDocker::OnMouseMove()
{
	if(m_bInit==false) ASSERT(0);
	if(m_bCaptured==false) return;
	CPoint	point;
	CPoint	pntNew;
	GetCursorPos(&point);

	m_rWindow = m_rWindow + (point - m_pntOld);
	DockMove();
	m_pntOld = point;
}

/* ������ */
void GDocker::OnLButtonUp()
{
	if(m_bInit==false) ASSERT(0);
	m_bCaptured = false;
	ReleaseCapture();
}

/* �ٸ� �����쿡 ������� �� �����찡 �����̸� ���� �ٴѴ�. */
void GDocker::OnTimer(UINT nIDEvent) 
{
	if(m_bInit==false) ASSERT(0);
	if(nIDEvent!=TIMERID_DOCKER) return;
	if(m_pWndToDock==NULL) return;
	if(m_bDockedToWindow==false) return;
	if(m_bCaptured) return;


	CRect r;

	m_pWnd->GetWindowRect(r);
	// ���� �������� ����� ��ȭ�� �־��� ��� - �鷯������ ������ //
	if(r.Width()!=m_rWindow.Width() || r.Height()!=m_rWindow.Height())
	{
		m_bDockedToWindow = false;
		return;
	}

	if(m_pWndToDock->IsIconic()) return;								// �̴ϸ�����Ǿ��� ���....
	m_pWndToDock->GetWindowRect(r);

	// �鷯���� �����찡 �������� ��� - �m�Ƽ� �����δ� //
	if(r!=m_rWindowToDock)
	{
		CPoint pntNew=CPoint(0,0);											// ��ȭ��
		// (������ - ����) ��ȭ���� ���ش�..
		if(m_bDockToLeftOfWindow && m_rWindowToDock.left!=r.left) 
		{
			pntNew.x = -( m_rWindowToDock.left - r.left) ;
		}
		if(m_bDockToTopOfWindow && m_rWindowToDock.top!=r.top)
		{
			pntNew.y = -( m_rWindowToDock.top  - r.top ) ;
		}
		if(m_bDockToLeftOfWindow==false && m_rWindowToDock.right!=r.right)	// ������ �پ� �����鼭 ������ ��ȭ�� ����
		{
			pntNew.x =  - (m_rWindowToDock.right-r.right) ;
		}
		if(m_bDockToTopOfWindow==false && m_rWindowToDock.bottom!=r.bottom)
		{
			pntNew.y =  - (m_rWindowToDock.bottom-r.bottom);
		}

		m_pWnd->GetWindowRect(m_rWindow);
		m_rWindow = m_rWindow + pntNew;
		m_pWnd->MoveWindow(m_rWindow);
		DockMove();															// ������ �پ� �ִ����� üũ�Ѵ�.

		m_rWindowToDock = r;
	}
}

/* app ���۽� �����찡 parent �� �پ� �ִ��� üũ�� �ش�. */
void GDocker::CheckDockAtStart()
{
	if(m_pWndToDock==NULL) return;

	m_pWnd->GetWindowRect(m_rWindow);
	DockMove();
}

//////////////////////////////////////////////////////////////////////
//
//	PRIVATE CLASSES
//
//////////////////////////////////////////////////////////////////////
void GDocker::DockMove()
{
	CPoint	pntNew;

	int x,y;
	int x1, y1, x2, y2;
	bool	bDock1, bDock2;
	int w = m_rWindow.Width();							// ���� �������� ���� ����
	int h = m_rWindow.Height();			

	x = m_rWindow.left;									// ���� �������� ��/��� ��ǥ (ȭ����� ��ǥ�� �ǹ������� �ʴ´�.)
	y = m_rWindow.top;

	x2 = x1 = x;
	y2 = y1 = y;

	m_bDockedToWindow = false;

	// ���� �ٳ� üũ�ϱ� //
	bDock1 = CheckDockToScreen(x1,y1,w,h);

	// �����쿡 �ٳ� üũ�ϱ� //
	bDock2 = CheckDockToWindow(x2,y2,w,h);				// �ٸ� �����쿡 �ٿ� �ֱ�.


	if(bDock1 && bDock2)								// ���� ������ �Ѵ� ������ ���� ���
	{
		int tempx, tempy;
		tempx = x2;										// �ٸ� �����쿡 �ٴ� ��ǥ
		tempy = y2;
		if(CheckDockToScreen(tempx, tempy, w, h))		// ������ �ٰ� �����쿡�� ���� �������� �������.
		{
			x = x2;
			y = y2;
			m_bDockedToWindow = true;
		}
		else
		{
			int d1, d2;
			/* ���� �������� ����� �Ÿ��� ã�´�. */
			d1 = (x-x1)*(x-x1) + (y-y1)*(y-y1);			// ������ �Ÿ�
			d2 = (x-x2)*(x-x2) + (y-y2)*(y-y2);			// ������ ���� �Ÿ�

			/* ���� ����� ��ġ�� �̵��Ѵ� */
			if(d1 < d2 )			
			{
				x = x1;
				y = y1;
				m_bDockedToWindow = false;
			}
			else
			{
				x = x2;
				y = y2;
				m_bDockedToWindow = true;
			}
		}
	}
	else if(bDock1)										// ������ �������
	{
		x = x1;
		y = y1;
		m_bDockedToWindow = false;
	}
	else if(bDock2)										// �����쿡�� ���� ���.
	{
		x = x2;
		y = y2;
		m_bDockedToWindow = true;
	}

	// ���ο� ��ġ�� �ű�� //
	m_pWnd->MoveWindow(x, y, m_rWindow.Width(), m_rWindow.Height());
}


/* ���� ȭ�� �۾� ���� ��� ���� */
void _GetWorkArea(CRect& r)
{
	SystemParametersInfo(SPI_GETWORKAREA,NULL,&r,0);
}

/* ���� �ٳ� üũ�ϱ� */
bool GDocker::CheckDockToScreen(int &x, int &y, int w, int h)
{
	CRect r;
	_GetWorkArea(r);
	int sx = r.left;
	int sy = r.top;
	int sr = r.right;
	int sb = r.bottom;
	bool bRet=false;

	if(abs(x-sx)    < m_nDockingGap){x=sx  ;bRet=true;}			// ȭ�� �´�
	if(abs(y-sy)    < m_nDockingGap){y=sy  ;bRet=true;}			// ȭ�� ���
	if(abs(x+w - sr)< m_nDockingGap){x=sr-w;bRet=true;}			// ȭ�� ����
	if(abs(y+h - sb)< m_nDockingGap){y=sb-h;bRet=true;}			// ȭ�� �ϴ�.

	return bRet;
}

/* �ٸ� �����쿡 ������� ó���ϱ� */
bool GDocker::CheckDockToWindow(int &x, int &y, int w, int h)
{
	bool bRet=false;
	if(m_pWndToDock==NULL)
	{
		m_bDockedToWindow = false;
		return bRet;
	}

	CRect	rDockWnd;

	m_pWndToDock->GetWindowRect(rDockWnd);

	int ox, oy;
	int dx = rDockWnd.left;
	int dy = rDockWnd.top;
	int dw = rDockWnd.Width();
	int dh = rDockWnd.Height();

	ox = x;
	oy = y;

	m_bDockToLeftOfWindow = true;
	m_bDockToTopOfWindow = true;

	if((dy-m_nDockingGap<y+h && y<dy+dh+m_nDockingGap) && abs(dx+dw-x ) < m_nDockingGap) {x= dx+dw;bRet=true;m_bDockToLeftOfWindow=false;}	// ���� ���̱�
	if((dy-m_nDockingGap<y+h && y<dy+dh+m_nDockingGap) && abs(dx-(x+w)) < m_nDockingGap) {x= dx- w;bRet=true;m_bDockToLeftOfWindow=true; }	// ���� ���̱�
 	if((dx-m_nDockingGap<x+w && x<dx+dw+m_nDockingGap) && abs(dy+dh-y ) < m_nDockingGap) {y= dy+dh;bRet=true;m_bDockToTopOfWindow=false;}	// �ϴ� ���̱�
	if((dx-m_nDockingGap<x+w && x<dx+dw+m_nDockingGap) && abs(dy-(y+h)) < m_nDockingGap) {y= dy- h;bRet=true;m_bDockToTopOfWindow=true; }	// ��� ���̱�

	if(bRet)				// ���� ��/��/��/�� ������ �پ� �ִ� ��Ȳ�̶��..
	{
		x = ( abs(x+w-(dx+dw)) < m_nDockingGap ) ? dx+dw-w : x;		// ������ ����
		x = ( abs(x - dx     ) < m_nDockingGap ) ? dx      : x;		// ������ ����
		y = ( abs(y+h-(dy+dh)) < m_nDockingGap ) ? dy+dh-h : y;		// �ϴܼ� ����
		y = ( abs(y - dy     ) < m_nDockingGap ) ? dy      : y;		// ��ܼ� ����
	}

	m_rWindowToDock = rDockWnd;

	return bRet;
}

