#pragma once

#ifndef LIBCURLPP_CURL_EXTRA
#define LIBCURLPP_CURL_EXTRA

/*
ʾ����extra�ͱ���װ����ֱ����ء��κ���Ŀ�����������еĶ���ȫ������
*/
#include "libcurlpp.h"

namespace libcurlpp{
	namespace extraoption{
		void ProxyOpt(LibcurlPP* curl);
	}
}

#endif