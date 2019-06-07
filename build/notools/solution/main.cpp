#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main() {

  fs::path p("/usr/local");
  
  if (!fs::exists(p))
  {
    std::cout << "\nNot found: " << p << std::endl;
  }
}

