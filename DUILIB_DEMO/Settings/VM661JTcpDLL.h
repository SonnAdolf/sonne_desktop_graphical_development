#ifndef _VM661JTCPDLL_H_
#define _VM661JTCPDLL_H_
#ifdef VM661JTCPDLL_EXPORTS
#define VM661JTCPDLL_API _declspec(dllexport)
#else
#define VM661JTCPDLL_API _declspec(dllimport)
#endif 
/******************************************************************************
*以下为设备返回值
******************************************************************************/
#define TG_OK                0x00
#define TG_COMM_ERR          0x01
#define TG_NO_FINGER         0x02

/******************************************************************************
*以下为设备播放语音内容
******************************************************************************/
#define BI					0x00	//Bi
#define BIBI				0x01	//BiBi	
#define REG_SUCCESS			0x02	//登记成功
#define REG_FAIL 			0x03	//登记失败
#define PLS_REPUT			0x04	//请再放一次
#define PLS_PUT_CRUCLY     	0x05	//请正确放入手指
#define PLS_PUT_SOFTLY		0x06	//请自然轻放手指
#define IDENT_SUCCESS		0x07	//验证成功
#define IDENT_FAIL			0x08	//验证失败
#define PLS_REDO			0x09	//请重试
#define DEL_SUCCESS			0x0A	//删除成功
#define DEL_FAIL			0x0B	//删除失败
#define VEIN_FULL			0x0C	//指静脉已满
#define VOLUME0				0xE0	//最小音量级别0
#define VOLUME1				0xE1	//中间音量级别1
#define VOLUME2				0xE2	//中间音量级别2
#define VOLUME3				0xE3	//中间音量级别3
#define VOLUME4				0xE4	//中间音量级别4
#define VOLUME5				0xE5	//中间音量级别5
#define VOLUME6				0xE6	//中间音量级别6
#define VOLUME7				0xE7	//最大音量级别7

#include "my_including.h"
/******************************************************************************
*以下为PC操作设备接口函数
******************************************************************************/
#define WINAPI __stdcall

