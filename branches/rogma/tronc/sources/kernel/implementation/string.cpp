
#include <kernel/string.h>

std::string toString(const int& _i) 
{
  std::stringstream ss;
  std::string str;
  ss << _i;
  ss >> str;
  return str ;  
}