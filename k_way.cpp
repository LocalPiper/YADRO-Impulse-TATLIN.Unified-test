#include "k_way.hpp"
#include "config.hpp"
#include "tape.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
struct HeapNode {
  int value;
  int index;

  bool operator>(const HeapNode &other) const { return value > other.value; }
};

void merge_runs_batch(const std::vector<std::string> &batch,
                      const std::string &output_file) {
  std::vector<std::unique_ptr<Tape>> tapes;
  for (const auto &f : batch)
    tapes.emplace_back(std::make_unique<Tape>(f));
  std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<>> heap;

  for (int i = 0; i < (int)tapes.size(); ++i) {
    int val;
    tapes[i]->rewind();
    if (tapes[i]->read(val)) {
      heap.push({val, i});
      tapes[i]->move_forward();
    }
  }

  Tape output(output_file);
  output.rewind();

  while (!heap.empty()) {
    auto [val, idx] = heap.top();
    heap.pop();
    output.write(val);
    output.move_forward();

    int next;
    if (tapes[idx]->read(next)) {
      heap.push({next, idx});
      tapes[idx]->move_forward();
    }
  }

  output.close();
}

void k_way_merge(const std::vector<std::string> &run_files, Tape &output) {
  namespace fs = std::filesystem;
  fs::create_directory(global_config.tmp_dir);
  std::vector<std::string> curr_runs = run_files;

  size_t pass = 0;
  const size_t max_merge = global_config.ram_limit - 1;
  while (curr_runs.size() > max_merge) {
    std::vector<std::string> next_pass_runs;

    for (size_t i = 0; i < curr_runs.size(); i += max_merge) {
      std::vector<std::string> batch(
          curr_runs.begin() + i,
          curr_runs.begin() + std::min(i + max_merge, curr_runs.size()));

      std::ostringstream name;
      name << global_config.tmp_dir << "/pass" << pass << "_merged"
           << (i / max_merge) << ".txt";
      merge_runs_batch(batch, name.str());

      next_pass_runs.push_back(name.str());
    }

    curr_runs = std::move(next_pass_runs);
    pass++;
  }

  merge_runs_batch(curr_runs, global_config.tmp_dir + "/final_output.tmp");
  Tape input(global_config.tmp_dir + "/final_output.tmp");

  input.rewind();
  output.rewind();

  int val;
  while (input.read(val)) {
    output.write(val);
    output.move_forward();
    input.move_forward();
  }

  input.close();
  output.close();
}
