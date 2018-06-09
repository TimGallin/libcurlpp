#pragma once

#ifndef LIBCURLPP_CURL_UTILS
#define LIBCURLPP_CURL_UTILS

#include "include\curl.h"
#include <string>

namespace libcurlpp{
	namespace utils{
		/*
		URL���query string,�Զ���query string urlencode
		url = url?key1=value1&key2=value2
		*/
		std::string AddQueryString(const std::string& url, const std::string& key, const std::string& value);

		/*
		url encode����
		*/
		std::string UrlEncode(const std::string& url);
	}
}





#endif