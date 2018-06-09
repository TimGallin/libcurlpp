#include "curlutils.h"

namespace libcurlpp{
	namespace utils{
		/*
		URL添加query string
		url = url?key1=value1&key2=value2
		*/
		std::string AddQueryString(const std::string& url, const std::string& key, const std::string& value){
			std::string query = url;
			if (url.find('?') == std::string::npos){
				//url是否已有？ 不是则添加上
				query += "?";
			}

			std::string querypart = key + "&" + value;
			querypart = UrlEncode(querypart);

			query += querypart;

			return query;
		}

		/*
		url encode编码
		*/
		std::string UrlEncode(const std::string& url){
			CURL *curl = curl_easy_init();

			std::string urlencode = "";
			if (curl) {
				char *output = curl_easy_escape(curl, url.c_str(), url.length());
				if (output) {
					urlencode = output;
					curl_free(output);
				}
			}

			curl_easy_cleanup(curl);

			return urlencode;
		}
	}
}
