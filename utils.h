#include <string>
#include <vector>

struct UTILS {
  void split(std::string str, char character, std::vector<std::string> &strings) {
    std::string holder = "";
  
    str += " ";
    for (int i = 0; i < str.length(); ++i) {
      if (str[i] != character) {
        holder += str[i];
        std::cout << "Found " << str[i] << std::endl;
      } else {
        std::cout << "Found space" << std::endl;
        strings.push_back(holder);
        holder = "";
      }
    }
  }

  /* More functions to export here */





};
