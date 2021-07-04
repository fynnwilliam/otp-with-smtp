#pragma once
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <curl/curl.h>

class smtp
{
private:
    struct upload_status
    {
        int lines_read{};
    };

    std::string const sender_{"fynnwilliam@gmail.com"};
    curl_slist *recipients_ = nullptr;
    int status_;
    CURL *curl_ = curl_easy_init();
    upload_status upload_ctx_;
    std::string const recipient_;
    std::string const code_;
    std::string const password_{"password"};
    std::string const mailserver_{"smtp://smtp.gmail.com:587"};

    static std::vector<std::string> payload_text_;

public:
    smtp(std::string const &recipient, std::string const &code) : status_{-1}, recipient_{recipient}, code_{code} {}
    static size_t copy_data_to_ptr(char *ptr, std::string const &data, upload_status *upload_ctx);
    static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp);
    void establish_connection();
    void set_credentials();
    void connect_to_mailserver();
    CURLcode send_message();
    int check_status(CURLcode status);
    void cleanup();
    int send_email();
    void update_code();
    void add_recipients();
    void update_recipient();
    void read_data();
    void update_payload_text();
    void enable_debug_info(long choice);
    void specify_sender();
    void update_sender();
    ~smtp() { cleanup(); }
};


// http://www.cplusplus.com/forum/general/18964/
// https://en.cppreference.com/w/cpp/string/byte/memcpy
// https://en.cppreference.com/w/cpp/algorithm/transform