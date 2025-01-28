#include "Sushi.hh"
#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>

const size_t Sushi::MAX_INPUT = 256;
const size_t Sushi::HISTORY_LENGTH = 10;
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

std::string Sushi::read_line(std::istream &in){
  std::string line;
  char c;
  size_t count = 0;

  while (in.get(c)){
	  if (c == '\n') break;
	  line +=c;
	  count++;
  }

  if (in.fail() && !in.eof()){
	  // Handle I/O errors
	  std::perror("Error when reading input!");
	  return "";
  }

  //Handle lines exceeds max input
  if (count > Sushi::getMAXINPUT()){
	  while (in.get(c) && c != '\n');
	  std::cerr << "Line too long, truncated." << std::endl;
  return "";
  }
  
  //Check if the line is empty or contains only whitespace
  for (char ch : line) {
    if (!std::isspace(static_cast<unsigned char>(ch))) {
      return line;
    }
  }

  return "";
}

bool Sushi::read_config(const char *fname, bool ok_if_missing){
	std::ifstream file(fname);

	if(!file && !ok_if_missing){
		std::perror("Error opening file");
		return false;
	}
	if (!file && ok_if_missing) return true;
	std::string line;
	while(true){
		line = read_line(file);
		if (line.empty()) break;
		store_to_history(line);
	}
	if (file.bad()){
		std::perror("Error reading file");
		return false;
	}
	file.close();
	return true;
}

void Sushi::store_to_history(std::string line){
	if (line.empty()) return; // Check nullptr or empty 
	history.insert(history.begin(),line); // Insert the new line to the beginning
	if (history.size() > HISTORY_LENGTH) { // Check if the history size is exceeds the HISTORY_LENGTH
		history.pop_back(); // Discard the oldest entry
	}

}

void Sushi::show_history(){
  for (size_t i = 0; i<history.size(); ++i){
	  std::ostringstream index_stream;
	  index_stream.width(5);
	  index_stream.fill(' ');
	  index_stream << (i+1);
	  std::cout << index_stream.str() << " "<<history[i]<<std::endl;
  }
}
