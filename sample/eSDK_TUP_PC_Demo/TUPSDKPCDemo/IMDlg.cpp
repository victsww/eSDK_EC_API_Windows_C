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

// IMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TUPSDKPCDemo.h"
#include "IMDlg.h"
#include "Tools.h"
#include "IMManage.h"
#include "SelectDlg.h"
#include "NotifyCallBack.h"
#include "LoginDlg.h"
#include "MainDlg.h"
#include "NewCallDlg.h"
#include "ConfDlg.h"

const int WIDTH = 450;
const int HEITH = 550;
const int VIDEO_WIDTH = 700;

const int TOOLWIDTH = 400;
const int IMCONTENTBOTTOM = 418;

enum ImgQuery
{
	IMG_QUERY_ERR, 
	IMG_QUERY_TYPE_LOCAL, 
	IMG_QUERY_TYPE_BUFFER
};

// CIMDlg 对话框

IMPLEMENT_DYNAMIC(CIMDlg, CDialog)

CIMDlg::CIMDlg(CWnd* pParent /*=NULL*/)
: CDialog(CIMDlg::IDD, pParent)
, m_strLoginAccount("")
, m_strLoginName("")
, m_pCallCtrlDlg(NULL)
, m_DlgType(SIGNLE_CHAT)
, m_uiCallID(0)
, m_strGroupID("")
,m_uiConfID(0)
,m_fixGroupChat(false)
,IsVidesponsor(false)
,m_ImagePosition(0)
{

}

CIMDlg::~CIMDlg()
{
	SAFE_DELETE(m_pCallCtrlDlg);
}
void CIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
 	DDX_Control(pDX, IDC_EDIT_RECV_ZONE, m_edtIMContent);
 	DDX_Control(pDX, IDC_EDIT_SEND_CONTENT, m_edtSend);
	DDX_Control(pDX, IDC_STATIC_ACCOUNT, m_stcName);
	DDX_Control(pDX, IDC_STATIC_CALLWND, m_stcCallWnd);
	DDX_Control(pDX, IDC_BUTTON_UNFOLDVIDEO, m_btnUnfold);
	DDX_Control(pDX, IDC_STATIC_REMOTEVIDEO, m_stcRemoteVideo);
	DDX_Control(pDX, IDC_STATIC_REMOTEVIDEO2, m_stcLocalVideo);
	DDX_Control(pDX, IDC_BUTTON_VIDEOCALL, m_btnVideoCall);
	DDX_Control(pDX, IDC_BUTTON_CALL, m_btnCall);
	DDX_Control(pDX, IDC_LIST_MEMBER, m_listMember);
	DDX_Control(pDX, IDC_STATIC_HEAD, m_stcHead);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_BUTTON1, m_DataConfCall);
	DDX_Control(pDX, IDC_EDIT_RECV_ZONE, m_edtIMContent);
}


BEGIN_MESSAGE_MAP(CIMDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CIMDlg::OnBnClickedButtonAddUser)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CIMDlg::OnBnClickedButtonSendIM)
	ON_MESSAGE(WM_MENU_SEND_IM,&CIMDlg::OnSendIMMenuClick)
	ON_MESSAGE(WM_RECV_IM,&CIMDlg::OnRecvIM)
	ON_MESSAGE(WM_HANGUP,&CIMDlg::OnHangUp)
	ON_MESSAGE(WM_CAll_CONNECTED,&CIMDlg::OnCallConnected)
	ON_MESSAGE(WM_CAll_END,&CIMDlg::OnCallEnd)
	ON_MESSAGE(WM_CAll_HOLD,&CIMDlg::OnCallHold)
	ON_MESSAGE(WM_CAll_UNHOLD,&CIMDlg::OnCallUnHold)
	ON_MESSAGE(WM_CALL_MIC_MUTE,&CIMDlg::OnCallMicMute)
	ON_MESSAGE(WM_CALL_MIC_UNMUTE,&CIMDlg::OnCallMicUnMute)
	ON_MESSAGE(WM_CALL_SPK_MUTE,&CIMDlg::OnCallSpkMute)
	ON_MESSAGE(WM_CALL_SPK_UNMUTE,&CIMDlg::OnCallSpkUnMute)
	ON_MESSAGE(WM_CALL_START_REC,&CIMDlg::OnCallStartRec)
	ON_MESSAGE(WM_CALL_END_REC,&CIMDlg::OnCallEndRec)
	ON_MESSAGE(WM_CAll_UNHOLD,&CIMDlg::OnCallUnHold)
	ON_MESSAGE(WM_CALL_BLIND_TRAN,&CIMDlg::OnCallBlindTrans)
	ON_MESSAGE(WM_CALL_BLIND_RESULT,&CIMDlg::OnCallBlindTransResult)
	ON_MESSAGE(WM_CALL_SHOW_WND,&CIMDlg::OnShowVideoWnd)
	ON_MESSAGE(WM_CAll_ADD_VIDEO,&CIMDlg::OnCallAddVideo)
	ON_MESSAGE(WM_CAll_DEL_VIDEO,&CIMDlg::OnCallDelVideo)
	ON_MESSAGE(WM_NET_LEVEL,&CIMDlg::OnNetLevelNotify)
	ON_MESSAGE(WM_NET_INFO,&CIMDlg::OnNetSTATISTIC)
	ON_MESSAGE(WM_GROUP_NOTIFY,&CIMDlg::OnGroupNotify)
	ON_MESSAGE(WM_GROUP_INF_CHANGE,&CIMDlg::OnGroupInfoChange)
	ON_MESSAGE(WM_GROUP_MEM_ADD,&CIMDlg::OnGroupMemAdd)
	ON_MESSAGE(WM_GROUP_MEM_DEL,&CIMDlg::OnGroupMemDel)
	ON_MESSAGE(WM_GROUP_MEM_OWNER,&CIMDlg::OnGroupOwnerChange)
	ON_MESSAGE(WM_CAll_INCMING, &CIMDlg::OnCallComing)//Add by w00321336 for DTS2015010703551 at 2015-1-22
	ON_MESSAGE(WM_CALL_INFOCHANGE,&CIMDlg::OnCallInfoChange)
	ON_MESSAGE(WM_CALL_HOLE_RESULT,&CIMDlg::OnHoldCallResult)
	ON_MESSAGE(WM_CALL_UNHOLE_RESULT,&CIMDlg::OnUNHoldCallResult)
	ON_MESSAGE(WM_MENU_GROUP_CHAT,&CIMDlg::OnGroupMessageWindow)
	ON_MESSAGE(WM_SHOW_DOWNLOADIMAGE_IM, &CIMDlg::OnShowDownloadImage)

	ON_BN_CLICKED(IDC_BUTTON_UNFOLDVIDEO, &CIMDlg::OnBnClickedButtonUnfoldvideo)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCALL, &CIMDlg::OnBnClickedButtonVideocall)
	ON_BN_CLICKED(IDC_BUTTON_CALL, &CIMDlg::OnBnClickedButtonCall)
	ON_BN_CLICKED(IDC_BUTTON_ENDVIDEO, &CIMDlg::OnBnClickedButtonEndvideo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_MEMBER, &CIMDlg::OnNMRClickListMember)
	ON_COMMAND_RANGE(ID_IM_GROUP_DEL_MEM_MENU, ID_IM_GROUP_RECALL_MEM_MENU, &CIMDlg::OnClickListMemMenuItem)
	ON_BN_CLICKED(IDC_BUTTON1, &CIMDlg::OnBnClickedButtonDataConf)
END_MESSAGE_MAP()


// CIMDlg 消息处理程序

