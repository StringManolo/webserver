#pragma once

#include <limits.h>
#include <iostream>

struct DIRECTORIES {
  std::string pwd = realpath("./", NULL);
/*std::string pwd2 = getenv("PWD"); */
};

