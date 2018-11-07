#pragma once
#include <windows.h>  
#include <iostream>
#include <string>  
#include <vector>

extern char g_cers_path[256];
extern char g_manager_cers_path[256];

#ifndef MY_HEADERS_H 
#define MY_HEADERS_H 

#define TG_DEBUG
//#define REG_DEBUG

//CMD1;no date package
#define DEV_KEY 0x0001				           //设备密钥； 		PC->ARM
#define DEV_KEY_SET_SUCCESS 0x0002			   //设备密钥设置成功；  ARM->PC
#define DEV_KEY_SET_FAILED 0x0003		       //设备密钥设置失败；  ARM->PC


#define	RAN_NUM_REQ			0x0006		       //随机数请求；	PC->ARM
#define	RAN_NUM				0x0007	           //随机数；	ARM->PC

#define	RESEND_CERT_REQ		0x0008	           //请求重新传输证书，注册完的超管或管理员证书；	PC->ARM
#define	CERT_INFO_REQ		0x0020	           //请求传输h3上存储的各类证书个数,信息，对应 CERT_NUM；	PC->ARM
#define	CERT_DATA_REQ		0x0021	           //请求传输h3上存储的各类证书；	PC->ARM



#define	UPPER_CERT_CONFIRM			0x0022	   //上位机收到证书且CRC正确，删除原来的证书；	PC->ARM
#define	UPPER_CERT_NO_CONFIRM		0x0023	   //上位机没收到证书或者CRC错误，重新传输上一个证书；	PC->ARM

#define INFO_DATA_CRC_ERR		0x0025	       //下位机收到的 证书密钥+人员信息 的CRC错误	ARM->PC
#define CERT_DATA_B_CRC_RIGHT	0x0027	       //上位机导入到H3中的证书CRC正确；ARM->PC
#define CERT_DATA_B_CRC_ERR		0x0028	       //上位机导入到H3中的证书CRC错误；ARM->PC

#define	CERT_NUM			0x0030	           //h3上存储的各类证书个数,对应 CERT_INFO_REQ；	ARM->PC

#define ENROLL_REQ 			0x0100		       //注册请求；		PC->ARM
#define	ENROLL_SUCCESS		0x0101		       //注册成功；		ARM->PC
#define ENROLL_FAILED		0x0102		       //注册失败；		ARM->PC	

#define VALIDATE_LOCAL_REQ 		0x0110		   //本地证书验证请求；		PC->ARM
#define	VALIDATE_LOCAL_SUCCESS	0x0111		   //本地证书验证成功；		ARM->PC
#define VALIDATE_LOCAL_FAILED		0x0112	   //本地证书验证失败；		ARM->PC	

#define	VALIDATE_UPPER_SUCCESS	0x0114		   //上位机证书验证成功；		ARM->PC
#define VALIDATE_UPPER_FAILED		0x0115	   //上位机证书验证失败；		ARM->PC	

#define VALIDATE_UPPER_CERT_START 	0x0116	   //上位机证书验证,上位机开始传输证书		PC->ARM
#define VALIDATE_UPPER_CERT_END 	0x0117	   //上位机证书验证,上位机结束传输证书 (传输结束自动开始验证)		PC->ARM
#define VALIDATE_UPPER_CERT_DATA 	0x0118	   //上位机证书验证,上位机传输证书(单个证书传输)		PC->ARM

#define DELETE_REQ 		0x0120		           //删除请求；		PC->ARM
#define	DELETE_SUCCESS	0x0121		           //删除成功；		ARM->PC
#define DELETE_FAILED		0x0122		       //删除失败；		ARM->PC	

#define HEART_BEAT 0x6666			           //心跳包；ARM->PC

//CMD1;date package
#define	INFO_DATA	0x1000				       //证书密钥+人员信息+CRC；PC->ARM
#define CERT_DATA_A	0x1001				       //管理员注册完的证书+随机数；ARM->PC
#define CERT_DATA_A_FAIL 0x1004
#define CERT_DATA_B	0x1002				       //注册完的证书(导入到H3中)；PC->ARM
#define CERT_DATA_C	0x1003				       //存在H3上的证书(导入到PC中)；ARM->PC

//CERT_TYPE
#define SUPER_MGR	0x00	                   //超级管理员
#define MGR		0x01		                   //管理员
#define USR		0x02		                   //用户

#define DEV_KEY_LENGTH 32
#define RAN_NUM_LENGTH 32

#define CERT_LENGTH 6112
#define CERT_WHOLE_LENGTH 6116


#define DEV_NAME "UD55"	
#define SERIAL_NUM "04005035c2185831020e"

#define CERT_SIZE 6148                         //证书大小
#define CMD_SIZE 1024                          //指令包大小

#define CONTINUE_IMPT 1                        //继续导入
#define STOP_IMPT 2                            //退出
#define NONE_STATUS_OF_IMPT 0     

