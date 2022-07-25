#include <iostream>

#include "pushoverapi.hpp"


size_t PushoverAPI::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
     std::cout << "Here 2" << std::endl;
    return size * nmemb;
}

void PushoverAPI::SendNotification() {

    std::string messageText = "Alert: a detection has been made";
    std::string imagePath = "./testing2.jpg";

    struct curl_httppost* formpost = NULL;
    struct curl_httppost* lastptr = NULL;

    curl_global_init(CURL_GLOBAL_ALL);

    curl_formadd(&formpost,
        &lastptr,
        CURLFORM_COPYNAME, "token",
        CURLFORM_COPYCONTENTS , "abc5kk96z5ave92xg8edp6cc89dnui",
        CURLFORM_END);
        
    curl_formadd(&formpost,
        &lastptr,
        CURLFORM_COPYNAME, "user",
        CURLFORM_COPYCONTENTS , "ur8ix1abhx1s8wn3s4s6m8dd3trbiu",
        CURLFORM_END);

    curl_formadd(&formpost,
        &lastptr,
        CURLFORM_COPYNAME, "message",
        CURLFORM_COPYCONTENTS , messageText.data(),
        CURLFORM_END);

    // Todo: send picture from memory instad of reading it from disk
    curl_formadd(&formpost, 
        &lastptr,
        CURLFORM_COPYNAME, "attachment",        
        CURLFORM_FILE, imagePath.data(),
        CURLFORM_CONTENTTYPE, "image/jpeg",
        CURLFORM_END);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.pushover.net/1/messages.json");

        //curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);        

        if (res != CURLE_OK) {
            std::cout << "Call not succesfull " << std::endl;
        }

        std::cout << "Res: " << res << std::endl;
        std::cout << readBuffer << std::endl;
    }


    curl_formfree(formpost);
    std::cout << "Here" << std::endl;
    curl_easy_cleanup(curl);
    //curl_slist_free_all(headerlist);

    curl_global_cleanup();

}