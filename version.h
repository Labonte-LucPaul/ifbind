//
// Created by luc on 22/09/22.
//

#ifndef IFBIND_VERSION_H
#define IFBIND_VERSION_H

#include <ostream>
#include <string>

class Version {
 public:
  Version(std::string version);

  bool operator<(const Version& rhs) const;
  bool operator>(const Version& rhs) const;
  bool operator<=(const Version& rhs) const;
  bool operator>=(const Version& rhs) const;
  bool operator==(const Version& rhs) const;
  bool operator!=(const Version& rhs) const;

  friend std::ostream& operator<<(std::ostream& os, const Version& version);

 private:
  void parseVersion(std::string version);

  int major;
  int minor;
  int revision;
};

#endif  // IFBIND_VERSION_H
