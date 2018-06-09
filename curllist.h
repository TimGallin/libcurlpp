#pragma once

#ifndef LIBCURLPP_CURL_SLIST
#define LIBCURLPP_CURL_SLIST

#include "include\curl.h"
#include <list>

namespace libcurlpp{
	/*
	Description:
	����curl����Ҫ����list�Ĳ���
	��Append�����н�ͨ��curl_slist_append��str��ӵ��ڲ�curl_slist��
	�鹹�����н�����curl_slist_free_all�ͷ�list��Դ
	*/
	class CurlList
	{
	public:
		CurlList();
		~CurlList();

		/*
		Description:
		��list���������
		*/
		void Append(const std::string& str);

		/*
		��ȡcurl_slist
		*/
		curl_slist* GetSlist();

	private:
		/*
		curl_slist_free_all�ͷ�curl_slist��Դ
		*/
		void Clear();

		struct curl_slist *headers;
	};
}





#endif