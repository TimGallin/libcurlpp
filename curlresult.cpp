#include "curlresult.h"



namespace libcurlpp{

	CurlResult::CurlResult() :_memory(NULL), _size(0)
	{
	}

	CurlResult::~CurlResult()
	{
		if (_memory){
			free(_memory);
		}
	}

	void CurlResult::result_callback(const int code, const char* message){
		_code = code;
		if (message){
			_message = message;
		}
	}

	/*
	Description:
	CURLOPT_WRITEFUNCTION �ص�����
	*/
	size_t CurlResult::write_callback(char *ptr, size_t size, size_t nmemb){
		size_t realsize = size * nmemb;

		_memory = static_cast<char*>(realloc(_memory, _size + realsize + 1));
		if (_memory == NULL) {
			/* out of memory! */
			printf("not enough memory (realloc returned NULL)\n");
			return 0;
		}

		memcpy(&(_memory[_size]), ptr, realsize);
		_size += realsize;
		_memory[_size] = 0;

		return realsize;
	}

	bool CurlResult::IsFlushWrite() const{
		return true;
	}


	/*
	��ȡ��� \0��β
	*/
	char* CurlResult::GetResult(){
		return _memory;
	}


	/*
	��������浽�ļ�

	@param file:������ļ�·��

	�ļ�����ʱ�Ḳ�ǣ�������ʱ�ᴴ��
	*/
	bool CurlResult::FlushToFile(const std::wstring& file){
		FILE* pfile = NULL;
		_wfopen_s(&pfile, file.c_str(), L"wb+");
		if (!pfile){
			int n = GetLastError();
			return false;
		}

		int nCount = fwrite(_memory, sizeof(char), _size, pfile);
		if (nCount != _size){
			int n = GetLastError();
			return false;
		}

		fclose(pfile);
		return true;
	}
}
