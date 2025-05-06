#include "generator.hpp"
#include "k_way.hpp"
#include "tape.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0]
              << " <input_file> <output_file> <tmp_dir> <mem_limit>\n";
    return 1;
  }

  std::string input_filename = argv[1];
  std::string output_filename = argv[2];
  std::string tmp_dir = argv[3];
  size_t mem_limit = std::stoi(argv[4]);

  Tape input(input_filename);
  Tape output(output_filename);

  std::vector<std::string> run_files;
  generate_sorted_runs(input, tmp_dir, mem_limit, run_files);

  k_way_merge(run_files, output, mem_limit, tmp_dir);

  return 0;
}
