
// CFileDlg.h : ͷ�ļ�
//

#pragma once


// CCFileDlg �Ի���
class CCFileDlg : public CDialogEx
{
// ����
public:
	CCFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CFILE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	afx_msg void OnBnClickedWrite();
	afx_msg void OnBnClickedRead();
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	

	CString m_strName;
	CString m_strWrite;
	CString m_strRead;

public:

};
