#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

void usage(char *argv)
{
    cout << "\nUsage: " << argv << " <Bucket> <Service> <Key>\n" << endl;
	cout << "Example" << endl;
	cout << argv << " test TTS music_artist_2NE1" <<  endl;
}

//WRITEFUNCTION
size_t writer(char *data, size_t size, size_t nmemb, string *writerData)	
{
	if (writerData == NULL)
		return -1;

	writerData->append(data, size*nmemb);	//Add response to string
	return size * nmemb;
}

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		usage(argv[0]);
		return -1;
	}

	string bucket = argv[1];
	string service = argv[2];
	string key = argv[3];

	CURL *curl;
	CURLcode res;
	string response;

	string url 	= "http://10.40.92.196:7777"; 		//base url
	url = url 	+ "/key-value/" + bucket 			//add bucket
				+ "/search?service=" + service		//add service
				+ "&key=" + key;					//add key

	curl = curl_easy_init(); //easy handle을 생성
	if(curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());		//접속할 주소
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);		//redirect된 경우 경로를 따라 들어가도록 설정
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);	//여기 지정된 포인터를 WRITEFUNCTION에 넘겨준다.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);	//writer함수 지정
		res = curl_easy_perform(curl);							//curl 수행
		
		if (res != CURLE_OK)
		{
			cout << "curl_easy_perform() failed: " <<  curl_easy_strerror(res) << endl;
			return -1;
		}
		curl_easy_cleanup(curl);								//handle cleanup
        curl = NULL;
	}
		
	cout << response << endl;									//response display

	return 0;
}

