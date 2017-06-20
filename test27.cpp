/*You are given a string of n lines, each substring being n characters long: For example:

s = "abcd\nefgh\nijkl\nmnop"

We will study some transformations of this square of strings.

Symmetry with respect to the main cross diagonal: diag_2_sym (or diag2Sym or diag-2-sym)
diag_2_sym(s) => "plhd\nokgc\nnjfb\nmiea"
Counterclockwise rotation 90 degrees: rot_90_counter (or rot90Counter or rot-90-counter)
rot_90_counter(s)=> "dhlp\ncgko\nbfjn\naeim"
selfie_diag2_counterclock (or selfieDiag2Counterclock or selfie-diag2-counterclock) It is initial string + string obtained by symmetry with respect to the main cross diagonal + counterclockwise rotation 90 degrees .
s = "abcd\nefgh\nijkl\nmnop" --> 
"abcd|plhd|dhlp\nefgh|okgc|cgko\nijkl|njfb|bfjn\nmnop|miea|aeim"
or printed for the last:
selfie_diag2_counterclock
abcd|plhd|dhlp
efgh|okgc|cgko
ijkl|njfb|bfjn
mnop|miea|aeim
#Task:

Write these functions diag_2_sym, rot_90_counter, selfie_diag2_counterclock
and

high-order function oper(fct, s) where

fct is the function of one variable f to apply to the string s (fct will be one of diag_2_sym, rot_90_counter, selfie_diag2_counterclock)
#Examples:

s = "abcd\nefgh\nijkl\nmnop"
oper(diag_2_sym, s) => "plhd\nokgc\nnjfb\nmiea"
oper(rot_90_counter, s) => "dhlp\ncgko\nbfjn\naeim"
oper(selfie_diag2_counterclock, s) => "abcd|plhd|dhlp\nefgh|okgc|cgko\nijkl|njfb|bfjn\nmnop|miea|aeim"
Notes:

The form of the parameter fct in oper changes according to the language. You can see each form according to the language in "Your test cases".
It could be easier to take these katas from number (I) to number (IV)*/

#include <string>
#include <algorithm>

class Opstrings4
{
public:
	static std::string diag2Sym(const std::string &strng);
	static std::string rot90Counter(const std::string &strng);
	static std::string selfieDiag2Counterclock(const std::string &strng);
	// your function oper...
	static std::string oper(decltype(diag2Sym) func, const std::string &s){
		return func(s);
	}
};
std::string Opstrings4::diag2Sym(const std::string &strng){
	const size_t n = std::count(strng.cbegin(), strng.cend(), '\n') + 1;
	std::string output(strng.length(),'\n');
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			output[(n+1)*i+j] = strng[(n+1)*(n-1-j)+(n-1-i)];
	return output;
}
std::string Opstrings4::rot90Counter(const std::string &strng){
	const size_t n = std::count(strng.cbegin(), strng.cend(), '\n') + 1;
	std::string output(strng.length(),'\n');
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			output[(n+1)*i+j] = strng[(n+1)*j+(n-1-i)];
	return output;		
}
std::string Opstrings4::selfieDiag2Counterclock(const std::string &strng){
	const size_t n = std::count(strng.cbegin(), strng.cend(), '\n') + 1;
	size_t columns = 3*(n+1);
	std::string output(n*columns-1,'\n');
	for (size_t i = 0; i < n; ++i){
		for (size_t j = 0; j < n; ++j)
			output[columns*i+j] = strng[(n+1)*i+j];
		output[columns*i+n] = '|';
		for (size_t j = 0; j < n; ++j)
			output[columns*i+j+(n+1)] = strng[(n+1)*(n-1-j)+(n-1-i)];
		output[columns*i+2*n+1] = '|';
		for (size_t j = 0; j < n; ++j)
			output[columns*i+j+2*(n+1)]= strng[(n+1)*j+(n-1-i)];
	}
	return output;
}

// test
#include <iostream>
int main(){

	std::string s = "abcd\nefgh\nijkl\nmnop";
	//std::cout << s << std::endl;
	//std::cout << Opstrings4::diag2Sym(s) << std::endl;
	//std::cout << Opstrings4::rot90Counter(s) << std::endl;
	//std::cout << Opstrings4::selfieDiag2Counterclock(s) << std::endl;
	std::cout << Opstrings4::oper(Opstrings4::selfieDiag2Counterclock,s);
}