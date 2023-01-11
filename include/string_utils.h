#pragma once

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>
#include <sstream>

void replace_string(std::string &str, const std::string &old_str, const std::string &new_str) {
	std::size_t pos = 0;
	while ((pos = str.find(old_str, pos)) != std::string::npos) {
		str.replace(pos, old_str.length(), new_str);
		pos += new_str.length();
	}
}

std::vector<std::string> split(const std::string &str, char delim) {
	std::vector<std::string> vec;
	std::stringstream ss(str);
	std::string word;

	while (!ss.eof()) {
		std::getline(ss, word, delim);
		vec.push_back(word);
	} return vec;
}

std::string join(const std::vector<std::string> &vec, const char *sep) {
	std::string str;
	for (const std::string &itm : vec) str += itm + sep;
	str.erase(str.end() - std::strlen(sep));
	return str;
}

std::string toLowerCase(std::string &str){
	std::string cpy = str;
	for (char &c : cpy) c = std::tolower(c);
	return cpy;
}

std::string toUpperCase(std::string &str){
	std::string cpy = str;
	for (char &c : cpy) c = std::toupper(c);
	return cpy;
}

#endif // !STRING_UTILS_H