#define VALIDATE_REQ 		0x0110		       //验证请求；		PC->ARM
#define	VALIDATE_SUCCESS	0x0111		       //验证成功；		ARM->PC
#define VALIDATE_FAILED		0x0112		       //验证失败；		ARM->PC	
#define REGISTER_SUCCESS    0x1001             //注册成功

#define DEV_VALIDATE_SUCCESS 1
#define DEV_VALIDATE_FAIL 2
#define DEV_VALIDATE_NOT_SUCCESS_NOT_FAIL 666

#define LOGIN_BY_PASSWORD 0
#define LOGIN_BY_FINGER 1
#define LOGIN_BY_FINGER_AND_PASSWD 2

#define VALIDATE_UPPER_END	0x0119		       //上位机证书验证结束；		PC->ARM

#define USER_TYPE_OF_USER 2
#define USER_TYPE_OF_MANAGE 1

#define YES_DELETE 111111
#define NO_DELETE  111112

#define ENCRYPT_SUCCESS 111113
#define ENCRYPT_FAIL 111114
#define ENCRYPT_NONE 111115

#define MAX_USERNAME_LEN 20

#define FINGER_PIC_SIZE 17328
#define FINGER_SAVE_SIZE 138625

#define USERLIST_BUF_SIZE 20000

#define DELETE_ADMIN_LOG  "4"
#define ADD_ADMIN_LOG "2"
#define ADMIN_LOGIN "1"
#define ADD_USER "3"
#define ADD_USER_FINGER "5"
#define ADD_CERT "6"
#define ADD_DEV_LOG "7"
#define LATER_THAN_TODAY 0
#define DYNAMIC_KEYT "0"
#define PACK_KEYT "1"
#define ADD_CERT_LOG_STR "8"
#define ADD_CERT_LOG 8
#define ADD_USER_FINGER_LOG 9
#define ADD_USER_FINGER_LOG_STR "9"
#define DEL_CERT_LOG 10
#define DEL_CERT_LOG_STR "10"
#define DEL_FINGER_LOG 11
#define DEL_FINGER_LOG_STR "11"
#define ADD_USER_LOG 3
#define CONFIGURE_CERTS_LOG 12
#define CONFIGURE_CERTS_LOG_STR "12"
#define CLEAR_DEV_LOG_STR "13"
#define CLEAR_DEV_LOG 13
#define DEL_USER_LOG 14
#define DEL_USER_LOG_STR "14"

#define MAKE_SURE_DELETE_MSG "确认删除？"


typedef struct {
	std::vector<std::string> usrnames;
	int num;
	bool error_flag;
}   selectUsrnamesResult;

typedef struct {
	std::vector<std::string> manager_names;
	std::vector<std::string> contents;
	std::vector<std::string> times;
	std::vector<std::string> types;
	bool error_flag;
	int num;
}   log_select_ret;

typedef struct {
	char id[17];
	char name[200];
	char date[20];
	char status[10];
}	dev_sel_ret;

typedef struct {
	char id[17];
	char content[255];
	char manager_name[80];
	char str_time[60];
	char type[2];
	char date[20];
}	log_sel_ret;

typedef struct {
	char id[10];
	char user_id[128];
	char dev_id[16];
}	user_dev_sel_ret;

typedef struct {
	char id[128];
	char user_id[128];
	char content[255];
	char type[5];
	char date[30];
	char name[32];
}	cert_sel_ret;

typedef struct {
	char id[128];
	char name[200];
	char date[20];
	char dev_name[200];
}	user_sel_ret;


typedef struct {
	char id[128];
	char name[200];
	char date[20];
	char dev_name[200];
	int fingerNum;
	int certNum;
}	USER_INFO_SEL, *P_USER_INFO_SEL;


typedef struct {
	char name[225];
	char finger[FINGER_PIC_SIZE];
	int id;
}	sel_admin_ret;

typedef struct {
	char name[225];
	char finger[FINGER_SAVE_SIZE];
	int id;
}	sel_admin_ret2;


typedef struct {
	char id[12];
	char finger[FINGER_SAVE_SIZE];
	char name[100];
	char user_id[128];
	char username[255];
	char date[20];
}	sel_finger_ret3;

typedef struct {
	char name[100];
	char date[20];
	std::string id;
}   sel_finger_ret;

typedef struct {
	char name[100];
	char date[20];
	char finger[FINGER_PIC_SIZE];
	int id;
	char user_id[128];
	char username[100];
}   sel_finger_ret2;

typedef struct{
	char byKey[65];
	char wszName[32];
	int dwFlags;
	int dwReserved;
	FILETIME ftCreateDate;
	FILETIME ftExpireDate;
}SW_CERT,*PSW_CERT;

typedef struct {
	BYTE byKey[32];
	WCHAR wszName[32];
	DWORD dwFlags;
	DWORD dwReserved;
	FILETIME ftCreateDate;
	FILETIME ftExpireDate;
}FINAL_SW_CERT, *FINAL_PSW_CERT, **FINAL_PPSW_CERT;

