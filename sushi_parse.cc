#include "Sushi.hh"

std::string *Sushi::unquote_and_dup(const char* s){
//Create a empty string* connect to the new string to store the result in
  std::string* result = new std::string();

  for (size_t i = 0; s[i] != '\0'; i++){
	if (s[i] == '\\' && s[i+1] != '\0') {
		char next = s[i+1];
		switch(next) {
			case 'a':
			*result += '\a';
			case 'b':
			*result += '\b';
			case 'e':
			*result += '\e';
			case 'f':
                        *result += '\f';
                        case 'n':
                        *result += '\n';
                        case 'r':
                        *result +='\r';
			case 't':
                        *result += '\t';
                        case 'v':
                        *result += '\v';
                        case '\\': //Might be wrong
                        *result += '\\';
			case '\'': //Might be wrong
                        *result += '\'';
                        case '\"': //Might be wrong
                        *result += '\"';
			default:
			*result += s[i];
		}
	}
	else *result += s[i];
  }
  return result;
}

void Sushi::re_parse(int i) {
  if (i == 0 || i > history.size()) {
	std::cerr << "Error: !"<< history[i] <<": event not found" << std::endl;
	return;
  }
  std::string i_command = history[history.size() - i];
  int result_of_parse_command = parse_command(i_command);
  if (result_of_parse_command != 0) {
	history.emplace_back(history[history.size() - i]);
  }
}

//---------------------------------------------------------------
// Do not modify this function YET
std::string *Sushi::getenv(const char* s) 
{
  return new std::string(s); // Must be changed - eventually
}

//---------------------------------------------------------------
// Do not modify this function
void yyerror(const char* s) {
  std::cerr << "Parse error: " << s << std::endl;
}

