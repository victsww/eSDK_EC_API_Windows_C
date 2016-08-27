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


// TUPSDKPCDemo.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "TUPSDKPCDemo_i.h"


// CTUPSDKPCDemoApp:
// 有关此类的实现，请参阅 TUPSDKPCDemo.cpp
//

class CTUPSDKPCDemoApp : public CWinApp
{
public:
	CTUPSDKPCDemoApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
public:
	CWnd* m_pMainDlgWnd;
	CWnd* m_pLoginDlgWnd;
	BOOL ExitInstance(void);
};

extern CTUPSDKPCDemoApp theApp;