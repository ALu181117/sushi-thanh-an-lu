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

  // DZ: Very inefficient; Why not use std::getline? 
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

  // DZ: This is incorrect. The line has been already read in full.
  //Handle lines exceeds max input
  // DZ: No need to call a function
  if (count > MAX_INPUT){
  //if (count > Sushi::getMAXINPUT()){
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
	  // DZ: Wrong use of perror
	  //std::perror("Error opening file");
	  std::perror(fname);
		return false;
	}
	if (!file && ok_if_missing) return true;
	std::string line;
	while(true){
		line = read_line(file);
		if (line.empty()) {
		  // DZ: wrong condition, stops the loop at the first blank line
		  break;
		}
		// DZ: This does not belong here
		store_to_history(line);
	}
	if (file.bad()){
	  // DZ: See above
		std::perror("Error reading file");
		return false;
	}
	// DZ: C++ closes local ifstream automatically
	// file.close();
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
    // DZ: You do not need std::ostringstream for this
	  std::ostringstream index_stream;
	  index_stream.width(5);
	  index_stream.fill(' ');
	  index_stream << (i+1);
	  // DZ: Must be TWO spaces
	  std::cout << index_stream.str() << " "<<history[i]<<std::endl;
  }
}

void Sushi::set_exit_flag()
{
  // To be implemented
}

bool Sushi::get_exit_flag() const
{
  return false; // To be fixed
}
