#include <dirent.h>
#include <sys/types.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void GetChildren(const std::string& dir, std::vector<std::string>* result) {
  result->clear();
  DIR* d = opendir(dir.c_str());

  struct dirent* entry;
  while ((entry = readdir(d)) != nullptr) {
    result->push_back(entry->d_name);
  }
  closedir(d);
}

// including "." and ".."
int main() {
  std::vector<std::string> res;
  GetChildren(".", &res);
  std::for_each(res.begin(), res.end(),
                [](std::string const& s) { std::cout << s << std::endl; });
}