BOOL CIMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	if(NULL == m_pCallCtrlDlg)
	{
		m_pCallCtrlDlg = new CCallCtrlDlg;
	}
	if(!IsWindow(m_pCallCtrlDlg->GetSafeHwnd()))
	{
		m_pCallCtrlDlg->Create(CCallCtrlDlg::IDD,&m_stcCallWnd);
	}

	m_DlgType = SIGNLE_CHAT;
	RefreshWindow();

	//获取屏幕中间的位置
	int cxFrame = ::GetSystemMetrics(SM_CXSCREEN);
	int cyFrame = ::GetSystemMetrics(SM_CYSCREEN);

	MoveWindow((cxFrame-WIDTH)/2,(cyFrame-HEITH)/2,WIDTH,HEITH);

	m_listMember.ModifyStyle(0,LVS_SINGLESEL);
	m_listMember.InsertColumn(COL_MEM_Compere, _T("主席"), LVCFMT_LEFT, 40);
	m_listMember.InsertColumn(COL_MEM_Status, _T("状态"), LVCFMT_LEFT, 40);
	m_listMember.InsertColumn(COL_MEM_Name, _T("姓名"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_ACCOUNT, _T("账号"), LVCFMT_LEFT, 70);
	m_listMember.InsertColumn(COL_MEM_CALLNO, _T("号码"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_CALLSTATE, _T("呼叫状态"), LVCFMT_LEFT, 60);
	m_listMember.InsertColumn(COL_MEM_SPK, _T("发言"), LVCFMT_LEFT, 60);
	DWORD dwStyle = m_listMember.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;	//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;		//网格线（只适用与report风格的listctrl）
	m_listMember.SetExtendedStyle(dwStyle); //设置扩展风格

	/////DTS2015110405099 限制IM消息一次发送字符   by c00327158 Start////
	m_edtSend.LimitText(IM_D_MAX_MESSAGE_LENGTH);
	/////DTS2015110405099 限制IM消息一次发送字符   by c00327158 End////
	m_edtSend.SetTargetDevice(NULL,1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CIMDlg::OnBnClickedButtonSendIM()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sendMSG;
	m_edtSend.GetWindowText(sendMSG);

	m_edtSend.msgTxtPic.txtMsg=CTools::UNICODE2UTF(sendMSG);
	m_edtSend.analysisMsg();////分析图片输入情况使用本例中无图片输入，可以缺省////

	int m_length = m_edtSend.msgTxtPic.txtMsg.length();
	std::string Content("");
	FontInfo m_font;
	m_font.m_size = 14,m_font.face = _T("Segoe UI"),m_font.m_rgb = RGB(0,0,0);////字体格式默认处理/////
	if (m_length == 0)
	{
		////无发送内容////
		CTools::ShowMessageTimeout(_T("no content please retry"),2000);
		return;
	} 
	else
	{
		if (m_length <= 500)
		{
			// 未压缩的消息格式
			Content = CTools::MakeUncomMessage(m_font,m_edtSend.msgTxtPic);
		}
		else if (m_length <= 1000)
		{
			// 压缩的消息格式
			Content = CTools::MakeRARMessage(m_font,m_edtSend.msgTxtPic);
			ComCodeMsg(Content,Content);
		}
		else
		{
			AfxMessageBox(_T("Message is too long, please re-enter !"));
			m_edtSend.SetWindowText(_T(""));
			m_edtSend.SetFocus();
			return;
		}
	}
	IM_S_SENDIM_ARG SendImArg;
	memset(&SendImArg,0,sizeof(IM_S_SENDIM_ARG));
	if(m_DlgType == SIGNLE_CHAT || m_DlgType == SIGNLE_CALL)
	{	
		if(0 == strlen(m_targetUserInfo.account))
		{
			AfxMessageBox(_T("Target Account is empty!"));
			return;
		}
		SendImArg.chatType = IM_E_IM_CHAT_TYPE_SINGLE;
		SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
		SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;
		strncpy_s(SendImArg.target,IM_D_MAX_ACCOUNT_LENGTH,m_targetUserInfo.account,_TRUNCATE);	
		strncpy_s(SendImArg.origin,IM_D_MAX_ACCOUNT_LENGTH,m_strLoginAccount.c_str(),_TRUNCATE);
		strncpy_s(SendImArg.displayname,IM_D_MAX_NAME_LENGTH,m_strLoginName.c_str(),_TRUNCATE);
		strncpy_s(SendImArg.content,IM_D_MAX_MESSAGE_LENGTH,Content.c_str(),_TRUNCATE);
		SendImArg.mediaType = tagIM_E_IM_CHATMEDIA_TYPE_TEXT;
		SendImArg.utcStamp = CTools::GetCurUTCTime();
		SendImArg.clientChatID = CTools::GetCurUTCTime();
		SendImArg.regionID = 0;

	}
	else if(m_fixGroupChat)
	{
		SendImArg.chatType = IM_E_IM_CHAT_TYPE_FIXEDGROUP;
		SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
		SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;
		CTools::CString2Char(CTools::UTF2UNICODE(g_Account),SendImArg.origin,IM_D_MAX_ACCOUNT_LENGTH);
		strncpy_s(SendImArg.target,IM_D_MAX_ACCOUNT_LENGTH,"",_TRUNCATE);
		strncpy_s(SendImArg.displayname,IM_D_MAX_NAME_LENGTH,m_strLoginName.c_str(),_TRUNCATE);
		strncpy_s(SendImArg.content,IM_D_MAX_MESSAGE_LENGTH,Content.c_str(),_TRUNCATE);
		SendImArg.mediaType = tagIM_E_IM_CHATMEDIA_TYPE_TEXT;
		SendImArg.utcStamp = CTools::GetCurUTCTime();
		SendImArg.regionID = 0;
		memcpy(SendImArg.groupID,m_strGroupID.c_str(),IM_D_GROUPID_LENGTH);
	}
	else 
	{
		SendImArg.chatType = IM_E_IM_CHAT_TYPE_DISCUSSIONGROUP;
		SendImArg.contentType = IM_E_IM_CHAT_CONTENT_TYPE_TEXT;
		SendImArg.sourceFlag = IM_E_IM_CHAT_SOURCE_FLAG_IM_DIALOG;
		strncpy_s(SendImArg.origin,IM_D_MAX_ACCOUNT_LENGTH,m_strLoginAccount.c_str(),_TRUNCATE);
		strncpy_s(SendImArg.target,IM_D_MAX_ACCOUNT_LENGTH,"",_TRUNCATE);
		strncpy_s(SendImArg.displayname,IM_D_MAX_NAME_LENGTH,m_strLoginName.c_str(),_TRUNCATE);
		strncpy_s(SendImArg.content,IM_D_MAX_MESSAGE_LENGTH,Content.c_str(),_TRUNCATE);
		SendImArg.mediaType = tagIM_E_IM_CHATMEDIA_TYPE_TEXT;
		SendImArg.utcStamp = CTools::GetCurUTCTime();
		SendImArg.regionID = 0;
		memcpy(SendImArg.groupID,m_strGroupID.c_str(),IM_D_GROUPID_LENGTH);
	}


	TUP_RESULT tRet = tup_im_sendim(&SendImArg);
	if(TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_sendim failed."));
		return ;
	}
	UpdataChatContent(SendImArg.origin,SendImArg.utcStamp,sendMSG);
	///清空发送栏目/////
	m_edtSend.SetWindowText(L""); 
	m_edtSend.Invalidate(TRUE);
 	UpdateData(TRUE);
	m_edtIMContent.PostMessage(WM_VSCROLL, SB_BOTTOM);

}
LRESULT CIMDlg::OnGroupMessageWindow(WPARAM wParam,LPARAM lParam)
{
	IM_S_IMGROUPINFO* pGroupInfo = (IM_S_IMGROUPINFO*)lParam;
	if(NULL == pGroupInfo)
	{
		return -1L;
	}
	m_btnAdd.EnableWindow(TRUE);
	m_btnVideoCall.EnableWindow(FALSE);
	SetWindowText(CTools::UTF2UNICODE(pGroupInfo->name));
	m_stcName.SetWindowText(CTools::UTF2UNICODE(pGroupInfo->name));
	RefreshMemberList(pGroupInfo->id);
	m_DlgType =  MULTI_CHAT;
	m_fixGroupChat = true;
	RefreshWindow();
	RefershChairMan(pGroupInfo->owner);
	//设置群组头像
	SetGroupHeadImg();
	ShowWindow(SW_SHOW);
	SAFE_DELETE(pGroupInfo);
	return 0L;

}
LRESULT CIMDlg::OnSendIMMenuClick(WPARAM wParam,LPARAM lParam)
{
	IM_S_USERINFO* pUserInfo = (IM_S_USERINFO *)lParam;
	if(NULL == pUserInfo)
	{
		return -1L;
	}

	m_strLoginName = pUserInfo->name;
	m_strLoginAccount = pUserInfo->account;
	memcpy(&m_targetUserInfo,pUserInfo,sizeof(IM_S_USERINFO));

	m_stcName.SetWindowText(CTools::UTF2UNICODE(m_targetUserInfo.name));
	SetWindowText(CTools::UTF2UNICODE(m_targetUserInfo.name));

	//Modified by w00321336 to code refactoring at 2015-1-21 begin
	//设置头像
	SetUserHeadImg(m_targetUserInfo);
	//Modified by w00321336 end

	ShowWindow(SW_SHOW);

	SAFE_DELETE(pUserInfo);
	return 0L;
}

//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 begin
BOOL CIMDlg::GetUserDefHeadImg(const TUP_CHAR imageID[], IM_S_IMAGEINFO& imgInfo)
{
	IM_S_IMAGEREQARG ImageArg;
	IM_S_USERIMAGEINFO ImageAck;
	strcpy_s(ImageArg.id, IM_D_MAX_ACCOUNT_LENGTH, imageID);
	TUP_RESULT tRet = tup_im_getuserdefineimage(&ImageArg, &ImageAck);
	if(TUP_FAIL == tRet)
	{
		return false;
	}

	imgInfo = ImageAck.imagebits;
	return true;
}

CString CIMDlg::GetLocalHeadImg(const TUP_CHAR imageID[])
{
	CString strImgPath;
	CString strPath = CTools::getCurrentPath();
	strImgPath.Format(_T("%s\\face\\%s.png"), strPath, CTools::UTF2UNICODE(imageID));
	return strImgPath;
}

CString CIMDlg::GetDefaultHeadImg()
{
	CString strImgPath;
	CString strPath = CTools::getCurrentPath();
	strImgPath.Format(_T("%s\\face\\0.png"), strPath);
	return strImgPath;
}

int CIMDlg::GetUserHeadImg(const IM_S_USERINFO& userInfo, IM_S_IMAGEINFO& imgeInfo, CString& strImgPath)
{
	int nRet = IMG_QUERY_ERR;

	if(0 != strlen(userInfo.imageID))
	{	
		if(strcmp(userInfo.imageID, userInfo.account) == 0)
		{
			//自定义头像
			if (GetUserDefHeadImg(userInfo.imageID, imgeInfo))
			{
				nRet = IMG_QUERY_TYPE_BUFFER;
			}
			//Modified by w00321336 to draw byte image for DTS2015010701095 at 2015-1-21 end
		}
		else
		{
			//系统头像
			strImgPath = GetLocalHeadImg(userInfo.imageID);
			nRet = IMG_QUERY_TYPE_LOCAL;
		}
	}
	else
	{
		//默认头像
		strImgPath = GetDefaultHeadImg();
		nRet = IMG_QUERY_TYPE_LOCAL;
	}

	return nRet;
}

void CIMDlg::SetGroupHeadImg()
{
	CString strPath = CTools::getCurrentPath();
	CString strFullPath;
	strFullPath.Format(_T("%s\\image\\group.png"), strPath);
	m_stcHead.SetImageFile(strFullPath);
}

BOOL CIMDlg::SetUserHeadImg(const IM_S_USERINFO& userInfo)
{
	BOOL bRet = FALSE;

	IM_S_IMAGEINFO imgInfo;
	CString strImgPath;
	int nRet = GetUserHeadImg(userInfo, imgInfo, strImgPath);
	if (IMG_QUERY_TYPE_BUFFER == nRet)
	{//自定义头像
		m_stcHead.SetImgBuffer(imgInfo.data, imgInfo.length);
		bRet = TRUE;
	}
	else if (IMG_QUERY_TYPE_LOCAL == nRet)
	{//本地头像
		m_stcHead.SetImageFile(strImgPath);
		bRet = TRUE;
	}
	return bRet;
}
//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 end

LRESULT CIMDlg::OnRecvIM(WPARAM wParam,LPARAM)
{
	IM_S_CODECHAT_NOTIFY *notify  = (IM_S_CODECHAT_NOTIFY *)wParam;
	if(NULL == notify)
	{
		return -1L;
	}
	/////设置消息为已读消息//////
	IM_S_SETMESSAGEREAD_ARG *arg = new IM_S_SETMESSAGEREAD_ARG;
	IM_S_MESSAGEINFO *argMsgInfo = new IM_S_MESSAGEINFO;

	if ((IM_E_IM_CHAT_TYPE_SINGLE == notify->chatInfo.chatType)
		|| (IM_E_IM_CHAT_TYPE_TEMP == notify->chatInfo.chatType))
	{
		strcpy_s(m_targetUserInfo.account,IM_D_MAX_ACCOUNT_LENGTH,notify->chatInfo.origin);
		strcpy_s(m_targetUserInfo.name,IM_D_MAX_NAME_LENGTH,notify->chatInfo.name);		

		//设置头像
		//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 begin
		IM_S_GETUSERINFOARG sefInfoarg;
		IM_S_USERINFO userInfoAck;
		strncpy_s(sefInfoarg.account, IM_D_MAX_ACCOUNT_LENGTH*sizeof(TUP_CHAR), notify->chatInfo.origin,_TRUNCATE);
		TUP_RESULT tRet = tup_im_getuserinfo(&sefInfoarg, &userInfoAck);
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_getuserinfo fail."));
		}
		m_stcName.SetWindowText(CTools::UTF2UNICODE(userInfoAck.name));
		SetWindowText(CTools::UTF2UNICODE(userInfoAck.name));

		m_DlgType = SIGNLE_CHAT;
		strncpy_s(m_targetUserInfo.bindNO,IM_D_MAX_PHONE_LENGTH*sizeof(TUP_CHAR),userInfoAck.bindNO,_TRUNCATE);

		//Set head image
		SetUserHeadImg(userInfoAck);
		//Add by w00321336 to fix DTS2015010701095 at 2005-1-21 end

		argMsgInfo->msgType = IM_E_IM_HISTORYMESSAGEMSG_TYPE_SINGLECHAT;
		memcpy(argMsgInfo->sender, notify->chatInfo.origin, strlen(notify->chatInfo.origin) + 1);
	}
	// 固定群聊、临时群聊、多人会话讨论组
	else if ((IM_E_IM_CHAT_TYPE_FIXEDGROUP == notify->chatInfo.chatType)
		|| (IM_E_IM_CHAT_TYPE_TEMPGROUP == notify->chatInfo.chatType)
		|| (IM_E_IM_CHAT_TYPE_DISCUSSIONGROUP == notify->chatInfo.chatType))
	{
		strcpy_s(m_targetUserInfo.account,IM_D_MAX_ACCOUNT_LENGTH,"");
		strcpy_s(m_targetUserInfo.name,IM_D_MAX_NAME_LENGTH,"");
		m_btnVideoCall.EnableWindow(FALSE);
		m_DlgType = MULTI_CHAT;
		RefreshWindow();

		RefreshMemberList(notify->chatInfo.groupID);

		IM_S_IMGROUPINFO info;
		TUP_RESULT tRet = tup_im_getfixedgroupdetail(m_strGroupID.c_str(),&info);
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_getfixedgroupdetail fail"));
		}

		RefershChairMan(info.owner);

		SetWindowText(CTools::UTF2UNICODE(info.name));	
		m_stcName.SetWindowText(CTools::UTF2UNICODE(info.name));

		//设置群组头像
		SetGroupHeadImg();

		argMsgInfo->msgType = IM_E_IM_HISTORYMESSAGEMSG_TYPE_GROUPCHAT;
		memcpy(argMsgInfo->sender, notify->chatInfo.groupID, strlen(notify->chatInfo.groupID) + 1);
	}
	// 短信消息和系统广告目前暂不处理
	// 	else if()
	// 	{
	// 
	// 	}
	argMsgInfo->msgId = notify->chatInfo.serverChatID;
	TUP_S_LIST *pData = new TUP_S_LIST;
	pData->data = (TUP_VOID *)argMsgInfo;
	pData->next = NULL;
	arg->messageinfo = pData;
	////设置消息已读/////
	TUP_RESULT tRet = tup_im_setmessageread(arg);
	if (TUP_SUCCESS != tRet)
	{
		AfxMessageBox(_T("tup_im_setmessageread failed!"));
	}
	SAFE_DELETE(pData);
	SAFE_DELETE(argMsgInfo);
	SAFE_DELETE(arg);
	ShowWindow(SW_SHOW);

	// 解析收到的eSpace纯文本消息
	string strMSG(notify->chatInfo.content);

	// 处理从eSpace或UC传过来的消息内容（判断是否压缩，是否进行相应解压等操作）
	ProcessCotentFromeSpaceOrUC(strMSG);

	// 将字符串转换为宽字符
	wstring comment = CTools::string2wstring(strMSG);
	CString strComment(comment.c_str());

	switch (notify->chatInfo.mediaType)
	{
	case  tagIM_E_IM_CHATMEDIA_TYPE_TEXT:    /*< 纯文本 */
		{
			//////解析IM消息////
			IMINfo m_Iminfo;
			vector<PicPathInfo> m_Imagelist;;
			if(CTools::GetIMFromContent(strComment,m_Iminfo,m_Imagelist))
			{
				/////处理PC端发来的消息/////
				CTools::AnalysePCMessage(m_Imagelist);
			}
			////显示消息//////
			UpdataChatContent(notify->chatInfo.origin,notify->chatInfo.utcStamp,m_Iminfo.Content);
			InsertEmotion(m_Imagelist,m_Iminfo.Content.GetLength());
		}
		break;
	case tagIM_E_IM_CHATMEDIA_TYPE_AUDIO:	 /**< 富媒体 语音 */
		{
			/////暂时不处理语音类消息/////
		}
		break;
	case tagIM_E_IM_CHATMEDIA_TYPE_VIDEO:  /**< 富媒体 视频 */
		{
			/////暂时不处理视频类消息//////

		}break;
	case tagIM_E_IM_CHATMEDIA_TYPE_IMAGE:  /**< 富媒体 图片 */
		{
			//////解析IM消息////
			IMINfo m_Iminfo;
			vector<PicPathInfo> m_Imagelist;
			if(CTools::GetIMFromContent(strComment,m_Iminfo,m_Imagelist))
			{
				/////处理PC端发来的消息/////
				CTools::AnalysePCMessage(m_Imagelist);
			}
			////显示消息//////
			UpdataChatContent(notify->chatInfo.origin,notify->chatInfo.utcStamp,m_Iminfo.Content);
			InsertEmotion(m_Imagelist,m_Iminfo.Content.GetLength());
			////下面显示富媒体消息中的图片//////
			m_ImagePosition = m_Iminfo.Content.GetLength() - m_Iminfo.m_uminfo.m_Pos +1;
			m_downloadImagePath = DownloadImageFromServerce(m_Iminfo.m_uminfo);
			Sleep(300);  ////延时，给予下载图片时间
		}
		break;
	default:
		break;
	} 
	SAFE_DELETE(notify);

	return 0L;
}
int CIMDlg::UpdataChatContent(TUP_CHAR account[], TUP_INT64 utcStamp, const CString& chatContent)
{

	CHARFORMAT cf;
	m_edtIMContent.GetDefaultCharFormat(cf);

	CHARFORMAT cfNew;
	ZeroMemory(&cfNew, sizeof(CHARFORMAT));
	cfNew.cbSize = sizeof(CHARFORMAT);
	cfNew.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE |CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;
	cfNew.dwEffects = 0;
	cfNew.yHeight = 16*16;//文字高度

	if (strcmp(m_targetUserInfo.account, account) == 0)
	{
		cfNew.crTextColor = RGB(200, 100, 255); //文字颜色
	}
	else
	{
		cfNew.crTextColor = RGB(0, 100, 255); //文字颜色
	}

	CString recvMSG;
	m_edtIMContent.GetWindowText(recvMSG);

	std::string msg=CTools::UNICODE2UTF(recvMSG);

	CString strShowMSGS("");
	strShowMSGS += CTools::UTF2UNICODE(account);
	strShowMSGS += _T(" ");
	strShowMSGS += CTools::FormatUTCTime(utcStamp);
	strShowMSGS += CString("\r\n");

	m_edtIMContent.SetSel(msg.size(),msg.size()+CTools::UNICODE2UTF(strShowMSGS).size()-1);
	m_edtIMContent.SetSelectionCharFormat(cfNew);
	m_edtIMContent.ReplaceSel(strShowMSGS);


	CString strShowMSGBODY("");
	strShowMSGBODY += chatContent;
	strShowMSGBODY += CString("\r\n");

	m_edtIMContent.SetSel(msg.size()+CTools::UNICODE2UTF(strShowMSGS).size(),msg.size()+CTools::UNICODE2UTF(strShowMSGS).size()+CTools::UNICODE2UTF(strShowMSGBODY).size()-1);
	m_edtIMContent.SetSelectionCharFormat(cf);
	m_edtIMContent.ReplaceSel(strShowMSGBODY);
	m_edtIMContent.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	return strShowMSGS.GetLength();
}

