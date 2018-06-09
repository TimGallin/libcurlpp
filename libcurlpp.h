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
			//���մ����������
			virtual void result_callback(const int code, const char* message) = 0;

			//CURLOPT_WRITEFUNCTION
			/*
			CURLOPT_WRITEFUNCTION
			curl�������ݵĻص�����
			*/
			virtual size_t write_callback(char *ptr, size_t size, size_t nmemb) = 0;

			/*
			����true�򽫻�����write�ص��������ص�write_callback
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
		����curl����
		ִ��OptionList�е���������
		ִ��curl_easy_perform

		Return:
		true:����ɹ�
		false������ʧ��
		*/
		bool Perform();

		/*
		Description:
		��������

		@param: opt ���õ����� new xx(type,value)������������ӵ�OptionList�У�����type�Ѿ���OptionList�д��ڣ���ԭ����ɾ����ִ����Ӳ���


		���ú�ִ��delete opt��
		*/
		void SetOpt(options::OptionBase* opt);


		/*
		�������curl�������õ�optionʹ֮����մ�����״̬һ��
		�����������Ѵ��ڵ����ӡ������SessionID���桢DNS���桢Cookies�Լ�shares
		*/
		void Reset();

		/*
		����ĸ������ã���LibcurlPP�ڲ�ά��һ��function list����ÿ��performʱ��һ��ִ�и�list�е��������á�������ȫ����Ч�������ڴ���ȫ�ִ������õ�����ȫ����������
		*/
		typedef std::function<void(LibcurlPP*)> ExOption;
		static void AddExtraOption(ExOption extra);

		/*
		���ûص�����
		*/
		void FlushToDelegate(Delegate* delegate);
	private:
		/*
		Description:
		��������

		@param: opt ���õ����� new xx(type,value)������������ӵ�OptionList�У�����type�Ѿ���OptionList�д��ڣ���ԭ����ɾ����ִ����Ӳ���
		*/
		void SetOption(options::OptionBase* opt);

		/*
		���ô���Ļص�����
		*/
		void SetCallback();

		/*
		�����ͷ�curl�Լ�list��Դ
		*/
		void Clean();



		//��ǰ����ӵĲ��ظ���option
		typedef std::list<options::OptionBase*> OptionList;
		OptionList _optlist;

		//��ǰ����ӵ�ȫ������
		static std::list<ExOption> _extraoption;

		//�ص�����
		Delegate* _delegate;

		//ԭCURL����
		CURL* _curl;
	};

}

#endif