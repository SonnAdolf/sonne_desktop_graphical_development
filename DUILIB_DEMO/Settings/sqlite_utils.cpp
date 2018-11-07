#include "sqlite_utils.h"

sqlite3 * pDB = NULL;

/*
*  author: sonne
*  date  : 2018-08-07
*  note  : close sqlite connection
*/
int sqliteClose() {
	sqlite3_close(pDB);
	return OK;
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : connect to sqlite
*/
int sqliteConn() {
	int nRes = sqlite3_open("data.db", &pDB);
	if (nRes != SQLITE_OK)
		return RET_ERROR;
	return OK;
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : create tables if not exists
*/
bool createTables() {
	using namespace std;
	string strSql = "CREATE TABLE IF NOT EXISTS admin (id integer primary key autoincrement,name varchar(255) NOT NULL,finger mediumtext NOT NULL,date varchar(20) NOT NULL);CREATE TABLE IF NOT EXISTS dev(dev_id varchar(16) primary key NOT NULL,name varchar(200) NOT NULL,date varchar(20) DEFAULT NULL,status varchar(10) DEFAULT NULL);CREATE TABLE if not exists user (id char(128)  primary key NOT NULL,username varchar(200) NOT NULL,date varchar(20) NOT NULL,dev_id varchar(16) NOT NULL,dev_name varchar(200));CREATE TABLE if not exists  finger (  id integer  primary key autoincrement ,finger mediumtext NOT NULL,name varchar(100) NOT NULL,user_id char(128) NOT NULL,username varchar(255) NOT NULL,date varchar(20) NOT NULL,dev_id varchar(16) DEFAULT NULL); CREATE TABLE if not exists  cert (id char(128) NOT NULL PRIMARY KEY,user_id char(128) DEFAULT NULL,content varchar(255) NOT NULL,type varchar(5) DEFAULT NULL,date char(50) NOT NULL,dev_id varchar(16) NOT NULL,name varchar(32) NOT NULL,time char(50) NOT NULL); CREATE TABLE if not exists user_cert (user_id char(128) NOT NULL  COLLATE NOCASE,cert_id char(128) NOT NULL,id integer  primary key autoincrement,dev_id varchar(16) NOT NULL);CREATE TABLE log (id integer  primary key autoincrement,content varchar(255) NOT NULL,manager_name varchar(80) NOT NULL,str_time varchar(60) NOT NULL,type int(1) NOT NULL,date date NOT NULL); ";
	char* cErrMsg;
	int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
	if (nRes != SQLITE_OK)
		return false;
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : check if dev of id exists
*/
bool checkIfDevExists(char* Msg, const char* sn) {
	using namespace std;
	string sql = "select count(*) from dev where dev_id = '";
	sql.append(sn);
	sql.append("';");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}

	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}


/*
*  author: sonne
*  date  : 2018-08-08
*  note  : get num of users
*/
int getNumOfUsers() {
	using namespace std;
	string sql = "select count(*) from user;";
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


/*
*  author: sonne
*  date  : 2018-08-08
*  note  : get num of users of current device
*/
int getNumOfCurDevUsers() {
	using namespace std;
	string sql = "select count(*) from user where dev_id = '";
	sql.append(g_sn);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : check if there is any admin
*/
bool checkIfAdminExists() {
	using namespace std;
	string sql = "select count(*) from admin;";

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}

	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}



/*
*  author: sonne
*  date  : 2018-08-07
*  note  : check if admin of name exists
*/
bool checkIfAdminOfNameExists(char* name) {
	using namespace std;
	string sql = "select count(*) from admin where name = '";
	sql.append(name).append("';");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}

	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}


/*
*  author: sonne
*  date  : 2018-09-26
*  note  : check if user of id exists
*/
bool checkIfUserOfIdExists(char* id) {
	using namespace std;
	string sql = "select count(*) from user where id = '";
	sql.append(id).append("';");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}

	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : add a device
*/
bool addDevSqlite(char *devName, char *devCode, char *strDate, char *status) {
	using namespace std;
	string sqlStr = "INSERT INTO dev (dev_id, name, date, status) VALUES ('";
	sqlStr.append(devCode).append("','").append(devName).append("','").append(strDate);
	sqlStr.append("','").append(status).append("');");

	char* errmsg;
	if (sqlite3_exec(pDB, sqlStr.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : select device by id
*/
bool getDevById(dev_sel_ret* devRet) {
	using namespace std;
	string sql = "select * from dev where dev_id = '";
	sql.append(g_sn).append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	if (nRow != 1) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	strcpy(devRet->name, pResult[nCol + 1]);
	strcpy(devRet->date, pResult[nCol + 2]);
	strcpy(devRet->status, pResult[nCol + 3]);
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : add admin
*/
bool writeAdminSqlite(char* finger, char* name, char* date) {
	using namespace std;
	char *chSaveBuf = new char[FINGER_SAVE_SIZE];
	STROPERATION::char_array_2_binary_str(finger, FINGER_PIC_SIZE, chSaveBuf, FINGER_SAVE_SIZE, 0);
	chSaveBuf[FINGER_SAVE_SIZE - 1] = '\0';

	string s1 = "INSERT INTO admin(name,finger,date) VALUES ('";
	s1.append(name).append("','").append(chSaveBuf).append("','").append(date).append("');");

	delete[] chSaveBuf;
	char* errmsg;
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-08
*  note  : add user
*/
bool addUser(std::string name) {
	using namespace std;
	time_t t = time(0);
	char ch_time[64];
	strftime(ch_time, sizeof(ch_time), "%Y-%m-%d %H-%M-%S", localtime(&t));
	string guid;
	STROPERATION::get_guid(guid);
	transform(guid.begin(), guid.end(), guid.begin(), ::toupper);
	string s1 = "INSERT INTO user(id,username,date,dev_id) VALUES ('";
	s1.append(guid);
	s1.append("','");
	s1.append(STROPERATION::ASCII2UTF_8(name));
	s1.append("','");
	s1.append(ch_time);
	s1.append("','");
	//s1.append(g_sn);
	s1.append("-");
	s1.append("');");
	char* errmsg;
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : select all admins
*/
bool selAllAdmins(int *num, sel_admin_ret** adminRet) {
	using namespace std;
	string sql = "select * from admin;";
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*num = nRow;
	*adminRet = new sel_admin_ret[nRow];
	int nIndex = nCol;
	sel_admin_ret *tmpAdmin;
	char buf[FINGER_PIC_SIZE];
	for (int i = 0; i < nRow; i++) {
		tmpAdmin = new sel_admin_ret;
		STROPERATION::char_array_2_binary_str(buf, FINGER_PIC_SIZE, pResult[nIndex + 2], FINGER_SAVE_SIZE - 1, 1);
		memcpy(tmpAdmin->name, pResult[nIndex + 1], 250);
		memcpy(tmpAdmin->finger, buf, FINGER_PIC_SIZE);
		(*adminRet)[i] = *tmpAdmin;
		delete tmpAdmin;
		memset(buf, 0, FINGER_PIC_SIZE);
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-07
*  note  : select all admins
*/
bool selAllAdminsToShowInList(sel_admin_ret3* adminRet) {
	using namespace std;
	adminRet->usrnames.clear();
	adminRet->dates.clear();
	adminRet->num = 0;
	string sql = "select name,date from admin;";
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	for (int i = 0; i < nRow; i++) {
		// 中文的显示在使用sqlite时需要做转化，由utf-8转化为ascii
		adminRet->usrnames.push_back(STROPERATION::UTF_82ASCII(string(pResult[nIndex])));
		adminRet->dates.push_back(string(pResult[nIndex + 1]));
		nIndex = nIndex + nCol;
	}
	adminRet->num = nRow;
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-08
*  note  : select users of pageinfo
*/
bool selUsers(user_sel_ret** users, c_page_info page_info) {
	using namespace std;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);
	string sql = "select * from user limit ";
	sql.append(buff1);
	sql.append(",");
	sql.append(buff2);
	sql.append(";");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*users = new user_sel_ret[nRow];
	int nIndex = nCol;
	user_sel_ret *tmpUser;
	for (int i = 0; i < nRow; i++) {
		tmpUser = new user_sel_ret;
		memcpy(tmpUser->id, pResult[nIndex], 128);
		memcpy(tmpUser->name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 1])).c_str(), 200);
		memcpy(tmpUser->date, pResult[nIndex + 2], 20);
		//strcpy(tmpUser->dev_name, pResult[nIndex + 4]);
		(*users)[i] = *tmpUser;
		delete tmpUser;
		nIndex = nIndex + nCol;
	}
	return true;
}


/**
*    sonne
*    2018-10-13
*    获取用户证书数
*/
int searchUserCertsNum(std::string userId) {
	using namespace std;
	string sql = "select count(*) from user_cert where user_id = '";
	sql.append(userId);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


/*
*  author: sonne
*  date  : 2018-10-12
*  note  : select users of pageinfo
*/
bool selUsers(P_USER_INFO_SEL* users, c_page_info page_info) {
	using namespace std;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);
	string sql = "select * from user limit ";
	sql.append(buff1);
	sql.append(",");
	sql.append(buff2);
	sql.append(";");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*users = new USER_INFO_SEL[nRow];
	int nIndex = nCol;
	P_USER_INFO_SEL tmpUser;
	for (int i = 0; i < nRow; i++) {
		tmpUser = new USER_INFO_SEL;
		memcpy(tmpUser->id, pResult[nIndex], 128);
		tmpUser->fingerNum = searchUserFingersNum(tmpUser->id);
		tmpUser->certNum = searchUserCertsNum(tmpUser->id);
		memcpy(tmpUser->name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 1])).c_str(), 200);
		strcpy(tmpUser->dev_name, pResult[nIndex + 3]);
		memcpy(tmpUser->date, pResult[nIndex + 2], 20);
		//strcpy(tmpUser->dev_name, pResult[nIndex + 4]);
		(*users)[i] = *tmpUser;
		delete tmpUser;
		nIndex = nIndex + nCol;
	}
	return true;
}

bool addDevSqlite(std::string username) {
	using namespace std;
	string sql = "DELETE FROM admin WHERE name = '" + STROPERATION::ASCII2UTF_8(username) + "';";

	char* errmsg;
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : delete admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : select users of pageinfo of current device
*/
bool selUsersOfCurDev(user_sel_ret** users, c_page_info page_info) {
	using namespace std;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);
	string sql = "select * from user where dev_id = '";
	sql.append(g_sn);
	sql.append("' limit ");
	sql.append(buff1);
	sql.append(",");
	sql.append(buff2);
	sql.append(";");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*users = new user_sel_ret[nRow];
	int nIndex = nCol;
	user_sel_ret *tmpUser;
	for (int i = 0; i < nRow; i++) {
		tmpUser = new user_sel_ret;
		memcpy(tmpUser->id, pResult[nIndex], 128);
		memcpy(tmpUser->name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 1])).c_str(), 200);
		memcpy(tmpUser->date, pResult[nIndex + 2], 20);
		//strcpy(tmpUser->dev_name, pResult[nIndex + 4]);
		(*users)[i] = *tmpUser;
		delete tmpUser;
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-09-13
*  note  : select users  of current device
*/
bool selUsersOfCurDev(user_sel_ret** users, int* num) {
	using namespace std;
	string sql = "select * from user where dev_id = '";
	sql.append(g_sn);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*users = new user_sel_ret[nRow];
	*num = nRow;
	int nIndex = nCol;
	user_sel_ret *tmpUser;
	for (int i = 0; i < nRow; i++) {
		tmpUser = new user_sel_ret;
		memcpy(tmpUser->id, pResult[nIndex], 128);
		memcpy(tmpUser->name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 1])).c_str(), 200);
		memcpy(tmpUser->date, pResult[nIndex + 2], 20);
		//strcpy(tmpUser->dev_name, pResult[nIndex + 4]);
		(*users)[i] = *tmpUser;
		delete tmpUser;
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : select fingers by user id
*/
bool selFingersOfUser(sel_finger_ret** fingers, std::string user_id, int* num) {
	using namespace std;
	string sql = "select * from finger where user_id = '";
	sql.append(user_id);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*num = nRow;
	*fingers = new sel_finger_ret[nRow];
	int nIndex = nCol;
	sel_finger_ret *tmpFinger;
	for (int i = 0; i < nRow; i++) {
		tmpFinger = new sel_finger_ret;
		tmpFinger->id.append(pResult[nIndex]);
		memcpy(tmpFinger->name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 2])).c_str(), 100);
		memcpy(tmpFinger->date, pResult[nIndex + 5], 20);
		(*fingers)[i] = *tmpFinger;
		delete tmpFinger;
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : select certs by user id
*/
bool selCertsOfUser(SW_CERT** certs, std::string user_id, int* num) {
	using namespace std;
	string sql = "select * from cert where user_id = '";
	sql.append(user_id);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*num = nRow;
	*certs = new SW_CERT[nRow];
	int nIndex = nCol;
	SW_CERT *tmpCert;
	for (int i = 0; i < nRow; i++) {
		tmpCert = new SW_CERT;
		memcpy(tmpCert->byKey, pResult[nIndex + 2], 64);
		tmpCert->dwFlags = atoi(pResult[nIndex + 3]);
		(*certs)[i] = *tmpCert;
		delete tmpCert;
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : write user finger
*/
bool writeUserFinger(const char* finger, const char* name, const char* user_id, const char* username, char* date) {
	using namespace std;
	char *chSaveBuf = new char[FINGER_SAVE_SIZE];
	STROPERATION::char_array_2_binary_str(finger, FINGER_PIC_SIZE, chSaveBuf, FINGER_SAVE_SIZE, 0);
	chSaveBuf[FINGER_SAVE_SIZE - 1] = '\0';

	string s1 = "INSERT INTO finger(finger,name,user_id,username,date,dev_id) VALUES ('";
	s1.append(chSaveBuf).append("','").append(STROPERATION::ASCII2UTF_8(string(name))).append("','").append(user_id).append("','");
	s1.append(username).append("','").append(date).append("','").append(g_sn).append("');");

	delete[] chSaveBuf;
	char* errmsg;
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : select all certs
*/
bool selAllCerts(int *num, cert_sel_ret** certs) {
	using namespace std;
	string sql = "select * from cert;";
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*num = nRow;
	*certs = new cert_sel_ret[nRow];
	int nIndex = nCol;
	cert_sel_ret *tmpCerts;
	for (int i = 0; i < nRow; i++) {
		tmpCerts = new cert_sel_ret;
		memcpy(tmpCerts->id, pResult[nIndex], 128);
		memcpy(tmpCerts->user_id, pResult[nIndex + 1], 128);
		memcpy(tmpCerts->content, pResult[nIndex + 2], 255);
		memcpy(tmpCerts->type, pResult[nIndex + 3], 5);
		strcpy(tmpCerts->date, pResult[nIndex + 4]);
		strcpy(tmpCerts->name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 6])).c_str());
		(*certs)[i] = *tmpCerts;
		delete tmpCerts;
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : add cert
*/
bool addCert(std::string date, std::string content, std::string user_id, std::string type, std::string name) {
	using namespace std;
	char ch_time[40];
	STROPERATION::getDateString(ch_time);
	string guid;
	STROPERATION::get_guid(guid);

	string s1 = "INSERT INTO cert(id,user_id,content,type,date,name,dev_id,time) VALUES ('";
	s1.append(guid).append("','").append(user_id).append("','").append(content).append("','");
	s1.append(type).append("','").append(date).append("','").append(name).append("','").append("-");
	s1.append("','").append(ch_time).append("');");
	char* errmsg;
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/**
* author: sonne
* date:   2018-08-14
* note:   delete cert
*/
bool deleteCert(std::string id) {
	using namespace std;
	string s1 = "delete from user_cert where cert_id='";
	s1.append(id);
	s1.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	s1 = "delete from cert where content='";
	s1.append(id);
	s1.append("';");
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


bool clearDb() {
	using namespace std;
	char* errmsg;
	string s1 = "update user_cert set dev_id='-'  where dev_id='";
	s1.append(g_sn);
	s1.append("';");
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	//s1 = "delete from cert where dev_id='";
	//s1.append(g_sn);
	//s1.append("';");
	//if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
	//	cout << "sqlite : insert admin failed. error : " << errmsg << endl;
	//	sqlite3_free(errmsg);
	//	return false;
	//}
	//s1 = "delete from user where dev_id='";
	//s1.append(g_sn);
	//s1.append("';");
	s1 = "update user set dev_id = '-'  where dev_id='";
	s1.append(g_sn);
	s1.append("';");
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	s1 = "update finger set dev_id='-' where dev_id='";
	s1.append(g_sn);
	s1.append("';");
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/**
*      sonne
*      2018-08-14
*      删除用户，和该用户指静脉
*/
bool deleteUserWithFingers(std::string userId) {
	using namespace std;
	string sql = "delete from finger where user_id='";
	sql.append(userId);
	sql.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	//sql = "delete from user_dev where user_id='";
	//sql.append(userId);
	//sql.append("' and dev_id = '");
	//sql.append(g_sn);
	//sql.append("';");
	//if (mysql_query(&mysql, sql.c_str()) != 0)
	//	return RET_ERROR;
	sql = "delete from user where id='";
	sql.append(userId);
	sql.append("';");
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/**
*      sonne
*      2018-10-11
*      设置用户及用户指静脉设备id为初始值
*/
bool updateUserFingersDevIdNull(std::string userId) {
	using namespace std;
	string sql = "update finger set dev_id = '-' where user_id = '";
	sql.append(userId);
	sql.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	sql = "update user set dev_id = '-' where id = '";
	sql.append(userId);
	sql.append("';");
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	sql = "update user_cert set dev_id = '-' where user_id = '";
	sql.append(userId);
	sql.append("';");
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/**
*      sonne
*      2018-10-16
*      编辑用户名
*/
bool editUserName(std::string name, std::string userId) {
	using namespace std;
	string sql = "update user set username = '";
	sql.append(name);
	sql.append("' where id = '");
	sql.append(userId);
	sql.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/**
*      sonne
*      2018-10-16
*      编辑指静脉名
*/
bool editFingerName(std::string id, std::string name) {
	using namespace std;
	string sql = "update finger set name = '";
	sql.append(name);
	sql.append("' where id = '");
	sql.append(id);
	sql.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/**
*      sonne
*      2018-08-14
*      删除用户_证书 关系表项
*/
bool deleteUserCertByUserId(std::string userId) {
	using namespace std;
	string sql = "delete from user_cert where user_id='";
	sql.append(userId);
	sql.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/**
* author: sonne
* date:   2018-08-14
* note:   delete finger
*/
bool deleteFinger(std::string id) {
	using namespace std;
	string s1 = "delete from finger where id='";
	s1.append(id);
	s1.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, s1.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-08-09
*  note  : know how many certs in current device
*/
int getNumOfCurDevCerts() {
	using namespace std;
	string sql = "select count(*) from cert where dev_id = '";
	sql.append(g_sn);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


/*
*  author: sonne
*  date  : 2018-09-15
*  note  : know how many certs
*/
int getNumOfCerts() {
	using namespace std;
	string sql = "select count(*) from cert";
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


/*
*  author: sonne
*  date  : 2018-09-13
*  note  : know how many users have not been imported into device
*/
int getNumOfNoDevUsers() {
	using namespace std;
	string sql = "select count(*) from user where dev_id = '-';";
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


bool checkIfUserOfNameExsit(std::string strUsername) {
	using namespace std;
	string sql = "select count(*) from user where username = '";
	sql.append(strUsername);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	if (atoi(pResult[nIndex]) > 0)
		return true;
	return false;
}


/*
*  author: sonne
*  date  : 2018-08-10
*  note  : select all certs of current device
*/
bool selAllCertsOfCurDev(SW_CERT2** certs, c_page_info page_info) {
	using namespace std;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);

	string sql = "select * from cert where dev_id = '";
	sql.append(g_sn);
	sql.append("' limit ");
	sql.append(buff1);
	sql.append(",");
	sql.append(buff2);
	sql.append(";");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*certs = new SW_CERT2[nRow];
	int nIndex = nCol;
	SW_CERT2 *tmpCerts;
	for (int i = 0; i < nRow; i++) {
		tmpCerts = new SW_CERT2;
		memcpy(tmpCerts->id, pResult[nIndex], 128);
		memcpy(tmpCerts->byKey, pResult[nIndex + 2], 64);
		tmpCerts->dwFlags = atoi(pResult[nIndex + 3]);
		memcpy(tmpCerts->wszName, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 6])).c_str(), 32);
		(*certs)[i] = *tmpCerts;
		delete tmpCerts;
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
*  author: sonne
*  date  : 2018-09-15
*  note  : select all certs
*/
bool selAllCertsWithPage(SW_CERT2** certs, c_page_info page_info) {
	using namespace std;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);

	string sql = "select * from cert ";
	sql.append(" limit ");
	sql.append(buff1);
	sql.append(",");
	sql.append(buff2);
	sql.append(";");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*certs = new SW_CERT2[nRow];
	int nIndex = nCol;
	SW_CERT2 *tmpCerts;
	for (int i = 0; i < nRow; i++) {
		tmpCerts = new SW_CERT2;
		memcpy(tmpCerts->id, pResult[nIndex], 128);
		memcpy(tmpCerts->byKey, pResult[nIndex + 2], 64);
		tmpCerts->dwFlags = atoi(pResult[nIndex + 3]);
		memcpy(tmpCerts->wszName, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 6])).c_str(), 32);
		(*certs)[i] = *tmpCerts;
		delete tmpCerts;
		nIndex = nIndex + nCol;
	}
	return true;
}



/*
*  author: sonne
*  date  : 2018-09-13
*  note  : select all certs of current device
*/
bool selUsersOfNoDev(user_sel_ret** users, c_page_info page_info) {
	using namespace std;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);

	string sql = "select * from user where dev_id = '";
	sql.append("-");
	sql.append("' limit ");
	sql.append(buff1);
	sql.append(",");
	sql.append(buff2);
	sql.append(";");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*users = new user_sel_ret[nRow];
	int nIndex = nCol;
	user_sel_ret *tmpUser;
	for (int i = 0; i < nRow; i++) {
		tmpUser = new user_sel_ret;
		memcpy(tmpUser->id, pResult[nIndex], 128);
		memcpy(tmpUser->name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 1])).c_str(), 200);
		memcpy(tmpUser->date, pResult[nIndex + 2], 20);
		(*users)[i] = *tmpUser;
		delete tmpUser;
		nIndex = nIndex + nCol;
	}
	return true;
}


bool initCertsList(std::string user_id, std::list<SW_CERT2>* selCertsLst) {
	using namespace std;
	string sql = "SELECT * FROM cert INNER JOIN user_cert ON user_cert.cert_id=cert.content INNER JOIN user ON user.id='";
	sql.append(user_id);
	sql.append("' and user.id=user_cert.user_id;");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	SW_CERT2 *tmpCerts;
	for (int i = 0; i < nRow; i++) {
		SW_CERT2 tmpCert;
		strcpy(tmpCert.id, pResult[nIndex]);
		strcpy(tmpCert.byKey, pResult[nIndex + 2]);
		tmpCert.dwFlags = atoi(pResult[nIndex + 3]);
		strcpy(tmpCert.wszName, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 6])).c_str());
		selCertsLst->push_back(tmpCert);
		nIndex = nIndex + nCol;
	}
	return true;
}


bool  select_certs_of_name(SW_CERT2 ** certs, const char* cert_name) {
	using namespace std;
	string sql = "select * from cert where name = '";
	sql.append(STROPERATION::ASCII2UTF_8(string(cert_name))).append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*certs = new SW_CERT2[nRow];
	int nIndex = nCol;
	SW_CERT2 *tmpCerts;
	for (int i = 0; i < nRow; i++) {
		tmpCerts = new SW_CERT2;
		memcpy(tmpCerts->id, pResult[nIndex], 128);
		memcpy(tmpCerts->byKey, pResult[nIndex + 2], 64);
		tmpCerts->byKey[64] = '\0';
		tmpCerts->dwFlags = atoi(pResult[nIndex + 3]);
		memcpy(tmpCerts->wszName, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 6])).c_str(), 32);
		(*certs)[i] = *tmpCerts;
		delete tmpCerts;
		nIndex = nIndex + nCol;
	}
	return true;
}


