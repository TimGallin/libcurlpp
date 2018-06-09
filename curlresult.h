#pragma once

#ifndef LIBCURLPP_CURL_CURLRESULT
#define LIBCURLPP_CURL_CURLRESULT

/*
示例，CurlResult和libcurlpp封装类无直接相关。任何项目都可能有特有的结果设置
*/

#include "libcurlpp.h"

namespace libcurlpp{

	class CurlResult : public LibcurlPP::Delegate
	{
	public:
		CurlResult();
		~CurlResult();

		void result_callback(const int code, const char* message) override;

		/*
		Description:
		CURLOPT_WRITEFUNCTION 回调函数
		*/
		size_t write_callback(char *ptr, size_t size, size_t nmemb) override;

		bool IsFlushWrite() const override;

		/*
		获取结果 \0结尾
		*/
		char* GetResult();

		/*
		将结果保存到文件

		@param file:保存的文件路径

		文件存在时会覆盖，不存在时会创建
		*/
		bool FlushToFile(const std::wstring& file);
	private:
		//错误码和描述
		int _code;
		std::string _message;

		//用于writefunction回调存储数据
		char *_memory;
		size_t _size;
	};
}


#endif