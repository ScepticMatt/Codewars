/*Inspired from real-world Brainf**k, we want to create an interpreter of that language which will support the following instructions (the machine memory or 'data' should behave like a potentially infinite array of bytes, initialized to 0):

> increment the data pointer (to point to the next cell to the right).
< decrement the data pointer (to point to the next cell to the left).
+ increment (increase by one, truncate overflow: 255 + 1 = 0) the byte at the data pointer.
- decrement (decrease by one, treat as unsigned byte: 0 - 1 = 255 ) the byte at the data pointer.
. output the byte at the data pointer.
, accept one byte of input, storing its value in the byte at the data pointer.
[ if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
] if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.
The function will take in input...

the program code, a string with the sequence of machine instructions,
the program input, a string, eventually empty, that will be interpreted as an array of bytes using each character's ASCII code and will be consumed by the , instruction
... and will return ...

the output of the interpreted code (always as a string), produced by the . instruction.*/
#include <string>
#include <array>
#include <climits>

std::string brainLuck(std::string code, std::string input)
{
  if (CHAR_BIT != 8) throw std::domain_error(
    "not supported on systems where a byte is not 8 bits");
  std::string output;
  std::array<unsigned char, 255> data{};
  unsigned char mar;  // memory address register
  auto in = input.begin();
  size_t missing;
  for (auto it = code.cbegin(); it!=code.cend(); ++it){
    switch(*it){
      case '>': ++mar; break;
      case '<': --mar; break;
      case '+': ++data[mar]; break;
      case '-': --data[mar]; break;
      case '.': output+=data[mar]; break;
      case ',': data[mar]= *in++; break;
      case '[': 
        if (!data[mar]){
          missing = 1;
          while(missing){
            switch(*++it){
              case '[': ++missing; break;
              case ']': --missing; break;
            }
          }
        }
        break;
      case ']': 
        if (data[mar]){
          missing = 1;
          while(missing){
            switch(*--it){
              case ']': ++missing; break;
              case '[': --missing; break;
            }
          }
          
        }
        break; 
    }
  }
  return output;
}


// test
#include <iostream>
#include <chrono>

int main(){
  
  /*std::string tw = "codewars";
  tw.append(1,(char)255);
  std::cout << brainLuck(",+[-.,+]",tw) << std::endl;*/
  using namespace std::chrono;
  auto t1 = high_resolution_clock::now();
  for (auto i = 1; i< 10000; ++i){
    std::string mw = "codewars";
    mw.append(1,(char)0);
    brainLuck(",[.[-],]",mw);
  }
  auto t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << time_span.count() << " seconds." << std::endl;
}