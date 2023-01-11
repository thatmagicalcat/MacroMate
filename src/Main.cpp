#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <string>
#include <variant>
#include <istream>
#include <algorithm>
#include <chrono>
#include <vector>

#include "string_utils.h"
#include "keys_names.h"
#include "Keyboard.h"

using KEY = std::variant<int, char>;

void exec(std::istream &in) {
  std::string str;

  while (std::getline(in, str)) {
    if (str.size() == 0) continue;

    auto arr = split(str, ' ');

    std::string &front = arr.front();

    // Comment
    if (front.starts_with("#")) continue;

    if (front.starts_with('!')) {
      front = front.substr(1);

      Keyboard::type(join(arr, " "));
    } else if (front.starts_with("@delay")) {
      if (arr.size() == 1) {
        std::cout << "An argument exepcted after the exec function\n";
        exit(1);
      } std::this_thread::sleep_for(std::chrono::milliseconds(std::stoll(*(arr.begin() + 1))));
    } else if (front.starts_with("@exec")) {
      if (arr.size() == 1) {
        std::cout << "An argument exepcted after the exec function\n";
        exit(1);
      } system(join({ arr.begin() + 1, arr.end() }, " ").c_str());
    } else {
      std::vector<KEY> vec;
      std::for_each(arr.begin(), arr.end(), [&](std::string &current) {
        if (current.starts_with('\'')) vec.push_back(*(current.begin() + 1));
        else {
          if (KEY_NAMES.find(toUpperCase(current)) == KEY_NAMES.end()) {
            std::cerr << "Key name: '" << current << "' not found\n";
            exit(1);
          }

          vec.push_back(KEY_NAMES.at(toUpperCase(current)));
        }
      });

      Keyboard::multiple_keyPress(vec);
    }
  }
}

int main(int argc, const char ** const argv) {
#if !defined(_DEBUG)
  if (argc <= 1) {
    std::cerr << "Usage: mm [file-path]\n";
    return 0;
  }
  
  if (!std::filesystem::exists(argv[1])) {
    std::cout << "File: '" << argv[1] << "' not found\n";
    return 0;
  }
#endif

  std::ifstream in(
#if defined(_DEBUG)
    "code.txt" // temporary file for testing
#else
    argv[1]
#endif
  );

  exec(in);
  in.close();
}
