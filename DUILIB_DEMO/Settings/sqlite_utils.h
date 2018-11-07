#pragma once

#include "sqlite3.h"
#include "my_including.h"
#include "str_utils.h"
#include "page_info.h"
#include "str_utils.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

extern char g_sn[32];


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : close sqlite connection
*/
int sqliteClose();


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : connect to sqlite
*/
int sqliteConn();


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : check if dev of id exists
*/
bool checkIfDevExists(char* Msg, const char* sn);


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : create tables if not exists
*/
bool createTables();


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : add a device
*/
bool addDevSqlite(char *devName, char *devCode, char *strDate, char *status);


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : select device by id
*/
bool getDevById(dev_sel_ret* devRet);


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : check if there is any admin
*/
bool checkIfAdminExists();


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : add admin
*/
bool writeAdminSqlite(char* finger, char* name, char* date);


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : check if admin of name exists
*/
bool checkIfAdminOfNameExists(char* name);


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : select all admins
*/
bool selAllAdmins(int *num, sel_admin_ret** adminRet);


bool selAllAdminsToShowInList(sel_admin_ret3* adminRet);


bool addDevSqlite(std::string username);


/*
*  author: sonne
*  date  : 2018-08-08
*  note  : get num of users
*/
int getNumOfUsers();


/*
*  author: sonne
*  date  : 2018-08-08
*  note  : select users of pageinfo
*/
bool selUsers(user_sel_ret** users, c_page_info page_info);


/*
*  author: sonne
*  date  : 2018-08-08
*  note  : add user
*/
bool addUser(std::string name);


/*
*  author: sonne
*  date  : 2018-08-08
*  note  : get num of users of current device
*/
int getNumOfCurDevUsers();


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : select users of pageinfo of current device
*/
bool selUsersOfCurDev(user_sel_ret** users, c_page_info page_info);


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : select fingers by user id
*/
bool selFingersOfUser(sel_finger_ret** fingers, std::string user_id, int* num);


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : select certs by user id
*/
bool selCertsOfUser(SW_CERT** certs, std::string user_id, int* num);


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : write user finger
*/
bool writeUserFinger(const char* finger, const char* name, const char* user_id, const char* username, char* date);


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : select all certs
*/
bool selAllCerts(int *num, cert_sel_ret** certs);


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : add cert
*/
bool addCert(std::string date, std::string content, std::string user_id, std::string type, std::string name);


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : know how many certs in current device
*/
int getNumOfCurDevCerts();



/*
*  author: sonne
*  date  : 2018-08-10
*  note  : select all certs of current device
*/
bool selAllCertsOfCurDev(SW_CERT2** certs, c_page_info page_info);


bool initCertsList(std::string user_id, std::list<SW_CERT2>* selCertsLst);


bool  select_certs_of_name(SW_CERT2 ** certs, const char* cert_name);


int CreateCertuserMany2Many(std::list<SW_CERT2> selCertsLst, std::string user_id);


int getCertsOfDevWithoutPageNum(int* cert_num);


void getUsersForEncryptionNum(int *users_num);

bool selectertsOfDevWithoutPage(SW_CERT** certs);


int selectUsersForEncryption(PSW_CERT certs, PSW_USER users, int certs_num, int *users_num);

int setUserCertMap(PSW_USER p_user, PSW_CERT p_certs, int certs_num);

int searchDevNum();


/**
*   作者：sonne
*   日期：2018-08-13
*   备注：select devices
*/
bool select_devs(dev_sel_ret** devs, c_page_info page_info);


/**
*    sonne
*    2018-08-13
*    存储日志
*/
int insertLog(char *ch_content, int type, char *manager_name, char *ch_time, char *str_date);


/**
*    sonne
*    2017-07-21
*    获取日志数
*/
int searchLogNum();


/*
* 作者：sonne
* 日期：2018-08-13
* 备注：查询日志
*/
bool  getLogs(log_select_ret* logs, c_page_info page_info);