/**
*   sonne
*   2018-09-14
*   select users by username
*/
bool  selectUsersByName(user_sel_ret ** users, const char* strUserName) {
	using namespace std;
	string sql = "select * from user where username = '";
	sql.append(STROPERATION::ASCII2UTF_8(string(strUserName))).append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*users = new user_sel_ret[nRow];
	int nIndex = nCol;
	user_sel_ret *tmpUser;
	for (int i = 0; i < nRow; i++) {
		tmpUser = new user_sel_ret;
		memcpy(tmpUser->id, pResult[nIndex], 128);
		memcpy(tmpUser->name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 1])).c_str(), 200);
		memcpy(tmpUser->date, pResult[nIndex + 2], 20);
		(*users)[i] = *tmpUser;
		delete tmpUser;
		nIndex = nIndex + nCol;
	}
	return true;
}


/**
*   sonne
*   2018-09-14
*   set users of list selected device id.
*/
bool setUserListDeiviceId(std::list<user_sel_ret> userList) {
	using namespace std;
	string sql;
	char* errmsg;
	for (list<user_sel_ret>::iterator iter = userList.begin(); iter != userList.end(); iter++) {
		sql = "update user set dev_id='";
		sql.append(g_sn);
		sql.append("' where username = '");
		sql.append(STROPERATION::ASCII2UTF_8(string(iter->name)));
		sql.append("';");

		if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
			cout << "sqlite : insert admin failed. error : " << errmsg << endl;
			sqlite3_free(errmsg);
			return false;
		}

		sql = "update user_cert set dev_id='";
		sql.append(g_sn);
		sql.append("' where user_id = '");
		sql.append(iter->id);
		sql.append("';");

		if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
			cout << "sqlite : insert admin failed. error : " << errmsg << endl;
			sqlite3_free(errmsg);
			return false;
		}
	}
	return true;
}


