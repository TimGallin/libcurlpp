#pragma once

#ifndef LIBCURLPP_CURL_CURLRESULT
#define LIBCURLPP_CURL_CURLRESULT

/*
ʾ����CurlResult��libcurlpp��װ����ֱ����ء��κ���Ŀ�����������еĽ������
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
		CURLOPT_WRITEFUNCTION �ص�����
		*/
		size_t write_callback(char *ptr, size_t size, size_t nmemb) override;

		bool IsFlushWrite() const override;

		/*
		��ȡ��� \0��β
		*/
		char* GetResult();

		/*
		��������浽�ļ�

		@param file:������ļ�·��

		�ļ�����ʱ�Ḳ�ǣ�������ʱ�ᴴ��
		*/
		bool FlushToFile(const std::wstring& file);
	private:
		//�����������
		int _code;
		std::string _message;

		//����writefunction�ص��洢����
		char *_memory;
		size_t _size;
	};
}


#endif