void  CIMDlg::InsertEmotion(vector<PicPathInfo>& OutImagelist,int Pos)
{
	////插入收到消息所带有的本地表情消息/////
	vector<PicPathInfo>::iterator itbegin = OutImagelist.begin();
	for(;itbegin != OutImagelist.end();itbegin++)
	{
		/////获取当前光标的位置/////
		m_edtIMContent.SetSel(-1,-1);
		long nStartChar = 0;
		long nEndChar = 0;
		m_edtIMContent.GetSel(nStartChar,nEndChar);
		m_edtIMContent.SetSel(nStartChar - Pos + itbegin->pos - 1,nStartChar - Pos + itbegin->pos - 1);
		m_edtIMContent.InsertImage(CTools::UTF2UNICODE(itbegin->picPath),0);
	}
}
//////从UM服务端下载截图并返回本地存储URL///////
CString CIMDlg::DownloadImageFromServerce(UMINFo& m_UMinfo)
{
	/////获取%appdata%路径/////
	char myDir[MAX_PATH];
	SHGetSpecialFolderPathA(this->GetSafeHwnd(), myDir, CSIDL_APPDATA, 0);
	std::string fileSavePath(myDir);
	fileSavePath += "\\";
	///目前仅支持图片下载//////
	if (m_UMinfo.umFileType == "Img")
	{
		OFFLINEHANDLE fileHandle;
		OFFLINE_DOWN_FILEINFO downloadInfo;
		if (!m_UMinfo.umTransCode.empty())
		{
			std::string accessCode = m_UMinfo.umTransCode.c_str();
			downloadInfo.pPlainAccess = new OFFLINE_PlainAccess;
			downloadInfo.pPlainAccess->pcplainAccessCode = new HTTPChar[accessCode.length() + 1];
			memset(downloadInfo.pPlainAccess->pcplainAccessCode, 0, accessCode.length()+1);
			memcpy_s(downloadInfo.pPlainAccess->pcplainAccessCode, accessCode.length(),
				accessCode.c_str(), accessCode.length());
			downloadInfo.pPlainAccess->pcplainAccessCode[accessCode.length()] = '\0';
		}
		downloadInfo.bDownDelete = TUP_FALSE;// 适配漫游场景，文件不删除
		std::string filePath = fileSavePath + m_UMinfo.umFileName;
		downloadInfo.pcFilePath = const_cast<TUP_CHAR*>(filePath.c_str());
		downloadInfo.pcFileDownUrl = const_cast<TUP_CHAR*>(m_UMinfo.umFileUrl.c_str());
		downloadInfo.bUseSvnFile = TUP_FALSE;// 适配漫游场景，文件不删除
		////增加UserInfo信息
		downloadInfo.userInfo = const_cast<IM_S_USERINFO*>(&m_targetUserInfo);
 		TUP_RESULT tupRet = tup_offlinefile_downloadfile(&downloadInfo, &fileHandle, &NotifyCallBack::ProgressCallBack, &NotifyCallBack::UMMsgTransResultCallback);
		if (TUP_SUCCESS != tupRet)
		{
			AfxMessageBox(_T("tup_offlinefile_downloadfile failed!"));
		}
		if (downloadInfo.pPlainAccess)
		{
			if (downloadInfo.pPlainAccess->pcplainAccessCode)
			{
				delete[] downloadInfo.pPlainAccess->pcplainAccessCode;
			}
			delete downloadInfo.pPlainAccess;
		}
	//	SAFE_DELETE_ARRAY(downloadInfo.userInfo);
		return CTools::UTF2UNICODE(filePath);
	}
	else
		return CString("");
}

//************************************************************************
LRESULT CIMDlg::OnShowDownloadImage(WPARAM wParam, LPARAM lParam)
{
	CImage image;
	image.Load(m_downloadImagePath.GetBuffer(0));
	CSize imageSize = CTools::GetImageSize (image.GetHeight(), image.GetWidth());
	ResizeImage(imageSize.cx, imageSize.cy);// 调整图片大小
	/////获取当前光标的位置/////
	m_edtIMContent.SetSel(-1,-1);
	long nStartChar = 0;
	long nEndChar = 0;
	m_edtIMContent.GetSel(nStartChar,nEndChar);
	m_edtIMContent.SetSel(nStartChar - m_ImagePosition ,nStartChar - m_ImagePosition);
	m_edtIMContent.InsertImage(m_downloadImagePath,0);
	return 0;
}
void CIMDlg::ResizeImage(LONG& lWidth, LONG& lHeight)
{
	RECT rcShowImg = {0, 0, 0, 0};
	int iShowImgWidth = (rcShowImg.right - rcShowImg.left) - 35;
	// 调整大小
	if (lWidth > iShowImgWidth && 0 != lWidth)
	{
		double tmpHeight = (((iShowImgWidth * (double)lHeight)/(double)lWidth) *1.0);
		lWidth = iShowImgWidth;
		lHeight = (int)tmpHeight;
	}
}