int CreateCertuserMany2Many(std::list<SW_CERT2> selCertsLst, std::string user_id) {
	using namespace std;
	// 首先清空原有的该用户 user_cert项
	string del_sql = "delete from user_cert where user_id = '";
	del_sql.append(user_id);
	del_sql.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, del_sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return -1;
	}
	// 添加证书和用户  多对一关系
	string sql2 = "";
	for (list<SW_CERT2>::iterator iter = selCertsLst.begin(); iter != selCertsLst.end(); iter++) {
		sql2 = "insert into user_cert(user_id,cert_id,dev_id) values('";
		sql2.append(user_id).append("','");
		sql2.append(iter->byKey);
		sql2.append("','");
		//sql2.append(g_sn);
		sql2.append("-");
		sql2.append("');");
		if (sqlite3_exec(pDB, sql2.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
			cout << "sqlite : insert admin failed. error : " << errmsg << endl;
			sqlite3_free(errmsg);
			return -1;
		}
	}
	return 0;
}


int getCertsOfDevWithoutPageNum(int* cert_num) {
	using namespace std;
	std::string sql = "select * from cert where dev_id = '";
	sql.append(g_sn);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	*cert_num = nRow;
	return OK;
}


void getUsersForEncryptionNum(int *users_num) {
	using namespace std;
	// 获取当前设备的所有用户
	string sql = "select * from user where dev_id = '";
	sql.append(g_sn);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return;
	}
	*users_num = nRow;
}


