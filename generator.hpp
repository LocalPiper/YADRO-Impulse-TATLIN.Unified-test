#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "tape.hpp"
#include <cstddef>
#include <string>
#include <vector>
void generate_sorted_runs(Tape &input, const std::string &tmp_dir,
                          size_t mem_limit,
                          std::vector<std::string> &out_run_files);

#endif // GENERATOR_HPP
