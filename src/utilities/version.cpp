// Copyright (c) 2022 NoviFlow Inc. All Rights Reserved.

#include "version.h"

Version::Version(std::string version) {
  parseVersion(version);
}

void Version::parseVersion(std::string version) {
  const auto first_delimiter = version.find(".");
  const auto v1 = version.substr(0, first_delimiter);
  version = version.substr(first_delimiter+1);
  const auto second_delimiter = version.find(".");
  const auto v2 = version.substr(0, second_delimiter);
  const auto v3 = version.substr(second_delimiter+1);

  major = std::stoi(v1);
  minor = std::stoi(v2);
  revision = std::stoi(v3);
}

bool Version::operator<(const Version& rhs) const {
  if (major < rhs.major) return true;
  if (rhs.major < major) return false;
  if (minor < rhs.minor) return true;
  if (rhs.minor < minor) return false;
  return revision < rhs.revision;
}
bool Version::operator>(const Version& rhs) const { return rhs < *this; }
bool Version::operator<=(const Version& rhs) const { return !(rhs < *this); }
bool Version::operator>=(const Version& rhs) const { return !(*this < rhs); }
bool Version::operator==(const Version& rhs) const {
  return major == rhs.major && minor == rhs.minor && revision == rhs.revision;
}
bool Version::operator!=(const Version& rhs) const { return !(rhs == *this); }

std::ostream& operator<<(std::ostream& os, const Version& version) {
  os << version.major << "." << version.minor << "." << version.revision;
  return os;
}
