//
// Created by luc on 22/09/22.
//

#ifndef IFBIND_FILEREADER_H
#define IFBIND_FILEREADER_H

#include <experimental/filesystem>
#include <string>

using Path = std::experimental::filesystem::path;
class FileReader {
 public:
  static std::string readFile(const Path& path);
};

#endif  // IFBIND_FILEREADER_H
