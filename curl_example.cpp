// curl01.cpp : http://stackoverflow.tistory.com/3
//

#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

size_t writer(char *data, size_t size, size_t nmemb, string *writerData)	//WRITEFUNCTION 구현
{
	if (writerData == NULL)
		return 0;

	writerData->append(data, size*nmemb);	//지정된 string에 data를 덧붙인다.
	return size * nmemb;
}

int main(void)
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init(); //easy handle을 생성
	if(curl) {
		string html;		curl_easy_setopt(curl, CURLOPT_URL, "http://www.naver.com");	//접속할 주소
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);			//redirect된 경우 경로를 따라 들어가도록 설정
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);			//여기 지정된 포인터를 WRITEFUNCTION에 넘겨준다.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);		//writer함수 지정
		res = curl_easy_perform(curl);		//수행
		cout << "222" << endl;
		if (res != CURLE_OK)
		{
			cout << "curl_easy_perform() failed: " <<  curl_easy_strerror(res) << endl;
			return false;
		}
 
		cout << html;	//완성된 string을 화면에 뿌려준다.

		curl_easy_cleanup(curl);	//handle cleanup
	}
	return 0;
}
