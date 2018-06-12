#pragma once

#ifndef LIBCURLPP_CURL_OPTION
#define LIBCURLPP_CURL_OPTION

#include "include/curl.h"

#include "curllist.h"

#include <list>
#include <string>
#include <algorithm>
namespace libcurlpp{

	namespace options{
		//Option Virtual Class
		class OptionBase
		{
		public:
			/**
			调用本函数将option设置到curl
			*/
			virtual bool Update(CURL* handle) = 0;


			virtual CURLoption GetOption() const = 0;

			/**
			由libcurl在析构时自动调用用于释放Option
			不要在外部手动调用！！！
			*/
			virtual void _destory() = 0;
		protected:
			virtual ~OptionBase(){};
		};

		//调用curl设置
		template<CURLoption OptionType, typename ValueType>
		class OptionSetter
		{
		public:
			static void setopt(CURL* handle, ValueType& value){
				curl_easy_setopt(handle, OptionType, value);
			}

		};

		//Specilize for CurlList
		template<CURLoption OptionType>
		class OptionSetter<OptionType, CurlList>
		{
		public:
			static void setopt(CURL* handle, CurlList& value){
				curl_easy_setopt(handle, OptionType, value.GetSlist());
			}
		};


		//Specilize for std::string
		template<CURLoption OptionType>
		class OptionSetter<OptionType, std::string>
		{
		public:
			static void setopt(CURL* handle, std::string& value){
				curl_easy_setopt(handle, OptionType, (char*)value.c_str());
			}
		};

		//Option Template Class
		template <CURLoption OptionType, class ValueType>
		class Option : public OptionBase
		{
		public:
			static OptionBase* Create(const ValueType& value){
				return dynamic_cast<OptionBase*>(new Option<OptionType, ValueType>(value));
			}

			void _destory(){
				delete this;
			}

			

			ValueType GetValue() const{
				return _value;
			}

			CURLoption GetOption() const override{
				return _option;
			}


			bool Update(CURL* handle) override{
				if (handle == NULL){
					return false;
				}

				OptionSetter<OptionType, ValueType>::setopt(handle, _value);

				return true;
			}

		private:
			explicit Option(const ValueType& value) :_option(OptionType), _value(value){};
			~Option(){};

			CURLoption _option;
			ValueType _value;
		};

		//Specilize for CurlList
		template <CURLoption OptionType>
		class Option<OptionType, std::list<std::string>> : public OptionBase{
		public:
			static OptionBase* Create(const std::list<std::string>& value){
				return dynamic_cast<OptionBase*>(new Option<OptionType, std::list<std::string>>(value));
			}

			void _destory(){
				delete this;
			}



			CurlList GetValue() const{
				return _value;
			}

			CURLoption GetOption() const override{
				return _option;
			}


			bool Update(CURL* handle) override{
				if (handle == NULL){
					return false;
				}

				OptionSetter<OptionType, CurlList>::setopt(handle, _value);

				return true;
			}

		private:
			explicit Option(const std::list<std::string>& value) :_option(OptionType), _value(value){};
			~Option(){};

			CURLoption _option;
			CurlList _value;
		};


		typedef Option<CURLOPT_URL, std::string> URL;  //目标URL
		typedef Option<CURLOPT_PROXY, std::string> PROXY;      //代理地址 scheme://xx.xx.xx.xx:port
		typedef Option<CURLOPT_PROXYUSERPWD, std::string> PROXYAUTH;//代理验证  user:passwd
		typedef Option<CURLOPT_PROXYAUTH, unsigned long> PROXY_AUTH_TYPE;//代理认证类型 建议使用CURLAUTH_ANY
		typedef Option<CURLOPT_HTTPHEADER, std::list<std::string>> HTTPHEADER; //Http header设置
		typedef Option<CURLOPT_POSTFIELDS, std::string> HTTPPOSTDATA; //POST数据，该选项会默认让curl CURLOPT_POST设置为1，若不采用CURLOPT_POSTFIELDSIZE指定char*长度，则libcurl使用strlen函数确认长度

		typedef Option<CURLOPT_POSTFIELDSIZE, long> HTTPPOSTDATASIZE; //手动指定POSTDATA长度
		typedef Option<CURLOPT_TIMEOUT, long> TIMEOUT; //超时设置 秒为单位

		typedef Option<CURLOPT_SSL_VERIFYPEER, long> VERIFY_PEER; //是否验证服务端证书授权 0:不验证 1:验证 （默认为1）
		typedef Option<CURLOPT_SSL_VERIFYHOST, long> VERIFY_HOST; //是否验证服务端身份与URL指定身份是否匹配 0:忽略验证 1:debug选项 不可用 2：验证 （默认2）


	}

}

#endif
