#pragma once  

#include <windows.h>

/**
 *    作者：sonne
 *    日期：2017.07-27
 *    备注：分页信息类
 */
class c_page_info {

private:
	/**每页显示数量*/
	int every_page;
	
	/**总记录数*/
	long total_count;
	
	/**总页数*/
	long total_page;
	
	/**当前页*/
	int current_page;
	
	/**起始点*/
	int begin_index;
	
	/**是否有上一页*/
	bool has_pre_page;
	
	/**是否有下一页*/
	bool has_next_page;

public:
	c_page_info(int every_page, long total, long total_page, int current_page,
			int begin_index, bool has_pre_page, bool has_next_page);

	c_page_info(int current_page, int every_page);

	c_page_info();

	int get_every_page();

	void set_every_page(int every_page);

	long get_total_count();

	void set_total_count(long total_count);

	long get_total_page();

	void set_total_page(long total_page);

	int get_current_page();

	void set_current_page(int current_page);

    int get_begin_index();

	void set_begin_index(int begin_index);

	bool is_has_pre_page();

	void set_has_pre_page(bool has_pre_page);

	bool is_has_next_page();

	void set_has_next_page(bool has_next_page);

};