LRESULT CIMDlg::OnHangUp(WPARAM,LPARAM)
{
	if(m_DlgType == SIGNLE_CALL || m_DlgType == SIGNLE_CHAT)
	{
		tup_call_del_video(m_uiCallID);

		tup_call_destroy_video_window(CALL_E_VIDEOWND_CALLREMOTE);
		tup_call_destroy_video_window(CALL_E_VIDEOWND_CALLLOCAL);

		PostMessage(WM_CALL_SHOW_WND,0,0);

		TUP_RESULT tRet = tup_call_end_call(m_uiCallID);
		if(TUP_FAIL == tRet)
		{
			AfxMessageBox(L"tup_call_end_call failed.");
		}

		m_DlgType = SIGNLE_CHAT;
		RefreshWindow();	

	}
	m_uiCallID = 0;

	PostMessage(WM_CALL_SHOW_WND,0,0);
	m_btnVideoCall.EnableWindow(TRUE);

	//////发布状态/////
	if (!PubSelfStatus(IM_E_STATUS_ONLINE))
	{
		TRACE("PubSelf Status Failed");
	}
	return 0L;
}

void CIMDlg::SetDefualtHeadImg()
{
	CString strDefImg = GetDefaultHeadImg();
	m_stcHead.SetImageFile(strDefImg);
}

LRESULT CIMDlg::OnCallComing(WPARAM wParam, LPARAM)
{
	if(NULL != m_pCallCtrlDlg)
	{
		m_pCallCtrlDlg->SetCallState(CALL_CONNECTED);
	}

	m_btnCall.EnableWindow(FALSE);
	m_DataConfCall.EnableWindow(FALSE);
	m_DlgType = SIGNLE_CALL;
	RefreshWindow();


	CALL_S_CALL_INFO* pNotifyInfo = (CALL_S_CALL_INFO*)wParam;
	m_uiCallID = pNotifyInfo->stCallStateInfo.ulCallID;

	//Add by w00321336 to fix DTS2015010703551 at 2015-1-22 begin
	if(!GetTargetUserInfo(pNotifyInfo->stCallStateInfo.acTelNum, m_targetUserInfo))
	{
		AfxMessageBox(_T("Get target user info failed by bind no."));
	}

	m_stcName.SetWindowText(CTools::UTF2UNICODE(m_targetUserInfo.name));
	SetWindowText(CTools::UTF2UNICODE(m_targetUserInfo.name));

	//设置头像
	SetUserHeadImg(m_targetUserInfo);
	//Add by w00321336 to fix DTS2015010703551 at 2015-1-22 end

	//////发布状态/////
	if (!PubSelfStatus(IM_E_STATUS_BUSY))
	{
		TRACE("PubSelf Status Failed");
	}

	return 0L;
}
LRESULT CIMDlg::OnCallInfoChange(WPARAM wParam, LPARAM)
{
	CALL_S_CALL_INFO* pNotifyInfo = (CALL_S_CALL_INFO*)wParam;
	/////检查呼叫权限/////
	if (CALL_E_MEDIA_SENDMODE_SENDRECV == pNotifyInfo->enAudioSendMode)
	{
		OnUNHoldCallResult(CALL_E_EVT_CALL_UNHOLD_SUCCESS,NULL);
	}
	else
	{
		/////呼叫权限受限，默认是保持状态/////
		OnHoldCallResult(CALL_E_EVT_CALL_HOLD_SUCCESS,NULL);
	}
	SAFE_DELETE(pNotifyInfo);
	return 0L;
}
LRESULT CIMDlg::OnCallDTMF(WPARAM wParam, LPARAM)
{
	tup_call_send_DTMF(m_uiCallID,(CALL_E_DTMF_TONE)wParam);
	return 0L;
}

LRESULT CIMDlg::OnCallConnected(WPARAM wParam,LPARAM)
{
	if(NULL != m_pCallCtrlDlg)
	{
		m_pCallCtrlDlg->SetCallState(CALL_CONNECTED);
	}

	m_btnCall.EnableWindow(FALSE);
	m_btnVideoCall.EnableWindow(TUP_TRUE);
	m_DataConfCall.EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ENDVIDEO)->EnableWindow(TRUE);
	//接听电话后，不能加人
	m_btnAdd.EnableWindow(FALSE);
	m_DlgType = SIGNLE_CALL;
	RefreshWindow();

	CALL_S_CALL_INFO* pNotifyInfo = (CALL_S_CALL_INFO*)wParam;
	m_uiCallID = pNotifyInfo->stCallStateInfo.ulCallID;

	SAFE_DELETE(pNotifyInfo);
	return 0L;
}

LRESULT CIMDlg::OnCallEnd(WPARAM wParam,LPARAM)
{
	CALL_S_CALL_INFO* pNotifyInfo = (CALL_S_CALL_INFO*)wParam;
	m_pCallCtrlDlg->SetCallState(NO_CALL);

	PostMessage(WM_CALL_SHOW_WND,0,0);

	m_DlgType = SIGNLE_CHAT;
	RefreshWindow();

	m_uiCallID = 0;
	IsVidesponsor = false;
	m_pCallCtrlDlg->ReshCallCtrlWindow();
	///////发布自己状态///////
	if(PubSelfStatus(IM_E_STATUS_ONLINE))
	{
		TRACE("PubSelf Status Sucess!");
	}
	SAFE_DELETE(pNotifyInfo);

	return 0L;
}
LRESULT CIMDlg::OnCallAddVideo(WPARAM l,LPARAM)
{
	TRACE0("CIMDlg::OnCallAddVideo\n");
	CALL_S_CALL_INFO* notifyInfo = (CALL_S_CALL_INFO*)l;
	/////添加是否同意升级为视频////////
	CNewCallDlg dlg;
	dlg.m_strName.Format(_T("来电姓名: %s"), CTools::UTF2UNICODE(notifyInfo->stCallStateInfo.acDisplayName));
	dlg.m_strNum.Format(_T("来电号码：%s"), CTools::UTF2UNICODE(notifyInfo->stCallStateInfo.acTelNum));
	dlg.m_BVideoCall  = TRUE;

	INT_PTR retCode = dlg.DoModal();
	if(retCode == IDOK)
	{
		SendMessage(WM_CALL_SHOW_WND,1,m_uiCallID);
		TUP_RESULT tRet = tup_call_reply_add_video(m_uiCallID,TUP_TRUE);
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(L"tup_call_reply_add_video failed");
		}

	}
	else
	{
		TUP_RESULT tRet = tup_call_reply_add_video(m_uiCallID,TUP_FALSE);
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(L"tup_call_reply_del_video failed");
		}
		PostMessage(WM_CALL_SHOW_WND,0,0);
	}

	return 0L;
}
LRESULT CIMDlg::OnCallDelVideo(WPARAM,LPARAM)
{
	TRACE0("CIMDlg::OnCallDELVideo\n");
	////视频转音频，默认同意/////
	TUP_RESULT tRet = tup_call_reply_del_video(m_uiCallID,TUP_FALSE);
	PostMessage(WM_CALL_SHOW_WND,0,0);
	return 0L;
}
LRESULT CIMDlg::OnCallHold(WPARAM,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	CString m_str;
	m_btnVideoCall.GetWindowText(m_str);
	if (m_str == L"视频降级")
	{
		//////视频呼叫不支持呼叫转移//////
		CTools::ShowMessageTimeout(_T("不支持视频呼叫保持，请降级为音频后操作"),5000);
		return -1L;
	}
	TUP_RESULT tRet = tup_call_hold_call(m_uiCallID);
	if(TUP_SUCCESS == tRet)
	{
		return 0L;
	}
	else
	{
		return -1L;
	}

}

LRESULT CIMDlg::OnHoldCallResult(WPARAM l,LPARAM)
{
	//////呼叫保持结果//////
	CHECK_POINTER_RETURN(m_pCallCtrlDlg,-1L);
	int ID = int(l);
	if (ID == CALL_E_EVT_CALL_HOLD_SUCCESS)
	{
		/////保持成功/////
		m_pCallCtrlDlg->m_btnHold.SetWindowText(L"恢复通话");
		/////DTS2015103101975呼叫保持中的语音通话，录音、转移、升级视频、升级数据会议功能不可使用 c00327158 Start/////
		m_pCallCtrlDlg->m_btnRec.EnableWindow(FALSE);
		m_pCallCtrlDlg->m_btnTrans.EnableWindow(FALSE);
		m_btnVideoCall.EnableWindow(FALSE);
		m_DataConfCall.EnableWindow(FALSE);
		/////DTS2015103101975呼叫保持中的语音通话，录音、转移、升级视频、升级数据会议功能不可使用 c00327158 Start/////
	} 
	else
	{
		////保持失败/////
		AfxMessageBox(_T("HoldCall Failed"));
	}
	return 0L;
}
LRESULT CIMDlg::OnCallUnHold(WPARAM,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	TUP_RESULT tRet = tup_call_unhold_call(m_uiCallID);
	if(TUP_SUCCESS == tRet)
	{
		return 0L;
	}
	else
	{
		return -1L;
	}
}

LRESULT CIMDlg::OnUNHoldCallResult(WPARAM l,LPARAM)
{
	//////取消呼叫保持结果//////
	CHECK_POINTER_RETURN(m_pCallCtrlDlg,-1L);
	int ID = int(l);
	if (ID == CALL_E_EVT_CALL_UNHOLD_SUCCESS)
	{
		/////保持成功/////
		m_pCallCtrlDlg->m_btnHold.SetWindowText(L"呼叫保持");
		/////DTS2015103101975呼叫保持中的语音通话，录音、转移、升级视频、升级数据会议功能不可使用 c00327158 Start/////
		m_pCallCtrlDlg->m_btnRec.EnableWindow(TRUE);
		m_pCallCtrlDlg->m_btnTrans.EnableWindow(TRUE);
		m_btnVideoCall.EnableWindow(TRUE);
		m_DataConfCall.EnableWindow(TRUE);
		/////DTS2015103101975呼叫保持中的语音通话，录音、转移、升级视频、升级数据会议功能不可使用 c00327158 Start/////

	} 
	else
	{
		////保持失败/////
		AfxMessageBox(_T("UNHoldCall Failed"));
	}
	return 0L;
}
LRESULT CIMDlg::OnCallMicMute(WPARAM,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	TUP_RESULT tRet = tup_call_media_mute_mic(m_uiCallID,TUP_TRUE);
	if(TUP_SUCCESS == tRet)
	{
		return 0L;
	}
	else
	{
		return -1L;
	}


}
LRESULT CIMDlg::OnCallMicUnMute(WPARAM,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	TUP_RESULT tRet = tup_call_media_mute_mic(m_uiCallID,TUP_FALSE);
	if(TUP_SUCCESS == tRet)
	{
		return 0L;
	}
	else
	{
		return -1L;
	}

}
LRESULT CIMDlg::OnCallSpkMute(WPARAM,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	return 0L;

}
LRESULT CIMDlg::OnCallSpkUnMute(WPARAM,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	return 0L;
}

