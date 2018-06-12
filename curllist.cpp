#include "curllist.h"

#include <algorithm>
namespace libcurlpp{
	CurlList::CurlList(const std::list<std::string> list) :headers(NULL)
	{
		for each (const std::string& var in list)
		{
			Append(var);
		}
	}

	CurlList::~CurlList(){
		Clear();
	}


	/*
	Description:
	在list中添加内容
	*/
	void CurlList::Append(const std::string& str){
		headers = curl_slist_append(headers, str.c_str());
	}


	/*
	获取curl_slist
	*/
	curl_slist* CurlList::GetSlist(){
		return headers;
	}


	/*
	curl_slist_free_all释放curl_slist资源
	*/
	void CurlList::Clear(){
		if (headers){
			curl_slist_free_all(headers);
		}
	}
}
