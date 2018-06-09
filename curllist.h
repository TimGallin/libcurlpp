#pragma once

#ifndef LIBCURLPP_CURL_SLIST
#define LIBCURLPP_CURL_SLIST

#include "include\curl.h"
#include <list>

namespace libcurlpp{
	/*
	Description:
	用于curl中需要设置list的操作
	在Append函数中将通过curl_slist_append将str添加到内部curl_slist中
	虚构函数中将调用curl_slist_free_all释放list资源
	*/
	class CurlList
	{
	public:
		CurlList();
		~CurlList();

		/*
		Description:
		在list中添加内容
		*/
		void Append(const std::string& str);

		/*
		获取curl_slist
		*/
		curl_slist* GetSlist();

	private:
		/*
		curl_slist_free_all释放curl_slist资源
		*/
		void Clear();

		struct curl_slist *headers;
	};
}





#endif