
#include "page_info.h"

c_page_info::c_page_info(int every_page, long total, long total_page, int current_page,
				int begin_index, bool has_pre_page, bool has_next_page) {
	this->every_page = every_page;
	this->total_count = total;
	this->total_page = total_page;
	this->current_page = current_page;
	this->begin_index = begin_index;
	this->has_pre_page = has_pre_page;
	this->has_next_page = has_next_page;
}

c_page_info::c_page_info(int current_page, int every_page) {
	this->every_page = every_page;
}

c_page_info::c_page_info() {
}

int c_page_info::get_every_page() {
	return every_page;
}

void c_page_info::set_every_page(int every_page) {
	this->every_page = every_page;
}

long c_page_info::get_total_count() {
	return this->total_count;
}

void c_page_info::set_total_count(long total_count) {
	this->total_count = total_count;
}

long c_page_info::get_total_page() {
	return total_page;
}

void c_page_info::set_total_page(long total_page) {
	this->total_page = total_page;
}

int c_page_info::get_current_page() {
	return current_page;
}

void c_page_info::set_current_page(int current_page) {
	this->current_page = current_page;
}

int c_page_info::get_begin_index() {
	return begin_index;
}

void c_page_info::set_begin_index(int begin_index) {
	this->begin_index = begin_index;
}

bool c_page_info::is_has_pre_page() {
	return this->has_pre_page;
}

void c_page_info::set_has_pre_page(bool has_pre_page) {
	this->has_pre_page = has_pre_page;
}

bool c_page_info::is_has_next_page() {
	return has_next_page;
}

void c_page_info::set_has_next_page(bool has_next_page) {
	this->has_next_page = has_next_page;
}

