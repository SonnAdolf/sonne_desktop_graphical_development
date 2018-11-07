#pragma once


#include "my_log.h"

/**
 *     sonne
 *     2017-07-21
 *     写日志
 */
namespace MYLOG {

	/**
	 *     sonne
	 *     2017-07-21
	 *     写日志（输入内容、管理员、类型）
	 *     日志内容（管理员、内容、时间、日志类型）
	 */
	void write_log(char *ch_content, int type, char *manager_name) {
		char limited_manager_name[10];
		time_t t = time(0);
		char ch_time[64];
		strftime(ch_time, sizeof(ch_time), "%Y-%m-%d %H-%M-%S", localtime(&t));
		STROPERATION::str_len_limit(limited_manager_name, manager_name);
		char str_date[15];
		STROPERATION::getDateString(str_date);
		//MYSQL_INTERFACES::insert_log(ch_content, type, limited_manager_name, ch_time, str_date);
		insertLog(ch_content, type, (char*)STROPERATION::ASCII2UTF_8(string(limited_manager_name)).c_str(), ch_time, str_date);
		//insertLog(ch_content, type, limited_manager_name, ch_time, str_date);
	}
}