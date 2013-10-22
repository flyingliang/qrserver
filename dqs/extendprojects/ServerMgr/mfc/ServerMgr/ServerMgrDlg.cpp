
// ServerMgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerMgr.h"
#include "ServerMgrDlg.h"
//#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const UINT WM_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CServerMgrDlg �Ի���

#define WM_NOTIFYICON (WM_USER +101)

CServerMgrDlg::CServerMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerMgrDlg::IDD, pParent)
	, pMenuContext(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerMgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//add
	ON_MESSAGE (WM_NOTIFYICON ,&OnNotifyIcon)
	ON_WM_CLOSE()
	ON_REGISTERED_MESSAGE(WM_TASKBARCREATED,OnTaskBarCreated)
	ON_COMMAND(ID_MENU_APP_EXIT, &CServerMgrDlg::OnAppExit)
	ON_BN_CLICKED(IDC_BUTTON11, &CServerMgrDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CServerMgrDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CServerMgrDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON21, &CServerMgrDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CServerMgrDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &CServerMgrDlg::OnBnClickedButton23)
	ON_COMMAND(ID_MENU_SERVER_START, &CServerMgrDlg::OnMenuServerStart)
	ON_COMMAND(ID_MENU_SERVER_STOP, &CServerMgrDlg::OnMenuServerStop)
	ON_COMMAND(ID_MENU_DATA_START, &CServerMgrDlg::OnMenuDataStart)
	ON_COMMAND(ID_MENU_DATA_STOP, &CServerMgrDlg::OnMenuDataStop)
END_MESSAGE_MAP()


#define WM_NOTIFYICON (WM_USER +101)
// CServerMgrDlg ��Ϣ�������

BOOL CServerMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//���ע���
	CheckRegister();
	//���ϵͳ����
	if(appExist==true)
	{
		CheckService();
	}

	//��ʼ�������Ҽ��˵�
	menu.LoadMenu(IDR_MENU_CONTEXT);
	pMenuContext = menu.GetSubMenu(0);
	
	//��ʼ��״̬
	InitItemState();

	//���ϵͳ����ͼ��
	InstallIcons();
	 

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CServerMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerMgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServerMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���
LRESULT CServerMgrDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)//����lParam�ж����Ӧ���¼�
	{
	case WM_LBUTTONDBLCLK://������˫������ͼ��,����ʾ����
		ShowWindow(SW_SHOWNORMAL );
		SetForegroundWindow();
		break;
	case WM_RBUTTONUP://����Ҽ��˵�����,�򵯳��˵�
		CPoint pos;
		GetCursorPos(&pos);
		if(pMenuContext != NULL)
		{
			SetForegroundWindow();
			pMenuContext->TrackPopupMenu(TPM_RIGHTBUTTON|TPM_RIGHTALIGN,pos.x+1,pos.y+1,this);
		}
		break;
	}
	return 0;
}
void CServerMgrDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_INFO;
	wcscpy(nid.szTip, L"DQSƽ̨������");
	wcscpy(nid.szInfo, L"��������������.");
	wcscpy(nid.szInfoTitle, L"I'm here");
	Shell_NotifyIcon(NIM_MODIFY,&nid);
	ShowWindow (SW_HIDE);
	//CDialog::OnClose();
}

void CServerMgrDlg::OnMenuShow()
{
	// TODO: �ڴ���������������
	if(IsWindowVisible ())
		ShowWindow(SW_HIDE );
	else
		ShowWindow(SW_SHOWNORMAL );
}

BOOL CServerMgrDlg::InstallIcons()
{
	//��������ͼ��
	nid.cbSize =sizeof(NOTIFYICONDATA);
	nid.hWnd =m_hWnd;
	nid.uID = 0;
	nid.hIcon =m_hIcon;
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nid.uCallbackMessage =WM_NOTIFYICON;
	wcscpy(nid.szTip, L"DQSƽ̨������");
	//wcscpy(nid.szInfo, L"������������");
	//wcscpy(nid.szInfoTitle, L"I'm here");
	nid.dwInfoFlags = NIIF_INFO;
	nid.uTimeout = 1000;
	nid.uVersion = NOTIFYICON_VERSION;
	//���ϵͳ����ͼ��
	return (Shell_NotifyIcon(NIM_ADD,&nid));
}

LRESULT CServerMgrDlg::OnTaskBarCreated(WPARAM wParam, LPARAM lParam)
{
	VERIFY(InstallIcons());
    return 0;
}

//�����˳�
void CServerMgrDlg::OnAppExit()
{
	// TODO: �ڴ���������������
	::Shell_NotifyIcon (NIM_DELETE ,&nid);
	PostMessage(WM_CLOSE);
	exit(0);
}

void CServerMgrDlg::CheckRegister()
{
	 CRegKey reg;       //����һ��CRegKey����
     CString key("software\\DqsServer");
	 LONG result=reg.Open(HKEY_LOCAL_MACHINE,key,KEY_READ);
	 if (ERROR_SUCCESS !=result)
	 {
		// MessageBox(_T("ע����ʧ��"));
		 appExist=false;
	 }else{
		 appExist=true;
			 
		 LPTSTR dir;
         DWORD pCount=1024;
         if(reg.QueryStringValue(_T("installDir"),dir,&pCount)==ERROR_SUCCESS)
	     {
				 installDir=dir;
		 }else{
			 installDir=CString("C:\\Program Files\\dqs");
		 }

		 DWORD database;
		 if(reg.QueryDWORDValue(_T("database"),database)==ERROR_SUCCESS)
		 {
		   if (database==1)
		   {
			   localDatabase=true;
		   }else{
			   localDatabase=false;
		   }
		 }else{
			 localDatabase=false;
		   }
	 }

	 reg.Close();
}




