#include "generator.hpp"
#include "config.hpp"
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

void generate_sorted_runs(Tape &input,
                          std::vector<std::string> &out_run_files) {
  namespace fs = std::filesystem;
  fs::create_directories(global_config.tmp_dir);

  std::vector<int> buffer;
  int value;
  size_t run_index = 0;

  input.rewind();

  while (input.read(value)) {
    buffer.push_back(value);
    input.move_forward();
    if (buffer.size() == global_config.ram_limit) {
      std::sort(buffer.begin(), buffer.end());

      std::ostringstream run_file_name;
      run_file_name << global_config.tmp_dir << "/run" << run_index++ << ".txt";
      std::ofstream run_file(run_file_name.str());

      for (int val : buffer) {
        run_file << val << "\n";
      }

      run_file.close();
      out_run_files.push_back(run_file_name.str());
      buffer.clear();
    }
  }

  if (!buffer.empty()) {
    std::sort(buffer.begin(), buffer.end());
    std::ostringstream run_file_name;
    run_file_name << global_config.tmp_dir << "/run" << run_index++ << ".txt";
    std::ofstream run_file(run_file_name.str());

    for (int val : buffer) {
      run_file << val << "\n";
    }

    run_file.close();
    out_run_files.push_back(run_file_name.str());
  }
}
