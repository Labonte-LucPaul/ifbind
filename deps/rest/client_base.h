//   Copyright (C) 2021  Luc Paul Labonté
//
//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU Affero General Public License as published
//   by the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU Affero General Public License for more details.
//
//   You should have received a copy of the GNU Affero General Public License
//   along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef STOCKIT_CLIENT_BASE_H
#define STOCKIT_CLIENT_BASE_H

#include <curl/curl.h>
#include <string>

namespace stockit::rest {
struct Header;
class ClientBase {
 public:
  ClientBase() = default;
  virtual ~ClientBase() = default;

  virtual std::string sendGetRequest(const Header& header, const std::string& uri) = 0;
};

struct Header {
  Header() = default;
  ~Header();

  void append(const std::string& header);

  struct curl_slist& operator*() const {
    return *headers;
  }
  struct curl_slist* get() {
    return headers;
  }
  [[nodiscard]] const struct curl_slist* get() const;

 private:
  struct curl_slist* headers = nullptr;
};

}  // namespace stockit::rest

#endif  // STOCKIT_CLIENT_BASE_H
