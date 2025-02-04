#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Sushi.hh"

Sushi my_shell; // New global var
// Initialize the static constants
///const size_t Sushi::MAX_INPUT = 256;
///const size_t Sushi::HISTORY_LENGTH = 10;
///const std::string Sushi::DEFAULT_PROMPT = "sushi> ";

int main(int argc, char *argv[])
{
  UNUSED(argc);
  UNUSED(argv);
  
  //Get the $HOME environment variable
  const char* home_dir = std::getenv("HOME");
  // DZ: No need to exit because "ok if missing"
  if (!home_dir){
	std::cerr << "Error: HOME environment variable is not set." << std::endl;
        return EXIT_FAILURE;
    }

    // Construct the full path to the sushi.conf file
    std::string config_path =  "sushi.conf";
    // DZ: Unneeded message
    // std::cout << "Attempting to open configuration file: " << config_path << std::endl;
    // DZ: Moved to globals (not an error)
    // Sushi sushi;

    // DZ: `config_path` is incorrect
    // DZ: must be `true`, not `false`
    // Read commands from the sushi.conf file if it exists
    if (!my_shell.read_config(config_path.c_str(), true/*false*/)) {
      // DZ: Duplicate error message
      // std::cerr << "Error: Failed to read configuration file." << std::endl;
        return EXIT_FAILURE;
    }

    // Main loop: display prompt, read command, store in history, and show history
    while (true) {
        // Display the prompt
        std::cout << Sushi::DEFAULT_PROMPT;

        // Read a line from stdin
        std::string command = my_shell.read_line(std::cin);
        if (command.empty()) {
            // If the command is empty, continue the loop (could be just hitting enter)
            continue;
        }

        // Store the command in the history
        my_shell.store_to_history(command);

        // Show the current history
        my_shell.show_history();

        // You may want to add an exit condition here, for example:
        if (command == "exit") {
            break;
        }
    }
    
  return EXIT_SUCCESS;
}