bool selectertsOfDevWithoutPage(SW_CERT** certs) {
	using namespace std;
	string sql = "select * from cert where dev_id = '";
	sql.append(g_sn);
	sql.append("';");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	//*certs = new SW_CERT[nRow];
	int nIndex = nCol;
	for (int i = 0; i < nRow; i++) {
		SW_CERT tmpCert;
		strcpy(tmpCert.byKey, pResult[nIndex + 2]);
		tmpCert.dwFlags = atoi(pResult[nIndex + 3]);
		// 从数据库读取的有效期字符串转化为FILETIME
		SYSTEMTIME time;
		STROPERATION::string_to_date(pResult[nIndex + 4], time);
		FILETIME file_time;
		SystemTimeToFileTime(&time, &file_time);
		tmpCert.ftExpireDate = file_time;
		// 从数据库读取的创建证书时间转化为FILETIME
		STROPERATION::string_to_date(pResult[nIndex + 7], time);
		SystemTimeToFileTime(&time, &file_time);
		tmpCert.ftCreateDate = file_time;
		strcpy(tmpCert.wszName, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 6])).c_str());
		(*certs)[i] = tmpCert;
		nIndex = nIndex + nCol;
	}
	return true;
}



int selectUsersForEncryption(PSW_CERT certs, PSW_USER users, int certs_num, int *users_num) {
	using namespace std;
	// 获取当前设备的所有用户
	std::string sql = "select * from user where dev_id = '";
	sql.append(g_sn);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*users_num = nRow;
	int nIndex = nCol;
	int num = 0;
	for (int i = 0; i < nRow; i++) {
		SW_USER tmp_user;
		//CLSIDFromString((LPCOLESTR)m_users_row[0], (LPCLSID)&tmp_user.UserID);
		STROPERATION::LPCTSR2GUID(pResult[nIndex], tmp_user.UserID);
		setUserCertMap(&tmp_user, certs, certs_num);

		users[num++] = tmp_user;
		nIndex = nIndex + nCol;
	}

	return OK;
}


