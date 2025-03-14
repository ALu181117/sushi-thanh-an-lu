#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include "Sushi.hh"
#include <csignal>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

std::string Sushi::read_line(std::istream &in)
{
  std::string line;
  if(!std::getline (in, line)) {// Has the operation failed?
    if(!in.eof()) { 
      std::perror("getline");
    }
    return "";
  }
    
  // Is the line empty?
  if(std::all_of(line.begin(), line.end(), isspace)) {
    return "";
  }

  // Is the line too long?
  if(line.size() > MAX_INPUT_SIZE) {
    line.resize(MAX_INPUT_SIZE);
    std::cerr << "Line too long, truncated." << std::endl;
  }
  
  return line; 
}

bool Sushi::read_config(const char *fname, bool ok_if_missing)
{
  // Try to open a config file
  std::ifstream config_file(fname);
  if (!config_file) {
    if (!ok_if_missing) {
      std::perror(fname);
      return false;
    }
    return true;
  }

  // Read the config file
  while(!config_file.eof()) {
    std::string line = read_line(config_file);
	// New modified add here
    int valid_or_invalid = parse_command(line);
    if (valid_or_invalid == 0){
	store_to_history(line);
    }
  }
  
  return true; 
}

void Sushi::store_to_history(std::string line)
{
  if (line.empty()) {
    return;    
  }

  // Is the history buffer full?
  while (history.size() >= HISTORY_LENGTH) {
    history.pop_front();
  }
  
  history.emplace_back(line);
}
void Sushi::show_history() const
{
  int index = 1;
  for (const auto &cmd: history) {
    std::cout << std::setw(5) << index++ << "  " << cmd << std::endl;
  }
}

void Sushi::set_exit_flag()
{
  exit_flag = true;
}

bool Sushi::get_exit_flag() const
{
  return exit_flag;
}

//---------------------------------------------------------
// New methods
int Sushi::spawn(Program *exe, bool bg)
{
  (void)bg;
  int pid = fork();
  if (pid == -1){
	std::perror("folk");
	return EXIT_FAILURE;
  }
  if (pid == 0){
	char* const* argv = exe->vector2array();
	if(execvp(argv[0],argv) == -1){
	  // DZ: Incorerct use of perror
	  // std::perror("execvp");
	  std::perror(argv[0]);
	  exit(EXIT_FAILURE);
	}
	exe->free_array(argv);
  }else{
	int status;
	if(waitpid(pid,&status,0) == -1) {
	  std::perror("waitpid");
	  return EXIT_FAILURE;
	}
  } return 1;
}

void Sushi::prevent_interruption() {
  struct sigaction interrupt_action;
  interrupt_action.sa_handler = Sushi::refuse_to_die;
  interrupt_action.sa_flags = SA_RESTART;
  sigaction(SIGINT, &interrupt_action, NULL);
}

void Sushi::refuse_to_die(int signo) {
  if (signo == SIGINT){
	std::cerr<<"\nType exit to exit the shell"<<std::endl;
  }
}

void Sushi::mainloop() {
  // Must be implemented
}

char* const* Program::vector2array() {
  char** argv = new char*[args->size()+1];
  for (size_t i = 0; i < args->size(); ++i){
    // DZ: Do not copy data without necessity. It's a `char* CONST*`
	size_t len = args->at(i)->size();
	argv[i] = new char[len+1];
	std::memcpy(argv[i], args->at(i)->c_str(), len+1);
  }
  argv[args->size()] = nullptr;
  return argv;
}

void Program::free_array(char* const argv[]) {
  // DZ: See above
  for (size_t i = 0; argv[i] != nullptr; ++i){
	free(argv[i]);
  }
  delete[] argv;
}

Program::~Program() {
  // Do not implement now
}

