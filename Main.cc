#include <cstdlib>
#include "Sushi.hh"

// Initialize the static constants
const std::string Sushi::DEFAULT_PROMPT = "sushi> ";
const std::string Sushi::DEFAULT_CONFIG = "sushi.conf";
Sushi my_shell; 

int main(int argc, char *argv[]){
  for (int i = 1; i < argc; ++i) {
    if (!my_shell.read_config(argv[i], false)) {
      // DZ: Already reported by read_config
      // std::cerr << "Error: Failed to process script '" << argv[i] << "'" << std::endl;
      return EXIT_FAILURE;
    }
    if (my_shell.get_exit_flag()){
      return EXIT_SUCCESS;
    }
  }
  // DZ: Always run the main loop
  if (/*argc == 1 &&*/ !my_shell.get_exit_flag()) {
    my_shell.mainloop();
  }
  return EXIT_SUCCESS;
}