int setUserCertMap(PSW_USER p_user, PSW_CERT p_certs, int certs_num) {
	using namespace std;
	string sql;
	int rnum, j;
	string str_guid = STROPERATION::GUID2LPCTS(p_user->UserID);
	p_user->dwCertMap[0] = 0;
	p_user->dwCertMap[1] = 0;

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	for (int i = 0; i < certs_num; i++) {
		sql = "select * from user_cert where user_id = '";
		sql.append(str_guid);
		sql.append("' and cert_id = '");
		sql.append(p_certs[i].byKey);
		sql.append("';");
		if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
			cout << "sqlite : select data failed. error : " << errmsg << endl;
			sqlite3_free(errmsg);
			return RET_ERROR;
		}
		if (nRow > 0) {
			if (i < 32)
				STROPERATION::dword_bit_set(&p_user->dwCertMap[0], 1 + i, 1);
			else
				STROPERATION::dword_bit_set(&p_user->dwCertMap[1], i - 31, 1);
		}
	}
	return OK;
}


int searchDevNum() {
	using namespace std;
	string sql = "select count(*) from dev;";
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


/**
*    sonne
*    2017-07-21
*    获取日志数
*/
int searchLogNum() {
	using namespace std;
	string sql = "select count(*) from log;";
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


/**
*    sonne
*    2018-10-12
*    获取用户指静脉数
*/
int searchUserFingersNum(std::string userId) {
	using namespace std;
	string sql = "select count(*) from finger where user_id = '";
	sql.append(userId);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}


/**
*   作者：sonne
*   日期：2018-08-13
*   备注：select devices
*/
bool select_devs(dev_sel_ret** devs, c_page_info page_info) {
	using namespace std;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);

	string sql = "select * from dev limit ";
	sql.append(buff1);
	sql.append(",");
	sql.append(buff2);
	sql.append(";");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*devs = new dev_sel_ret[nRow];
	int nIndex = nCol;
	dev_sel_ret *tmpDev;
	for (int i = 0; i < nRow; i++) {
		tmpDev = new dev_sel_ret;
		strcpy(tmpDev->id, pResult[nIndex]);
		tmpDev->id[16] = '\0';
		memcpy(tmpDev->name, pResult[nIndex + 1], 200);
		memcpy(tmpDev->date, pResult[nIndex + 2], 20);
		memcpy(tmpDev->status, pResult[nIndex + 3], 10);
		(*devs)[i] = *tmpDev;
		delete tmpDev;
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
* 作者：sonne
* 日期：2018-08-13
* 备注：查询日志
*/
bool  getLogs(log_select_ret* logs, c_page_info page_info) {
	using namespace std;
	logs->error_flag = false;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);
	string sql = "select manager_name,content,str_time,type from log order by id desc limit ";
	sql.append(buff1).append(",").append(buff2).append(";");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		logs->error_flag = true;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	for (int i = 0; i < nRow; i++) {
		logs->manager_names.push_back(STROPERATION::UTF_82ASCII(string(pResult[nIndex])));
		logs->contents.push_back(string(pResult[nIndex + 1]));
		logs->times.push_back(string(pResult[nIndex + 2]));
		logs->types.push_back(string(pResult[nIndex + 3]));
		nIndex = nIndex + nCol;
	}
	return true;
}


/*
* 作者：sonne
* 日期：2018-08-13
* 备注：条件搜索后，查询日志
*/
bool searchLogs(log_select_ret * logs, c_page_info page_info,
	const char *input_manager_name, const char *input_type, const char *str_inpt_1st_date, const char *str_inpt_2nd_date) {
	using namespace std;
	bool is_input1_null =
		STROPERATION::check_is_charpointer_null(input_manager_name);
	bool is_input2_null =
		STROPERATION::check_is_charpointer_null(input_type);
	bool is_input3_null =
		STROPERATION::check_is_charpointer_null(str_inpt_1st_date);
	bool is_input4_null =
		STROPERATION::check_is_charpointer_null(str_inpt_2nd_date);
	if (is_input1_null && is_input2_null && is_input3_null && is_input4_null)
		return getLogs(logs, page_info);
	logs->error_flag = false;
	int begin_index = page_info.get_begin_index();
	int every_page = page_info.get_every_page();
	char buff1[5];
	char buff2[5];
	itoa(begin_index, buff1, 10);
	itoa(every_page, buff2, 10);

	char sql[2048] = "select manager_name,content,str_time,type from log where ";
	if (!is_input1_null) {
		STROPERATION::link(sql, "manager_name = '");
		STROPERATION::link(sql, input_manager_name);
		STROPERATION::link(sql, "'");
		if (!is_input2_null) {
			STROPERATION::link(sql, " and ");
		}
	}
	if (!is_input2_null) {
		STROPERATION::link(sql, "type = ");
		STROPERATION::link(sql, input_type);
	}
	if (!is_input3_null && !is_input4_null) {
		if (!is_input1_null || !is_input2_null)
			STROPERATION::link(sql, " and ");
		STROPERATION::link(sql, " date between '");
		STROPERATION::link(sql, str_inpt_1st_date);
		STROPERATION::link(sql, "' and '");
		STROPERATION::link(sql, str_inpt_2nd_date);
		STROPERATION::link(sql, "'");
	}
	if (!is_input3_null && is_input4_null) {
		if (!is_input1_null || !is_input2_null)
			STROPERATION::link(sql, " and ");
		STROPERATION::link(sql, " date >= '");
		STROPERATION::link(sql, str_inpt_1st_date);
		STROPERATION::link(sql, "'");
	}
	if (is_input3_null && !is_input4_null) {
		if (!is_input1_null || !is_input2_null)
			STROPERATION::link(sql, " and ");
		STROPERATION::link(sql, " date <= '");
		STROPERATION::link(sql, str_inpt_2nd_date);
		STROPERATION::link(sql, "'");
	}

	STROPERATION::link(sql, "  order by id desc limit ");
	STROPERATION::link(sql, buff1);
	STROPERATION::link(sql, ",");
	STROPERATION::link(sql, buff2);
	STROPERATION::link(sql, ";");

	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql, &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		logs->error_flag = true;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	for (int i = 0; i < nRow; i++) {
		logs->manager_names.push_back(STROPERATION::UTF_82ASCII(string(pResult[nIndex])));
		logs->contents.push_back(string(pResult[nIndex + 1]));
		logs->times.push_back(string(pResult[nIndex + 2]));
		logs->types.push_back(string(pResult[nIndex + 3]));
		nIndex = nIndex + nCol;
	}
	return true;
}


/**
*    sonne
*    2018-08-13
*    查询日志  数
*/
int searchLogNumWithInputs(const char *input_manager_name, const char *input_type, const char *str_inpt_1st_date, const char *str_inpt_2nd_date) {
	using namespace std;
	bool is_input1_null =
		STROPERATION::check_is_charpointer_null(input_manager_name);
	bool is_input2_null =
		STROPERATION::check_is_charpointer_null(input_type);
	bool is_input3_null =
		STROPERATION::check_is_charpointer_null(str_inpt_1st_date);
	bool is_input4_null =
		STROPERATION::check_is_charpointer_null(str_inpt_2nd_date);
	if (is_input1_null && is_input2_null && is_input3_null && is_input4_null)
		return searchLogNum();

	char sql[2048] = "select count(*) from log where ";
	if (!is_input1_null) {
		STROPERATION::link(sql, "manager_name = '");
		STROPERATION::link(sql, input_manager_name);
		STROPERATION::link(sql, "'");
		if (!is_input2_null) {
			STROPERATION::link(sql, " and ");
		}
	}
	if (!is_input2_null) {
		STROPERATION::link(sql, "type = ");
		STROPERATION::link(sql, input_type);
	}
	if (!is_input3_null && !is_input4_null) {
		if (!is_input1_null || !is_input2_null)
			STROPERATION::link(sql, " and ");
		STROPERATION::link(sql, " date between '");
		STROPERATION::link(sql, str_inpt_1st_date);
		STROPERATION::link(sql, "' and '");
		STROPERATION::link(sql, str_inpt_2nd_date);
		STROPERATION::link(sql, "'");
	}
	if (!is_input3_null && is_input4_null) {
		if (!is_input1_null || !is_input2_null)
			STROPERATION::link(sql, " and ");
		STROPERATION::link(sql, " date >= '");
		STROPERATION::link(sql, str_inpt_1st_date);
		STROPERATION::link(sql, "'");
	}
	if (is_input3_null && !is_input4_null) {
		if (!is_input1_null || !is_input2_null)
			STROPERATION::link(sql, " and ");
		STROPERATION::link(sql, " date <= '");
		STROPERATION::link(sql, str_inpt_2nd_date);
		STROPERATION::link(sql, "'");
	}
	STROPERATION::link(sql, ";");


	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql, &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}



/**
*    sonne
*    2018-08-13
*    存储日志
*/
int insertLog(char *ch_content, int type, char *manager_name, char *ch_time, char *str_date) {
	char sql_str[200] = { 0 };
	sprintf_s(sql_str, "%s%s%s%s%s%s%s%s%s%s%d%s",
		"INSERT INTO log (content,manager_name,str_time,date,type) VALUES ('",
		ch_content,
		"','",
		manager_name,
		"','",
		ch_time,
		"',",
		"'",
		str_date,
		"',",
		type,
		");");
	char* errmsg;
	if (sqlite3_exec(pDB, sql_str, NULL, NULL, &errmsg) != SQLITE_OK) {
		sqlite3_free(errmsg);
		return false;
	}
	return 0;
}



/**
*   sonne
*   2018-09-14
*   select cert by id
*/
bool  selectCertById(SW_CERT ** cert, const char* chCertId) {
	using namespace std;
	string sql = "select * from cert where content = '";
	sql.append(chCertId).append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	*cert = new SW_CERT[nRow];
	int nIndex = nCol;
	for (int i = 0; i < nRow; i++) {
		SW_CERT tmpCert;
		strcpy(tmpCert.byKey, pResult[nIndex + 2]);
		tmpCert.dwFlags = atoi(pResult[nIndex + 3]);
		// 从数据库读取的有效期字符串转化为FILETIME
		SYSTEMTIME time;
		STROPERATION::string_to_date(pResult[nIndex + 4], time);
		FILETIME file_time;
		SystemTimeToFileTime(&time, &file_time);
		tmpCert.ftExpireDate = file_time;
		// 从数据库读取的创建证书时间转化为FILETIME
		STROPERATION::string_to_date(pResult[nIndex + 7], time);
		SystemTimeToFileTime(&time, &file_time);
		tmpCert.ftCreateDate = file_time;
		strcpy(tmpCert.wszName, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 6])).c_str());
		(*cert)[i] = tmpCert;
		nIndex = nIndex + nCol;
	}
	return true;
}


