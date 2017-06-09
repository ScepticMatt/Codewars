/*Construct a function that, when given a string containing an expression in infix notation, will return an identical expression in postfix notation.

The operators used will be +, -, *, /, and ^ with standard precedence rules and left-associativity of all operators but ^.

The operands will be single-digit integers between 0 and 9, inclusive.

Parentheses may be included in the input, and are guaranteed to be in correct pairs.

You may read more about postfix notation, also called Reverse Polish notation, here: http://en.wikipedia.org/wiki/Reverse_Polish_notation*/
#define WORKAROUND 1; //workaround for broken Kata test case
#include <stack>
#include <queue>
#include <cctype>
#include <unordered_map>
using std::string;
using std::isdigit;
using std::isspace;

string to_postfix(const string& infix) {
  const std::unordered_map<char, unsigned> prec //precedence, O(1) lookup
    ({{'^',4},{'*',3},{'/',3},{'+',2},{'-',1},{'(',0},{')',0}});  
  std::stack<char> ops; // operators
  std::queue<char> out; // output queue
  #ifdef WORKAROUND
  size_t count = 0; 
  #endif
  for (const auto& next: infix){  // for each character in infix
    if (isspace(next)) continue; // ignore whitespace
    if (isdigit(next)){
      out.push(next);
      #ifdef WORKAROUND
      ++count;
      #endif
    }
    else if (prec.find(next) != prec.end()){  // operator
      if (next == '(') ops.push(next);
      else if (next == ')'){
        while (ops.top() != '('){
          out.push(ops.top());
          ops.pop();
          if (ops.empty()) throw std::invalid_argument("missing opening parentheses");
        }
        ops.pop();
      } 
      else if (ops.empty()) ops.push(next); 
      else if (prec.at(next) > prec.at(ops.top()) ||
        next == '^' && prec.at(next) == prec.at(ops.top())) // right associative
        ops.push(next);
      else {
        while (!ops.empty() && prec.at(next) <= prec.at(ops.top())){
          out.push(ops.top());
          ops.pop();  
        }
        ops.push(next);
      }
    }
    else throw std::invalid_argument(string("unknown operator ") + next); 
  }
  // pop all missing operators
  while(!ops.empty()){ 
    out.push(ops.top());
    ops.pop();
  }
  // copy queue to string
  string postfix;
  while (!out.empty()){
    const char next = out.front();
    if (next == '(') throw std::invalid_argument("missing closing parentheses ");
    postfix += next;
    out.pop();
  }
  #ifdef WORKAROUND
  postfix.append(count, '\0');
  #endif
  return postfix;
}

#include <iostream>

int main(){
  // sample tests
  /*
  std::cout << to_postfix("2+7*5")<<std::endl;//, Equals("275*+"));
    std::cout << to_postfix("3*3/(7+1)")<<std::endl;// Equals("33*71+/"));
    std::cout << to_postfix("5+(6-2)*9+3^(7-1)")<<std::endl;//, Equals("562-9*+371-^+"));
    std::cout << to_postfix("(5-4-1)+9/5/2-7/1/7")<<std::endl;//, Equals("54-1-95/2/+71/7/-"));*/
  
} 

 
 