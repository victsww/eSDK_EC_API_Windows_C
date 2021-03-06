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
#include "afxcmn.h"
#include "DetailDlg.h"
#include "Data.h"
#include "afxwin.h"

typedef std::map<std::string, IM_E_USER_ONLINESTATUS > UCmMembStatus;

// CContactDlg 对话框

class CContactDlg : public CDialog
{
	DECLARE_DYNAMIC(CContactDlg)

public:
	CContactDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CContactDlg();

// 对话框数据
	enum { IDD = IDD_CONTACT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnNMDblclkTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickPriGroupMenuItem(UINT nID);
	afx_msg void OnClickPriContactMenuItem(UINT nID);
	afx_msg LRESULT OnUpdateConatct(WPARAM,LPARAM);
	
	DECLARE_MESSAGE_MAP()
public:
	void GetContactList(MAP_GROUP&,MAP_USER_GROUP&,MAP_CONTACT&,MAP_USER&,MAP_IMGROUP&);
	void UpdateContactListContrl(void);
	void AddImage(CImageList& imageList, UINT _id); 
public:
	CTreeCtrl m_treeContact;
	CImageList m_imageList;	
	CButton m_btnAdd;
	typedef std::map<int,TUP_INT64> MENU_GROUP_MAP;
	MENU_GROUP_MAP m_mapGroup;
	bool UpdateConStatus(std::string _account ,IM_E_USER_ONLINESTATUS _status);
	void UpdateLocalMenbStatus();
private:
	UCmMembStatus LocalStatus;

public:
	afx_msg void OnNMClickTreeContact(NMHDR *pNMHDR, LRESULT *pResult);
};

