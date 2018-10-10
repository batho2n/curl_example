#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

#define DWORD uint32_t

typedef struct _ARG_ 
{
	std::string		f0_file;
	std::string		sp_file;
	std::string		nm_file;
	std::string		f0_type;
	std::string		sp_type;
	std::string		nm_type;

	int 			fs;
	int				dftlen;
	double			shift;
	bool			nm_cont;
	bool			verbose;
	
	std::string		wav_file;
} ARG_t;

DWORD get_time() 
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	DWORD ret = (DWORD)(tv.tv_usec / 1000 + tv.tv_sec * 1000);
	return ret;
}


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

	double elapsed_time = 0.0;
	curl = curl_easy_init(); //easy handle을 생성
	if(curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());		//접속할 주소
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);		//redirect된 경우 경로를 따라 들어가도록 설정
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);	//여기 지정된 포인터를 WRITEFUNCTION에 넘겨준다.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);	//writer함수 지정
		curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 300L);			//Response 5millisecond time out setting
		res = curl_easy_perform(curl);							//curl 수행
	
		if (res != CURLE_OK)
		{
			cout << "ERR" << endl;
			return -1;
		}

		curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed_time);
		cout << "Elapsed time: " << elapsed_time << endl;
		curl_easy_cleanup(curl);								//handle cleanup
        curl = NULL;
	}
		
	cout << response << endl;									//response display

	return 0;
}

