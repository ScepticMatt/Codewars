/*For encrypting strings this region of chars is given (in this order!):

all letters (ascending, first all UpperCase, then all LowerCase)
all digits (ascending)
the following chars: ".,:;-?! '()$%&" and the '"'-char
These are 77 chars! (This region is zero-based.)

Write two methods: 

std::string encrypt(std::string text)
std::string decrypt(std::string text)
Prechecks:

If the input-string has chars, that are not in the region, throw an Exception(C#, Python) or Error(JavaScript).
If the input-string is null or empty return exactly this value!
For building the encrypted string:

For every second char do a switch of the case.
For every char take the index from the region. Take the difference from the region-index of the char before (from the input text! Not from the fresh encrypted char before!). (Char2 = Char1-Char2)
Replace the original char by the char of the difference-value from the region. In this step the first letter of the text is unchanged.
Replace the first char by the mirror in the given region. ('A' -> '"', 'B' -> '&', ...)
Simple example:

Input: "Business"
Step 1: "BUsInEsS"
Step 2: "B61kujla"
B -> U
B (1) - U (20) = -19
-19 + 77 = 58
Region[58] = "6"
U -> s
U (20) - s (44) = -24
-24 + 77 = 53
Region[53] = "1"
Step 3: "&61kujla"
This kata is part of the Simple Encryption Series:
Simple Encryption #1 - Alternating Split
Simple Encryption #2 - Index-Difference
Simple Encryption #3 - Turn The Bits Around
Simple Encryption #4 - Qwerty

*/
#include <stdexcept>
#include <cctype>
class Kata
{
public:
    std::string encrypt(std::string text)
    {
    //prechecks: 
        if (text.empty()) return text; // return empty text 
        for (const auto& c: text) // only certain characters allowed
            if (region.find(c) == std::string::npos)
                throw std::invalid_argument(std::string("character ") + c + " not allowed");
    // encryption:
        // 1) switch case of every second character
        for (size_t i=1; i<text.length(); i+=2)
            text[i]= isalpha(text[i]) ? text[i]^32 : text[i];
        // 2) Take the difference from the region-index of the char before 
        //  Replace the original char by the char of the difference-value from the region. 
        std::string encrypted;
        encrypted.resize(text.length());
        for (size_t i=1; i!=text.length(); ++i){
            const auto diff= (77+region.find(text[i-1])-region.find(text[i]))%77;
            encrypted[i]= region[diff];
        }
        // 3) Replace the first char by the mirror in the given region.
        encrypted[0]= region[76-region.find(text[0])];
        return encrypted;
    }
  
    std::string decrypt(std::string encryptedText)
    {
        // same steps as encryption in reverse
        if (encryptedText.empty()) return encryptedText;
        for (const auto& c: encryptedText)
            if (region.find(c) == std::string::npos)
                throw std::invalid_argument(std::string("character ") + c + " not allowed");
        encryptedText[0]= region[76-region.find(encryptedText[0])]; 
        for (size_t i=1; i!=encryptedText.length(); ++i){
            const auto undiff= (77+region.find(encryptedText[i-1])-region.find(encryptedText[i]))%77;
            encryptedText[i]= region[undiff];
        }
        for (size_t i=1; i<encryptedText.length(); i+=2)
            encryptedText[i]= isalpha(encryptedText[i])? encryptedText[i]^32: encryptedText[i];
        return encryptedText;
    }
private:
    const std::string region= "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789" ".,:;-?! '()$%&\"";
};

#include <iostream> // test
int main(){
    Kata kata;
    std::cout << kata.region;
    //std::cout << kata.encrypt("Business") << std::endl;
    //std::cout << kata.decrypt("&61kujla") << std::endl;
    //std::cout << kata.encrypt("This is a test") << std::endl;// should be 5MyQa9p0riYplZc
}