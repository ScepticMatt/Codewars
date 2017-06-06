#include <unordered_set>
#include <string>
#include <cctype>
size_t duplicateCount(const std::string& in); // helper for tests

size_t duplicateCount(const char* in)
{
    std::unordered_set<char> found, found_twice;
    while (*in != '\0'){
      if (found.find(tolower(*in)) == found.end())
        found.insert(tolower(*in));        // set of characters found once
      else
        found_twice.insert(tolower(*in));  // set of characters found twice or more
      ++in;
    }
    return found_twice.size();
}

#include <iostream>
int main(){
  std::cout << duplicateCount("aabbcde") << std::endl;

        std::cout << duplicateCount(" ");//, Equals(0));
        std::cout << duplicateCount("");//, Equals(0));
        std::cout << duplicateCount("asdfghjkl;'\\");//, Equals(0));
        std::cout << duplicateCount("asdfghjkl;'\\'");//, Equals(1));
        std::cout << duplicateCount("aabbcde");//, Equals(2));
        std::cout << duplicateCount("aabBcde");//, Equals(2));
        std::cout << duplicateCount("Indivisibility");//, Equals(1));
        std::cout << duplicateCount("Indivisibilities");//, Equals(2));
}