int selCertsToWrite(user_sel_ret* users, int user_num, std::list<SW_CERT>* certs, int* cert_num) {
	using namespace std;
	for (int i = 0; i < user_num; i++) {
		user_sel_ret temp_user = users[i];
		// 查询和该用户关联的证书id
		string sql = "select cert_id from user_cert where user_id = '";
		sql.append(temp_user.id);
		sql.append("';");
		char* errmsg;
		char** pResult;
		int nRow, nCol;
		if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
			cout << "sqlite : select data failed. error : " << errmsg << endl;
			sqlite3_free(errmsg);
			return false;
		}
		int nIndex = nCol;
		string tmpStrCertId;
		for (int j = 0; j < nRow; j++) {
			tmpStrCertId = pResult[nIndex];
			PSW_CERT cert;
			selectCertById(&cert, tmpStrCertId.c_str());
			bool bAlreadyInLst = false;
			for (list<SW_CERT>::iterator iter = certs->begin(); iter != certs->end(); iter++) {
				if (0 == strcmp(iter->byKey, cert->byKey)) {
					bAlreadyInLst = true;
				}
			}
			if (!bAlreadyInLst)
				certs->push_back(*cert);
			delete[] cert;
			cert = NULL;
			nIndex = nIndex + nCol;
		}
	}
	*cert_num = certs->size();
	return true;
}