/*
* 作者：sonne
* 日期：2018-08-13
* 备注：条件搜索后，查询日志
*/
bool searchLogs(log_select_ret * logs, c_page_info page_info,
	const char *input_manager_name, const char *input_type, const char *str_inpt_1st_date, const char *str_inpt_2nd_date);


/**
*    sonne
*    2018-08-13
*    查询日志  数
*/
int searchLogNumWithInputs(const char *input_manager_name,
	const char *input_type, const char *str_inpt_1st_date, const char *str_inpt_2nd_date);


/**
* author: sonne
* date:   2018-08-14
* note:   delete cert
*/
bool deleteCert(std::string id);


/**
* author: sonne
* date:   2018-08-14
* note:   delete finger
*/
bool deleteFinger(std::string id);


/**
*      sonne
*      2018-08-14
*      删除用户，和该用户指静脉
*/
bool deleteUserWithFingers(std::string userId);


/**
*      sonne
*      2018-08-14
*      删除用户_证书 关系表项
*/
bool deleteUserCertByUserId(std::string userId);


bool clearDb();


/*
*  author: sonne
*  date  : 2018-09-13
*  note  : select users  of current device
*/
bool selUsersOfCurDev(user_sel_ret** users, int* num);


/*
*  author: sonne
*  date  : 2018-09-13
*  note  : know how many users have not been imported into device
*/
int getNumOfNoDevUsers();


/*
*  author: sonne
*  date  : 2018-09-13
*  note  : select all certs of current device
*/
bool selUsersOfNoDev(user_sel_ret** users, c_page_info page_info);


/**
*   sonne
*   2018-09-14
*   select users by username
*/
bool  selectUsersByName(user_sel_ret ** users, const char* strUserName);


/**
*   sonne
*   2018-09-14
*   set users of list selected device id.
*/
bool setUserListDeiviceId(std::list<user_sel_ret> userList);


/**
*   sonne
*   2018-09-14
*   select cert by id
*/
bool  selectCertById(SW_CERT ** cert, const char* chCertId);


int selCertsToWrite(user_sel_ret* users, int user_num, std::list<SW_CERT>* certs, int* cert_num);



/*
*  author: sonne
*  date  : 2018-09-15
*  note  : select all certs
*/
bool selAllCertsWithPage(SW_CERT2** certs, c_page_info page_info);


/*
*  author: sonne
*  date  : 2018-09-15
*  note  : know how many certs
*/
int getNumOfCerts();


/**
*  sonne
*  2018-09-17
*  查询导入用户的全部指静脉
*/
bool selUsersFingers(std::list<user_sel_ret> selUserOfNoDevlist, P_USER_DATA pUsers);


bool  selectUserNameById(std::string* name, const char* id);



bool checkUsersFingersInfo(P_USER_INFO pUserFingerInfo, int num, std::list<SYNC_DATA>* pLstSyncData);

bool checkIfUserOfIdExists(char* id);

int getNumOfFingersCurDev();

std::string getNameOfUserId(std::string user_id);

/**
*      sonne
*      2018-10-11
*      设置用户及用户指静脉设备id为初始值
*/
bool updateUserFingersDevIdNull(std::string userId);


/**
*    sonne
*    2018-10-12
*    获取用户指静脉数
*/
int searchUserFingersNum(std::string userId);


/*
*  author: sonne
*  date  : 2018-10-12
*  note  : select users of pageinfo
*/
bool selUsers(P_USER_INFO_SEL* users, c_page_info page_info);


/**
*    sonne
*    2018-10-13
*    获取用户证书数
*/
int searchUserCertsNum(std::string userId);


/**
*      sonne
*      2018-10-16
*      编辑用户名
*/
bool editUserName(std::string name, std::string userId);


/**
*      sonne
*      2018-10-16
*      编辑指静脉名
*/
bool editFingerName(std::string id, std::string name);


/*
*  author: sonne
*  date  : 2018-10-17
*  note  : edit cert
*/
bool editCert(std::string id, std::string name, std::string date, std::string type);


bool checkIfUserOfNameExsit(std::string strUsername);

