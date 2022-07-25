#ifndef PUSHOVER_API
#define PUSHOVER_API

#include <iostream>
#include <curl/curl.h>

class PushoverAPI 
{
    private:
        CURL *curl;
        CURLcode res;
        std::string readBuffer;

        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        

    public:
        void SendNotification();

};

#endif