/**
*  sonne
*  2018-09-17
*  查询导入用户的全部指静脉
*/
bool selUsersFingers(std::list<user_sel_ret> selUserOfNoDevlist, P_USER_DATA pUsers) {
	using namespace std;

	string sql;
	char *chFingerBuf = new char[FINGER_PIC_SIZE];
	char crc1, crc2;
	WORD crc;
	int i = 0;
	for (list<user_sel_ret>::iterator iter = selUserOfNoDevlist.begin(); iter != selUserOfNoDevlist.end(); iter++) {
		sql = "select * from finger where user_id = '";
		sql.append(iter->id);
		sql.append("';");
		char* errmsg;
		char** pResult;
		int nRow, nCol;
		if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
			cout << "sqlite : select data failed. error : " << errmsg << endl;
			sqlite3_free(errmsg);
			return false;
		}
		int nIndex = nCol;

		pUsers[i].fnum = nRow;
		strcpy(pUsers[i].user_name, iter->name);
		strcpy(pUsers[i].user_id, iter->id);

		for (int j = 0; j < nRow; j++) {
			if (j > 6)
				break;
			memset(chFingerBuf, 0, FINGER_PIC_SIZE);
			STROPERATION::char_array_2_binary_str(chFingerBuf, FINGER_PIC_SIZE, pResult[nIndex + 1], FINGER_SAVE_SIZE - 1, 1);
			memcpy(pUsers[i].fingers[j].fdata, chFingerBuf, FINGER_PIC_SIZE);
			strcpy(pUsers[i].fingers[j].finger_name, STROPERATION::UTF_82ASCII(string(pResult[nIndex + 2])).c_str());

			nIndex = nIndex + nCol;
		}

		// crc
		crc = STROPERATION::CrcCompute((BYTE*)&pUsers[i], sizeof(USER_DATA) - 4);
		crc1 = (crc >> 8) & 0xff;
		crc2 = crc & 0xff;
		pUsers[i].crc[0] = crc1;
		pUsers[i].crc[1] = crc2;
		i++;
	}
	delete[] chFingerBuf;
	return true;
}


bool  selectUserNameById(std::string* name, const char* id) {
	using namespace std;
	string sql = "select username from user where id = '";
	sql.append(id).append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	int nIndex = nCol;
	*name = STROPERATION::UTF_82ASCII(string(pResult[nIndex]));
	return true;
}


