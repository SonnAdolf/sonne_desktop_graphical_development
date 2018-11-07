#pragma once  

#include <windows.h>

#include "page_info.h"

/**
 *    作者：sonne
 *    日期：2017.07-27
 *    备注：分页工具类
 */
class c_page_utils  {
private:
public:

	/**
	 * 根据everyPage，total，currentPage创建分页信息对象
	 */
    static c_page_info create_page(int every_page,long total,int current_page);

	/**
	 * 翻页
	 */
	static void get_next_page(c_page_info *page_info);

	/**
	 * 上一页
	 */
	static void get_pre_page(c_page_info *page_info);


	static void get_first_page(c_page_info *page_info);


	static void get_last_page(c_page_info *page_info);


	/**
	 * 根据everyPage，total，currentPage重新整理分页信息对象
	 */
    static void set_page_info(c_page_info *page_info,int every_page,long total,int current_page);
    

    /**
     * 获得每页显示记录数
     */
    static int get_every_page(int every_page);
    

    /**
     * 获得当前页
     */
    static int get_current_page(int current_page);

    
    /**
     * 获得总页数
     */
    static long get_total_page(int every_page,long total);
    

    /**
     * 获得起始位置
     */
    static int get_begin_index(int every_page,int current_page);

    
    /**
     * 获得是否有上一页
     */
    static bool get_has_pre_page(int current_page);


    /**
     * 获得是否有上一页
     */
    static bool get_has_next_page(long total_page, int current_page);
};