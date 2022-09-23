//
// Created by luc on 2021-09-29.
//

#ifndef STOCKIT_CLIENT_H
#define STOCKIT_CLIENT_H

#include "../client_base.h"

namespace stockit::rest::curl {

class Client : public ClientBase {
 public:
  Client();
  std::string sendGetRequest(const Header& header, const std::string& uri) override;
};

struct Curl {
  Curl();
  ~Curl();

  std::string get(const Header& header, const std::string& url);

 private:
  CURL* curlHandler = nullptr;
};

}  // namespace stockit::rest:curl

#endif  // STOCKIT_CLIENT_H
