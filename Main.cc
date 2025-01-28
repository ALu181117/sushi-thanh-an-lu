#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "Sushi.hh"

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
  if (!home_dir){
	std::cerr << "Error: HOME environment variable is not set." << std::endl;
        return EXIT_FAILURE;
    }

    // Construct the full path to the sushi.conf file
    std::string config_path =  "sushi.conf";
    std::cout << "Attempting to open configuration file: " << config_path << std::endl;
    Sushi sushi;

    // Read commands from the sushi.conf file if it exists
    if (!sushi.read_config(config_path.c_str(), false)) {
        std::cerr << "Error: Failed to read configuration file." << std::endl;
        return EXIT_FAILURE;
    }

    // Main loop: display prompt, read command, store in history, and show history
    while (true) {
        // Display the prompt
        std::cout << Sushi::DEFAULT_PROMPT;

        // Read a line from stdin
        std::string command = sushi.read_line(std::cin);
        if (command.empty()) {
            // If the command is empty, continue the loop (could be just hitting enter)
            continue;
        }

        // Store the command in the history
        sushi.store_to_history(command);

        // Show the current history
        sushi.show_history();

        // You may want to add an exit condition here, for example:
        if (command == "exit") {
            break;
        }
    }
    
  return EXIT_SUCCESS;
}