bool checkUsersFingersInfo(P_USER_INFO pUserFingerInfo, int iUserFingerInfoNum, std::list<SYNC_DATA>* pLstSyncData) {
	using namespace std;
	bool flag = true;
	bool bIsSync = true;
	string sql;
	char* errmsg;
	char** pResult;
	int nRow, nCol, iUserNumDb, nIndex;
	SYNC_DATA tempSyncData;
	char *chFingerBuf = new char[FINGER_PIC_SIZE];
	string strTempName;

	// 遍历  设备中   用户
	for (int i = 0; i < iUserFingerInfoNum; i++) {

		// 如果该设备中用户 DB里不存在，发指令删除该用户
		if (!checkIfUserOfIdExists(pUserFingerInfo[i].user_id)) {
			strcpy(tempSyncData.user_id, pUserFingerInfo[i].user_id);
			tempSyncData.sync_flag = 2;
			pLstSyncData->push_back(tempSyncData);
			bIsSync = false;
			continue;
		}

		// 若存在该用户，判断用户名是否变更
		if (pUserFingerInfo[i].user_id) {
			selectUserNameById(&strTempName, pUserFingerInfo[i].user_id);
			if (strTempName.compare(pUserFingerInfo[i].user_name) != 0) {
				strcpy(tempSyncData.user_id, pUserFingerInfo[i].user_id);
				tempSyncData.sync_flag = 3;
				strcpy(tempSyncData.user_name, strTempName.c_str());
				pLstSyncData->push_back(tempSyncData);
				bIsSync = false;
				//continue;
			}
		}

		sql = "select name,finger from finger where user_id ='";
		sql.append(pUserFingerInfo[i].user_id);
		sql.append("';");
		if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
			sqlite3_free(errmsg);
			return false;
		}

		nIndex = nCol;

		for (int k = 0; k < nRow; k++) {
			// 遍历该用户设备中指静脉信息
			flag = false;
			for (int j = 0; j < pUserFingerInfo[i].fnum; j++) {
				if (strcmp((char*)pUserFingerInfo[i].fdata[j].finger_name, STROPERATION::UTF_82ASCII(string(pResult[nIndex])).c_str()) == 0) {
					flag = true;
					break;
				}
			}
			if (flag == false) {
				bIsSync = false;
				strcpy(tempSyncData.user_id, pUserFingerInfo[i].user_id);
				strcpy(tempSyncData.finger_name, STROPERATION::UTF_82ASCII(string(pResult[nIndex])).c_str());
				memset(chFingerBuf, 0, FINGER_PIC_SIZE);
				STROPERATION::char_array_2_binary_str(chFingerBuf, FINGER_PIC_SIZE, pResult[nIndex + 1], FINGER_SAVE_SIZE - 1, 1);
				memcpy(tempSyncData.fdata, chFingerBuf, FINGER_PIC_SIZE);
				tempSyncData.sync_flag = 1;
				pLstSyncData->push_back(tempSyncData);
			}
			nIndex = nIndex + nCol;
		}


		for (int jj = 0; jj < pUserFingerInfo[i].fnum; jj++) {
			nIndex = nCol;
			// 遍历该用户id查询到的数据库中指静脉信息
			flag = false;
			for (int kk = 0; kk < nRow; kk++) {
				if (strcmp((char*)pUserFingerInfo[i].fdata[jj].finger_name, STROPERATION::UTF_82ASCII(string(pResult[nIndex])).c_str()) == 0) {
					flag = true;
					break;
				}
				nIndex = nIndex + nCol;
			}
			if (flag == false) {
				bIsSync = false;
				strcpy(tempSyncData.user_id, pUserFingerInfo[i].user_id);
				strcpy(tempSyncData.finger_name, (char*)pUserFingerInfo[i].fdata[jj].finger_name);
				tempSyncData.sync_flag = 0;
				pLstSyncData->push_back(tempSyncData);
			}
		}
	}

	// 遍历 DB 中用户
	// 判断是否存在  db中有这个用户，而设备中没有的情况
	// 一般这种情况不会发生，因为删除设备中的用户都需要通过管理软件
	user_sel_ret* usersInDb;
	selUsersOfCurDev(&usersInDb, &iUserNumDb);
	for (int iii = 0; iii < iUserNumDb; iii++) {
		flag = true;
		for (int jjj = 0; jjj < iUserFingerInfoNum; jjj++) {
			if (strcmp(usersInDb[iii].id, pUserFingerInfo[jjj].user_id) == 0) {
				flag = false;
			}
		}
		// 该用户 DB中存在，但设备中不存在
		if (flag) {
			sql = "select name,finger from finger where user_id ='";
			sql.append(usersInDb[iii].id);
			sql.append("';");
			if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
				sqlite3_free(errmsg);
				return false;
			}
			nIndex = nCol;

			for (int kkk = 0; kkk < nRow; kkk++) {
				//bIsSync = false;
				strcpy(tempSyncData.user_id, usersInDb[iii].id);
				strcpy(tempSyncData.finger_name, STROPERATION::UTF_82ASCII(string(pResult[nIndex])).c_str());
				memset(chFingerBuf, 0, FINGER_PIC_SIZE);
				STROPERATION::char_array_2_binary_str(chFingerBuf, FINGER_PIC_SIZE, pResult[nIndex + 1], FINGER_SAVE_SIZE - 1, 1);
				memcpy(tempSyncData.fdata, chFingerBuf, FINGER_PIC_SIZE);
				tempSyncData.sync_flag = 1;
				pLstSyncData->push_back(tempSyncData);
			}
		}
	}

	delete[] chFingerBuf;
	chFingerBuf = NULL;
	return bIsSync;
}


/*
*  author: sonne
*  date  : 2018-09-30
*  note  : know how many fingers of current dev
**/
int getNumOfFingersCurDev() {
	using namespace std;
	string sql = "select count(*) from finger where dev_id = '";
	sql.append(g_sn);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return RET_ERROR;
	}
	int nIndex = nCol;
	return atoi(pResult[nIndex]);
}



/*
*  author: sonne
*  date  : 2018-10-10
*  note  : get name of user by id
*/
std::string getNameOfUserId(std::string user_id) {
	using namespace std;
	string sql = "select username from user where id = '";
	sql.append(user_id);
	sql.append("';");
	char* errmsg;
	char** pResult;
	int nRow, nCol;
	if (sqlite3_get_table(pDB, sql.c_str(), &pResult, &nRow, &nCol, &errmsg) != SQLITE_OK) {
		cout << "sqlite : select data failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return STROPERATION::UTF_82ASCII(string(pResult[nCol]));
}


/*
*  author: sonne
*  date  : 2018-10-17
*  note  : edit cert
*/
bool editCert(std::string id, std::string name, std::string date, std::string type) {
	using namespace std;
	string sql = "update cert set name = '";
	sql.append(STROPERATION::ASCII2UTF_8(name));
	sql.append("', date = '");
	sql.append(date);
	sql.append("', type = '");
	sql.append(type);
	sql.append("' where content = '");
	sql.append(id);
	sql.append("';");
	char* errmsg;
	if (sqlite3_exec(pDB, sql.c_str(), NULL, NULL, &errmsg) != SQLITE_OK) {
		cout << "sqlite : insert admin failed. error : " << errmsg << endl;
		sqlite3_free(errmsg);
		return false;
	}
	return true;
}