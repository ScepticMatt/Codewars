/*
These are 64 chars! (This region is zero-based.)
So, every char from this region has 6 bits!

Write two methods: 

std::string encrypt(std::string text)
std::string decrypt(std::string encryptedText)
Prechecks:

1. If the input-string (for both methods!) has chars, that are not in the region, 
   throw an Exception(C#, C++, Python) or Error(JavaScript).
2. If the input-string is null or empty return exactly this value!
For building the encrypted string:
For every char use these rules:

1. Change the fifth bit of the char and the first bit of the next char. (C1.5 <==> C2.1, only if there is a next char!)
2. Inverse the second and the forth bit of the char.           (2,4 => 0->1 or 1->0)
3. Change the first 3 bit against the last 3 bit of the char.  (1,2,3 <==> 4,5,6)
4. Change every odd bit against the following bit of the char. (1 <==> 2, 3 <==> 4, 5 <==> 6)
5. Reverse the whole line of bits of the char.
6. Change the first against the third bit of the char.         (1 <==> 3)
Of course every rule takes the changed char from the previous rule.
The position of a bit starts from the beginning and not from the end! (So maybe in different order as you thought! See the example.)

Example for the first rule for "B9":

pos: 1 2 3 4 5 6 
B -> 0 0 0 0 0 1
9 -> 1 1 1 1 0 1
Change pos 5 from "B" against pos 1 from "9".
 ->  0 0 0 0 1 1 
 ->  0 1 1 1 0 1*/

#include <bitset>
#include <cctype>
#include <stdexcept>

#include <iterator>
void swap(std::bitset<6>::reference left, std::bitset<6>::reference right){
	const bool temp = left;	// inplicit conversion
	left =  static_cast<bool>(right);
	right = temp;
}
std::bitset<6> bits(char c){
	if (c >= 'A' && c <= 'Z')		// a(97)-z(122)
		return std::bitset<6>(c-'A');
	else if (c >= 'a' && c <= 'z')	// A(65)-Z(90)	
		return std::bitset<6>(c-'a' + 26);
	else if (c >= '0' && c <= '9')
		return std::bitset<6>(c-'0' + 52);
	else if (c == ' ') return std::bitset<6>(62);
	else if (c == '.') return std::bitset<6>(63);
	else throw std::invalid_argument("");
}
char chars(const std::bitset<6>& input){
	const unsigned long value = input.to_ulong();
	if (value < 26) return 'A' + value;
	else if (value < 52) return 'a' + (value-26);
	else if (value < 62) return '0' + (value-52);
	else if (value == 62) return ' ';
	else if (value == 63) return '.';
	else throw std::invalid_argument("");
}

std::string encrypt(std::string text){
	using std::next;
	if (text.empty()) return "";
	// do the steps in order
	for (auto it = text.begin(); it != text.end(); ++it){
		auto first =  bits(*it);
		if (std::next(it) != text.end()){
			auto second = bits(*std::next(it));
			swap(first[6-5],second[6-1]);	//1.
			*std::next(it) = chars(second);
		}
		first[6-2].flip();	// 2.
		first[6-4].flip();	// 2.
		swap(first[6-1],first[6-4]);	// 3.
		swap(first[6-2],first[6-5]);	// 3.
		swap(first[6-3],first[6-6]);	// 3.
		swap(first[6-1],first[6-2]);	// 4.
		swap(first[6-3],first[6-4]);	// 4.
		swap(first[6-5],first[6-6]);	// 4.
		for (auto i = 0; i != 3; ++i)
			swap(first[i],first[5-i]);	// 5.
		swap(first[6-1],first[6-3]);	// 6.
		*it = chars(first);
  }
  return text;
}
std::string decrypt(std::string encryptedText){
  if (encryptedText.empty()) return "";
  	using std::next;
	if (encryptedText.empty()) return "";
	// do the steps in reverse
	for (auto it = encryptedText.rbegin(); it != encryptedText.rend(); ++it){
		
		//std::cout << *it << std::endl;

		auto first = bits(*it);
		swap(first[6-1],first[6-3]);	// 6.
		for (auto i = 0; i != 3; ++i)
			swap(first[i],first[5-i]);	// 5.
		swap(first[6-5],first[6-6]);	// 4.	
		swap(first[6-3],first[6-4]);	// 4.
		swap(first[6-1],first[6-2]);	// 4.
		swap(first[6-3],first[6-6]);	// 3.
		swap(first[6-2],first[6-5]);	// 3.	
		swap(first[6-1],first[6-4]);	// 3.
		first[6-4].flip();	// 2.
		first[6-2].flip();	// 2.
		if (it != encryptedText.rbegin()){
			auto second = bits(*std::prev(it));
			swap(first[6-5],second[6-1]);	//1.
			*std::prev(it) = chars(second);
		}
		*it = chars(first);
  }
  return encryptedText;
}

// tests
#include <iostream>
int main(){
	//std::cout << chars(std::bitset<6>("011101")) << std::endl;
	//std::cout << encrypt("B9") << std::endl;	//Dd after first step?

	std::cout << decrypt(encrypt("Hello World"));
	/*std::bitset<3> test1(3);
	std::cout << test1 << " ";
	swap(test1[1], test1[2]);
	std::cout << test1;*/

	//std::cout << first << std::endl;
	//std::cout << second << std::endl;
}