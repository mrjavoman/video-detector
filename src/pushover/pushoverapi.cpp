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

    public:
        void SendNotification();

};

#endif
