/*General Patron is faced with a problem , his intelligence has intercepted some secret messages from the enemy but they are all encrypted. Those messages are crucial to getting the jump on the enemy and winning the war. Luckily intelligence also captured an encoding device as well. However even the smartest programmers weren't able to crack it though. So the general is asking you , his most odd but brilliant programmer.

You can call the encoder like this.

std::cout << Encoder::encode("Hello World!");
Our cryptoanalysts kept poking at it and found some interesting patterns.

std::cout << (Encoder::encode ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")) << "\n" ;
std::cout << (Encoder::encode ("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb")) << "\n" ;  
std::cout << (Encoder::encode ("!@#$%^&*()_+-")) << "\n" ;
std::string a, b, c;
for (const auto& w : std::string("abcdefghijklmnopqrstuvwxyz")) {
    a += Encoder::encode (std::string(  "") + w)[0];
    b += Encoder::encode (std::string( "_") + w)[1];
    c += Encoder::encode (std::string("__") + w)[2];
}
std::cout << a << "\n";
std::cout << b << "\n";
std::cout << c << "\n";
We think if you keep on this trail you should be able to crack the code! You are expected to fill in the

std::string Decoder::decode(const std::string&)
function. Good luck ! General Patron is counting on you!*/
#include <algorithm>
#include <array>
#include <mutex>
#include <string>
using std::string;
using std::array;
struct Encoder{
    static string encode(string text){return "";};  // dummy, does nothing 
};


struct Decoder {

private:
  static array<array<char,66>,66> rainbowtable;
  const static string sequence;
  static void generate_rainbowtable(){
    string empties;
    empties.reserve(66);
    for (size_t i =0; i != 66; ++i,empties+='_')
      for (size_t j=0; j != 66;++j)
        rainbowtable[i][j] = Encoder::encode(empties + sequence[j])[i]; //C++17: use string_view instead of char array
  }

public:
  static string decode (const string& p_what) {  
    std::once_flag hasTable;
    std::call_once(hasTable, generate_rainbowtable);
    string decoded;
    decoded.reserve(p_what.length());
    for (size_t i=0; i != p_what.length(); ++i){
      const auto pos = std::find(rainbowtable[i%66].cbegin(), rainbowtable[i%66].cend(), p_what[i]);
      if (pos == rainbowtable[i%66].cend()) decoded += p_what[i];
      else decoded+=sequence[pos-rainbowtable[i%66].cbegin()];
    }
    return decoded;
  }
};
const string Decoder::sequence = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,? ";
array<array<char,66>,66> Decoder::rainbowtable{};

// test
int main(){
  Decoder::decode("");  
}