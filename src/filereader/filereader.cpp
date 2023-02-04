// Copyright (c) 2022 NoviFlow Inc. All Rights Reserved.

#include "filereader.h"

#include <cstring>
#include <fstream>

std::string FileReader::readFile(const Path& path) {
  if(!std::experimental::filesystem::exists(path)) {
    std::string message{"Could not read file '"};
    message += path.c_str();
    message += "'.";
    throw std::runtime_error(message);
  }

  std::ifstream read_stream{path.c_str(), std::ios::binary|std::ios::in};
  if(!read_stream.is_open()) {
    std::string message{"Could not create stream to read file '"};
    message += path.c_str();
    message += "'.";
    message += std::strerror(errno);
    throw std::runtime_error(message);
  }

  std::string content{std::istreambuf_iterator<char>(read_stream), std::istreambuf_iterator<char>()};

  read_stream.close();

  return content;
}