#ifdef __cplusplus 
extern "C" {
#endif	
	/******************************************************************************
	Function:
	打开设备：检测设备连接状态
	Output：
	Return：
	>0：已连接
	-1：断开连接
	Others：
	设备的操作句柄指针用于其他接口调用
	*****************************************************************************/
	VM661JTCPDLL_API	int TGGetStatus();
	/******************************************************************************
	Function:
	打开设备：PC端打开下位机设备
	Output：
	mode:通讯模式（1为HID通讯）
	Return：
	>0：设备打开成功
	-1：设备打开失败
	Others：
	设备的操作句柄指针用于其他接口调用
	*****************************************************************************/
	VM661JTCPDLL_API	int TGOpenDev(int* mode);
	/******************************************************************************
	Function:
	关闭设备：PC端关闭下位机设备
	Return：
	0：设备关闭成功
	-1：设备已关闭
	Others：
	*****************************************************************************/
	VM661JTCPDLL_API int TGCloseDev();
	/******************************************************************************
	Function:
	设备获取图像：设备的传感器获取指静脉图像
	Input：
	unsigned char* pImageData：图像数据(500*200)
	int timeout:获取图像等待的时间（即：超过这个时间没有检测到touch就返回-1）
	timeout<=50,单位s;
	timeout>50，单位ms;
	Output：
	无
	Return：
	0：设备获取图像成功
	-1：设备获取图像失败
	Others：
	设备获取图像是指PC发送命令让设备自身获取外界环境图像
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevGetImage(unsigned char* pImageData, int timeout);
	/******************************************************************************
	Function:
	设备播放语音：设备播放提示语音
	Input：
	int iVoiceValue：语音内容
	Output：
	无
	Return：
	0：设备播放语音成功
	-1：设备播放语音失败
	Others：
	语音内容已在宏中定义，设备第一次上电时，上位机要给设备设置一次语音音量，
	否则设备按最大音量播放语音。
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevPlayVoice(int VoiceValue);
	/******************************************************************************
	Function:
	获取设备固件号，即firmware
	Input：
	无
	Output：
	char *fw：获取到的固件号（16位）
	Return：
	0：获取设备固件号成功
	-1：获取设备固件号失败
	Others：
	固件号为字符串
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevGetFW(char *fw);
	/******************************************************************************
	Function:
	获取设备序列号，即sn
	Input：
	无
	Output：
	char *sn：获取到的序列号（16位）
	Return：
	0：获取设备序列号成功
	-1：获取设备序列号失败
	Others：
	序列号为字符串
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevGetSN(char *sn);

	/******************************************************************************
	Function:
	设置设备的模式：前比/后比 （本功能暂时无效）
	Input：
	int mode：1：后比  ；  2：前比
	Output：
	无
	Return：
	1：设置成功
	-1：设置失败
	Others：
	下次上电后生效
	*****************************************************************************/
	VM661JTCPDLL_API int TGSetMode(int mode);
	/******************************************************************************
	Function:
	设置并获取图像截取开始行及开始列
	Input：
	无
	Output：
	char *rowcol：图像截取的开始行及开始列；rowcol为空，只获取；rowcol不为空，先设置再获取；
	Return：
	0：获取图像截取的开始行及开始列成功
	-1：获取图像截取的开始行及开始列失败
	Others：
	开始行及开始列为字符串
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevSetGetRC(char *rowcol);
	/******************************************************************************
	Function:
	获取连接TF卡状态
	Input：
	无
	Output：
	char *tf：获取连接TF卡状态，‘0’：异常；‘1’：正常；
	Return：
	0：获取连接TF卡状态成功
	-1：获取连接TF卡状态失败
	Others：
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevGetTF(char *tf);
	/******************************************************************************
	Function:
	设置获取设备序列号，即sn
	Input：
	无
	Output：
	char *sn：获取到的序列号（16位），如果sn为空，则只获取；否则，设置sn并获取；
	Return：
	0：设置获取设备序列号成功
	-1：设置获取设备序列号失败
	Others：
	序列号为字符串
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevSetGetSN(char *sn);
	VM661JTCPDLL_API int TGDevSetGetClientSN(char *sn);
	/******************************************************************************
	Function:
	设置led灯
	Input：
	int led_blue：蓝灯控制：0：灭；1：亮；
	int led_green：绿灯控制：0：灭；1：亮；
	int led_red：红灯控制：0：灭；1：亮；
	Output：
	无
	Return：
	0：设置led灯成功
	-1：设置led灯失败
	Others：
	*****************************************************************************/
	VM661JTCPDLL_API int TGDevSetLed(int led_blue, int led_green, int led_red);
	/*****************************************************************************
	*注意：以下接口可以给生产厂家，但是不能给客户
	*1、VM661JTCPDLL_API int TGDevSetGetSN(char *sn);
	*******************************************************************************/
#if 0
	struct Package{
		char	device_name[32];	//设备名
		int 	id;					//ID
		int		cmd1;				//指令1
		int		cmd2;				//指令2
		int 	length;				//数据长度
		int		cert_type;			//证书类型
		int		sup_mgr_num;		//本地超管证书个数
		int		mgr_num;			//本地管理员证书个数
		int		usr_num;			//本地用户证书个数
		char	serial_num[32];		//序列号
		char	random_num[32];		//随机数
		char	cert_name[32];		//证书名字
		char 	reserve_char[96];	//预留备用
	};//指令包  1024B
#endif

	//VM661JTCPDLL_API int tg_net_send_cmd_package(Package send_pack);
	//VM661JTCPDLL_API int tg_net_send_data_package(char * data, int length);

	VM661JTCPDLL_API int admin_start_register(char *buff, char* username);

	VM661JTCPDLL_API int admin_login(sel_admin_ret* sel_admins, int num, char* admin_name); 

	VM661JTCPDLL_API int registerUserFingerOnlyDB(char *buff);

	VM661JTCPDLL_API int registerUserFinger(char *buff, const char* chUserIdAndFingerName);

	VM661JTCPDLL_API int get_user_lst(char* buf,int *num,int *len);

	//VM661JTCPDLL_API int load_user(SW_CERT* certs,sel_finger_ret2* fingers,char* username, char* user_id, int cert_num, int f_num);

	VM661JTCPDLL_API int get_cert_content_func(char *content);

	VM661JTCPDLL_API int set_dev_ciphercode(char *content, int length);

	VM661JTCPDLL_API int clearDev();

	VM661JTCPDLL_API int del_single_finger(const char* userAndFingerId);

	VM661JTCPDLL_API int delUserFingers(char* userId);

	VM661JTCPDLL_API int decryptTest();


	VM661JTCPDLL_API int imptUserFingersBegin(int num);
	/**
	*    sonne
	*    2018-09
	*    导入用户指静脉
	*/
	VM661JTCPDLL_API int imptUsersFingers(P_USER_DATA  user);


	VM661JTCPDLL_API int imptUserFingersEnd(int num);


	/**
	*    sonne
	*    2018-09
	*    获取设备指静脉信息
	*/
	VM661JTCPDLL_API int getFingerInfo(P_USER_INFO* pUserFingerInfo, int * num);


	/**
	*    sonne
	*    2018-09
	*    发送同步指静脉数据
	*/
	VM661JTCPDLL_API int sendSyncFingers(P_SYNC_DATA arr, int num);

	VM661JTCPDLL_API void fastDelete(void* pvAddr);
	VM661JTCPDLL_API void  fastDeleteArrs(void* pvAddr);
}
#endif

