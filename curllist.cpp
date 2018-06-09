#include "curllist.h"

namespace libcurlpp{
	CurlList::CurlList() :headers(NULL)
	{
	}

	CurlList::~CurlList(){
		Clear();
	}


	/*
	Description:
	��list���������
	*/
	void CurlList::Append(const std::string& str){
		headers = curl_slist_append(headers, str.c_str());
	}


	/*
	��ȡcurl_slist
	*/
	curl_slist* CurlList::GetSlist(){
		return headers;
	}


	/*
	curl_slist_free_all�ͷ�curl_slist��Դ
	*/
	void CurlList::Clear(){
		if (headers){
			curl_slist_free_all(headers);
		}
	}
}
