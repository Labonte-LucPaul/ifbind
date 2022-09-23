
#include "client.h"

#include <curl/curl.h>

namespace stockit::rest::curl {

Client::Client() : ClientBase() {}

std::string Client::sendGetRequest(const Header& header, const std::string& uri) {
  Curl curl{};
  return curl.get(header, uri);
}

Curl::Curl() : curlHandler(curl_easy_init()) {}

Curl::~Curl() {
  if (curlHandler != nullptr) curl_easy_cleanup(curlHandler);
}

std::string Curl::get(const Header& header, const std::string& url) {
  curl_easy_setopt(curlHandler, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(curlHandler, CURLOPT_HTTPHEADER, header.get());
  curl_easy_setopt(curlHandler, CURLOPT_URL, url.c_str());
  curl_easy_setopt(
      curlHandler, CURLOPT_WRITEFUNCTION, +[](void* content, size_t size, size_t member, void* userp) {
        static_cast<std::string*>(userp)->append(static_cast<char*>(content), size * member);
        return size * member;
      });
  std::string body;
  curl_easy_setopt(curlHandler, CURLOPT_WRITEDATA, &body);
  CURLcode ret = curl_easy_perform(curlHandler);

  return body;
}
}  // namespace stockit::rest::curl