#if 0

#include "my_including.h"



#ifndef _TGVM661JCOMAPI_H_
#define _TGVM661JCOMAPI_H_

#ifdef TGVM661JCOMAPI_EXPORTS
#define TGVM661JCOMAPI_API _declspec(dllexport) __stdcall
#else
#define TGVM661JCOMAPI_API _declspec(dllimport) __stdcall
#endif 

#define FRONT
#define FACTORY

/******************************************************************************
*以下为设备播放语音内容
******************************************************************************/
#define VOICE_BI					0x00	//Bi
#define VOICE_BIBI					0x01	//BiBi	
#define VOICE_REG_SUCCESS			0x02	//登记成功
#define VOICE_REG_FAIL 				0x03	//登记失败
#define VOICE_PLS_REPUT				0x04	//请再放一次
#define VOICE_PLS_PUT_CRUCLY     	0x05	//请正确放入手指
#define VOICE_PLS_PUT_SOFTLY		0x06	//请自然轻放手指
#define VOICE_IDENT_SUCCESS			0x07	//验证成功
#define VOICE_IDENT_FAIL			0x08	//验证失败
#define VOICE_PLS_REDO				0x09	//请重试
#define VOICE_DEL_SUCCESS			0x0A	//删除成功
#define VOICE_DEL_FAIL				0x0B	//删除失败
#define VOICE_VEIN_FULL				0x0C	//指静脉已满
#define VOICE_REREG					0x0D	//登记重复 
#define VOICE_VOLUME0				0xF0	//静音
#define VOICE_VOLUME1				0xF2	//音量级别1
#define VOICE_VOLUME2				0xF4	//音量级别2
#define VOICE_VOLUME3				0xF6	//音量级别3
#define VOICE_VOLUME4				0xF8	//音量级别4
#define VOICE_VOLUME5				0xFA	//音量级别5
#define VOICE_VOLUME6				0xFA	//音量级别6
#define VOICE_VOLUME7				0xFA	//音量级别7

/****************+**************************************************************
*以下为PC操作设备接口函数
******************************************************************************/

