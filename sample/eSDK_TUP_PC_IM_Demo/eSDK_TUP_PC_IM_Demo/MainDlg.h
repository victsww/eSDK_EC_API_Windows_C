/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "EntAddrDlg.h"
#include "ContactDlg.h"
#include "IMDlg.h"


// CMainDlg �Ի���

class CMainDlg : public CDialog,public CUserQueryHelper
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonEntaddr();
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickMainMenuItem(UINT nID);
	afx_msg LRESULT OnMenuSendIM(WPARAM,LPARAM);
	afx_msg LRESULT OnMenuGroupSendMsg(WPARAM,LPARAM);
	afx_msg LRESULT OnCloseIMWnd(WPARAM,LPARAM);
	afx_msg LRESULT OnRecvIM(WPARAM,LPARAM);
	afx_msg LRESULT OnUpdateConatct(WPARAM,LPARAM);
	afx_msg LRESULT OnCloseEntAddrDlg(WPARAM,LPARAM);
	afx_msg LRESULT OnDispatchMessage(WPARAM,LPARAM);
	afx_msg LRESULT OnGroupNotify(WPARAM,LPARAM);
	afx_msg LRESULT OnKickOutUser(WPARAM, LPARAM);
	afx_msg void OnCbnSelchangeComboStatus();
	DECLARE_MESSAGE_MAP()

protected:
	CString GetCurLoginAccount(void)const {return m_cstrLoginAccount;}
	void RefreshControl(void);	
	void Logout(void);
	void ShowSetDlg(void);
	int GetCurStatus() const;

public:
	void SetLoginFlag(bool);
	void SetCurLoginAccount(CString&);

private:
	CStatic m_stcUserName;
	CEdit m_editSearch;
	CTabCtrl m_tabMainWnd;	
	CEdit m_edtSign;
	CButton m_btnSysMenu;
	CButton m_btnEntAddr;
	CImageStatic m_stcHead;
	bool m_bLoginFlag;
	CString m_cstrLoginAccount;
	CEntAddrDlg *m_pEntAddDlg;
	CContactDlg *m_pContactDlg;
public:
	afx_msg void OnKillfocusEditSigntrue();
};
