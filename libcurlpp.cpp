#include "libcurlpp.h"



namespace libcurlpp{

	size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
		LibcurlPP::Delegate* _delegate = static_cast<LibcurlPP::Delegate*>(userdata);
		return _delegate->write_callback(ptr, size, nmemb);
	}

	//libcurl 
	std::list<LibcurlPP::ExOption> LibcurlPP::_extraoption;

	LibcurlPP::LibcurlPP() :_delegate(NULL){
		_curl = curl_easy_init();
	}

	LibcurlPP::LibcurlPP(LibcurlPP::Delegate* delegate) : _delegate(delegate){
		_curl = curl_easy_init();
	}

	LibcurlPP::~LibcurlPP(){
		Clean();
	}

	void LibcurlPP::AddExtraOption(ExOption extra){
		LibcurlPP::_extraoption.push_back(extra);
	}

	bool LibcurlPP::Perform()
	{
		CURLcode res;

		//ִ��Ԥ���ȫ������
		for each (ExOption var in _extraoption)
		{
			var(this);
		}

		//ִ�е�ǰ�����ã�����ǰ�����÷�����ȫ�����ú��潫�л��Ḳ��ȫ�����ý������⴦��
		for each (options::OptionBase* var in _optlist)
		{
			var->Update(_curl);
		}

		SetCallback();

		//perform
		res = curl_easy_perform(_curl);

		//���ô�������������
		if (_delegate){
			_delegate->result_callback(res, curl_easy_strerror(res));
		}

		return res == CURLE_OK;
	}

	/*
	�����ͷ�curl�Լ�list��Դ
	*/
	void LibcurlPP::Clean(){
		for each (options::OptionBase* var in _optlist){
			var->_destory();
			var = NULL;
		}

		if (_curl){
			curl_easy_cleanup(_curl);
		}
	}

	/*
	�������curl�������õ�optionʹ֮����մ�����״̬һ��
	�����������Ѵ��ڵ����ӡ������SessionID���桢DNS���桢Cookies�Լ�shares
	*/
	void LibcurlPP::Reset(){
		if (_curl){
			curl_easy_reset(_curl);
		}
	}

	/*
	���ûص�����
	*/
	void LibcurlPP::FlushToDelegate(Delegate* delegate){
		_delegate = delegate;
	}

	/*
	���ô���Ļص�����
	*/
	void LibcurlPP::SetCallback(){
		if (_delegate){
			if (_delegate->IsFlushWrite()){
				curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_callback);
				curl_easy_setopt(_curl, CURLOPT_WRITEDATA, (void *)_delegate);
			}
		}
	}

	/*
	Description:
	��������

	@param: opt ���õ����� new xx(type,value)������������ӵ�OptionList�У�����type�Ѿ���OptionList�д��ڣ���ԭ����ɾ����ִ����Ӳ���,ɾ�����������_destory�ͷ�option
	*/
	void LibcurlPP::SetOption(options::OptionBase* opt){
		OptionList::const_iterator ite = _optlist.cbegin();
		for (; ite != _optlist.cend();){
			if ((*ite)->GetOption() == opt->GetOption()){
				(*ite)->_destory();
				ite = _optlist.erase(ite);
			}
			else{
				++ite;
			}
		}

		_optlist.push_back(opt);
	}


	void LibcurlPP::SetOpt(options::OptionBase* opt){
		SetOption(opt);
	}

}