#ifdef __cplusplus 
extern "C" {
#endif	

	//2018-05-19
	int TGVM661JCOMAPI_API TGGetStatus();
	/******************************************************************************
	Function:
	打开设备：PC端打开下位机设备
	Input：
	无
	Output：
	mode:通讯模式（1为HID通讯）
	Return：
	0：设备打开成功
	-1：超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGOpenDev(int* mode);

	/******************************************************************************
	Function:
	关闭设备：PC端关闭下位机设备
	Return：
	0：设备关闭成功
	-1：超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGCloseDev();

	/******************************************************************************
	Function:
	获取设备状态
	Input：
	无
	Output：
	无
	Return：
	>=0：设备已连接
	<0：设备未连接
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevStatus();

	/******************************************************************************
	Function:
	获取设备固件号，即firmware
	Input：
	无
	Output：
	char* fw：获取到的固件号（16 Bytes）
	Return：
	0：获取设备固件号成功
	-1：超时
	Others：
	固件号为字符串
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevFW(char* fw);

	/******************************************************************************
	Function:
	获取设备序列号，即sn
	Input：
	无
	Output：
	char* sn：获取到的序列号（16 Bytes）
	Return：
	0：获取设备序列号成功
	-1：超时
	Others：
	序列号为字符串
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevSN(char* sn);

	/******************************************************************************
	Function:
	获取设备的工作模式：前比/后比
	Input：
	无
	Output：
	int* mode： 0：前比 ; 1：后比
	Return：
	0：获取成功
	-1：超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevMode(int* mode);

	/******************************************************************************
	Function:
	设置设备的比对模式：前比/后比
	Input：
	int mode： 0：前比 ; 1：后比
	Output：
	无
	Return：
	0：设置成功
	-1：设置失败
	Others：
	立即生效
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetDevMode(int mode);

	/******************************************************************************
	Function:
	获取设备图像
	Input：
	int timeout:获取图像等待的时间（即：超过这个时间没有检测到touch就返回-1）
	timeout<=50,单位s;
	timeout>50，单位ms;
	Output：
	unsigned char* imageData：图像数据(208+500*200 Bytes)
	Return：
	0：设备获取图像成功
	-1：抓图超时
	-2:设备断开
	-3:操作取消
	Others：
	无
	*****************************************************************************/
	//int TGVM661JCOMAPI_API TGGetDevImage(unsigned char* imageData, int timeout);

	/******************************************************************************
	Function:
	取消获取设备图像
	Input：
	无
	Output：
	无
	Return：
	0：取消成功
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGCancelGetImage();

	/******************************************************************************
	Function:
	播放设备语音：设备播放提示语音
	Input：
	int voiceValue：语音内容或音量级别
	Output：
	无
	Return：
	0：设备播放语音成功
	-1：设备播放语音失败
	Others：
	语音内容已在宏中定义，设备第一次上电时，上位机要给设备设置一次语音音量，
	默认音量为VOICE_VOLUME4。
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGPlayDevVoice(int voiceValue);

	/******************************************************************************
	Function:
	设置led灯
	Input：
	int ledBlue：蓝灯控制：0：灭；1：亮；
	int ledGreen：绿灯控制：0：灭；1：亮；
	int ledRed：红灯控制：0：灭；1：亮；
	Output：
	无
	Return：
	0：设置led灯成功
	-1：设置led灯失败
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetDevLed(int ledBlue, int ledGreen, int ledRed);

	/******************************************************************************
	Function:
	写设备信息
	Input：
	char* devInfo;待写入设备的信息
	int writeLen:带写入的信息长度。0<writeLen<=1024 Bytes。
	Output：
	无;
	Return：
	>0：成功,实际写入长度
	-1：超时
	-2：入参错误
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGWriteDevInfo(char* devInfo, int writeLen);

	/******************************************************************************
	Function:
	读设备信息
	Input：
	char* devInfo;待读出的信息
	int readLen:待读出的信息长度。0<readLen<=1024 Bytes。
	Output：
	无;
	Return：
	>=0：成功,实际读取长度
	-1：超时
	-2：入参错误
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGReadDevInfo(char* devInfo, int readLen);

	/******************************************************************************
	Function:
	设置获取设备序列号，即sn
	Input：
	无
	Output：
	char* sn：获取到的序列号（16 Bytes），如果sn为空，则只获取；否则，设置sn并获取；
	Return：
	0：设置或获取设备序列号成功
	-1：超时
	Others：
	序列号为字符串
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetGetDevClientSN(char* sn);



	// 55 project functions
	int TGVM661JCOMAPI_API register_user_finger(char *buff, const char* user_id, const char* username, int cert_num, const char* finger_name, SW_CERT* certs);
	int TGVM661JCOMAPI_API get_user_lst(char* buf, int *num, int *len);
	int TGVM661JCOMAPI_API load_user(SW_CERT* certs, sel_finger_ret2* fingers, char* username, char* user_id, int cert_num, int f_num);
	int TGVM661JCOMAPI_API get_cert_content_func(char *content);
	int TGVM661JCOMAPI_API admin_start_register(char *buff, char* username);
	int TGVM661JCOMAPI_API admin_login(sel_admin_ret* sel_admins, int num, char* admin_name);

	int TGVM661JCOMAPI_API TGDevGetSN(char *sn);

#ifdef FRONT
	/******************************************************************************
	*以下设备端比对相关接口
	*******************************************************************************/

	/******************************************************************************
	Function:
	请求设备端注册
	Input：
	int retImgMode：1：设备返回加密图片数据 ；0：设备不返回加密图片数据
	char* userName:用户ID（<50Bytes）
	Output：
	无
	Return：
	0：请求成功，需循环调用 TGGetFuncMoreReturn获取注册过程返回值
	-1：请求失败
	Others：
	循环调用 TGGetDevRegIdentReturn,获取注册过程返回值。
	retImgMode为1时，当TGGetDevRegIdentReturn的返回值为VOICE_BI时，
	调用TGGetDevImage获取加密图片数据。
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDevRegFinger(int retImgMode, char* userName);

	/******************************************************************************
	Function:
	请求设备端验证
	Input：
	int retImgMode：1：设备返回加密图片数据 ；0：设备不返回加密图片数据
	Output：
	无
	Return：
	0：请求成功,需调用 TGGetFuncMoreReturn获取验证返回值
	-1：请求失败
	Others：
	调用 TGGetDevRegIdentReturn获取验证结果
	retImgMode为1时，当TGGetDevRegIdentReturn的返回值为VOICE_BI时，
	调用TGGetDevImage获取加密图片数据。
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDevIdentFinger(int retImgMode);

	/*****************************************************************************
	Function:
	请求设备端连续验证
	Input：
	int retImgMode：1：设备返回加密图片数据 ；0：设备不返回加密图片数据
	Output：
	无
	Return：
	0：请求成功,需循环调用 TGGetDevRegIdentReturn获取验证结果
	-1：请求失败
	Others：
	循环调用 TGGetDevRegIdentReturn获取验证结果
	retImgMode为1时，当TGGetDevRegIdentReturn的返回值为VOICE_BI时，
	调用TGGetDevImage获取加密图片数据。
	**************************************************************************/
	int TGVM661JCOMAPI_API TGDevContinueIdentFinger(int retImgMode);

	/**************************************************************************
	Function:
	获取设备注册和设备连续验证时的返回值
	Input：
	int timeOutMs:超时（ms）
	Output：
	char* templId：注册成功或验证成功时返回的ID(<50 Bytes)
	Return：
	返回值为语音和CMD的宏定义值,根据宏名表示相应情况。
	Others：
	仅用于获取设备端注册和设备端验证时的返回值。
	***************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevRegIdentReturn(char* tmplId, int timeOutMs);

	/***************************************************************************
	Function:
	取消设备端注册或验证
	Input：
	无
	Output：
	无
	Return：
	0：请求成功
	-1：请求失败
	Others：
	无
	****************************************************************************/
	int TGVM661JCOMAPI_API TGCancelDevRegIdent(void);

	/****************************************************************************
	Function:
	获取设备模板数。
	Input：
	int maxTemplNumMode：0：设备中已注册的模板数；1：设备中可注册的最大模板数
	Output：
	无
	Return：
	>=0：模板数
	-1:超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevTmplNum(int maxTemplNumMode);

	/*****************************************************************************
	Function:
	获取设备模板信息列表。
	Input：
	无
	Output：
	int* templNum：设备中已注册的模板数
	char* templNameList：设备中模板信息列表 （templNum * 50 Bytes）
	Return：
	0：读取设备模板信息列表成功
	-1：超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevTmplInfo(int* templNum, char* templNameList);

	/*****************************************************************************
	Function:
	删除设备中指定的ID模板。
	Input：
	char* templId：待删除的ID号,例如"0"
	Output：
	无
	Return：
	0：删除成功
	1：设备中不存在待删除的ID
	-1：超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDelDevTmpl(char* templId);

	/*****************************************************************************
	Function:
	清空设备中的模板。
	Input：
	无
	Output：
	无
	Return：
	0：清空成功
	1：设备中不存在模板
	-1：超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGEmptyDevTmpl();

	/*****************************************************************************
	Function:
	上传设备中指定ID模板到主机。
	Input：
	char* templId：设备中待上传的模板ID名，例如"0"
	Output：
	unsigned char* tmplData：接收到的模板数据（17632 Bytes）
	int* tmplSize：接收到的模板大小
	Return：
	0：上传成功
	1：设备中不存在待上传的模板
	-1：超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGUpDevTmpl(char* tmplId, unsigned char* tmplData, int* tmplSize);

	/******************************************************************************
	Function:
	设备中上传模板包到主机（模板包包含设备中所有模板）。
	Input：
	无
	Output：
	unsigned char* tmplPkgData：接收到的模板包数据（<（17632+50）*300 Bytes)
	int* tmplPkgSize：接收到的模板包大小
	Return：
	0：上传成功
	1：设备中不存在模板
	-1：超时
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGUpDevTmplPkg(unsigned char* tmplPkgData, int* tmplPkgSize);

	/******************************************************************************
	Function:
	下载主机中指定ID模板到设备。
	Input：
	char* tmplId：待下载模板的ID名，例如"0"
	unsigned char* tmplData：待下载的模板数据
	int tmplSize：待下载的模板数据的大小
	Output：
	无
	Return：
	0：下载成功
	-1:超时
	-2:模板错误
	-3:指静脉已满
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDownDevTmpl(char* tmplId, unsigned char* tmplData, int tmplSize);

	/******************************************************************************
	Function:
	主机下载模板包到设备（会清空设备中的模板）。
	Input：
	unsigned char* tmplPkgData:待下载的模板包数据
	int tmplPkgSize：待下载的模板数据的大小
	Output：
	无
	Return：
	0：下载成功
	-1:超时
	-2:模板包错误
	-3:指静脉已满，设备中仅保存最大模板数
	Others：
	无
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGDownDevTmplPkg(unsigned char* tmplPkgData, int tmplPkgSize);
#endif // FRONT

#ifdef FACTORY
	/*****************************************************************************
	*以下生产相关接口，不开发给客户
	*******************************************************************************/

	/******************************************************************************
	Function:
	设置获取设备序列号，即sn
	Input：
	无
	Output：
	char* sn：获取到的序列号（16 Bytes），如果sn为空，则只获取；否则，设置sn并获取；
	Return：
	0：设置获取设备序列号成功
	-1：超时
	Others：
	序列号为字符串
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetGetDevSN(char* sn);

	/******************************************************************************
	Function:
	设置并获取图像截取开始行及开始列
	Input：
	无
	Output：
	char* rowcol：图像截取的开始行及开始列；rowcol为空，只获取；rowcol不为空，先设置再获取；
	Return：
	0：成功
	-1：超时
	Others：
	开始行及开始列为字符串
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGSetGetDevRC(char* rowcol);

	/******************************************************************************
	Function:
	获取连接TF卡状态
	Input：
	无
	Output：
	char* tf：获取连接TF卡状态，‘0’：异常；‘1’：正常；
	Return：
	0：获取连接TF卡状态成功
	-1：超时
	Others：
	*****************************************************************************/
	int TGVM661JCOMAPI_API TGGetDevTF(char* tf);

	/******************************************************************************
	Function:
	获取设备图像(不检测手指)
	Input：
	无
	Output：
	unsigned char* imageData：图像数据(208+500*200 Bytes)
	Return：
	0：设备获取图像成功
	-1：抓图超时
	-2:设备断开
	-3:操作取消
	Others：
	无
	*****************************************************************************/
	//int TGVM661JCOMAPI_API TGGetDevImageWithoutFinger(unsigned char* pImageData);
#endif // FACTORY
#ifdef __cplusplus 
}
#endif

#endif


#endif