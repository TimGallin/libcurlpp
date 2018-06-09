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
			���ñ�������option���õ�curl
			*/
			virtual bool Update(CURL* handle) = 0;


			virtual CURLoption GetOption() const = 0;

			/**
			��libcurl������ʱ�Զ����������ͷ�Option
			��Ҫ���ⲿ�ֶ����ã�����
			*/
			virtual void _destory() = 0;
		protected:
			virtual ~OptionBase(){};
		};

		//����curl����
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
				curl_easy_setopt(handle, OptionType, value.c_str());
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

		typedef Option<CURLOPT_URL, std::string> URL;  //Ŀ��URL
		typedef Option<CURLOPT_PROXY, std::string> PROXY;      //�����ַ scheme://xx.xx.xx.xx:port
		typedef Option<CURLOPT_PROXYUSERPWD, std::string> PROXYAUTH;//������֤  user:passwd
		typedef Option<CURLOPT_PROXYAUTH, unsigned long> PROXY_AUTH_TYPE;//������֤���� ����ʹ��CURLAUTH_ANY
		typedef Option<CURLOPT_HTTPHEADER, CurlList> HTTPHEADER; //Http header����
		typedef Option<CURLOPT_POSTFIELDS, char*> HTTPPOSTDATA; //POST���ݣ���ѡ���Ĭ����curl CURLOPT_POST����Ϊ1����������CURLOPT_POSTFIELDSIZEָ��char*���ȣ���libcurlʹ��strlen����ȷ�ϳ���

		typedef Option<CURLOPT_POSTFIELDSIZE, long> HTTPPOSTDATASIZE; //�ֶ�ָ��POSTDATA����
		typedef Option<CURLOPT_TIMEOUT, long> TIMEOUT; //��ʱ���� ��Ϊ��λ


	}

}

#endif
