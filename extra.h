#pragma once

#ifndef LIBCURLPP_CURL_EXTRA
#define LIBCURLPP_CURL_EXTRA

/*
示例，extra和本封装类无直接相关。任何项目都可能有特有的额外全局设置
*/
#include "libcurlpp.h"

namespace libcurlpp{
	namespace extraoption{
		void ProxyOpt(LibcurlPP* curl);
	}
}

#endif