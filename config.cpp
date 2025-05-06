
#include "config.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Config global_config;

bool read_config(const std::string &file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    std::cerr << "Error opening config file: " << file_name << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string key;
    std::getline(iss, key, '=');

    if (key == "RAM_LIMIT") {
      iss >> global_config.ram_limit;
      global_config.ram_limit /= 4; // assuming that int is 4 bytes
    } else if (key == "TMP_DIR") {
      std::getline(iss, global_config.tmp_dir);
    } else if (key == "TAPE_READ_DELAY") {
      iss >> global_config.tape_read_delay;
    } else if (key == "TAPE_WRITE_DELAY") {
      iss >> global_config.tape_write_delay;
    } else if (key == "TAPE_MOVE_DELAY") {
      iss >> global_config.tape_move_delay;
    }
  }

  file.close();
  return true;
}