LRESULT CIMDlg::OnCallStartRec(WPARAM,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	tup_call_media_startrecord(m_uiCallID,"D\\:123.wav",TUP_FALSE);
	return 0L;

}
LRESULT CIMDlg::OnCallEndRec(WPARAM,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	tup_call_media_stoprecord(m_uiCallID);
	return 0L;

}
LRESULT CIMDlg::OnCallBlindTrans(WPARAM wParam,LPARAM)
{
	if(0 == m_uiCallID)
	{
		return -1L;
	}
	CString m_str;
	m_btnVideoCall.GetWindowText(m_str);
	if (m_str == L"视频降级")
	{
		//////视频呼叫不支持呼叫转移//////
		CTools::ShowMessageTimeout(_T("请降级为音频呼叫后转移"),5000);
		return -1L;
	}
	TUP_CHAR* num = (char*)wParam;
	TUP_RESULT tRet = tup_call_blind_transfer(m_uiCallID,num);
	if(tRet != TUP_SUCCESS)
	{
		CTools::ShowMessageTimeout(_T("tup_call_blind_transfer failed"),5000);
	}

	return 0L;

}

LRESULT CIMDlg::OnCallBlindTransResult(WPARAM wParam,LPARAM lParam)
{
	//////取消呼叫保持结果//////
	CHECK_POINTER_RETURN(m_pCallCtrlDlg,-1L);
	CALL_S_CALL_INFO *pNotify = (CALL_S_CALL_INFO*)wParam;
	int Result = (int)lParam;
	if (CALL_E_EVT_CALL_BLD_TRANSFER_SUCCESS == Result)
	{
		/////转移成功/////
		CTools::ShowMessageTimeout(_T("呼叫转移成功"),500);
	} 
	else
	{
		//////转移失败/////
		if (CALL_E_CALL_STATE_HOLD == pNotify->stCallStateInfo.enCallState)
		{
			tup_call_unhold_call(pNotify->stCallStateInfo.ulCallID);
		}
		CTools::ShowMessageTimeout(_T("呼叫转移失败"),500);
	}


	SAFE_DELETE(pNotify);
	return 0L;
}

BOOL CIMDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
	{
		int nVirtKey = (int)pMsg->wParam;
		if(nVirtKey == VK_RETURN)   
		{  
			////将输入框增加一行////
			CString recvMSG;
			m_edtSend.GetWindowText(recvMSG);
			recvMSG += CString("\r\n");
			m_edtSend.SetWindowText(recvMSG);
			m_edtSend.SetSel(-1,-1);
			return TRUE;   
		}   
		if(nVirtKey == VK_ESCAPE)   
		{   
			return TRUE;
		}   
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CIMDlg::OnBnClickedButtonAddUser()
{
	// TODO: 在此添加控件通知处理程序代码
	CSelectDlg dlg;
	if(IDOK != dlg.DoModal())
	{
		return;
	}

	MAP_SELECT_USER selUser;
	dlg.GetSelectUser(selUser);	
	int iSize = selUser.size();
	if(iSize == 0)
	{
		return;		
	}

	if(m_DlgType == SIGNLE_CHAT)
	{		
		CALL_MEMBER member;
		strcpy_s(member.account,IM_D_MAX_ACCOUNT_LENGTH,m_targetUserInfo.account);
		strcpy_s(member.name,IM_D_MAX_NAME_LENGTH,m_targetUserInfo.name);
		strcpy_s(member.CallNo,IM_D_MAX_PHONE_LENGTH,m_targetUserInfo.bindNO);
		selUser[m_targetUserInfo.account]  = member;

		IM_S_GETUSERINFOARG sefInfoarg;
		strcpy_s(sefInfoarg.account,IM_D_MAX_ACCOUNT_LENGTH,g_Account.c_str());
		IM_S_USERINFO userinfo;	
		tup_im_getuserinfo(&sefInfoarg,&userinfo);
		strcpy_s(member.account,IM_D_MAX_ACCOUNT_LENGTH,userinfo.account);
		strcpy_s(member.name,IM_D_MAX_NAME_LENGTH,userinfo.name);
		strcpy_s(member.CallNo,IM_D_MAX_PHONE_LENGTH,userinfo.bindNO);
		selUser[userinfo.account]  = member;

		if(selUser.size() <= 2)
		{
			return;
		}

		std::string groupname = m_strLoginName;

		MAP_SELECT_USER::iterator it = selUser.begin();
		MAP_SELECT_USER::iterator itEnd = selUser.end();
		for(;it!=itEnd;it++)
		{
			if(it->first != m_strLoginAccount)
			{
				groupname.append(",");
				groupname.append(it->second.name);
			}
		}
		SetWindowText(CTools::UTF2UNICODE(groupname));
		m_stcName.SetWindowText(CTools::UTF2UNICODE(groupname));

		//Modified by w00321336 to fix some image missing issue begin
		SetGroupHeadImg();
		//Modified by w00321336 to fix some image missing issue end

		m_stcHead.ShowWindow(SW_HIDE);
		m_stcHead.ShowWindow(SW_SHOW);

		m_btnVideoCall.EnableWindow(FALSE);

		IM_S_IMGROUP_OP_ARG addDgroupArg;
		IM_S_ADDIMGROUP_ACK addDGroupAck;
		strcpy_s(addDgroupArg.fixedgroupInfo.name,IM_D_MAX_NAME_LENGTH,groupname.c_str());
		strcpy_s(addDgroupArg.fixedgroupInfo.owner,IM_D_MAX_ACCOUNT_LENGTH,m_strLoginAccount.c_str());
		TUP_RESULT tRet = tup_im_adddiscussiongroup(&addDgroupArg,&addDGroupAck);
		if(tRet == TUP_FAIL || addDGroupAck.result == TUP_FALSE)
		{
			AfxMessageBox(L"tup_im_adddiscussiongroup failed");
			return;
		}

		m_strGroupID = addDGroupAck.id;

		m_DlgType = MULTI_CHAT;
		RefreshWindow();

		it = selUser.begin();
		itEnd = selUser.end();
		for(;it!=itEnd;it++)
		{
			std::string strAccount = it->first;
			//添加讨论组成员
			IM_S_ADDIMGROUPMEMBER_ARG AddMemberArg;
			strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,addDGroupAck.id);
			strcpy_s(AddMemberArg.groupName,IM_D_MAX_NAME_LENGTH,groupname.c_str());
			strcpy_s(AddMemberArg.account,IM_D_MAX_ACCOUNT_LENGTH,strAccount.c_str());

			tRet = tup_im_adddiscussiongroupmember(&AddMemberArg);
			if(tRet == TUP_FAIL)
			{
				AfxMessageBox(L"tup_im_adddiscussiongroupmember failed");
			}
		}
	}
	else if(m_DlgType == MULTI_CHAT)
	{
		CString cstrName;
		m_stcName.GetWindowText(cstrName);
		MAP_SELECT_USER::iterator it = selUser.begin();
		MAP_SELECT_USER::iterator itEnd = selUser.end();
		for(;it!=itEnd;it++)
		{	
			std::string strAccount = it->first;
			if (IsMemberInGroup(strAccount,m_strGroupID))
			continue;
			//添加讨论组成员
			IM_S_ADDIMGROUPMEMBER_ARG AddMemberArg;
			strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,m_strGroupID.c_str());
			strcpy_s(AddMemberArg.groupName,IM_D_MAX_NAME_LENGTH,CTools::UNICODE2UTF(cstrName).c_str());
			strcpy_s(AddMemberArg.account,IM_D_MAX_ACCOUNT_LENGTH,strAccount.c_str());
			strcpy_s(AddMemberArg.displayName,IM_D_MAX_NAME_LENGTH,it->second.name);

			TUP_RESULT tRet = tup_im_adddiscussiongroupmember(&AddMemberArg);
			if(tRet == TUP_FAIL)
			{
				AfxMessageBox(L"tup_im_adddiscussiongroupmember failed");
			}
		}
	}

}

void CIMDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	IM_S_IMGROUPINFO info;
	TUP_RESULT  tRet;
	if(m_DlgType == SIGNLE_CHAT)
	{
		::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_IM_WND,(WPARAM)this,NULL);
	}
	else if(m_DlgType == SIGNLE_CALL)
	{
		TUP_RESULT tRet = tup_call_end_call(m_uiCallID);
		if(TUP_FAIL == tRet)
		{
			AfxMessageBox(L"tup_call_end_call failed.");
		}
		m_uiCallID = 0;
		::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_IM_WND,(WPARAM)this,NULL);
		PubSelfStatus(IM_E_STATUS_ONLINE);
	}
	else if(m_DlgType == MULTI_CHAT)
	{
		tRet = tup_im_getfixedgroupdetail(m_strGroupID.c_str(),&info);
		if (TUP_FAIL == tRet)
		{
			AfxMessageBox(_T("tup_im_getfixedgroupdetail fail"));
		}
		if(info.groupType != IM_E_IMGROUP_FIXGROUP_TYPE)
		{
			TUP_RESULT tRet = tup_im_leavediscussiongroup(m_strGroupID.c_str());
			if(TUP_FAIL == tRet)
			{
				AfxMessageBox(L"tup_im_leavediscussiongroup failed.");
			}
		}
		m_strGroupID = "";
		::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_IM_WND,(WPARAM)this,NULL);
	}

	CDialog::OnClose();
}

void CIMDlg::CloseDlg(void)
{
	m_strLoginAccount = "";
	m_strLoginName = "";
	m_DlgType = SIGNLE_CHAT;
	m_uiCallID = 0;
	m_strGroupID = "";
	m_uiConfID = 0;
	IsVidesponsor = false;
	::PostMessage(theApp.m_pMainDlgWnd->GetSafeHwnd(),WM_CLOSE_IM_WND,(WPARAM)this,NULL);
	CDialog::OnClose();
}


