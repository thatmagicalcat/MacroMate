#include "Keyboard.h"

void Keyboard::SetKey(win::INPUT *input, const KEY &key, bool is_multiple) {
  input->type = INPUT_KEYBOARD;

  if (!is_multiple) {
    input->ki.dwFlags = GetFlag(key);

    if (auto itm = std::get_if<int>(&key))
      input->ki.wVk = *itm;
    else
      input->ki.wScan = std::get<char>(key);
    return;
  }

  input->ki.dwFlags = 0;
  if (auto itm = std::get_if<int>(&key))
    input->ki.wVk = *itm;
  else {
    auto s = ""s + (char) std::toupper(std::get<char>(key));
    input->ki.wVk = KEY_NAMES.at(s);
  }
}

win::DWORD Keyboard::GetFlag(const KEY &key, bool keyUp) {
  static auto end_flag = [&]() -> win::DWORD { return keyUp ? KEYEVENTF_KEYUP:0; };

  if (std::get_if<int>(&key)) return end_flag();
  else return KEYEVENTF_UNICODE | end_flag();
}

void Keyboard::keyPress(KEY key) {
  win::INPUT input = {0};

  SetKey(&input, key);

  win::SendInput(1, &input, sizeof(win::INPUT));

  input.ki.dwFlags |= KEYEVENTF_KEYUP;
  win::SendInput(1, &input, sizeof(win::INPUT));
}

void Keyboard::multiple_keyPress(const std::vector<KEY> &vec) {
  win::INPUT *inputs = new win::INPUT[vec.size()];

  for (size_t i = 0; i < vec.size(); ++i)
    SetKey(&inputs[i], vec[i], true);

  win::SendInput(vec.size(), inputs, sizeof(win::INPUT));

  for (size_t i = 0; i < vec.size(); ++i) inputs[i].ki.dwFlags |= KEYEVENTF_KEYUP;

  win::SendInput(vec.size(), inputs, sizeof(win::INPUT));

  delete [] inputs;
}

void Keyboard::type(std::string_view str) {
  win::INPUT input = {0};

  std::for_each(str.begin(), str.end(), [&](const char &ch) {
    SetKey(&input, ch);
    win::SendInput(1, &input, sizeof(win::INPUT));
  });

  input.ki.dwFlags |= KEYEVENTF_KEYUP;
  win::SendInput(1, &input, sizeof(win::INPUT));
}
