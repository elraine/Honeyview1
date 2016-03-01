// Docker.h: interface for the GDocker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCKER_H__7C0C22A9_4F23_4086_9087_40A26809571F__INCLUDED_)
#define AFX_DOCKER_H__7C0C22A9_4F23_4086_9087_40A26809571F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////////////////////////////////////////////
//
// GDocker 
//	- �����츦 �鷯�ٰ� ������ִ� Ŭ����.
//	- ���� �ۼ��� : 1999/12/14 by hong
//	- ���� ��Ʈ
//		99/12/16 : �ʱ�ȭ ������ ��� ASSERT�ϱ� �߰�.
//		99/12/27 : �����쿡 �鷯������ ���� ����, math �Լ� ������. 
//		00/02/23 : ���� �����쿡 ���ÿ� �ٴ� ��� ó���� ����� ��. 
//					& �ٸ� �����쿡 �鷯 ������ ����� �i�ư��� ���ϴ� ���� �ذ�
//		00/02/26 : �ٸ� �����쿡 �鷯������ ���� �ذ�...
//		00/03/15 : CheckDockAtStart() �߰� .
//
//	- ���� 
//		. CWnd �� ����μ� GDocker �� ����ִ´�.
//		. Create�� ȣ���ϸ鼭  this �� �鷯 �ٰ� ���� �������� �����͸� �ѱ��.
//		. OnLButtonDown() / OnNcLButtonDown() / OnMouseMove() / 
//		  OnLButtonUp() / OnTimer() ���� ȣ���Ѵ�.
//		. OnLButtonDown() �� ȣ���ϸ� Ŭ���̾�Ʈ ������ �������� ������ �̵��� �����ϸ�.
//		. OnNcLButtonDown() �� ȣ���ϸ� ĸ�� ������ ��� �̵��ÿ� ������ �̵��� ó���ȴ�.
//		. OnTimer() �� �ٸ� �����쿡 �鷯 ���� ��쿡�� ȣ���Ͽ� �ָ� �ȴ�.
//
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************
******************************* ��뿹 *****************************************

BOOL CDockingWnd::Create(CWnd* pWndToDock)
{
	...
	...
  	m_docker.Create(this,pWndToDock);
	...
	...
}

// Ŭ���̾�Ʈ ���� �巡�� ó���� //
void CDockingWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_docker.OnLButtonDown(nFlags, point);
}
void CDockingWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_docker.OnMouseMove();
}
void CDockingWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_docker.OnLButtonUp();
}
// ĸ�� ���� �巡�� ó���� //
void CDockingWnd::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	m_docker.OnNcLButtonDown(nHitTest);
}
// �ٸ� �����쿡 �鷯 ���� ��� ó�� //
void CDockingWnd::OnTimer(UINT nIDEvent) 
{
	m_docker.OnTimer(nIDEvent);
}

*******************************************************************************
*******************************************************************************/


class GDocker  
{
public :
	void				Create(CWnd* pWnd, CWnd* pWndToDock=NULL);
	void				SetDockingGap(int nDockingGap) { m_nDockingGap = nDockingGap; }		// �鷯 ���� �Ÿ� ����.

public :
	void				OnLButtonDown();
	void				OnNcLButtonDown(UINT nHitTest);
	void				OnMouseMove();
	void				OnLButtonUp();
	void				OnTimer(UINT nIDEvent);
	void				CheckDockAtStart();									

private :
	bool				m_bCaptured;
	bool				m_bDockedToWindow;
	bool				m_bDockToLeftOfWindow;											// m_bDockedToWindow �� true �ϰ�� left �ΰ� �ƴϸ� right �ΰ�?
	bool				m_bDockToTopOfWindow;											// m_bDockedToWindow �� true �ϰ�� top  �ΰ� �ƴϸ� bottom �ΰ�?
	CPoint				m_pntOld;
	CRect				m_rWindow;
	CRect				m_rWindowToDock;
	CWnd*				m_pWndToDock;
	CWnd*				m_pWnd;
	int					m_nDockingGap;
	bool				m_bInit;

private :
	void				DockMove();
	bool				CheckDockToScreen(int &x, int &y, int w, int h);
	bool				CheckDockToWindow(int &x, int &y, int w, int h);

public:
	GDocker();
	virtual ~GDocker();

};

#endif // !defined(AFX_DOCKER_H__7C0C22A9_4F23_4086_9087_40A26809571F__INCLUDED_)
