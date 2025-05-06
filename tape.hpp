#ifndef TAPE_HPP
#define TAPE_HPP

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
class TapeInterface {
public:
  virtual bool read(int &value) = 0;
  virtual bool write(int value) = 0;
  virtual bool rewind() = 0;
  virtual bool move_forward() = 0;
  virtual bool move_backward() = 0;
  virtual ~TapeInterface() = default;
};

class Tape : public TapeInterface {
private:
  std::string filename;
  std::fstream file;
  std::vector<int> buffer;
  size_t head = 0;

  void load();
  void save();

public:
  Tape(const std::string &filename);
  ~Tape();

  bool read(int &value) override;
  bool write(int value) override;
  bool move_forward() override;
  bool move_backward() override;
  bool rewind() override;

  void close();
};

#endif // TAPE_HPP
