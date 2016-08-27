/** 
* @file httpapi.h
* 
* Copyright(C), 2012-2015, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
* 
* ������TUP IM HTTP��ϵͳ�����ӿڽṹ�嶨��ͷ�ļ��� \n
*/

/**
*
*  @{
*/


#ifndef __HTTPAPI_H__
#define __HTTPAPI_H__


#include <stdio.h>

#ifdef __cplusplus
extern "C" {    /* Assume C declarations for C++ */
#endif  /* __cplusplus */


#if (defined(WIN32) || defined(_WIN32))
#define HTTP_API  __declspec(dllexport)
#else

#define HTTP_API   __attribute__ ((__visibility__ ("default")))
#endif


typedef unsigned long HTTPHANDLE;
typedef unsigned long HTTPULong;
typedef long HTTPLong;
typedef int HTTPInt;
typedef unsigned int HTTPUInt;
typedef unsigned long long HTTPUInt64;
typedef char HTTPChar;
typedef unsigned char HTTPuint8;
typedef HTTPULong HTTPBOOL;

#define HTTP_TRUE 1
#define HTTP_FALSE 0

#define HTTP_FAILURE (-1)
#define HTTP_SUCCESS (0)

#ifdef __cplusplus
#define HTTP_NULL    0
#else
#define HTTP_NULL    ((void *)0)
#endif

#define     EN_HTTP_CURLE_ERR_START         100      /**< libcurl return error code mappting to HTTP error code  base value */
#define     HTTP_DEFAULT_HANDLE_NUM         16       /**< Default supported handle number */
#define     HTTP_MAX_HANDLE_NUM             500      /**< Max supported handle number */
#define     HTTP_MIN_HANDLE_NUM             1        /**< Min supported handle number */


/**
 * HTTPģ�������
 */
typedef enum{
    EN_HTTP_OK,
    EN_HTTP_INIT_FAIL,                      /**< 1 Init fail */
    EN_HTTP_UNINIT,                         /**< 2 uninit */
    EN_HTTP_INVALID_PARAM,                  /**< 3 invalid param */
    EN_HTTP_INVALID_HANDLE,                 /**< 4 invalid handle */ 
    EN_HTTP_HANDLE_INUSE,                   /**< 5 handle in using, can't be set*/ 
    EN_HTTP_HANDLE_STATE_ERROR,             /**< 6 current handle state not support this operation*/
    EN_HTTP_ALLOC_MEM_FAIL,                 /**< 7 alloc fail */
    EN_HTTP_CREATE_HANDLE_FAIL,             /**< 8 alloc handle fail */
    EN_HTTP_INVALID_TLS_MODE,               /**< 9 tls mode error */
    EN_HTTP_INVALID_URL,                    /**< 10 invalid URL */
    EN_HTTP_INVALID_HEAD_TYPE,              /**< 11 invalid head type */
    EN_HTTP_OPEN_LOG_FAIL,                  /**< 12 open log file fail */
    EN_HTTP_WRITE_LOG_FAIL,                 /**< 13 write log file fail */
    EN_HTTP_INVALID_FILEPATH,               /**< 14 invalid file path */
    EN_HTTP_HANDLE_RELEASED,                /**< 15 handle has been released */
    EN_HTTP_CREATE_MUTEX_FAIL,              /**< 16 create mutex fail */
    EN_HTTP_LOCK_MUTEX_FAIL,                /**< 17 lock mutex fail*/
    EN_HTTP_UNLOCK_MUTEX_FAIL,              /**< 18 unlock mutex fail */
    EN_HTTP_CREATE_THREAD_FAIL,             /**< 19 create thread fail */
    EN_HTTP_NOT_SUPPORT,                    /**< 20 not support this function */
    EN_HTTP_SVN_SOCKET_CREATE_FAIL,         /**< 21 svn socket create fail */
    EN_HTTP_SVN_SOCKET_CONNECT_FAIL,        /**< 22 svn socket connect fail */
    EN_HTTP_SVN_SOCKET_SLECET_FAIL,         /**< 23 svn socket select fail */
    EN_HTTP_SVN_SOCKET_SEND_FAIL,           /**< 24 svn socket send fail */
    EN_HTTP_SVN_SOCKET_RECV_FAIL,           /**< 25 svn socket recv fail */
    EN_HTTP_GETHOSTNAME_FAIL,               /**< 26 get hostname fail */
    EN_HTTP_NET_NTOA_FAIL,                  /**< 27 IP net transfer fail*/
    EN_HTTP_RESPONSE_PARSE_ERR,             /**< 28 response parse fail */
    EN_HTTP_INVALID_AUTH_MODE,              /**< 29.invalid auth mode */
    EN_HTTP_NOT_LOGIN,                      /**< 30 is not login  */
    EN_HTTP_LOGINING,                       /**< 31 is  logining  */
    EN_HTTP_UPLOAD_DOWNLOAD_TIMEOUT,        /**< 32 is  TIMEOUT  */
    EN_HTTP_LOGINED,                        /**< 33 is  logined  */
    EN_HTTP_INITED,                         /**< 34 is  inited  */
    EN_HTTP_LOGPATH_TOOLONG,                /**< 35 is  LogPath is too long */
    EN_HTTP_LOGPATH_EMPTY,                  /**< 36 is  LogPath is empty */

    EN_HTTP_CURLE_UNSUPPORTED_PROTOCOL = EN_HTTP_CURLE_ERR_START + 1,    /**< 101 */
    EN_HTTP_CURLE_FAILED_INIT,             /**< 102 */
    EN_HTTP_CURLE_URL_MALFORMAT,           /**< 103 */
    EN_HTTP_CURLE_NOT_BUILT_IN,            /**< 104 */
    EN_HTTP_CURLE_COULDNT_RESOLVE_PROXY,   /**< 105 */
    EN_HTTP_CURLE_COULDNT_RESOLVE_HOST,    /**< 106 */
    EN_HTTP_CURLE_COULDNT_CONNECT,         /**< 107 */
    EN_HTTP_CURLE_FTP_WEIRD_SERVER_REPLY,  /**< 108 */
    EN_HTTP_CURLE_REMOTE_ACCESS_DENIED,    /**< 109 a service was denied by the server due to lack of access-when login fails this is not returned */
    EN_HTTP_CURLE_FTP_ACCEPT_FAILED,       /**< 110 */
    EN_HTTP_CURLE_FTP_WEIRD_PASS_REPLY,    /**< 111 */
    EN_HTTP_CURLE_FTP_ACCEPT_TIMEOUT,      /**< 112 - timeout occurred accepting server*/
    EN_HTTP_CURLE_FTP_WEIRD_PASV_REPLY,    /**< 113 */
    EN_HTTP_CURLE_FTP_WEIRD_227_FORMAT,    /**< 114 */
    EN_HTTP_CURLE_FTP_CANT_GET_HOST,       /**< 115 */
    EN_HTTP_CURLE_OBSOLETE16,              /**< 116 - NOT USED */
    EN_HTTP_CURLE_FTP_COULDNT_SET_TYPE,    /**< 117 */
    EN_HTTP_CURLE_PARTIAL_FILE,            /**< 118 */
    EN_HTTP_CURLE_FTP_COULDNT_RETR_FILE,   /**< 119 */
    EN_HTTP_CURLE_OBSOLETE20,              /**< 120 - NOT USED */
    EN_HTTP_CURLE_QUOTE_ERROR,             /**< 121 - quote command failure */
    EN_HTTP_CURLE_HTTP_RETURNED_ERROR,     /**< 122 */
    EN_HTTP_CURLE_WRITE_ERROR,             /**< 123 */
    EN_HTTP_CURLE_OBSOLETE24,              /**< 124 - NOT USED */
    EN_HTTP_CURLE_UPLOAD_FAILED,           /**< 125 - failed upload "command" */
    EN_HTTP_CURLE_READ_ERROR,              /**< 126 - couldn't open/read from file */
    EN_HTTP_CURLE_OUT_OF_MEMORY,           /**< 127 Note: CURLE_OUT_OF_MEMORY may sometimes indicate a conversion error
                                                    <br>instead of a memory allocation error if CURL_DOES_CONVERSIONS  is defined */
    EN_HTTP_CURLE_OPERATION_TIMEDOUT,      /**< 128 - the timeout time was reached */
    EN_HTTP_CURLE_OBSOLETE29,              /**< 129 - NOT USED */
    EN_HTTP_CURLE_FTP_PORT_FAILED,         /**< 130 - FTP PORT operation failed */
    EN_HTTP_CURLE_FTP_COULDNT_USE_REST,    /**< 131 - the REST command failed */
    EN_HTTP_CURLE_OBSOLETE32,              /**< 132 - NOT USED */
    EN_HTTP_CURLE_RANGE_ERROR,             /**< 133 - RANGE "command" didn't work */
    EN_HTTP_CURLE_HTTP_POST_ERROR,         /**< 134 */
    EN_HTTP_CURLE_SSL_CONNECT_ERROR,       /**< 135 - wrong when connecting with SSL */
    EN_HTTP_CURLE_BAD_DOWNLOAD_RESUME,     /**< 136 - couldn't resume download */
    EN_HTTP_CURLE_FILE_COULDNT_READ_FILE,  /**< 137 */
    EN_HTTP_CURLE_LDAP_CANNOT_BIND,        /**< 138 */
    EN_HTTP_CURLE_LDAP_SEARCH_FAILED,      /**< 139 */
    EN_HTTP_CURLE_OBSOLETE40,              /**< 140 - NOT USED */
    EN_HTTP_CURLE_FUNCTION_NOT_FOUND,      /**< 141 */
    EN_HTTP_CURLE_ABORTED_BY_CALLBACK,     /**< 142 */
    EN_HTTP_CURLE_BAD_FUNCTION_ARGUMENT,   /**< 143 */
    EN_HTTP_CURLE_OBSOLETE44,              /**< 144 - NOT USED */
    EN_HTTP_CURLE_INTERFACE_FAILED,        /**< 145 - CURLOPT_INTERFACE failed */
    EN_HTTP_CURLE_OBSOLETE46,              /**< 146 - NOT USED */
    EN_HTTP_CURLE_TOO_MANY_REDIRECTS ,     /**< 147 - catch endless re-direct loops */
    EN_HTTP_CURLE_UNKNOWN_OPTION,          /**< 148 - User specified an unknown option */
    EN_HTTP_CURLE_TELNET_OPTION_SYNTAX ,   /**< 149 - Malformed telnet option */
    EN_HTTP_CURLE_OBSOLETE50,              /**< 150 - NOT USED */
    EN_HTTP_CURLE_PEER_FAILED_VERIFICATION, /**< 151 - peer's certificate or fingerprint wasn't verified fine */
    EN_HTTP_CURLE_GOT_NOTHING,             /**< 152 - when this is a specific error */
    EN_HTTP_CURLE_SSL_ENGINE_NOTFOUND,     /**< 153 - SSL crypto engine not found */
    EN_HTTP_CURLE_SSL_ENGINE_SETFAILED,    /**< 154 - can not set SSL crypto engine as default */
    EN_HTTP_CURLE_SEND_ERROR,              /**< 155 - failed sending network data */
    EN_HTTP_CURLE_RECV_ERROR,              /**< 156 - failure in receiving network data */
    EN_HTTP_CURLE_OBSOLETE57,              /**< 157 - NOT IN USE */
    EN_HTTP_CURLE_SSL_CERTPROBLEM,         /**< 158 - problem with the local certificate */
    EN_HTTP_CURLE_SSL_CIPHER,              /**< 159 - couldn't use specified cipher */
    EN_HTTP_CURLE_SSL_CACERT,              /**< 160 - problem with the CA cert (path?) */
    EN_HTTP_CURLE_BAD_CONTENT_ENCODING,    /**< 161 - Unrecognized/bad encoding */
    EN_HTTP_CURLE_LDAP_INVALID_URL,        /**< 162 - Invalid LDAP URL */
    EN_HTTP_CURLE_FILESIZE_EXCEEDED,       /**< 163 - Maximum file size exceeded */
    EN_HTTP_CURLE_USE_SSL_FAILED,          /**< 164 - Requested FTP SSL level failed */
    EN_HTTP_CURLE_SEND_FAIL_REWIND,        /**< 165 - Sending the data requires a rewind that failed */
    EN_HTTP_CURLE_SSL_ENGINE_INITFAILED,   /**< 166 - failed to initialise ENGINE */
    EN_HTTP_CURLE_LOGIN_DENIED,            /**< 167 - user, password or similar was not accepted and we failed to login */
    EN_HTTP_CURLE_TFTP_NOTFOUND,           /**< 168 - file not found on server */
    EN_HTTP_CURLE_TFTP_PERM,               /**< 169 - permission problem on server */
    EN_HTTP_CURLE_REMOTE_DISK_FULL,        /**< 170 - out of disk space on server */
    EN_HTTP_CURLE_TFTP_ILLEGAL,            /**< 171 - Illegal TFTP operation */
    EN_HTTP_CURLE_TFTP_UNKNOWNID,          /**< 172 - Unknown transfer ID */
    EN_HTTP_CURLE_REMOTE_FILE_EXISTS,      /**< 173 - File already exists */
    EN_HTTP_CURLE_TFTP_NOSUCHUSER,         /**< 174 - No such user */
    EN_HTTP_CURLE_CONV_FAILED,             /**< 175 - conversion failed */
    EN_HTTP_CURLE_CONV_REQD,               /**< 176 - caller must register conversion callbacks using curl_easy_setopt options
                                               <br>CURLOPT_CONV_FROM_NETWORK_FUNCTION,CURLOPT_CONV_TO_NETWORK_FUNCTION, and CURLOPT_CONV_FROM_UTF8_FUNCTION */
    EN_HTTP_CURLE_SSL_CACERT_BADFILE,      /**< 177 - could not load CACERT file, missing  or wrong format */
    EN_HTTP_CURLE_REMOTE_FILE_NOT_FOUND,   /**< 178 - remote file not found */
    EN_HTTP_CURLE_SSH,                     /**< 179 - error from the SSH layer, somewhat generic so the error message will be of
                                               <br>interest when this has happened */
    EN_HTTP_CURLE_SSL_SHUTDOWN_FAILED,     /**< 180 - Failed to shut down the SSL connection */
    EN_HTTP_CURLE_AGAIN,                   /**< 181 - socket is not ready for send/recv,wait till it's ready and try again */
    EN_HTTP_CURLE_SSL_CRL_BADFILE,         /**< 182 - could not load CRL file, missing or wrong format (Added in 7.19.0) */
    EN_HTTP_CURLE_SSL_ISSUER_ERROR,        /**< 183 - Issuer check failed. */
    EN_HTTP_CURLE_FTP_PRET_FAILED,         /**< 184 - a PRET command failed */
    EN_HTTP_CURLE_RTSP_CSEQ_ERROR,         /**< 185 - mismatch of RTSP CSeq numbers */
    EN_HTTP_CURLE_RTSP_SESSION_ERROR,      /**< 186 - mismatch of RTSP Session Ids */
    EN_HTTP_CURLE_FTP_BAD_FILE_LIST,       /**< 187 - unable to parse FTP file list */
    EN_HTTP_CURLE_CHUNK_FAILED,            /**< 188 - chunk callback reported error */

    EN_HTTP_CURL_RSP_200            = 200, /**< 200 http/https�ɹ���Ӧ*/
    EN_HTTP_CURL_CREATE_HANDLE_FAIL = 201, /**< 201 */
    EN_HTTP_CURL_SET_HEAD_FAIL,            /**< 202 */
    EN_HTTP_ERRORCODE_BUTT                 /**< never used */
}EN_HTTP_ERRORCODE;


/**
 * TLSģʽ
 */
typedef enum{
    EN_TLS_CLOSE              = 0, /**< TLS closed */
    EN_TLS_VERIFY_NONE        = 1, /**< TLS opened,  but not verify */
    EN_TLS_VERIFY_SERVER      = 2, /**< TLS opened, only verify server */
    EN_TLS_VERIFY_CLIENT      = 3, /**< TLS opened��only verify client */
    EN_TLS_VERIFY_BOTH        = 4, /**< TLS opened��verify server and client both */
    EN_TLS_MODE_BUTT
}EN_TLS_MODE;

/**
 * TLS��Ȩ������ģʽ
 */
typedef enum{
    EN_VERIFY_SERVER_PEER             = 0, /**< only verify certificate (default mode) */
    EN_VERIFY_SERVER_PEER_AND_HOST    = 1, /**< verify certificate and host both */
    EN_VERIFY_SERVER_BUTT
}EN_VERIFY_SERVER_MODE;


/**
 * TLS����
 */
typedef struct tagHTTP_TLS_PARA
{
    HTTPChar    *pcCaCertPath;                  /**< CA certificate */
    HTTPChar    *pcClientCertPath;              /**< client certificate */
    HTTPChar    *pcClientCertType;              /**< client certificate type ("PEM"/"DER") */
    HTTPChar    *pcClientKeyPath;               /**< client key  */
    HTTPChar    *pcClientKeyType;               /**< client key type ("PEM"/"DER"/"ENG") */
    HTTPChar    *pcClientPrivKeyPw;             /**< client key password  */
    EN_VERIFY_SERVER_MODE  enVerifyServerMode;  /**< TLS VERIFY SERVER MODE */

    tagHTTP_TLS_PARA()
    {
        pcCaCertPath = HTTP_NULL;
        pcClientCertPath = HTTP_NULL;
        pcClientCertType = HTTP_NULL;
        pcClientKeyPath = HTTP_NULL;
        pcClientKeyType = HTTP_NULL;
        pcClientPrivKeyPw = HTTP_NULL;
        enVerifyServerMode = EN_VERIFY_SERVER_PEER;
    }
}ST_HTTP_TLS_PARA;

/**
 * HTTP ͷ���б�
 */
typedef struct tagST_HTTP_HEAD_LIST
{
    HTTPChar                      *pcHeadType;  /**< ͷ������ */
    HTTPChar                      *pcHeadValue; /**< ͷ��ֵ */
    struct tagST_HTTP_HEAD_LIST   *pNext;       /**< ��һ���ڵ� */

    tagST_HTTP_HEAD_LIST()
    {
        pcHeadType = HTTP_NULL;
        pcHeadValue = HTTP_NULL;
        pNext = HTTP_NULL;
    }

}ST_HTTP_HEAD_LIST;


/**
 * HTTP������
 */
typedef struct tagST_HTTP_BODY
{
    HTTPChar       *pcbody;    /**< body�� */
    HTTPULong       ulBodyLen; /**< body���� */

    tagST_HTTP_BODY()
    {
        pcbody = HTTP_NULL;
        ulBodyLen = 0;
    }

}ST_HTTP_BODY;

/**
 * HTTP������Ӧ
 */
typedef struct tagST_HTTP_RSP
{
    HTTPULong                  ulStatusCode;  /**< ��Ӧ�� */
    ST_HTTP_HEAD_LIST          *pstHeadList;  /**< ��Ӧͷ���б� */
    ST_HTTP_BODY               stHttpBody;    /**< ��Ӧ��Ϣ�� */

    tagST_HTTP_RSP()
    {
        ulStatusCode = 0;
        pstHeadList = HTTP_NULL;
    }

}ST_HTTP_RSP;

/**
 * ��Ȩģʽ
 */
typedef enum {
    EN_AUTH_CLOSE  = 0,          /**< auth closed (default mode) */
    EN_AUTH_BASIC  = 1,          /**< BASIC mode */
    EN_AUTH_DIGEST = 2,          /**< DIGEST mode */
    EN_AUTH_BASIC_DIGEST = 3,    /**< BASIC and DIGEST mode (adapted by internal) */
    EN_AUTH_MODE_BUTT 
} EN_AUTH_MODE;


/**
 * ��Ȩ����
 */
typedef struct tagHTTP_AUTH_PARA
{
    HTTPChar    *pcUserName;    /**< auth username */
    HTTPChar    *pcPassWord;    /**< auth password */
    HTTPChar    *pcCnonce;      /**< auth cnonce��if not configured, use random string which created by inernal) */
    
    tagHTTP_AUTH_PARA()
    {
        pcUserName = HTTP_NULL;
        pcPassWord = HTTP_NULL;
        pcCnonce = HTTP_NULL;
    }
}ST_HTTP_AUTH_PARA;


 /**
 * @brief �ļ���������Ӧ֪ͨ
 * 
 * @param [in] OFFLINEHANDLE fileHandle         <b>:</b> �ļ����
 * @param [in] TUP_ULONG enCode                 <b>:</b> ��������0��ʾ�ɹ�����0��ʾ�쳣
 * @param [in] OFFLINE_RSPFILEINFO *pstFileRsp  <b>:</b> ������Ӧ������ulStatusCode��ʾHTTP/HTTPS��Ӧ��200��ʾ�ɹ�����200��ʾ�쳣
 * @param [in] void *userInfo                   <b>:</b> �û��Զ�����Ϣ
 * @param [out] NA
 * @retval typedef int (* <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
typedef int (*HttpRspNotify)(HTTPHANDLE handle, EN_HTTP_ERRORCODE enCode, ST_HTTP_RSP *pstHttpRsp, void *userInfo);


/**
 * @brief �ļ��������(����)֪ͨ
 * 
 * @param [in] OFFLINEHANDLE fileHandle  <b>:</b> �ļ����
 * @param [in] TUP_UINT64 ulTotal        <b>:</b> ��Ҫ�����������С����λ: �ֽ�
 * @param [in] TUP_UINT64 ulNow          <b>:</b> �Ѿ�����Ĵ�С����λ: �ֽ�
 * @param [in] void *userInfo            <b>:</b> �û��Զ�����Ϣ
 * @param [out] NA
 * @retval typedef void (* <b>:</b> 
 * 
 * @attention NA
 * @see NA
 **/
typedef void (*HttpFileTransRrogressNotify)(HTTPHANDLE handle, HTTPUInt64 ulTotal, HTTPUInt64 ulNow, void *userInfo);

/**
 * http���ò���
 */
typedef struct tagST_HTTP_HANDLE_CONFIG
{

    HTTPChar               *pcHostIP;           /**< ����Զ˵�IP */
    HTTPUInt                hostPort;           /**< ����Զ˵Ķ˿� */

    EN_TLS_MODE             enTlsMode;          /**< TLSģʽ */
    ST_HTTP_TLS_PARA        stTLSPara;          /**< TLS���� */

    EN_AUTH_MODE            enAuthMode;         /**< auth mode */
    ST_HTTP_AUTH_PARA       stAuthPara;         /**< auth parameter */

    HTTPUInt               timeout;             /**< HTTP�����ܹ�ά�ֵ��ʱ�䣬��λ�� */
    HTTPUInt               tryConnectTimeout;   /**< HTTP������������ӳ�ʱʱ�� */
    
    tagST_HTTP_HANDLE_CONFIG()
    {
        pcHostIP = HTTP_NULL;
        hostPort  = 0;
        enTlsMode = EN_TLS_CLOSE;
        enAuthMode = EN_AUTH_CLOSE;
        timeout = 0;
        tryConnectTimeout = 0;
    }
}ST_HTTP_HANDLE_CONFIG;

/**
 * http������
 */
typedef struct tagST_HTTP_REQUEST_LINE
{
    HTTPChar          *pcMethod;     /**< ����ʽ */
    HTTPChar          *pcUrl;        /**< ������url */

    tagST_HTTP_REQUEST_LINE()
    {
        pcMethod = HTTP_NULL;
        pcUrl = HTTP_NULL;
    }

}ST_HTTP_REQUEST_LINE;


/**
 * HTTP��־����
 */
typedef enum
{
    EN_HTTP_LOG_NONE         = 0,    /**<  LOG CLOSED */
    EN_HTTP_LOG_ERROR        = 1,    /**<  ERROR LEVEL */
    EN_HTTP_LOG_WARNING      = 2,    /**<  WARNING LEVEL */
    EN_HTTP_LOG_INFO         = 3,    /**<  INFOMATION LEVEL */
    EN_HTTP_LOG_DEBUG        = 4,    /**<  DEBUG LEVEL */
    EN_HTTP_LOG_BUTT
}EN_HTTP_LOG_LEVEL;


/**
 * HTTP���ò���
 */
typedef struct tagST_HTTP_CONFIG
{
    EN_HTTP_LOG_LEVEL          enLevel;             /**<  log level */
    HTTPUInt                   uiLogFileSize;       /**<  log file size  */
    HTTPChar                   *pcFilePath;         /**<  log file path */
    HTTPUInt                   uiHandleNum;         /**<  supported handle number */
    HTTPBOOL                   bUseSvn;             /**<  use svn flag(default value is false) */
    HTTPBOOL                   bUseSvnFile;         /**<  use svn file flag(default value is false) */
    
    tagST_HTTP_CONFIG()
    {
        enLevel = EN_HTTP_LOG_NONE;
        pcFilePath = HTTP_NULL;
        uiLogFileSize = 3;
        uiHandleNum = HTTP_DEFAULT_HANDLE_NUM;
        bUseSvn = HTTP_FALSE;
        bUseSvnFile = HTTP_FALSE;
    }

}ST_HTTP_CONFIG;


/**
 * ��Ƭ�������
 */
typedef struct tagST_HTTP_PARTINFO
{
    HTTPUInt                    uiPartId;            /**< partid  */
    HTTPUInt                    uiPartSize;          /**< ÿƬĬ�ϵĴ�С */
    HTTPUInt                    uiThisPartSize;      /**< ��Ƭ������ļ���С */
    
    tagST_HTTP_PARTINFO()
    {
        uiPartId = 0;
        uiPartSize = 0;
        uiThisPartSize = 0;
    }

}ST_HTTP_PARTINFO;


/**
 * �ļ���Ϣ
 */
typedef struct tagST_HTTP_STAT
{
    unsigned short ulMode;          /**< �ļ�Ȩ�� */
    unsigned long ulCreateTime;     /**< �ļ�����ʱ�� */
    unsigned long ulModifyTime;     /**< �ļ��޸�ʱ�� */
    unsigned long ulAccessTime;     /**< �ļ�������ʱ�� */
    unsigned long ulSize;           /**< �ļ���С */
}ST_HTTP_STAT;

 
/**
 * @brief HTTP sdk��ʼ��
 * 
 * @param [in] const ST_HTTP_CONFIG *pstConfig  <b>:</b> ��ʼ������
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_UnInit
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_Init(const ST_HTTP_CONFIG *pstConfig);


/**
 * @brief HTTP sdkȥ��ʼ��
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention Ҫ��HTTPAPI_Init��Ӧ
 * @see HTTPAPI_Init
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_UnInit();

 
/**
 * @brief ����http crul easy handle
 * 
 * @param [in] const ST_HTTP_HANDLE_CONFIG *pstHttpHandleConfig  <b>:</b> �������ƿ�����
 * @param [in] void *userInfo                                    <b>:</b> �Զ����û���Ϣ
 * @param [out] HTTPHANDLE *pHandle                              <b>:</b> handle
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_CreateHandleByHandle
 * @see HTTPAPI_ReleaseHandle
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_CreateHandle(const ST_HTTP_HANDLE_CONFIG *pstHttpHandleConfig, void *userInfo, HTTPHANDLE *pHandle);

 
/**
 * @brief ����handle�������ƿ�
 * 
 * @param [in] const ST_HTTP_HANDLE_CONFIG *pstHttpHandleConfig  <b>:</b> �������ƿ�����
 * @param [in] void *userInfo                                    <b>:</b> �Զ����û���Ϣ
 * @param [in] HTTPHANDLE Handle                                 <b>:</b> handle
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �������ƿ��ʱ��handle����㴫�룬��������򷵻سɹ�
 * @see HTTPAPI_CreateHandle
 * @see HTTPAPI_ReleaseHandle
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_CreateHandleByHandle(const ST_HTTP_HANDLE_CONFIG *pstHttpHandleConfig, void *userInfo, HTTPHANDLE Handle);

/**
 * @brief �ͷſ��ƿ�
 * 
 * @param [in] HTTPHANDLE handle  <b>:</b> handle
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_CreateHandle
 * @see HTTPAPI_CreateHandleByHandle
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_ReleaseHandle(HTTPHANDLE handle);


/**
 * @brief ����HTTP������ʼ��
 * 
 * @param [in] HTTPHANDLE handle                           <b>:</b> handle
 * @param [in] const ST_HTTP_REQUEST_LINE *pstRequestLine  <b>:</b> ��������Ϣ
 * @param [out] NA
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_AddHead
 * @see HTTPAPI_SetBody
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_SetRequestLine(HTTPHANDLE handle, const ST_HTTP_REQUEST_LINE *pstRequestLine);

 
/**
 * @brief ����httpͷ��
 * 
 * @param [in] HTTPHANDLE handle            <b>:</b> handle
 * @param [in] const HTTPChar *pcHeadType   <b>:</b> ͷ������
 * @param [in] const HTTPChar *pcHeadValue  <b>:</b> ͷ��ֵ
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_SetRequestLine
 * @see HTTPAPI_SetBody
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_AddHead(HTTPHANDLE handle, const HTTPChar *pcHeadType, const HTTPChar *pcHeadValue);

 
/**
 * @brief ����http�����body
 * 
 * @param [in] HTTPHANDLE handle            <b>:</b> handle
 * @param [in] const ST_HTTP_BODY* pstBody  <b>:</b> ����body��
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_AddHead
 * @see HTTPAPI_SetRequestLine
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_SetBody(HTTPHANDLE handle, const ST_HTTP_BODY* pstBody);


/**
 * @brief ͬ������ͨ�õ�http����
 * 
 * @param [in] HTTPHANDLE handle          <b>:</b> handle
 * @param [out] ST_HTTP_RSP **pstHttpRsp  <b>:</b> http��Ӧ�ṹ
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention ��Ӧ�ṹʹ����ɺ���Ҫ�ͷ�
 * @see HTTPAPI_ReleaseSynRsp
 * @see HTTPAPI_ReqAsynSend
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_ReqSynSend(HTTPHANDLE handle, ST_HTTP_RSP **pstHttpRsp);

 
/**
 * @brief �ͷ�ͬ�������������Ӧ
 * 
 * @param [in] ST_HTTP_RSP *pstHttpRsp  <b>:</b> http�������Ӧ
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_ReqSynSend
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_ReleaseSynRsp(ST_HTTP_RSP *pstHttpRsp);

 
/**
 * @brief �첽����ͨ�õ�http����
 * 
 * @param [in] HTTPHANDLE handle                <b>:</b> handle
 * @param [in] HttpRspNotify httpRspNotifyFunc  <b>:</b> �첽�������Ӧ�ص�
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_ReqSynSend
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_ReqAsynSend(HTTPHANDLE handle, HttpRspNotify httpRspNotifyFunc);

 
/**
 * @brief �����ļ�ģʽ
 * 
 * @param [in] HTTPHANDLE handle           <b>:</b> handle
 * @param [in] const HTTPChar* pcFileMode  <b>:</b> �ļ�����ʱ���ļ���ģʽ
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �����ļ�ģʽ�����ļ��ϴ����ļ����ؽӿڵ���ǰ���ã�ȷ���ļ�����ʱ���ļ���ģʽ
 * @see NA
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_SetFileMode(HTTPHANDLE handle, const HTTPChar* pcFileMode);


/**
 * @brief �������ط�ʽ
 * 
 * @param [in] HTTPHANDLE handle       <b>:</b> handle
 * @param [in] HTTPBOOL bKeepDownload  <b>:</b> �Ƿ�֧�ֶϵ�����
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �������ط�ʽ���Ƿ�֧�ֶϵ����أ�֧�ֵĻ�������ȡ����ʱ��ɾ��ԭ���Ѿ����ص��ļ�
 * @see NA
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_SetDownloadMode(HTTPHANDLE handle, HTTPBOOL bKeepDownload);


/**
 * @brief �����ض����Ƿ�͸����offline��
 * 
 * @param [in] HTTPHANDLE handle         <b>:</b> handle
 * @param [in] HTTPBOOL bCurlNotRepoint  <b>:</b> ���ǽ�307�ض���͸����offline��
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention bCurlNotRepoint 1 ��ʾ͸�����ϲ㣬 0��ʾ��͸�����ϲ�
 * @see NA
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_SetCurlNotRepoint(HTTPHANDLE handle, HTTPBOOL bCurlNotRepoint);


/**
 * @brief ���÷�Ƭ�����ļ��Ĵ�С
 * 
 * @param [in] HTTPHANDLE handle           <b>:</b> handle
 * @param [in] HTTPUInt64 iPartFileLength  <b>:</b> ��Ƭ�Ĵ�С,��λ���ֽ�
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention 
 * @see NA
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_SetPartFileLength(HTTPHANDLE handle, HTTPUInt64 iPartFileLength);


/**
 * @brief �����Ƿ���curlLog
 * 
 * @param [in] HTTPHANDLE handle       <b>:</b> handle
 * @param [in] HTTPBOOL bStartCurlLog  <b>:</b> �Ƿ���curllog
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention 
 * @see NA
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_SetStartCurlLog(HTTPHANDLE handle, HTTPBOOL bStartCurlLog);

 
/**
 * @brief http�����ļ�
 * 
 * @param [in] HTTPHANDLE handle                                   <b>:</b> handle
 * @param [in] HTTPChar* pcPath                                    <b>:</b> �ļ�·����UTF8��ʽ
 * @param [in] HttpFileTransRrogressNotify httpFileProgNotifyFunc  <b>:</b> ���Ȼص�
 * @param [in] HttpRspNotify httpRspNotifyFunc                     <b>:</b> �ϴ��ļ�����ص�
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �첽�ӿڣ����ú�ֱ���ȷ��أ��������ص�����:
 *            �ļ�������Ȼص� httpFileProgNotifyFunc, ֪ͨUI�ļ��������
 *            ��Ӧ�ص�httpRspNotifyFunc���ɻ��status code��body��head����Ϣ
 * @see HTTPAPI_UploadFilePart
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_UploadFile(HTTPHANDLE handle, HTTPChar* pcPath, 
                            HttpFileTransRrogressNotify httpFileProgNotifyFunc, HttpRspNotify httpRspNotifyFunc);

 
/**
 * @brief http���ͷ�Ƭ�ļ�
 * 
 * @param [in] HTTPHANDLE handle                                   <b>:</b> handle
 * @param [in] HTTPChar* pcPath                                    <b>:</b> �ļ�·��
 * @param [in] ST_HTTP_PARTINFO* pstPartInfo                       <b>:</b> �ļ���Ƭ��Ϣ
 * @param [in] HttpFileTransRrogressNotify httpFileProgNotifyFunc  <b>:</b> ���Ȼص�
 * @param [in] HttpRspNotify httpRspNotifyFunc                     <b>:</b> �ļ��ϴ�����ص�
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �첽�ӿڣ����ú�ֱ���ȷ��أ��������ص�����:
 *            �ļ�������Ȼص� httpFileProgNotifyFunc, ֪ͨUI�ļ��������
 *            ��Ӧ�ص�httpRspNotifyFunc���ɻ��status code��body��head����Ϣ
 * @see HTTPAPI_UploadFile
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_UploadFilePart(HTTPHANDLE handle, HTTPChar* pcPath, ST_HTTP_PARTINFO* pstPartInfo, 
                                     HttpFileTransRrogressNotify httpFileProgNotifyFunc, HttpRspNotify httpRspNotifyFunc);
 
/**
 * @brief http�����ļ�
 * 
 * @param [in] HTTPHANDLE handle                                   <b>:</b> handle
 * @param [in] HTTPChar* pcPath                                    <b>:</b> �ļ�·��
 * @param [in] HttpFileTransRrogressNotify httpFileProgNotifyFunc  <b>:</b> ���Ȼص�
 * @param [in] HttpRspNotify httpRspNotifyFunc                     <b>:</b> ����ص�
 * @param [out] NA
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention �첽�ӿڣ����ú�ֱ���ȷ��أ��������ص�����:
 *            �ļ�������Ȼص� httpFileProgNotifyFunc, ֪ͨUI�ļ��������
 *            ��Ӧ�ص�httpRspNotifyFunc���ɻ��status code��body��head����Ϣ
 * @see NA
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_DownloadFile(HTTPHANDLE handle, HTTPChar* pcPath, 
                          HttpFileTransRrogressNotify httpFileProgNotifyFunc, HttpRspNotify httpRspNotifyFunc);

/**
 * @brief ����Ƿ����MDM���ܷ�ʽ
 * 
 * @param [in] void
 * @retval HTTP_API HTTPBOOL <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
HTTP_API HTTPBOOL          HTTPAPI_CheckBeUseSvnFile(void);

/**
 * @brief MDM��ʽ���ļ�
 * 
 * @param [in] const HTTPChar* pcPath  <b>:</b> �ļ�·��
 * @param [in] const HTTPChar* pcMode  <b>:</b> ���ļ���ʽ
 * @retval HTTP_API FILE* <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_FileFclose
 **/
HTTP_API FILE*             HTTPAPI_FileFopen(const HTTPChar* pcPath, const HTTPChar* pcMode);


/**
 * @brief MDM��ʽ�ر��ļ�
 * 
 * @param [in] FILE* pstFileHandle  <b>:</b> �ļ����
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_FileFopen
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_FileFclose(FILE* pstFileHandle);

/**
 * @brief MDM��ʽ��ȡ�ļ�����
 * 
 * @param [in] HTTPChar* pucOutBuf   <b>:</b> ��ȡ�ļ����ݴ��buf
 * @param [in] HTTPULong  ulSize     <b>:</b> ��ȡ�ļ��ĵ�����С
 * @param [in] HTTPULong  ulCount    <b>:</b> ��ȡ�ļ��ĸ���
 * @param [in] FILE* pstFileHandle   <b>:</b> �ļ����
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_FileFwrite
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_FileFread(HTTPuint8* pucOutBuf, HTTPULong  ulSize, HTTPULong  ulCount,FILE* pstFileHandle);

/**
 * @brief MDM��ʽд�ļ�����
 * 
 * @param [in] const HTTPuint8*    pucInBuf  <b>:</b> д�ļ����ݴ��buf
 * @param [in] HTTPULong ulSize              <b>:</b> д�ļ�������С
 * @param [in] HTTPULong ulCount             <b>:</b> д�ļ��ܵĸ���
 * @param [in] FILE*  pstFileHandle              <b>:</b> �ļ����
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_FileFread
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_FileFwrite(const HTTPuint8*  pucInBuf, HTTPULong ulSize, HTTPULong ulCount, FILE*  pstFileHandle);

/**
 * @brief MDM��ʽ�ƶ��ļ�λ��
 * 
 * @param [in] FILE* pstFileHandle  <b>:</b> �ļ����
 * @param [in] HTTPLong lOffset     <b>:</b> �ƶ�λ��
 * @param [in] HTTPLong lOrigin     <b>:</b> ���ȿ�ʼλ��
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_FileFtell
 * @see HTTPAPI_FileFstat
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_FileFseek(FILE* pstFileHandle, HTTPLong  lOffset, HTTPLong lOrigin);

/**
 * @brief �ƶ����ļ�ĩβ
 * 
 * @param [in] FILE* pstFileHandle  <b>:</b> �ļ����
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_FileFseek
 * @see HTTPAPI_FileFstat
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_FileFtell(FILE* pstFileHandle);

/**
 * @brief MDM��ʽ��ȡ�ļ���Ϣ
 * 
 * @param [in] const HTTPChar* pcPath <b>:</b> �ļ�·��
 * @param [in] ST_HTTP_STAT* pstStat  <b>:</b> �ļ���Ϣ
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see HTTPAPI_FileFseek
 * @see HTTPAPI_FileFtell
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_FileFstat(const HTTPChar* pcPath, ST_HTTP_STAT* pstStat);

/**
 * @brief �����ļ��Ƿ����
 * 
 * @param [in] const HTTPChar* pcPath  <b>:</b> �ļ�·��
 * @param [in] HTTPInt mode            <b>:</b> ���ҷ�ʽ��ȡֵ0:F_OK��1:X_OK��2:W_OK��4:R_OK�������
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_FileFaccess(const HTTPChar* pcPath, HTTPInt mode);

/**
 * @brief ��ȡ�ļ������Ĵ�����Ϣ
 * 
 * @param [in] void  <b>:</b> 
 * @retval HTTP_API int <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
HTTP_API int HTTPAPI_FileFgeterrno(void);

/**
 * @brief �����Ƿ����MDM���ܷ�ʽ
 * 
 * @param [in] HTTPHANDLE handle     <b>:</b> handle
 * @param [in] HTTPBOOL bUseSvnFile  <b>:</b> �Ƿ����MDM���ܷ�ʽ
 * @retval HTTP_API EN_HTTP_ERRORCODE <b>:</b> �ɹ�����TUP_SUCCESS��ʧ�ܷ�����Ӧ������
 * 
 * @attention NA
 * @see NA
 **/
HTTP_API EN_HTTP_ERRORCODE HTTPAPI_SetBeUseSvnFile(HTTPHANDLE handle, HTTPBOOL bUseSvnFile);


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif //__HTTPAPI_H__

/** @}*/

/*
* History: \n
* 2012-12-10, ��ʼ�����ļ��� \n
* 2015-12-30, TUP V100R001C50 TR5 ���������´��ļ��� \n
 *
* vi: set expandtab ts=4 sw=4 tw=80:
*/
