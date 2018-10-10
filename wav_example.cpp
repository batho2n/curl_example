#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <curl/curl.h>
 
using namespace std;

#define DWORD uint32_t

void usage(char *argv)
{
	cout << "\nUsage: " << argv << " <url.wav>\n" << endl;
	cout << "Example" << endl;
	cout << argv << " http://www.kozco.com/tech/piano2.wav" <<	endl;
}


static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}
 
static size_t write_wav(char *data, size_t size, size_t nmemb, vector<char> *buffer)
{
	if (buffer == NULL)	return -1;

	int i=0;
	for(i=0; i<nmemb; i++)
		buffer->push_back(data[i]);
	
	cout << "SIZE: " << size << endl;
	cout << "NMEM: " << nmemb << endl;
	return size * nmemb;
}

int main(int argc, char *argv[])
{
	CURL *curl_handle;
	static const char *pagefilename = "page.raw";
	FILE *pagefile;
 
	if(argc < 2) {
		usage(argv[0]);
		return 1;
	}
	
	vector<char> buffer;

	curl_global_init(CURL_GLOBAL_ALL);
	curl_handle = curl_easy_init();										/* init the curl session */ 
	curl_easy_setopt(curl_handle, CURLOPT_URL, argv[1]);				/* set URL to get here */ 
	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);					/* Switch on full protocol/debug output while testing */ 
	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);				/* disable progress meter, set to 0L to enable and disable debug output */ 
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_wav);	/* send all data to this function	*/ 
	/* open the file */ 
	if(curl_handle) {
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &buffer);		/* write the page body to this file handle */ 
		curl_easy_perform(curl_handle);									/* get it! */ 
	}

	printf("BUFFER: %lu\n", buffer.size());
	short *bufA = new short[buffer.size()];
	memcpy(bufA, &buffer[44], sizeof(char) * buffer.size()-44);

	pagefile = fopen(pagefilename, "wb");
	fwrite(bufA, sizeof(char), buffer.size()-44, pagefile);	
	fclose(pagefile);

	/* cleanup curl stuff */ 
	curl_easy_cleanup(curl_handle);
 
	curl_global_cleanup();
 
	return 0;
}
