/*You need to write a password generator that meets the following criteria:

6 - 20 characters long
contains at least one lowercase letter
contains at least one uppercase letter
contains at least one number
contains only alphanumeric characters (no special characters)
Return the random password as a string.

Note: "randomness" is checked by counting the characters used in the generated passwords - all characters should have less than 50% occurance. Based on extensive tests, the normal rate is around 35%.*/


#include <string>
#include <random>   // random_device, mt19937, distributions
#include <chrono>   // time seed
struct ValidPassword{
    bool hasUpper = false;
    bool hasLower = false;
    bool hasNumber = false;
    bool operator()(){ return hasUpper && hasLower && hasNumber;}
};
char mapncheck(int ch,  ValidPassword& checks){
    // map (0-61) to 48-57, 65-90 and 97-120
    if (ch < 10) ch+=48, checks.hasNumber = true;       //0-9
    else if (ch < 36) ch+=55, checks.hasUpper = true;   //A-Z
    else ch+=61, checks.hasLower = true;                //a-z
    return static_cast<char>(ch);
}
std::string password_gen() {
    constexpr unsigned MAX_LNG = 20U;   // minimum password length as defined in exercise
    constexpr unsigned MIN_LNG = 6U;    // maximum password length as defined in exercise
    // if non-deterministic random has entropy left, use it
    // otherwise, use backup mersenne-twister engine
    std::random_device rd;
    // use system time in nanoseconds as backup seed
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    // backup mersenne twister engine, used if rd has no entropy left
    std::mt19937 mt(rd.entropy()?rd():seed);
    // distributions for length and characters
    std::uniform_int_distribution<unsigned> lengths(MIN_LNG,MAX_LNG);
    std::uniform_int_distribution<char> printables(0, 61);  // amount of alphanumeric characters
    
    while(true){
        const unsigned length = rd.entropy()?lengths(rd):lengths(mt);
        std::string candidate;
        candidate.reserve(length);
        ValidPassword checks;
        // generate password
        for (int i=0; i<length; ++i){
            int ch = (rd.entropy()?printables(rd):printables(mt));  // generate character
            candidate += mapncheck(ch, checks);
        }
        // return password if it meets requirements, otherwise generate new one
        if (checks()) return candidate;
    }
}

#include <iostream>
int main(){
    std::cout << password_gen();
    return 0;
}