void CServerMgrDlg::OnBnClickedButton11()
{
	
	 if(StartService(sService,0,NULL))
	 {
		 statusChange_ServerRun();
		 bServerStart=true;
	 }
}


void CServerMgrDlg::OnBnClickedButton12()
{
	 if(ControlService(sService,SERVICE_CONTROL_STOP,returnstatus))
	 {
		 statusChange_ServerStop();
		 bServerStart=false;
	 }
}


void CServerMgrDlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CServerMgrDlg::OnBnClickedButton21()
{
	if(StartService(dService,0,NULL))
	 {
		 statusChange_DataRun();
		 bDataStart=true;
	 }
}


void CServerMgrDlg::OnBnClickedButton22()
{
	if(ControlService(dService,SERVICE_CONTROL_STOP,returnstatus))
	 {
		 statusChange_DataStop();
		 bDataStart=false;
	 }
}


void CServerMgrDlg::OnBnClickedButton23()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CServerMgrDlg::OnMenuServerStart()
{
	// TODO: �ڴ���������������
}


void CServerMgrDlg::OnMenuServerStop()
{
	// TODO: �ڴ���������������
}


void CServerMgrDlg::OnMenuDataStart()
{
	// TODO: �ڴ���������������
}


void CServerMgrDlg::OnMenuDataStop()
{
	// TODO: �ڴ���������������
}


// ���ø��ؼ��ĳ�ʼ��״̬
void CServerMgrDlg::InitItemState()
{
	if(appExist==false)
	{
		
		GetDlgItem(IDC_GROUP1)->EnableWindow(FALSE);
		GetDlgItem(IDC_GROUP2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON12)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON13)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON21)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON22)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON23)->EnableWindow(FALSE);
		pMenuContext->EnableMenuItem(ID_MENU_SERVER_START,MF_GRAYED);//MF_BYCOMMAND | MF_DISABLED | MF_GRAYED
		pMenuContext->EnableMenuItem(ID_MENU_SERVER_STOP,MF_GRAYED);
		pMenuContext->EnableMenuItem(ID_MENU_DATA_START,MF_GRAYED);
		pMenuContext->EnableMenuItem(ID_MENU_DATA_STOP,MF_GRAYED);
	}else{
		
		if(bServerStart==true){
			statusChange_ServerRun();
		}else{
			statusChange_ServerStop();
		}
		if(bDataStart==true){
			statusChange_DataRun();
		}else{
			statusChange_DataStop();
		}
		
		//�ޱ������ݿ�
		if(localDatabase==false)
		{
			GetDlgItem(IDC_GROUP2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON21)->EnableWindow(FALSE);
		    GetDlgItem(IDC_BUTTON22)->EnableWindow(FALSE);
		    GetDlgItem(IDC_BUTTON23)->EnableWindow(FALSE);
			pMenuContext->EnableMenuItem(ID_MENU_DATA_START,MF_GRAYED);
		    pMenuContext->EnableMenuItem(ID_MENU_DATA_STOP,MF_GRAYED);
		}
	}

}


void CServerMgrDlg::CheckService()
{
	 
	 hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	 sService=OpenService(hSCM,_T("DQS_Server"),SERVICE_ALL_ACCESS);
	 dService=OpenService(hSCM,_T("DQS_MongoDB"),SERVICE_ALL_ACCESS);

	 if(sService!=NULL)
	 {
		 QueryServiceStatus(sService,returnstatus);
	     if(returnstatus->dwCurrentState==SERVICE_RUNNING)
	     {
		   bServerStart=true;
	      }else{
		   bServerStart=false;
	      }
	 }else
	 {
		  bServerStart=false;
	 }

	 if(dService!=NULL)
	 {
	    QueryServiceStatus(dService,returnstatus);
	    if(returnstatus->dwCurrentState==SERVICE_RUNNING)
	    {
		   bDataStart=true;
	     }else{
		   bDataStart=false;
	   }
	 }
	 else
	 {
		 bDataStart=false;
	 }
	 //::CloseHandle(hSCM);
}


void CServerMgrDlg::statusChange_ServerRun(void)
{
	
	GetDlgItem(IDC_LABLE1)->SetWindowText(_T("Runing"));
	GetDlgItem(IDC_BUTTON11)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(TRUE);
}


void CServerMgrDlg::statusChange_ServerStop(void)
{
	GetDlgItem(IDC_LABLE1)->SetWindowText(_T("Stop"));
	GetDlgItem(IDC_BUTTON11)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON12)->EnableWindow(FALSE);
}


void CServerMgrDlg::statusChange_DataRun(void)
{
	GetDlgItem(IDC_LABLE2)->SetWindowText(_T("Runing"));
	GetDlgItem(IDC_BUTTON21)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON22)->EnableWindow(TRUE);
}


void CServerMgrDlg::statusChange_DataStop(void)
{
	GetDlgItem(IDC_LABLE2)->SetWindowText(_T("Stop"));
	SetDlgItemText(IDC_LABLE2,_T("Stop"));
	GetDlgItem(IDC_BUTTON21)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON22)->EnableWindow(FALSE);
}
