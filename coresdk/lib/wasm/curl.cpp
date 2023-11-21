#include "curl/curl.h"

CURL_EXTERN CURLcode curl_global_init(long flags){return CURLE_OK;}
CURL_EXTERN void curl_global_cleanup(void){}

CURL_EXTERN CURL *curl_easy_init(void){return nullptr;}
CURL_EXTERN CURLcode curl_easy_setopt(CURL *curl, CURLoption option, ...){return CURLE_OK;}
CURL_EXTERN CURLcode curl_easy_perform(CURL *curl){return CURLE_OK;}
CURL_EXTERN void curl_easy_cleanup(CURL *curl){}
CURL_EXTERN const char *curl_easy_strerror(CURLcode){return "cURL (and anything using the web driver) is not supported under WASM";}
CURL_EXTERN CURLcode curl_easy_getinfo(CURL *curl, CURLINFO info, ...){
	//if (info==CURLINFO_CONTENT_TYPE)
		//TODO: set first argument to nullptr
	return CURLE_OK;
}
CURL_EXTERN struct curl_slist *curl_slist_append(struct curl_slist *,
                                                 const char *){return nullptr;}

CURL_EXTERN void curl_slist_free_all(struct curl_slist *){}