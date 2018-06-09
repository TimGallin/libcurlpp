#pragma once

#include "extra.h"
#include "option.h"
namespace libcurlpp{
	namespace extraoption{
		void ProxyOpt(LibcurlPP* curl){

		}

		void GlobalHeader(LibcurlPP* curl){
			libcurlpp::CurlList list;
			list.Append("Content-Type:application/json;charset=UTF-8");
			curl->SetOpt(libcurlpp::options::HTTPHEADER::Create(list));
		}
	}
}