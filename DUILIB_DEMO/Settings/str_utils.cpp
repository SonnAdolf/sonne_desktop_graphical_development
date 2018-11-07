#pragma once

#include "str_utils.h"

/**
* 字符串相关操作
*/
namespace STROPERATION {

	void writeDataHex(unsigned char * my_array, int length, char *string) {
		int i = 0;
		FILE *fp;
		fp = fopen(string, "wb+");
		if (NULL == fp) {
			printf("file open Fail!\n");
		}

		while (i < length) {
			fwrite(&my_array[i], sizeof(unsigned char), 1, fp);
			i++;
		}

		fclose(fp);
	}


	bool is_num(char c) {
		return (c>='0' && c<='9');
	}


	bool is_chararr_nums(char *c) {
		while(*c != '\0') {
			if (!is_num(*c))
				return false;
			c++;
		}
		return true;
	}


	/**
	* 作      者:	sonne
	* 功      能:  wchar_t to string 
	*/
	void Wchar_tToString(std::string& szDst, const wchar_t *wchar)  { 
		const wchar_t * wText = wchar;  
		DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wText,-1,NULL,0,NULL,FALSE); 
		char *psText;
		psText = new char[dwNum];  
		WideCharToMultiByte (CP_OEMCP,NULL,wText,-1,psText,dwNum,NULL,FALSE);  
		szDst = psText; 
		delete []psText;  
	}  

	/**
	* 作     者：sonne
	* 功     能：字符串指针转化为字符串数组
	*/
	void CharPointerToCharArr(char* char_p, char char_arr[]) {
		int i = 0;
		while (*char_p != '\0') {
			char_arr[i] = *char_p;
			i++;
			char_p++;
		}
		char_arr[i] = '\0';
	}

	/**
	* 作     者：sonne
	* 功     能：wchar字符串转化为char字符串
	*/
	char* WcharToChar(const wchar_t * wChar) {
		int len= WideCharToMultiByte(CP_ACP,0,wChar,wcslen(wChar),NULL,0,NULL,NULL)+1; 
		size_t converted = 0;
		char *CStr;
		CStr=(char*)malloc(len*sizeof(char));
		memset(CStr,0,len);
		wcstombs_s(&converted, CStr, len, wChar, _TRUNCATE);
		return CStr;
	}


	/**
	* 作     者：sonne
	* 功     能：char字符串转化为wchar字符串
	*/
	void charToWchar(const char *s, WCHAR* wch){
		int w_nlen=MultiByteToWideChar(CP_ACP,0,s,-1,NULL,0);
		//WCHAR *ret;
		//ret=(WCHAR*) malloc(sizeof(WCHAR)*w_nlen);
		//memset(ret,0,sizeof(ret));
		MultiByteToWideChar(CP_ACP,0,s,-1, wch,w_nlen);
		return;
	}

	//UTF-8转Unicode 
	std::wstring Utf82Unicode(const std::string& utf8string)
	{
		int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
		if (widesize == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (widesize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<wchar_t> resultstring(widesize);
		int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
		if (convresult != widesize)
		{
			throw std::exception("La falla!");
		}
		return std::wstring(&resultstring[0]);
	}


	//unicode 转为 ascii 
	std::string WideByte2Acsi(std::wstring& wstrcode)
	{
		int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
		if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (asciisize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<char> resultstring(asciisize);
		int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
		if (convresult != asciisize)
		{
			throw std::exception("La falla!");
		}
		return std::string(&resultstring[0]);
	}



	//utf-8 转 ascii 
	std::string UTF_82ASCII(std::string& strUtf8Code)
	{
		using namespace std;
		string strRet = "";
		//先把 utf8 转为 unicode 
		wstring wstr = Utf82Unicode(strUtf8Code);
		//最后把 unicode 转为 ascii 
		strRet = WideByte2Acsi(wstr);
		return strRet;
	}



	//ascii 转 Unicode 
	std::wstring Acsi2WideByte(std::string& strascii)
	{
		using namespace std;
		int widesize = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, NULL, 0);
		if (widesize == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (widesize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<wchar_t> resultstring(widesize);
		int convresult = MultiByteToWideChar(CP_ACP, 0, (char*)strascii.c_str(), -1, &resultstring[0], widesize);
		if (convresult != widesize)
		{
			throw std::exception("La falla!");
		}
		return std::wstring(&resultstring[0]);
	}


	//Unicode 转 Utf8 
	std::string Unicode2Utf8(const std::wstring& widestring)
	{
		using namespace std;
		int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
		if (utf8size == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<char> resultstring(utf8size);
		int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
		if (convresult != utf8size)
		{
			throw std::exception("La falla!");
		}
		return std::string(&resultstring[0]);
	}


	//ascii 转 Utf8 
	std::string ASCII2UTF_8(std::string& strAsciiCode) {
		using namespace std;
		string strRet("");
		//先把 ascii 转为 unicode 
		wstring wstr = Acsi2WideByte(strAsciiCode);
		//最后把 unicode 转为 utf8 
		strRet = Unicode2Utf8(wstr);
		return strRet;
	}

	/**
	* 作     者：sonne
	* 日     期：2017-05-17
	* 功     能：判断输入字符串是否包含非法字符
	*/
	bool isStrIllegal(const wchar_t * wch) {
		while (*wch != '\0') {
			if (*wch == ';' || *wch == '\'' || *wch == '\'\'' || *wch == '&' || *wch == '<' || *wch == '>' || *wch == '-' || *wch == '=' || *wch == '%') {
				return true;
			}
			wch++;
		}
		return false;
	}


	bool isStrIllegal2(const char * ch) {
		while (*ch != '\0') {
			if (*ch == ';' || *ch == '\'' || *ch == '\'\'' || *ch == '&' || *ch == '<' || *ch == '>' || *ch == '-' || *ch == '=' || *ch == '%') {
				return true;
			}
			ch++;
		}
		return false;
	}


	/**
	* 作     者：sonne
	* 日     期：2017-07-27
	* 功     能：字符串数组相连
	*/
	void link(char *s, const char *t)  {  
		while (*s != '\0')  
			s++;  
		while (*t != '\0')  
			*s++ = *t++;  
		*s = '\0';  
	} 


	bool check_is_charpointer_null(const char* ch) {
		if (ch == NULL)
			return true;
		if (*ch == '\0')
			return true;
		return false;
	}


	/*
	*  作者：sonne
	*  日期：2017-08-30
	*  备注：日志打印过程如果用户名过长会对界面造成损坏
	*        用户名长度超过10则*限制
	*/
	void str_len_limit(char *dst, const char *src) {
		int len = strlen(src);
		if (len > 10)
			len = 10;
		memcpy(dst, src, len);
		if (len = 10) {
			*(dst + 8) = '*';
			*(dst + 9) = '\0';
		}
	}

	/**
	*   sonne 2017-11-01
	*   get string of date,format xxxx-xx-xx
	*/
	void getDateString(char *str_date) {
		//char buf[BUFSIZ];
		time_t t = time(NULL);
		struct tm* now = localtime(&t);
		strftime(str_date,BUFSIZ,"%Y-%m-%d",now);
		return;
	}


	void get_time_string(char *str_time) {
		//char buf[BUFSIZ];
		time_t t = time(NULL);
		struct tm* now = localtime(&t);

		strftime(str_time, sizeof(str_time), "%Y-%m-%d %H:%M:%S", now);
		return;
	}


	char* getDateTime()
	{
		static char nowtime[20];
		time_t rawtime;
		struct tm* ltime;
		time(&rawtime);
		ltime = localtime(&rawtime);
		strftime(nowtime, 20, "%Y-%m-%d %H:%M:%S", ltime);
		return nowtime;
	}

	int write_log(const char* path, const char* content) {
		FILE *fpWrite = fopen(path, "a+");
		if (fpWrite == NULL)
			return 0;
		fprintf(fpWrite, "%s----%s %c", content, getDateTime(), '\n');
		fclose(fpWrite);
	}



	/**
	*    设置一个字符第n位bit值
	*    2018-02-06
	*/
	int bit_set(unsigned char *p_data, unsigned char position, int flag)   {  
		int i = 0;  
		assert(p_data);  
		if (position > 8 || position < 1 || (flag != 0 && flag != 1))    
			return -1;  
		if (flag != (*p_data >> (position - 1) & 1))  
			*p_data |= 1 << (position - 1);   
		return 0;
	} 


	/**
	*    设置一个dword第n位bit值
	*    2018-05-14
	*/
	int dword_bit_set(DWORD *p_data, unsigned char position, int flag) {
		int i = 0;
		assert(p_data);
		if (position > 32 || position < 1 || (flag != 0 && flag != 1))
			return -1;
		if (flag != (*p_data >> (position - 1) & 1))
			*p_data |= 1 << (position - 1);
		return 0;
	}


	int read_bit(DWORD c, int pos)
	{
		char b_mask = 0x00000001;
		b_mask = b_mask <<pos;
		if ((c&b_mask) == b_mask) //字符c和b_mask做位运算如果还是等于b_mask,说明该位为1 
			return 1;
		else
			return 0;
	}

	void HexToStr(unsigned char *pbDest, unsigned char *pbSrc, int nLen) {
		unsigned char ddl, ddh;
		int i;

		for (i = 0; i < nLen; i++) {
			ddh = 48 + pbSrc[i] / 16;
			ddl = 48 + pbSrc[i] % 16;
			if (ddh > 57) ddh = ddh + 7;
			if (ddl > 57) ddl = ddl + 7;
			pbDest[i * 2] = ddh;
			pbDest[i * 2 + 1] = ddl;
		}

		pbDest[nLen * 2] = '\0';
	}


	void HexToStr2(unsigned char *pbDest, BYTE *pbSrc, int nLen) {
		unsigned char ddl, ddh;
		int i;

		for (i = 0; i < nLen; i++) {
			ddh = 48 + pbSrc[i] / 16;
			ddl = 48 + pbSrc[i] % 16;
			if (ddh > 57) ddh = ddh + 7;
			if (ddl > 57) ddl = ddl + 7;
			pbDest[i * 2] = ddh;
			pbDest[i * 2 + 1] = ddl;
		}

		pbDest[nLen * 2] = '\0';
	}


	void StrToHex(unsigned char *pbDest, unsigned char *pbSrc, int nLen) {
		unsigned char h1, h2;
		unsigned char s1, s2;
		int i;

		for (i = 0; i<nLen; i++)
		{
			h1 = pbSrc[2 * i];
			h2 = pbSrc[2 * i + 1];

			s1 = toupper(h1) - 0x30;
			if (s1 > 9)
				s1 -= 7;

			s2 = toupper(h2) - 0x30;
			if (s2 > 9)
				s2 -= 7;

			pbDest[i] = s1 * 16 + s2;
		}
	}


	void StrToHex2(BYTE *pbDest, unsigned char  *pbSrc, int nLen) {
		BYTE h1, h2;
		BYTE s1, s2;
		int i;

		for (i = 0; i<nLen; i++)
		{
			h1 = pbSrc[2 * i];
			h2 = pbSrc[2 * i + 1];

			s1 = toupper(h1) - 0x30;
			if (s1 > 9)
				s1 -= 7;

			s2 = toupper(h2) - 0x30;
			if (s2 > 9)
				s2 -= 7;

			pbDest[i] = s1 * 16 + s2;
		}
	}



	/**
	*     字符数组 与 二进制字符串 相互转化
	*     2018-02-06
	*/
	int char_array_2_binary_str(const char ch_buf[],int ch_len,char binary_char_buf[],int binary_char_len,int type){
		if(type!=0&&type!=1)
			return -1;
		//字节流转二进制字符流
		if(type==0){
			if(binary_char_len < 8*ch_len)
				return -1;
			int char_buf_index=0;
			for(int i=0;i<ch_len;++i){
				for(int j=7;j>=0;--j){
					if(ch_buf[i]>>j&0x1)
						binary_char_buf[char_buf_index++]='1';
					else
						binary_char_buf[char_buf_index++]='0';
				}
			}
			return 0;
		}
		if (type == 1) {
			if(8*ch_len < binary_char_len)
				return -1;
			char tmp_str[9]="";
			int ret_buf_index=0;
			for(int i=0;i<binary_char_len;i=i+8){
				strncpy_s(tmp_str, binary_char_buf+i, 8);
				for(int j=0; j<8; ++j){ 
					if (tmp_str[j] == '0')
						bit_set((unsigned char *)ch_buf+ret_buf_index, 8-j, 0);
					if (tmp_str[j] == '1')
						bit_set((unsigned char *)ch_buf+ret_buf_index, 8-j, 1);
				}
				ret_buf_index++;
			}
			return 0;
		}
		return 0;
	}

	// wchar_t to string  
	void wchar_tto_str(std::string& szDst, const wchar_t *wchar)  {  
		const wchar_t * wText = wchar;  
		DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wText,-1,NULL,0,NULL,FALSE);// WideCharToMultiByte的运用  
		char *psText; // psText为char*的临时数组，作为赋值给std::string的中间变量  
		psText = new char[dwNum];  
		WideCharToMultiByte (CP_OEMCP,NULL,wText,-1,psText,dwNum,NULL,FALSE);// WideCharToMultiByte的再次运用  
		szDst = psText;// std::string赋值  
		delete []psText;// psText的清除  
	}  

	// string to wstring  
	void string_to_wstring(std::wstring& szDst, std::string str)  {  
		std::string temp = str;  
		int len=MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL,0);   
		wchar_t * wszUtf8 = new wchar_t[len+1];   
		memset(wszUtf8, 0, len * 2 + 2);   
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);  
		szDst = wszUtf8;  
		std::wstring r = wszUtf8;  
		delete[] wszUtf8;  
	} 


	BOOL LPCTSR2GUID(LPCTSTR szGUID, GUID &Guid) {
		memset(&Guid, 0, sizeof(Guid));
		int nRet =
			sscanf_s(szGUID,
				_T("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"),
				&Guid.Data1,
				&Guid.Data2,
				&Guid.Data3,
				&Guid.Data4[0], &Guid.Data4[1],
				&Guid.Data4[2], &Guid.Data4[3], &Guid.Data4[4], &Guid.Data4[5], &Guid.Data4[6], &Guid.Data4[7]
			);
		return (nRet == 11) ? TRUE : FALSE;
	}


	LPCTSTR GUID2LPCTS(GUID Guid) {
		static TCHAR szBuf[65] = { 0 };
		_snprintf_s(szBuf, 64, _T("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"),
			Guid.Data1,
			Guid.Data2,
			Guid.Data3,
			Guid.Data4[0], Guid.Data4[1],
			Guid.Data4[2], Guid.Data4[3], Guid.Data4[4], Guid.Data4[5], Guid.Data4[6], Guid.Data4[7]
		);
		return szBuf;
	}

#
	BOOL string_to_date(LPCTSTR lpszValue, SYSTEMTIME &time) {
		if (!lpszValue) {
			return FALSE;
		}

		int         nYear = 0;
		int         nMonth = 0;
		int         nDay = 0;
		int         nHour = 0;
		int         nSecond = 0;
		int         nMinute = 0;
		//CString  str = lpszValue;

		sscanf_s(lpszValue, _T("%d-%d-%d %d:%d:%d"), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

		if (nMonth == 0 || nDay == 0)
		{
			sscanf_s(lpszValue, _T("%d/%d/%d %d:%d:%d"), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
		}

		time.wYear = nYear;
		time.wMonth = nMonth;
		time.wDay = nDay;
		time.wHour = nHour;
		time.wSecond = nSecond;
		time.wMinute = nMinute;

		return TRUE;
	}


	int dateComparing(const char* date1, const char* date2) {
		int year1, month1, day1;
		int year2, month2, day2;
		sscanf(date1, "%d-%d-%d", &year1, &month1, &day1);
		sscanf(date2, "%d-%d-%d", &year2, &month2, &day2);
		int tm1 = year1 * 10000 + month1 * 100 + day1;
		int tm2 = year2 * 10000 + month2 * 100 + day2;
		if (tm1 != tm2) return (tm1>tm2) ? 1 : 0;//如果相等，大返回1，小返回0
		return 2;
	}


	int timeCompare(const char* time1, const char* time2) {
		int year1, month1, day1, hour1, min1, sec1;
		int year2, month2, day2, hour2, min2, sec2;
		sscanf(time1, "%d-%d-%d %d:%d:%d", &year1, &month1, &day1, &hour1, &min1, &sec1);
		sscanf(time2, "%d-%d-%d %d:%d:%d", &year2, &month2, &day2, &hour2, &min2, &sec2);
		int tm1 = year1 * 10000 + month1 * 100 + day1;
		int tm2 = year2 * 10000 + month2 * 100 + day2;
		if (tm1 != tm2) return (tm1>tm2) ? 1 : 0;//如果相等，大返回1，小返回0
		tm1 = hour1 * 3600 + min1 * 60 + sec1;
		tm2 = hour2 * 3600 + min2 * 60 + sec2;//将时分秒转换为秒数
		if (tm1 != tm2) return (tm1>tm2) ? 1 : 0;//如果相等，大返回1，小返回0
		return 2;//到这里必然是相等了
	}


	/**
	*   作者：sonne
	*   日期：2018-03
	*   备注：获取guid
	*/
	int get_guid(std::string& ch_guid){
		char buffer[64] = { 0 };
		GUID guid;

		if (CoCreateGuid(&guid))
		{
			fprintf(stderr, "create guid error\n");
			return -1;
		}
		_snprintf(buffer, sizeof(buffer),
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		ch_guid = buffer;
		return 0;
	}


	/**
	* @brief 	Crc Value Compute,Poly is Given As Defined
	* @param
	* @return
	* @note
	*/
	WORD CrcCompute(BYTE *src, int len) {
		//	#define CRC_DFE_POLY    0x8005
		WORD crc;
		BYTE uc;
		for (int j = 0; j < len; j++) {
			uc = *(src + j);
			for (int i = 0; i < 8; i++) {
				crc = ((uc ^ (BYTE)(crc >> 8)) & 0x80) ? ((crc << 1) ^ 0x8005) : (crc << 1);
				uc <<= 1;
			}
		}
		return crc;
	}

}
