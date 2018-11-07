#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <io.h>  

#include "my_including.h"
#include "direct.h"
#include "io.h"


#pragma once

namespace FILE_OPERATION
{
	using namespace std;

	void init_cers_path();
	
	/*
	 *   sonne
	 *   在指定文件末尾写入新的一行
	 *   2017-09-20
	 */
	void write_next_line( char *path, const char *content);



	/**
	*   作者：sonne
	*   日期：2017-05-18
	*   功能：根据用户名获取对应证书路径
	**/
	void get_file_path_by_usrname(char *path, const char* usrname, int usr_type);

	/**
	*   作者：LYF
	*   日期：2017-05-16
	*   功能：根据用户名获取对应证书路径
	**/
	void writeDataHex(unsigned char * my_array,int length,char *string);

	/**
	* 作      者:	sonne
	* 函  数  名:   readTxt
	* 功      能:   文件逐字符读取
	*/
	char* readTxt(string file);

	/**
	* 作      者:	sonne
	* 函  数  名:   Remove_data_hex
	* 功      能:   删除文件本身
	*/
	bool Remove_data_hex(char* usrname, int usr_type);

	/**
	* 作      者:	LYF
	* 函  数  名:   read_data_hex功能和readTxt相同，不过参数有区别前者是路径字符串，后者可以是指针
	* 功      能:   文件逐字符读取
	*/
	void read_data_hex(unsigned char *buf,int length,char *string);


	/*
	** 作者：sonne
	** 日期：2017-06-12
	** 说明：读取制定目录下所有文件路径和文件名
	 */
	void getFileNamesAndPaths32Bit(string path, vector<string>& files, vector<string>& file_name);


	/*
	** 作者：sonne
	** 日期：2017-06-12
	** 说明：读取制定目录下所有文件路径和文件名
	*/
	void getFileNamesAndPaths(string path, vector<string>& files, vector<string>& file_name);

	void read_data_hex(char *buf,int length,const char *string);
}