#ifndef K_WAY_HPP
#define K_WAY_HPP

#include "tape.hpp"
#include <cstddef>
#include <string>
#include <vector>
void k_way_merge(const std::vector<std::string> &run_files, Tape &output,
                 size_t mem_limit, const std::string &tmp_dir);

#endif // K_WAY_HPP
