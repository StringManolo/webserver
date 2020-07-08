#pragma once

#include <string>

#define CRITICAL 1
#define WARNING 2
#define VERBOSE 3
#define DEBUG 4

struct colors { 
  std::string RED = "\x1b[31m";
  std::string YELLOW = "\x1b[33m";
  std::string BLUE = "\x1b[34m";
  std::string GREEN = "\x1b[32m";
  std::string RESET = "\x1b[0m";
}; 

struct CONSOLE {
  colors COLORS;
  void log(bool param, std::string message, int color) {
    switch(color) {
      case CRITICAL:
        std::cout << COLORS.RED << "CRITICAL ------------------------------------" << std::endl << message << std::endl << "------------------------------------------" << std::endl << COLORS.RESET;
      break;
      
      case WARNING:
        std::cout << COLORS.YELLOW << "WARNING ----------------------------------------" << std::endl << message << std::endl << std::endl << "./webserver --help" << std::endl << "------------------------------------------" << std::endl << COLORS.RESET;
      break;
      
      case VERBOSE:
        if(param == 1) {
          std::cout << COLORS.GREEN << "INFO -----------------------------------------" << std::endl << message << std::endl << "------------------------------------------" << std::endl << COLORS.RESET << std::endl;
        }
      break;
      
      case DEBUG:
        if(param == 1) {
          std::cout << COLORS.BLUE << "DEBUG ----------------------------------------" << std::endl << message <<
            std::endl << "------------------------------------------" << std::endl << COLORS.RESET << std::endl;
        }
      break;
    }
  }
};


