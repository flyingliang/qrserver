
// ServerMgr.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ServerMgr.h"
#include "ServerMgrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 const CString strClassName("DQS_Server_Manager");
 HANDLE m_hMutex; //ȫ��

// CServerMgrApp

BEGIN_MESSAGE_MAP(CServerMgrApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

  
 
// CServerMgrApp ����

CServerMgrApp::CServerMgrApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CServerMgrApp ����

CServerMgrApp theApp;


// CServerMgrApp ��ʼ��

BOOL CServerMgrApp::InitInstance()
{
	
  m_hMutex=OpenMutex(MUTEX_ALL_ACCESS,FALSE,strClassName);
  if (m_hMutex==NULL)
  {//��ʾû������ʵ��������.����
      m_hMutex=CreateMutex(NULL,TRUE,strClassName);
  }else
  {//��ʾ�Ѿ���һ��ʵ��������
      MessageBox(NULL,_T("����̨�Ѿ�������"),_T("������"),MB_OK|MB_ICONWARNING);
    //��������
    return FALSE;
  }

  CWinApp::InitInstance();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("DQS����ƽ̨���й�����"));

	CServerMgrDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

