#pragma once

#include<time.h>
#include "str_utils.h"
#include "sqlite_utils.h"

/**
 *     sonne
 *     2017-07-21
 *     写日志
 */
namespace MYLOG {

	using namespace std;

	/**
	 *     sonne
	 *     2017-07-21
	 *     写日志（输入内容、管理员、类型）
	 *     日志内容（管理员、内容、时间、日志类型）
	 */
	void write_log(char *ch_content, int type, char *manager_name) ;
}