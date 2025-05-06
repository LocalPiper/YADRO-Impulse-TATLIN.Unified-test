#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstddef>
#include <string>
struct Config {
  size_t ram_limit;
  std::string tmp_dir;
  int tape_read_delay;
  int tape_write_delay;
  int tape_move_delay;

  Config()
      : ram_limit(1024), tape_read_delay(100), tape_write_delay(100),
        tape_move_delay(50) {}
};

extern Config global_config;

bool read_config(const std::string &file_name);

#endif // CONFIG_HPP
