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

		//执行预设的全局设置
		for each (ExOption var in _extraoption)
		{
			var(this);
		}

		//执行当前的设置，将当前的设置放置在全局设置后面将有机会覆盖全局设置进行特殊处理
		for each (options::OptionBase* var in _optlist)
		{
			var->Update(_curl);
		}

		SetCallback();

		//perform
		res = curl_easy_perform(_curl);

		//设置代理错误码和描述
		if (_delegate){
			_delegate->result_callback(res, curl_easy_strerror(res));
		}

		return res == CURLE_OK;
	}

	/*
	清理释放curl以及list资源
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
	清空所有curl中已设置的option使之如果刚创建的状态一样
	但不会重置已存在的连接、保存的SessionID缓存、DNS缓存、Cookies以及shares
	*/
	void LibcurlPP::Reset(){
		if (_curl){
			curl_easy_reset(_curl);
		}
	}

	/*
	设置回调代理
	*/
	void LibcurlPP::FlushToDelegate(Delegate* delegate){
		_delegate = delegate;
	}

	/*
	设置代理的回调函数
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
	设置类型

	@param: opt 设置的类型 new xx(type,value)，将该类型添加到OptionList中，若该type已经在OptionList中存在，则将原类型删除再执行添加操作,删除操作会调用_destory释放option
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
