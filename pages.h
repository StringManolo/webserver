#pragma once
#include <string>
#include <vector>

struct HTMLTEMPLATE {
  std::string makeTemplate(std::vector<std::string> conf) {
    std::string web = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>";
    web += conf[0];
    web += "</title></head><body style=\"text-align:center\"><h1 style=\"display:inline\">";
    web += conf[1];
    web += "</h1><br /><p style=\"display:inline\"><h3>";
    web += conf[2];
    web += "</h3></p></body></html>";
    return web;
  }
}; HTMLTEMPLATE ht;


struct PAGES {

  struct ERROR {
    /* 200 */
    std::vector<std::string> twoZeroZeroV {"200 - Congratz", "200","Your server is working fine."};                     std::string twoZeroZero = ht.makeTemplate(twoZeroZeroV);


    /* 400 */                                                  std::vector<std::string> fourZeroZeroV {"400 - Bad Request", "400", "The request is not valid."};
    std::string fourZeroZero = ht.makeTemplate(fourZeroZeroV);


    /* 401 */
    std::vector<std::string> fourZeroOneV {"401 - Not authorization", "401", "Lack of authorization."};
    std::string fourZeroOne = ht.makeTemplate(fourZeroOneV);

    /* 403 */
    std::vector<std::string> fourZeroThreeV {"403 - Forbidden", "403", "You're not allowed."};
    std::string fourZeroThree = ht.makeTemplate(fourZeroThreeV);

    /* 404 */
    std::vector<std::string> fourZeroFourV {"404 - Page Not Found", "404", "The requested resource was not found."}; 
    std::string fourZeroFour = ht.makeTemplate(fourZeroFourV);

    /* 500 */
    std::vector<std::string> fiveZeroZeroV {"500 - Internal Server Error", "500", "The server has an error."};
    std::string fiveZeroZero = ht.makeTemplate(fiveZeroZeroV);

    /* 503 */
    std::vector<std::string> fiveZeroThreeV {"503 - Service Unavailable", "503", "The server is under maintenance."};
    std::string fiveZeroThree = ht.makeTemplate(fiveZeroThreeV);
  }; ERROR error;


};
