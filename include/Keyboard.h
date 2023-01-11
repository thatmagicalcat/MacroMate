#pragma once

#include <variant>
#include <algorithm>
#include <string>
#include <vector>

namespace win {
  #include <Windows.h>
}

#include "keys_names.h"

using namespace std::string_literals;

class Keyboard {
private:
  using KEY = std::variant<int, char>;
  Keyboard() = delete;

private:
  static void SetKey(win::INPUT *input, const KEY &key, bool is_multiple = false);
  static win::DWORD GetFlag(const KEY &key, bool keyUp = false);

public:
  /**
   * @brief Presses a particular key.
   * @param key The key to be pressed
  */
  static void keyPress(KEY key);

  /**
   * @brief Presses multiple keys at the same time.
   * @param vec Vector of keys to be pressed
  */
  static void multiple_keyPress(const std::vector<KEY> &vec);

  /**
   * @brief Type the string.
   * @param str The string to type
  */
  static void type(std::string_view str);
};
