
// ServerMgrDlg.h : ͷ�ļ�
//

#pragma once


// CServerMgrDlg �Ի���
class CServerMgrDlg : public CDialogEx
{
// ����
public:
	CServerMgrDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVERMGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//���
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam,LPARAM lParam);//����ͼ��ص�����
	afx_msg void OnClose();
	afx_msg LRESULT OnTaskBarCreated(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuShow();
	BOOL InstallIcons();
	afx_msg void OnAppExit();
	afx_msg void CheckRegister();
	DECLARE_MESSAGE_MAP()
private:
	// ����ͼ��ṹ
	NOTIFYICONDATA nid;
	// �Ҽ��˵�
	CMenu *pMenuContext;
	CMenu menu;
	bool appExist;
    CString installDir;
    bool localDatabase;
public:
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnMenuServerStart();
	afx_msg void OnMenuServerStop();
	afx_msg void OnMenuDataStart();
	afx_msg void OnMenuDataStop();
protected:
	// ���ø��ؼ��ĳ�ʼ��״̬
	void InitItemState(void);
public:
	void CheckService(void);
private:
	SC_HANDLE hSCM;
	LPSERVICE_STATUS returnstatus;
	// ������ϵͳ����
	SC_HANDLE sService;
	// ���ݿ�ϵͳ����
	SC_HANDLE dService;
	bool bServerStart,bDataStart;

	void statusChange_ServerRun(void);
	void statusChange_ServerStop(void);
	void statusChange_DataRun(void);
	void statusChange_DataStop(void);
};