void CIMDlg::RefreshWindow(void)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rc;
	rc.top = IMCONTENTBOTTOM+3;
	rc.bottom = IMCONTENTBOTTOM+57;
	rc.left = rcClient.left+13;
	rc.right = rcClient.left+TOOLWIDTH;
	m_edtSend.MoveWindow(&rc,TRUE);

	switch (m_DlgType)
	{
	case SIGNLE_CHAT:
		{
			CRect rc;
			rc.top = 105;
			rc.bottom = IMCONTENTBOTTOM;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_edtIMContent.MoveWindow(&rc,TRUE);
			m_edtIMContent.ShowWindow(SW_SHOW);

			m_listMember.ShowWindow(SW_HIDE);
			m_stcCallWnd.ShowWindow(SW_HIDE);			

		}
		break;
	case MULTI_CHAT:
		{
			CRect rc;

			rc.top = 105;
			rc.bottom = 185;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_listMember.MoveWindow(&rc,TRUE);
			m_listMember.ShowWindow(SW_SHOW);

			m_stcCallWnd.ShowWindow(SW_HIDE);

			rc.top = 185;
			rc.bottom = IMCONTENTBOTTOM;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_edtIMContent.MoveWindow(&rc,TRUE);
			m_edtIMContent.ShowWindow(SW_SHOW);


		}
		break;
	case SIGNLE_CALL:
		{
			CRect rc;
			rc.top = 105;
			rc.bottom = 185;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_stcCallWnd.MoveWindow(&rc,TRUE);
			m_stcCallWnd.ShowWindow(SW_SHOW);
			m_stcCallWnd.GetClientRect(&rc);

			m_pCallCtrlDlg->RedrawWindow(rc);
			m_pCallCtrlDlg->ShowWindow(SW_SHOW);

			rc.top = 185;
			rc.bottom = IMCONTENTBOTTOM;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_edtIMContent.MoveWindow(&rc,TRUE);
			m_edtIMContent.ShowWindow(SW_SHOW);

			m_listMember.ShowWindow(SW_HIDE);
		}
		break;
	case MULTI_CALL:
		{
			CRect rc;
			rc.top = 105;
			rc.bottom = 185;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_listMember.MoveWindow(&rc,TRUE);
			m_listMember.ShowWindow(SW_SHOW);

			rc.top = 185;
			rc.bottom = 265;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_stcCallWnd.MoveWindow(&rc,TRUE);
			m_stcCallWnd.ShowWindow(SW_SHOW);
			m_stcCallWnd.GetClientRect(&rc);

			m_pCallCtrlDlg->RedrawWindow(rc);
			m_pCallCtrlDlg->ShowWindow(SW_SHOW);


			rc.top = 265;
			rc.bottom = IMCONTENTBOTTOM;
			rc.left = rcClient.left+13;
			rc.right = rcClient.left+TOOLWIDTH;
			m_edtIMContent.MoveWindow(&rc,TRUE);
			m_edtIMContent.ShowWindow(SW_SHOW);

		}
		break;
	}

}
void CIMDlg::RefreshMemberList(const std::string& groupID)
{
	m_listMember.DeleteAllItems();

	IM_S_REQUESTIMGROUPMEMBERS_ARG groupMembArg;
	IM_S_GROUPUSERLIST groupList;

	strcpy_s(groupMembArg.groupID,IM_D_GROUPID_LENGTH,groupID.c_str());
	groupMembArg.isSyncAll = TUP_TRUE;
	strcpy_s(groupMembArg.timpstamp,IM_D_MAX_TIMESTAMP_LENGTH,"19000000000000");

	if(TUP_SUCCESS!= tup_im_getfixedgroupmembers(&groupMembArg,&groupList))
	{
		return;
	}

	TUP_S_LIST* list =  groupList.memberInfo;
	while(list != NULL)
	{
		IM_S_USERINFO* groupUser = (IM_S_USERINFO*)list->data;
		if(NULL != groupUser)
		{
			CString cstrAccount = CTools::UTF2UNICODE(groupUser->account);
			bool bFind = false;
			int iSize = m_listMember.GetItemCount();
			for(int i = 0; i< iSize; i++)
			{
				if(cstrAccount.Compare(m_listMember.GetItemText(i,COL_ACCOUNT)) == 0)
				{
					bFind = true;
					break;
				}
			}
			if(!bFind)
			{
				m_listMember.InsertItem(iSize,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Compere,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Status,L"");
				m_listMember.SetItemText(iSize,COL_MEM_Name,CTools::UTF2UNICODE(groupUser->name));
				m_listMember.SetItemText(iSize,COL_MEM_ACCOUNT,cstrAccount);
				m_listMember.SetItemText(iSize,COL_MEM_CALLNO,CTools::UTF2UNICODE(groupUser->bindNO));
				m_listMember.SetItemText(iSize,COL_MEM_CALLSTATE,L"");
				m_listMember.SetItemText(iSize,COL_MEM_SPK,L"");
			}
		}
		list = list->next;
	}
	//////释放IM_S_GROUPUSERLIST中的TUP_S_LIST指针/////
	tup_im_release_tup_list(groupList.memberInfo);
}
LRESULT CIMDlg::OnShowVideoWnd(WPARAM wParam,LPARAM lPara)
{
	CRect rcSize;
	GetWindowRect(&rcSize);

	CRect rc;
	int iShow = (int)wParam;
	TUP_UINT32 callid = (TUP_UINT32)lPara;
	if(iShow == 1)
	{
		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + VIDEO_WIDTH;
		rc.bottom = rcSize.top + HEITH;
		m_btnUnfold.SetWindowText(L"<");

		HWND mLocalVideoWnd = m_stcLocalVideo.GetSafeHwnd();
		HWND mRemoteVideoWnd = m_stcRemoteVideo.GetSafeHwnd();

		CALL_S_VIDEOWND_INFO videoWndInfo[2];
		memset(videoWndInfo, 0, sizeof(CALL_S_VIDEOWND_INFO)*2);
		videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulRender = (TUP_UINT32)mLocalVideoWnd;
		videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulVideoWndType = CALL_E_VIDEOWND_CALLLOCAL;
		videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulIndex = 1;
		videoWndInfo[CALL_E_VIDEOWND_CALLLOCAL].ulDisplayType = CALL_E_VIDEOWND_DISPLAY_FULL;

		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulRender = (TUP_UINT32)mRemoteVideoWnd;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulVideoWndType = CALL_E_VIDEOWND_CALLREMOTE;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulIndex = 0;
		videoWndInfo[CALL_E_VIDEOWND_CALLREMOTE].ulDisplayType = CALL_E_VIDEOWND_DISPLAY_FULL;

		if(callid != 0)//0表示要调用tup_call_create_video_window接口
		{
			tup_call_update_video_window(2, (CALL_S_VIDEOWND_INFO *)videoWndInfo,callid);
		}
		else		
		{
			TUP_RESULT tRet = tup_call_create_video_window(2, (CALL_S_VIDEOWND_INFO *)videoWndInfo);
			if(TUP_FAIL == tRet)
			{
				AfxMessageBox(L"tup_call_create_video_window failed.");
			}
		}		

		m_btnCall.EnableWindow(FALSE);		
		m_btnAdd.EnableWindow(FALSE);
		m_btnVideoCall.SetWindowText(L"视频降级");
		m_btnVideoCall.EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ENDVIDEO)->EnableWindow(TRUE);
	}
	else
	{
		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;
		m_btnUnfold.SetWindowText(L">");

		m_btnCall.EnableWindow(FALSE);
		if (m_uiCallID == 0)
		{
			m_btnAdd.EnableWindow(TRUE);
		}
		else
		{
			m_btnAdd.EnableWindow(FALSE);

		}
		m_DataConfCall.EnableWindow(TRUE);
		m_btnVideoCall.SetWindowText(L"视频呼叫");
		m_btnVideoCall.EnableWindow(TRUE);
		if ((m_pCallCtrlDlg != NULL) && (!m_pCallCtrlDlg->IsWindowVisible()))
		{
			m_btnCall.EnableWindow(TRUE);
			m_DataConfCall.EnableWindow(TRUE);
		}
	}

	MoveWindow(&rc,TRUE);
	ShowWindow(SW_SHOW);

	return 0L;

}

void CIMDlg::OnBnClickedButtonUnfoldvideo()
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rcSize;
	GetWindowRect(&rcSize);
	CString cstrFold;
	m_btnUnfold.GetWindowText(cstrFold);

	CRect rc;
	if(L">" == cstrFold)
	{

		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + VIDEO_WIDTH;
		rc.bottom = rcSize.top + HEITH;
		m_btnUnfold.SetWindowText(L"<");
	}
	else
	{
		rc.left = rcSize.left;
		rc.top = rcSize.top;
		rc.right = rc.left + WIDTH;
		rc.bottom = rcSize.top + HEITH;
		m_btnUnfold.SetWindowText(L">");

	}
	MoveWindow(&rc,TRUE);
	ShowWindow(SW_SHOW);
}

void CIMDlg::OnBnClickedButtonVideocall()
{
	// TODO: 在此添加控件通知处理程序代码
	//////暂时不支持多路呼叫 c00327158 Start////////

	if ( CIMManage::GetIntance().GetConfCallNUmber() >0)
	{
		CTools::ShowMessageTimeout(_T("不支持语音会议中发起点对点呼叫"),3000);
		return ;
	}
	CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
	if (pMainDlg->GetDataConfDlg())
	{
		if (0 != pMainDlg->GetDataConfDlg()->GetConfId())
		{
			CTools::ShowMessageTimeout(_T("不支持数据会议中发起点对点呼叫"),3000);
			return ;
		}
	}
	//////暂时不支持多路呼叫 c00327158 Etart////////
	//////获取远程与本地视频的窗口与参数///////
	CString m_str;
	m_btnVideoCall.GetWindowText(m_str);
	TUP_RESULT tRet = TUP_FALSE;
	if (L"视频呼叫" == m_str)
	{
		/////发起视频呼叫
		do{	

			if(0 == m_uiCallID)//没有视频呼叫
			{
				//////暂时不支持语音会话 c00327158 Start////////

				if ( CIMManage::GetIntance().GetImDlgCallNumber() >0)
				{
					CTools::ShowMessageTimeout(_T("不支持多路语音呼叫中发起点对点呼叫"),3000);
					return ;
				}
				//////暂时不支持语音会话 c00327158 End////////
				TUP_UINT32 callid;
				tRet = tup_call_start_call(&callid,CALL_E_CALL_TYPE_IPVIDEO,m_targetUserInfo.bindNO);
				if(TUP_FAIL == tRet)
				{
					AfxMessageBox(L"tup_call_start_call failed.");
					break;
				}
				m_uiCallID = callid;

				m_DlgType = SIGNLE_CALL;
				RefreshWindow();
				m_pCallCtrlDlg->SetCallState(CALLING);
				m_DataConfCall.EnableWindow(FALSE);
				///////发布状态///////
				if(!PubSelfStatus(IM_E_STATUS_BUSY))
				{
					TRACE("PubSelf Status Failed");
				}
			}
			else
			{
				if ( CIMManage::GetIntance().GetImDlgCallNumber() > 1)
				{
					CTools::ShowMessageTimeout(_T("不支持多路语音呼叫中发起点对点呼叫"),3000);
					return ;
				}
				tRet = tup_call_add_video(m_uiCallID);
				if(TUP_FAIL == tRet)
				{
					AfxMessageBox(L"tup_call_add_video failed.");
					break;
				}
			}
			SendMessage(WM_CALL_SHOW_WND,1,m_uiCallID);	

			break;
		}while(1);
		m_btnVideoCall.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ENDVIDEO)->EnableWindow(FALSE);
		if(TUP_SUCCESS != tRet)
		{
			SendMessage(WM_CALL_SHOW_WND,0,0);
			return ;
		}
		IsVidesponsor = true;
	}
	else if (L"视频降级" == m_str)
	{
		tRet = tup_call_del_video(m_uiCallID);
		if(TUP_SUCCESS != tRet)
		{
			AfxMessageBox(L"tup_call_del_video failed.");
			return ;
		}
		tup_call_destroy_video_window(CALL_E_VIDEOWND_CALLREMOTE);
		tup_call_destroy_video_window(CALL_E_VIDEOWND_CALLLOCAL);
		IsVidesponsor =false;
	}
	else
	{
		/////todo/////
	}

}

