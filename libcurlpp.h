#pragma once

#ifndef LIBCURLPP_CURL_LIBCURLPP
#define LIBCURLPP_CURL_LIBCURLPP

#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include "option.h"

namespace libcurlpp{


	class LibcurlPP
	{
	public:
		class Delegate
		{
		public:
			//接收错误码和描述
			virtual void result_callback(const int code, const char* message) = 0;

			//CURLOPT_WRITEFUNCTION
			/*
			CURLOPT_WRITEFUNCTION
			curl接收数据的回调函数
			*/
			virtual size_t write_callback(char *ptr, size_t size, size_t nmemb) = 0;

			/*
			返回true则将会设置write回调函数并回调write_callback
			*/
			virtual bool IsFlushWrite() const = 0;
		protected:
			~Delegate(){};
		};

		LibcurlPP(Delegate* delegate);
		LibcurlPP();
		~LibcurlPP();

		/*
		Description:
		创建curl对象
		执行OptionList中的所有设置
		执行curl_easy_perform

		Return:
		true:请求成功
		false：请求失败
		*/
		bool Perform();

		/*
		Description:
		设置类型

		@param: opt 设置的类型 new xx(type,value)，将该类型添加到OptionList中，若该type已经在OptionList中存在，则将原类型删除再执行添加操作


		设置后将执行delete opt：
		*/
		void SetOpt(options::OptionBase* opt);


		/*
		清空所有curl中已设置的option使之如果刚创建的状态一样
		但不会重置已存在的连接、保存的SessionID缓存、DNS缓存、Cookies以及shares
		*/
		void Reset();

		/*
		额外的附加设置，在LibcurlPP内部维护一个function list，在每次perform时将一次执行该list中的所有设置。本设置全局有效。可用于处理全局代理设置等其他全局设置需求
		*/
		typedef std::function<void(LibcurlPP*)> ExOption;
		static void AddExtraOption(ExOption extra);

		/*
		设置回调代理
		*/
		void FlushToDelegate(Delegate* delegate);
	private:
		/*
		Description:
		设置类型

		@param: opt 设置的类型 new xx(type,value)，将该类型添加到OptionList中，若该type已经在OptionList中存在，则将原类型删除再执行添加操作
		*/
		void SetOption(options::OptionBase* opt);

		/*
		设置代理的回调函数
		*/
		void SetCallback();

		/*
		清理释放curl以及list资源
		*/
		void Clean();



		//当前已添加的不重复的option
		typedef std::list<options::OptionBase*> OptionList;
		OptionList _optlist;

		//当前已添加的全局设置
		static std::list<ExOption> _extraoption;

		//回调代理
		Delegate* _delegate;

		//原CURL对象
		CURL* _curl;
	};

}

#endif