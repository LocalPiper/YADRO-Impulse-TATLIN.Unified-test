#include "tape.hpp"
#include "config.hpp"
#include <chrono>
#include <string>
#include <thread>
Tape::Tape(const std::string &filename) : filename(filename) { load(); }

Tape::~Tape() { save(); }

void Tape::load() {
  file.open(filename, std::ios::in);
  buffer.clear();
  int val;

  while (file >> val) {
    buffer.push_back(val);
  }

  file.close();
  head = 0;
}

void Tape::save() {
  file.open(filename, std::ios::out | std::ios::trunc);
  for (int val : buffer) {
    file << val << "\n";
  }
  file.close();
}

bool Tape::read(int &value) {
  if (head < buffer.size()) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(global_config.tape_read_delay));
    value = buffer[head];
    return true;
  }
  return false;
}

bool Tape::write(int value) {
  if (head < buffer.size()) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(global_config.tape_write_delay));
    buffer[head] = value;
  } else {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(global_config.tape_write_delay));
    buffer.push_back(value);
  }
  return true;
}

bool Tape::move_forward() {
  if (head + 1 <= buffer.size()) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(global_config.tape_move_delay));
    ++head;
    return true;
  }
  return false;
}

bool Tape::move_backward() {
  if (head == 0)
    return false;
  std::this_thread::sleep_for(
      std::chrono::milliseconds(global_config.tape_move_delay));
  --head;
  return true;
}

bool Tape::rewind() {
  head = 0;
  return true;
}

void Tape::close() { save(); }