void CIMDlg::OnBnClickedButtonCall()
{
	// TODO: 在此添加控件通知处理程序代码

	//////暂时不支持多路呼叫 c00327158 Start////////

	if (CIMManage::GetIntance().GetImDlgCallNumber() > 0 || CIMManage::GetIntance().GetConfCallNUmber() >0)
	{
		CTools::ShowMessageTimeout(_T("不支持多路语音中发起点对点呼叫"),3000);
		return ;
	}
	CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
	if (pMainDlg->GetDataConfDlg())
	{
		if (0 != pMainDlg->GetDataConfDlg()->GetConfId())
		{
			CTools::ShowMessageTimeout(_T("不支持数据会议中发起点对点呼叫"),3000);
			return ;
		}
	}
	//////暂时不支持多路呼叫 c00327158 Etart////////

	switch(m_DlgType)
	{

	case  SIGNLE_CHAT:
		{
			TUP_UINT32 callid;
			TUP_RESULT tRet = tup_call_start_call(&callid,CALL_E_CALL_TYPE_IPAUDIO,m_targetUserInfo.bindNO);
			if(TUP_FAIL == tRet)
			{
				AfxMessageBox(L"tup_call_start_call failed.");
				return;
			}

			m_uiCallID = callid;

			m_DlgType = SIGNLE_CALL;
			RefreshWindow();
			m_pCallCtrlDlg->SetCallState(CALLING);
			m_btnCall.EnableWindow(FALSE);
			m_DataConfCall.EnableWindow(FALSE);
			m_btnVideoCall.EnableWindow(FALSE);
		}
		break;
	case MULTI_CHAT:
		{
			/////将数据会议标记修改为false//////
			pMainDlg->m_bisDadtaConf = false;

			TUP_UINT32 uiConfID;
			TUP_UINT32 uiCallID;
			TUP_RESULT tRet = tup_call_serverconf_create(&uiConfID,&uiCallID,m_strGroupID.c_str());
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(L"tup_call_serverconf_create failed");
				return;
			}
			m_uiConfID = uiConfID;
			m_btnCall.EnableWindow(FALSE);
			m_DataConfCall.EnableWindow(FALSE);
			m_btnAdd.EnableWindow(FALSE);
		}
		break;
	default:
		{
			AfxMessageBox(L"Error Input!");
			return;
		}
		break;
	}

	///////发布状态///////
	if(!PubSelfStatus(IM_E_STATUS_BUSY))
	{
		TRACE("PubSelf Status Failed");
	}
}

void CIMDlg::OnBnClickedButtonEndvideo()
{
	if (!m_uiCallID)
	{
		////CallID为0////
		return ;
	}
	// TODO: 在此添加控件通知处理程序代码
	TUP_RESULT tRet = tup_call_del_video(m_uiCallID);
	if(TUP_FAIL == tRet)
	{
		AfxMessageBox(L"tup_call_del_video failed.");
	}

	tup_call_destroy_video_window(CALL_E_VIDEOWND_CALLREMOTE);
	tup_call_destroy_video_window(CALL_E_VIDEOWND_CALLLOCAL);
	IsVidesponsor = false;

}

void CIMDlg::OnNMRClickListMember(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CPoint pt, pmenu;
	::GetCursorPos(&pt);
	::GetCursorPos(&pmenu);
	m_listMember.ScreenToClient(&pt);

	UINT uFlag = 0;
	int hSelectedItem = m_listMember.HitTest(pt,&uFlag);
	if (0 <= hSelectedItem)
	{
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, ID_IM_GROUP_DEL_MEM_MENU, _T("移除与会者"));

		//Modified by w00321336 to disable this item when it's a chairman at 2015-1-20 begin
		CString strCompere = m_listMember.GetItemText(hSelectedItem, COL_MEM_Compere);
		if (strCompere.Compare(L"主席") == 0)
		{
			menu.EnableMenuItem(ID_IM_GROUP_DEL_MEM_MENU, MF_DISABLED|MF_GRAYED);
		}
		//Modified by w00321336 end

		menu.TrackPopupMenu(0, pmenu.x, pmenu.y, this);		                 
	}

	*pResult = 0;
}
void CIMDlg::OnClickListMemMenuItem(UINT nID)
{
	int nItem = -1;
	POSITION pos = m_listMember.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		TRACE0("No items were selected!\n");
		return;
	}
	else
	{
		while (pos)
		{
			nItem = m_listMember.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			break;
		}
	}
	CString cstrAccount = m_listMember.GetItemText(nItem,COL_MEM_ACCOUNT);

	if(nID == ID_IM_GROUP_DEL_MEM_MENU)
	{
		IM_S_DELIMGROUPMEMBER_ARG arg;
		CTools::CString2Char(cstrAccount,arg.account,IM_D_MAX_ACCOUNT_LENGTH);
		strcpy_s(arg.groupID,IM_D_GROUPID_LENGTH,m_strGroupID.c_str());
		TUP_RESULT tRet = tup_im_deldiscussiongroupmember(&arg);
		if(tRet == TUP_FAIL)
		{
			AfxMessageBox(L"tup_im_deldiscussiongroupmember failed");
		}
		else
		{
			m_listMember.DeleteItem(nItem);
		}
	}
}
LRESULT CIMDlg::OnNetLevelNotify(WPARAM w,LPARAM)
{
	CALL_S_NETQUALITY_CHANGE* pChangeInfo = (CALL_S_NETQUALITY_CHANGE*)w;
	if(m_pCallCtrlDlg)
	{
		m_pCallCtrlDlg->SetNetInfoLevel(pChangeInfo->ulNetLevel,pChangeInfo->uLNetError);
	}
	return 0L;

}
LRESULT CIMDlg::OnNetSTATISTIC(WPARAM,LPARAM)
{
	return 0L;
}
LRESULT CIMDlg::OnGroupNotify(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}

	m_DlgType = MULTI_CHAT;
	RefreshWindow();

	if(strcmp(pNotify->adminAccount,g_Account.c_str()) != 0)
	{
		m_btnVideoCall.EnableWindow(FALSE);
		m_btnUnfold.EnableWindow(FALSE);
		m_btnAdd.EnableWindow(FALSE);
	}

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	//Add by w00321336 to fix group title & image issue at 2015-1-22 begin
	m_stcName.SetWindowText(CTools::UTF2UNICODE(pNotify->groupName));
	SetWindowText(CTools::UTF2UNICODE(pNotify->groupName));
	SetGroupHeadImg();
	//Add by w00321336 to fix group title issue at 2015-1-22 end

	////释放IM_S_DISCUSSGROUP_NOTIFY结构体中申请的TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);
		SAFE_DELETE(pNotify);

	ShowWindow(SW_SHOW);
	return 0L;
}
LRESULT CIMDlg::OnGroupInfoChange(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);
	////释放IM_S_DISCUSSGROUP_NOTIFY结构体中申请的TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);
	SAFE_DELETE(pNotify);
	ShowWindow(SW_SHOW);
	return 0L;
}
LRESULT CIMDlg::OnGroupMemAdd(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	/////释放IM_S_DISCUSSGROUP_NOTIFY结构体中TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);	SAFE_DELETE(pNotify);
	ShowWindow(SW_SHOW);
	return 0L;
}
LRESULT CIMDlg::OnGroupMemDel(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}
	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	/////释放IM_S_DISCUSSGROUP_NOTIFY结构体中TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);	SAFE_DELETE(pNotify);
	ShowWindow(SW_SHOW);
	return 0L;
}
LRESULT CIMDlg::OnGroupOwnerChange(WPARAM w,LPARAM)
{
	IM_S_DISCUSSGROUP_NOTIFY* pNotify = (IM_S_DISCUSSGROUP_NOTIFY*)w;
	if(NULL == pNotify)
	{
		return -1L;
	}	

	RefreshMemberList(pNotify->groupID);
	RefershChairMan(pNotify->adminAccount);

	/////释放IM_S_DISCUSSGROUP_NOTIFY结构体中TUPLIST内存////
	tup_im_release_tup_list(pNotify->phonelist);	SAFE_DELETE(pNotify);
	ShowWindow(SW_SHOW);
	return 0L;
}
BOOL CIMDlg::FindColum(const CString& cstrKey,int iColnum,int& iFind)
{
	int iSize = m_listMember.GetItemCount();
	for(int i = 0; i< iSize; i++)
	{
		if(cstrKey.Compare(m_listMember.GetItemText(i,iColnum)) == 0)
		{
			iFind = i;
			return TRUE;
		}
	}
	return FALSE;
}
void CIMDlg::RefershChairMan(const std::string& strAccount)
{
	CString Chairman = CTools::UTF2UNICODE(strAccount);
	int iFind = -1;
	if(FindColum(Chairman,COL_MEM_ACCOUNT,iFind))
	{
		m_listMember.SetItemText(iFind,COL_MEM_Compere,L"主席");
	}
}