typedef struct {
	char byKey[65];
	char wszName[32];
	int dwFlags;
	int dwReserved;
	FILETIME ftCreateDate;
	FILETIME ftExpireDate;
	char id[128];
}SW_CERT2, *PSW_CERT2;

typedef struct {
	std::vector<std::string> usrnames;
	std::vector<std::string> dates;
	int num;
	bool error_flag;
}   sel_admin_ret3;


typedef struct
{
	GUID UserID;				// 用户标识GUID
	DWORD dwCertMap[2];		    // 证书映射表
							    // 目前最大支持64组证书，每位对应一个证书索引 
							    // 对应的位为1表示该用户拥有此证书
	DWORD dwReserved[2];		// 保留空间
} SW_USER, *PSW_USER, **PPSW_USER;

typedef struct
{
	DWORD dwSize;					// 此结构的总长度
	DWORD dwUserTableOffset;		// 用户表偏移量，相对于结构头部
	DWORD dwUserTableLength;		// 用户表长度bleLength/ dwUserUnitSize,
									// 考虑到以后的扩展，不能直接使
	DWORD dwUserUnitSize;			// 设置为sizeof(SW_USER)
									// UserTable中用户个数为dwUserTa用当前的SW_USER结构体长度
	DWORD dwCertTableOffset;		// 证书表偏移量
	DWORD dwCertTableLength;		// 证书表长度
									// 证书个数为dwCertTableLength/sizeof(SW_CERT)
} SW_USERCERTTABLE, *PSW_USERCERTTABLE;


typedef struct {
	char finger_name[32];
	unsigned char fdata[FINGER_PIC_SIZE];
} FINGER_DATA, *P_FINGER_DATA;


typedef struct {
	char user_name[128];
	char user_id[64];
	int fnum;            //指静脉数量(单个用户指静脉数量不超过6个)
	FINGER_DATA fingers[6];
	char	crc[2];						//crc
	char	reserve_2[2];
} USER_DATA, *P_USER_DATA;



typedef struct {
	char     finger_name[32];
}FINGER_INFO, *P_FINGER_INFO;

typedef struct {
	char     user_id[64];
	int             fnum;
	FINGER_INFO fdata[6];
	char	reserve_2[4];
	char       user_name[200];
}USER_INFO, *P_USER_INFO;



typedef struct
{
	DWORD dwSize;			// 本结构大小，用于以后的版本兼容
	HANDLE hevtNotify;		// 指纹用户状态切换通知
} SDD_INIT_DATA, *PSDD_INIT_DATA;


typedef struct {
	char user_id[64];
	char finger_name[32];
	unsigned char fdata[FINGER_PIC_SIZE];
	int sync_flag;        //同步标志位
	char	crc[2];
	char       user_name[200];
	char	reserve_2[2];
} SYNC_DATA, *P_SYNC_DATA;



typedef BOOL(WINAPI *SDFP_INIT_FUNC)(IN LPCSTR lpszSDFPLibFile);
typedef DWORD(WINAPI *SDFPDEV_INIT_FUNC)(IN PSDD_INIT_DATA psid);
typedef DWORD(WINAPI * SDFPDEV_CLOSE_FUNC)();
typedef BOOL(WINAPI *SDFP_CLOSE_FUNC)();
typedef DWORD(WINAPI *READ_USERCERT_TABLE_FUNC)(IN OUT DWORD*, OUT PSW_USERCERTTABLE);
typedef DWORD(WINAPI *WRITE_USERCERT_TABLE_FUNC)(IN PSW_USERCERTTABLE);
//typedef DWORD(WINAPI *TG_DEV_GET_SN)(char *sn);
//typedef DWORD(WINAPI *SD_DEV_INIT)(IN PSDD_INIT_DATA psid);
//typedef DWORD(WINAPI *TG_GET_RANDOM)(unsigned char *randombuf, int randomlength);



// 是否包括设备连接内容，如果注释掉，可单独调试界面
#define _TEST_TEST
//#define _TEST_WITH_LOGIN
#define _TEST_WITH_DEV_CONN
//#define _TEST_WH_LIB
#define _TEST_OUTO_CREATE_CERT


#define RET_ERROR -1
#define OK 0
#define CLOSE_DEV_FAIL "断开设备失败"
#define OPEN_DEV_FAIL "打开设备失败"
#define CLEAR_DEV_SUCCESS_STR "清空设备成功"
#define CLEAR_DEV_FAIL_STR "清空设备失败"
#define SHOW_AFTER_CONN_DEV_STR "连接设备后显示"
#define RESULT_TITLE_WIN_STR "结果"
#define RECONN_DEV_PLEASE_STR "请重新连接设备"


#define LEN_OF_CODE_WRONG 0
#define INPUTED_CH_NOT_HEX 1
#define INPUT_RIGHT 2

#define MAX_DEV_USER_CERT_SPACE  8072



#endif  
