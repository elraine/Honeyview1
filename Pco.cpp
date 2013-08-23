#include "stdafx.h"
#include "Pco.h"
#include "GUTIl.h"

CPco::CPco()
{

}

CPco::~CPco()
{

}


bool CPco::ReadHeader(CString sFileName)
{
	FILE* fp;

	m_sFileName = sFileName;

	fp = fopen(m_sFileName, "rb");

	if(fp==NULL) 
		return false;


	char* p = (char*)&m_head;

	memset(p, 0, sizeof(PCOHead));

	fread(p,	1, sizeof(int), fp);							// dummy �б�
	p+= sizeof(int);
	fread(p,	1, sizeof(char),  fp);							// ���� len �б�
	p+= sizeof(char);
	fread(p,	1, m_head.title_len,  fp);						// ����  �б�
	p+= LEN_TITLE;
	fread(p,	1, sizeof(int),  fp);							// image count;
	p+= sizeof(int);

	m_head.nHeaderSize = 4+1+m_head.title_len+4			// n0, title_len, title, image_count, 
		+ m_head.image_count * sizeof(PCOFileInfo);
	p+= sizeof(int);

	if(m_head.image_count >=MAX_INFO)							// �׸��� �ʹ� ���ų� �Ƹ��� �ջ�� ����
	{
		fclose(fp);
		return false;
	}

	for(int i=0;i<m_head.image_count;i++)
	{
		fread(p,	1, sizeof(PCOFileInfo),  fp);						// info
		m_head.info[i].pos += m_head.nHeaderSize;						// ���� ��ġ ����
		p+= sizeof(PCOFileInfo);
	}

	fclose(fp);

	if(GetFileSize(m_sFileName) <= min(m_head.nHeaderSize, 4+1+4))
		return false;											// �ջ�� ���..

	return true;

}


bool CPco::GetFileInfo(int nFilePos, PCOFileInfo& info)
{
	if(nFilePos<0 || nFilePos >= m_head.image_count) return false;

	info = m_head.info[nFilePos];
	return true;

}