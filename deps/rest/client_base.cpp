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

#include "client_base.h"

namespace stockit::rest {

Header::~Header() {
  if (headers) curl_slist_free_all(headers);
}

void Header::append(const std::string& header) { headers = curl_slist_append(headers, header.c_str()); }

const struct curl_slist* Header::get() const { return headers; }

}  // namespace stockit::rest
