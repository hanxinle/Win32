
// CFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CFile.h"
#include "CFileDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCFileDlg �Ի���



CCFileDlg::CCFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CFILE_DIALOG, pParent)
{
	m_strName = _T("");
	m_strWrite = _T("");
	m_strRead = _T("");

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CCFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILE_NAME, m_strName);
	DDX_Text(pDX, IDC_READ, m_strRead);
	DDX_Text(pDX, IDC_WRITE, m_strWrite);

}

BEGIN_MESSAGE_MAP(CCFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_READ, &CCFileDlg::OnBnClickedRead)
	ON_BN_CLICKED(ID_WRITE, &CCFileDlg::OnBnClickedWrite)
END_MESSAGE_MAP()


// CCFileDlg ��Ϣ�������

BOOL CCFileDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCFileDlg::OnPaint()
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
HCURSOR CCFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CCFileDlg::OnBnClickedRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);   //get data in edit control
	m_strName.TrimLeft();
	m_strName.TrimRight();
	
	if (m_strName.GetLength() == 0) { MessageBox(_T("No file !")); }
	else {
		CFile myfile(m_strName, CFile::modeRead);
		char * szBuff;
		UINT length = myfile.GetLength();
		szBuff = new char[length + 1];
		szBuff[length] = 0;
		myfile.Read(szBuff, length);
		myfile.Close();
		m_strRead.Format(_T("%s"), szBuff);
		UpdateData(FALSE);
	}

}


void CCFileDlg::OnBnClickedWrite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);   //get data in edit control

	m_strName.TrimLeft();
	m_strName.TrimRight();

	if (m_strName.GetLength() == 0) { MessageBox(_T("No file !")); }
	else {
		CFile myfile(m_strName, CFile::modeCreate | CFile::modeWrite);
		myfile.Write(m_strWrite, m_strWrite.GetLength());
		myfile.Close();
	}
	m_strWrite = "";
	UpdateData(FALSE);
}
