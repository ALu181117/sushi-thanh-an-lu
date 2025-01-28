#pragma once
#include <string> 
#include <vector>

class Sushi {
private:
  std::vector<std::string> history; // Change history type to vector
  static const size_t HISTORY_LENGTH;
  static const size_t MAX_INPUT;

public:
  Sushi() : history() {};
  std::string read_line(std::istream &in);
  bool read_config(const char *fname, bool ok_if_missing);
  void store_to_history(std::string line);
  void show_history();
  static size_t getMAXINPUT(){
	return MAX_INPUT;
  }
  static const std::string DEFAULT_PROMPT;
};

#define UNUSED(expr) do {(void)(expr);} while (0)
