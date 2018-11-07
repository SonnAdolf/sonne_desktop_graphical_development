#include "file_utils.h"

#pragma once

namespace FILE_OPERATION
{
	using namespace std;

	void init_cers_path() {
		// 证书路径
		//GetModuleFileName(NULL,(LPSTR)g_cers_path,sizeof(g_cers_path));
		getcwd(g_cers_path, 256); 
		strcat(g_cers_path,"\\cers");

		getcwd(g_manager_cers_path, 256); 
		strcat(g_manager_cers_path, "\\manager_cers"); 

		// 判断目录是否存在，创建
		fstream _file;
		_file.open(g_cers_path,ios::in);
		if(!_file) {
			_mkdir(g_cers_path);
		} 
		_file.open(g_manager_cers_path,ios::in);
		if(!_file) {
			_mkdir(g_manager_cers_path);
		} 
	}

	
	/*
	 *   sonne
	 *   在指定文件末尾写入新的一行
	 *   2017-09-20
	 */
	void write_next_line( char *path, const char *content) {
		ofstream file_out(path, ios::app);
        file_out << content<< "\n";
		file_out.close();
	}



	/**
	*   作者：sonne
	*   日期：2017-05-18
	*   功能：根据用户名获取对应证书路径
	**/
	void get_file_path_by_usrname(char *path, const char* usrname, int usr_type) {
		//char FilePath[500] = {0};
		if (usr_type == USER_TYPE_OF_MANAGE) {
			strcpy(path,g_manager_cers_path);
			strcat(path, "\\");
			strcat(path, usrname);
			strcat(path, ".dat");
			//MessageBox(NULL,FilePath,NULL,NULL);
			//MessageBox(NULL,FilePath,NULL,NULL);
		} else {
			strcpy(path,g_cers_path);
			strcat(path, "\\");
			strcat(path, usrname);
			strcat(path, ".dat");
		}
	}

	/**
	*   作者：LYF
	*   日期：2017-05-16
	**/
	void writeDataHex(unsigned char * my_array,int length,char *string)
	{
		int i = 0;
		FILE *fp;
		fp = fopen(string,"wb+");
		if(NULL == fp)
		{
			printf("file open Fail!\n");
		}
		while(i < length)
		{        
			fwrite(&my_array[i],sizeof(unsigned char ),1,fp);
			i++;
		}
		fclose(fp);
	}

	/**
	* 作      者:	sonne
	* 函  数  名:   readTxt
	* 功      能:   文件逐字符读取
	*/
	char* readTxt(string file)
	{
		char ch_arr[6200] = {0};

		int i = 0;
		if (!file.empty())
		{
			ifstream infile; 
			infile.open(file.data());   //将文件流对象与文件连接起来 
			assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
			char c;
			infile >> noskipws;
			while (!infile.eof())
			{
				infile>>c;
				ch_arr[i] = c;
				i++;
			}
			ch_arr[i-1] = '\0';			//由于infile.eof()是个后知后觉的函数，会多读一位，所以i-1未置0
			infile.close();             //关闭文件输入流 
		}
		return ch_arr;
	}

	/**
	* 作      者:	sonne
	* 函  数  名:   Remove_data_hex
	* 功      能:   删除文件本身
	*/
	bool Remove_data_hex(char* usrname, int usr_type) {
		char path[500] = {0};
	    get_file_path_by_usrname(path, usrname, usr_type);
		//char PathName[500] = {0};
		//memcpy(PathName,path,500);
		//MessageBox(NULL,PathName,NULL,NULL);
		if(remove(path) != 0)
			return false;
		return true;
	}

	/**
	* 作      者:	LYF
	* 函  数  名:   read_data_hex功能和readTxt相同，不过参数有区别前者是路径字符串，后者可以是指针
	* 功      能:   文件逐字符读取
	*/
	void read_data_hex(unsigned char *buf,int length,char *string)
	{
		int i = 0;
		int re;
		FILE *fp;
		fp = fopen(string,"rb");
		if(NULL == fp)
		{
			printf("file open Fail!\n");
		}
		fread(buf,sizeof(unsigned char),length,fp);
		fclose(fp);
	}


	/*
	** 作者：sonne
	** 日期：2017-06-12
	** 说明：读取制定目录下所有文件路径和文件名
	 */
	void getFileNamesAndPaths32Bit(string path, vector<string>& files, vector<string>& file_name)
	{
		//文件句柄  
		 long   hFile = 0;
		  //文件信息，声明一个存储文件信息的结构体  
		struct _finddata_t fileinfo;
		//字符串，存放路径
	    string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//若查找成功，则进入
		{
			do
			{
				//如果是目录,迭代之
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						getFileNamesAndPaths32Bit(p.assign(path).append("\\").append(fileinfo.name), files, file_name);
				}
				//如果不是,加入列表  
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					file_name.push_back(fileinfo.name);
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			//_findclose函数结束查找
			_findclose(hFile);
		}
	}


	/*
	** 作者：sonne
	** 日期：2017-06-12
	** 说明：读取制定目录下所有文件路径和文件名
	*/
	void getFileNamesAndPaths(string path, vector<string>& files, vector<string>& file_name)
	{
		//文件句柄  
		__int64   hFile = 0;
		//文件信息，声明一个存储文件信息的结构体  
		//struct _finddata_t fileinfo;
		struct __finddata64_t fileinfo;
		//字符串，存放路径
		string p;
		if ((hFile = _findfirst64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)//若查找成功，则进入
		{
			do
			{
				//如果是目录,迭代之
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					    getFileNamesAndPaths(p.assign(path).append("\\").append(fileinfo.name), files, file_name);
				}
				//如果不是,加入列表  
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					file_name.push_back(fileinfo.name);
				}
			} while (_findnext64(hFile, &fileinfo) == 0);
			//_findclose函数结束查找
			_findclose(hFile);
		}
	}

	void read_data_hex(char *buf,int length,const char *string)
	{
		int i = 0;
		int re;
		FILE *fp;
		fp = fopen(string,"rb");
		if(NULL == fp)
		{
			printf("file open Fail!\n");
		}
		fread(buf,sizeof(unsigned char),length,fp);
		fclose(fp);
	}
}