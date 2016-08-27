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

// CallSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "CallSetDlg.h"


// CCallSetDlg �Ի���

IMPLEMENT_DYNAMIC(CCallSetDlg, CDialog)

CCallSetDlg::CCallSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCallSetDlg::IDD, pParent)
{

}

CCallSetDlg::~CCallSetDlg()
{
}

void CCallSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCallSetDlg, CDialog)
END_MESSAGE_MAP()


// CCallSetDlg ��Ϣ��������