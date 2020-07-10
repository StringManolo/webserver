struct HTTP {
      std::string method = "";
      std::string path = "";
      std::string version = "";

      std::vector<std::string> headers;
      std::string body = "";
      int headersEnd = 0;
};

struct HTTP_PARSER {
  HTTP http;
  void parser(std::vector<char> buffer, struct HTTP &http) {
    std::vector<std::string> tmpVec, strings;
    std::string tmpString;
    for(int i = 0, j = 0; i < buffer.size(); ++i) {
      if(buffer[i] == '\n' || (buffer[i] == '\0' && buffer[i+1] != '\0')) {
        /* Debug/raw */ 
	tmpVec.push_back(tmpString);

	tmpString = "";
	++j;
      }
      tmpString += buffer[i];
    } 


    for(int k = 0; k < tmpVec.size(); ++k) {
      for(int l = 0; l < tmpVec[k].size(); ++l) {
        if(static_cast<char>(tmpVec[k][l]) == '\r') {
      /*  console.log(true, "Encontrado r", WARNING); */
          tmpVec[k][l] = '\0';
	} if (static_cast<char>(tmpVec[k][l]) == '\n') {
      /* console.log(true, "Encontrado n", WARNING); */
          tmpVec[k][l] = '\0';
	}
      }

      if (k == 0) {

	utils.split(tmpVec[k], ' ', strings);
	http.method = strings[0];
	http.path = strings[1];
	http.version = strings[2];

      }

      if (k > 0) {
	
        /* End of headers */
        if (tmpVec[k].size() == 2) {

	  /* Set only once */
	  if (http.headersEnd == 0) {
            http.headersEnd = k;
	  }
	}

	if (http.headersEnd == 0) {
          http.headers.push_back(tmpVec[k]);
	} else {
          http.body += tmpVec[k];
	}
	
      }

     /* std::cout << "HEADER:" << tmpVec[k] << std::endl << std::endl; */
    }

/*
    std::cout << "Method: " << http.method << std::endl;
    std::cout << "Path: " << http.path << std::endl;
    std::cout << "Version: " << http.version << std::endl;
*/

/*    for (int i = 0; i < http.headers.size(); ++i) {
 std::cout << "Header" << i+1 << ":"
        << http.headers[i] << std::endl;
    }

    std::cout << "Body: " << http.body << std::endl;
*/
  }
  
};