void CIMDlg::OnBnClickedButtonDataConf()
{
	// TODO: 在此添加控件通知处理程序代码
	//////暂时不支持多路呼叫 c00327158 Start////////

	if (CIMManage::GetIntance().GetConfCallNUmber() >0)
	{
		CTools::ShowMessageTimeout(_T("不支持语音会议中发起数据会议"),3000);
		return ;
	}
	CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
	if (pMainDlg->GetDataConfDlg())
	{
		if (0 != pMainDlg->GetDataConfDlg()->GetConfId())
		{
			CTools::ShowMessageTimeout(_T("不支持两路数据会议"),3000);
			return ;
		}
	}
	if (m_uiCallID == 0)
	{
		if (CIMManage::GetIntance().GetImDlgCallNumber() >0)
		{
			CTools::ShowMessageTimeout(_T("不支持点对点会话与数据会议同时存在"),3000);
			return ;
		}
	}
	else
	{
		if (CIMManage::GetIntance().GetImDlgCallNumber() >1)
		{
			CTools::ShowMessageTimeout(_T("不支持点对点会话与数据会议同时存在"),3000);
			return ;
		}
	}
	////标记为数据会议////
	pMainDlg->m_bisDadtaConf = true;

	//////暂时不支持多路呼叫 c00327158 Etart////////
	switch (m_DlgType)
	{
	case MULTI_CHAT:
		{
			///创建语音会议，后转数据会议/////
			TUP_UINT32 uiConfID;
			TUP_UINT32 uiCallID;
			TUP_RESULT tRet = tup_call_serverconf_create(&uiConfID,&uiCallID,m_strGroupID.c_str());
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(L"tup_call_serverconf_create failed");
				return;
			}
			m_uiConfID = uiConfID;
			m_btnCall.EnableWindow(FALSE);
			m_DataConfCall.EnableWindow(FALSE);
			m_btnAdd.EnableWindow(FALSE);
		}
		break;
	case SIGNLE_CHAT:
		{
			////创建2人群组/////
			std::string groupname = m_strLoginName;
			groupname.append(",");
			groupname.append(m_targetUserInfo.name);
			IM_S_IMGROUP_OP_ARG addDgroupArg={0};
			IM_S_ADDIMGROUP_ACK addDGroupAck={0};
			strcpy_s(addDgroupArg.fixedgroupInfo.name,IM_D_MAX_NAME_LENGTH,groupname.c_str());
			strcpy_s(addDgroupArg.fixedgroupInfo.owner,IM_D_MAX_ACCOUNT_LENGTH,g_Account.c_str());
			TUP_RESULT tRet = tup_im_adddiscussiongroup(&addDgroupArg,&addDGroupAck);
			if(tRet != TUP_SUCCESS || addDGroupAck.result == TUP_FALSE)
			{
				TRACE("tup_im_adddiscussiongroup failed");
				return ;
			}
			m_strGroupID = addDGroupAck.id;
			/////增加群组成员
			IM_S_ADDIMGROUPMEMBER_ARG AddMemberArg;
			strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,m_strGroupID.c_str());
			strcpy_s(AddMemberArg.groupName,IM_D_MAX_NAME_LENGTH,groupname.c_str());
			strcpy_s(AddMemberArg.account,IM_D_MAX_ACCOUNT_LENGTH,m_targetUserInfo.account);

			tRet = tup_im_adddiscussiongroupmember(&AddMemberArg);
			if(tRet != TUP_SUCCESS || addDGroupAck.result == TUP_FALSE)
			{
				TRACE("tup_im_adddiscussiongroup failed");
				return ;
			}
			//////界面转群组界面//////
			SetWindowText(CTools::UTF2UNICODE(groupname));
			m_stcName.SetWindowText(CTools::UTF2UNICODE(groupname));

			//Modified by w00321336 to fix some image missing issue begin
			SetGroupHeadImg();
			//Modified by w00321336 to fix some image missing issue end

			m_stcHead.ShowWindow(SW_HIDE);
			m_stcHead.ShowWindow(SW_SHOW);

			m_btnVideoCall.EnableWindow(FALSE);
			RefreshWindow();
			/////拉入数据会议/////
			TUP_UINT32 uiConfID;
			TUP_UINT32 uiCallID;
			tRet = tup_call_serverconf_create(&uiConfID,&uiCallID,m_strGroupID.c_str());
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(L"tup_call_serverconf_create failed");
				return;
			}
			m_uiConfID = uiConfID;
			m_btnCall.EnableWindow(FALSE);
			m_DataConfCall.EnableWindow(TRUE);

		}
		break;
	case SIGNLE_CALL:
		{
			///////检查是不是视频通话//////
			CRect rcSize;
			GetWindowRect(&rcSize);
			if(rcSize.right = rcSize.left + VIDEO_WIDTH)
			{
				SendMessage(WM_CALL_SHOW_WND,0,m_uiCallID);
			}
			////创建2人群组/////
			std::string groupname = m_strLoginName;
			groupname.append(",");
			groupname.append(m_targetUserInfo.name);
			IM_S_IMGROUP_OP_ARG addDgroupArg={0};
			IM_S_ADDIMGROUP_ACK addDGroupAck={0};
			strcpy_s(addDgroupArg.fixedgroupInfo.name,IM_D_MAX_NAME_LENGTH,groupname.c_str());
			strcpy_s(addDgroupArg.fixedgroupInfo.owner,IM_D_MAX_ACCOUNT_LENGTH,g_Account.c_str());
			TUP_RESULT tRet = tup_im_adddiscussiongroup(&addDgroupArg,&addDGroupAck);
			if(tRet != TUP_SUCCESS || addDGroupAck.result == TUP_FALSE)
			{
				TRACE("tup_im_adddiscussiongroup failed");
				return ;
			}
			m_strGroupID = addDGroupAck.id;

			/////增加群组成员
			IM_S_ADDIMGROUPMEMBER_ARG AddMemberArg;
			strcpy_s(AddMemberArg.groupID,IM_D_GROUPID_LENGTH,m_strGroupID.c_str());
			strcpy_s(AddMemberArg.groupName,IM_D_MAX_NAME_LENGTH,groupname.c_str());
			strcpy_s(AddMemberArg.account,IM_D_MAX_ACCOUNT_LENGTH,m_targetUserInfo.account);

			tRet = tup_im_adddiscussiongroupmember(&AddMemberArg);
			if(tRet != TUP_SUCCESS || addDGroupAck.result == TUP_FALSE)
			{
				TRACE("tup_im_adddiscussiongroup failed");
				return ;
			}
			//////界面转群组界面//////
			SetWindowText(CTools::UTF2UNICODE(groupname));
			m_stcName.SetWindowText(CTools::UTF2UNICODE(groupname));

			//Modified by w00321336 to fix some image missing issue begin
			SetGroupHeadImg();
			//Modified by w00321336 to fix some image missing issue end

			m_stcHead.ShowWindow(SW_HIDE);
			m_stcHead.ShowWindow(SW_SHOW);

			m_btnVideoCall.EnableWindow(FALSE);
			RefreshWindow();

			//////转语音会议//
			tRet  = tup_call_serverconf_transferto_conf_non_refer(m_uiCallID,&m_uiConfID,m_strGroupID.c_str());
			if(TUP_SUCCESS != tRet)
			{
				AfxMessageBox(L"tup_call_serverconf_transferto_conf_non_refer failed.");
				return;
			}
			m_uiCallID = 0;
		}
		break;
	default:
		break;

	}

	/////转数据会议成功后，将对话框属性设置为群组对话框的多人聊天情形  c00327158 2015-11-27 Start//////
	m_DlgType = MULTI_CHAT;
	memset(&m_targetUserInfo,0,sizeof(IM_S_USERINFO));
	/////转数据会议成功后，将对话框属性设置为群组对话框的多人聊天情形  c00327158 2015-11-27 End//////

}

// ////发布状态//////
bool CIMDlg::PubSelfStatus(IM_E_USER_ONLINESTATUS _status)
{
	IM_S_STATUSARG arg;
	CTools::CString2Char(L"desc",arg.desc,IM_D_MAX_STATUS_DESCLEN);
	arg.status = _status;

	TUP_RESULT tRet = tup_im_publishstatus(&arg);
	if (TUP_SUCCESS == tRet)
	{
		///////
		CMainDlg* pMainDlg = (CMainDlg*)theApp.m_pMainDlgWnd;
		if (NULL != pMainDlg)
		{
			pMainDlg->SetCurStatus(_status);
		}
		return true ;
	} 
	else
	{
		return false;
	}

}
//Add by lWX294490 to fix DTS2015082800973 at 2015-08-27 begin
void CIMDlg::EnableCallButton(bool bEnable)
{
	//该函数用来语音会议结束后，重置IM窗口的控件
	m_btnCall.EnableWindow(bEnable);
	m_DataConfCall.EnableWindow(bEnable);
	m_btnAdd.EnableWindow(bEnable);
	return;
}
//Add by lWX294490 to fix DTS2015082800973 at 2015-08-27 end


/*
*  函数名：   ProcessCotentFromeSpaceOrUC
*  功能说明： 将受到的消息进行解码，解压缩操作
*  入参    ： cotent    服务器发来的消息
*  出参    ： cotent     解析后的消息
*/
void CIMDlg::ProcessCotentFromeSpaceOrUC(std::string& cotent)
{
	size_t pos1 = cotent.find("<g>");
	size_t pos2 = cotent.find("</g>");
	std::string compValue = cotent.substr(pos1 + 3, pos2 - pos1 - 3);
	if (compValue == "1")
	{
		pos1 = cotent.find("<c>");
		pos2 = cotent.find("</c>");
		cotent = cotent.substr(pos1 + 3, pos2 - pos1 - 3);

		// 解码
		TUP_UINT nLength = cotent.length() + 1;
		TUP_UCHAR *pDecodeMsg = new TUP_UCHAR[nLength];
		tup_im_base64_decode(cotent.c_str(), pDecodeMsg,&nLength);

		// 解压缩
		TUP_CHAR *unCompSzbuffer = NULL;
		tup_im_gzlib_uncomp((TUP_CHAR*)pDecodeMsg, &unCompSzbuffer, (TUP_INT*)&nLength);
		cotent = unCompSzbuffer;

		SAFE_DELETE_ARRAY(pDecodeMsg);
		tup_im_release_tup_mem(unCompSzbuffer);
		unCompSzbuffer = NULL;
	}
	else
	{
		CTools::ReplaceSpecialTag(cotent);
		CTools::ReplaceParagraphTag(cotent);
	}
}

/*
*  函数名：   UnCompMsgFormat
*  功能说明： 未压缩的消息组装
*  入参    ： content  界面层获取的文本消息
*  出参    ： sendContent 组装好准备发送的文本
*/
void CIMDlg::UnCompMsgFormat(CString& content, CString& sendContent)
{
	sendContent = _T("<r><g>0</g><c>");
	content.Replace(_T(" "), _T("&nbsp;"));
	content.Replace(_T("\r\n"), _T("&lt;BR&gt;"));
	content.Replace(_T("<BR>"), _T("&amp;lt;BR&amp;gt;"));
	CString strTemp
		(_T("&lt;imbody&gt;&lt;imagelist/&gt;&lt;html&gt;&lt;![CDATA[&lt;FONT style=&apos;font-size:14px&apos; face=&apos;Segoe  UI&apos;&gt;"));
	strTemp += content;
	strTemp += _T("&lt;/FONT&gt;]]&gt;&lt;/html&gt;&lt;content&gt;");
	strTemp += content;
	strTemp += _T("&lt;/content&gt;&lt;/imbody&gt;");

	sendContent += strTemp;
	sendContent += _T("</c></r>");
	//sendContent.Replace(_T("&amp;"), _T("&"));
}

/*
*  函数名：   ComCodeMsg
*  功能说明： 压缩的消息组装
*  入参    ： content  界面层获取的文本消息
*  出参    ： sendContent 组装好准备发送的文本
*/
void CIMDlg::ComCodeMsg(std::string& m_strSource, std::string& m_strTarget)
{
	CString tmpMsg = CTools::UTF2UNICODE(m_strSource);
	tmpMsg.Replace(_T("\r\n"), _T("<BR>"));
	std::string strTmpContent = CTools::UNICODE2UTF(tmpMsg);
	int nLength = strTmpContent.length();
	// 压缩
	TUP_UCHAR *ack = NULL;
	TUP_INT nMsgLength = strTmpContent.length();
	tup_im_gzlib_comp(strTmpContent.c_str(), &ack, &nMsgLength);

	// 编码n
	TUP_UINT nLen = (TUP_UINT)(nMsgLength);
	TUP_CHAR *pEncode = new TUP_CHAR[sizeof(TUP_CHAR) * (nLength + 1)];
	memcpy(pEncode, strTmpContent.c_str(), nLength);
	pEncode[nLength] = '\0';
	tup_im_base64_encode(ack, pEncode, &nLen);
	m_strTarget = pEncode;
	SAFE_DELETE_ARRAY(pEncode);
	tup_im_release_tup_mem(ack);
	ack = NULL;
	m_strTarget = "<r><g>1</g><c>" + m_strTarget + "</c></r>";
}

bool CIMDlg::IsMemberInGroup(std::string _account,std::string _groupID)
{
	IM_S_REQUESTIMGROUPMEMBERS_ARG groupMembArg;
	IM_S_GROUPUSERLIST groupList;

	strcpy_s(groupMembArg.groupID,IM_D_GROUPID_LENGTH,_groupID.c_str());
	groupMembArg.isSyncAll = TUP_TRUE;
	strcpy_s(groupMembArg.timpstamp,IM_D_MAX_TIMESTAMP_LENGTH,"19000000000000");

	tup_im_getfixedgroupmembers(&groupMembArg,&groupList);
	TUP_S_LIST* list =  groupList.memberInfo;
	while(list != NULL)
	{
		IM_S_USERINFO* groupUser = (IM_S_USERINFO*)list->data;
		if(NULL != groupUser)
		{
			if(strcmp(_account.c_str(),groupUser->account) == 0)
			{
				tup_im_release_tup_list(groupList.memberInfo);
				return true;
			}
		}
		list = list->next;
	}
	//////释放IM_S_GROUPUSERLIST中的TUP_S_LIST指针/////
	tup_im_release_tup_list(groupList.memberInfo);
}

