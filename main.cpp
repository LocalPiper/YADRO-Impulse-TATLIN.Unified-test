#include "config.hpp"
#include "generator.hpp"
#include "k_way.hpp"
#include "tape.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
    return 1;
  }

  std::string input_filename = argv[1];
  std::string output_filename = argv[2];

  if (!read_config("config.txt")) {
    return 1;
  }

  Tape input(input_filename);
  Tape output(output_filename);

  std::vector<std::string> run_files;
  generate_sorted_runs(input, run_files);

  k_way_merge(run_files, output);

  return 0;
}
