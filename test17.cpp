/*Your school has hired you to keep track of the score at baseball games. Unfortunately you tend to be rather absent minded because most nights you stay up late playing video games and coding. Let's create a program that will keep track of the score for us.

We'll need to create a constructor ScoreCard that has two public functions: addEntry and getScore.

addEntry - Takes in the result of an at-bat. This result can be single, double, triple, homerun, or out.

getScore - Returns the score in the format Home: [HOME_SCORE] Away: [AWAY_SCORE]

To keep things simple, base runners will advance the amount of bases equal to that of the batter's hit (i.e. if the batter hits a double, each base-runner will advance two bases).

A few important baseball rules:

The Away team bats first.
There are three outs in an inning.
After three outs the opposing team hits.
The hits single, double, triple and homerun correspond to the batter reaching bases first, second, third and home respectively.
Base runners start at home and then cycle through the bases first, second, third and home.
Runners score for their team after they reach home.
For more information on baseball visit here: http://en.wikipedia.org/wiki/Baseball*/

// start of unique code
// using namespace std; //Bad style. I'd rather not add std to global namespace
#include <bitset>
#include <stdexcept>
using std::string;


class ScoreCard 
{
public:
  ScoreCard():
    homeBatting(false), hasEnded(false), 
    HOME_SCORE(0), AWAY_SCORE(0),
    outCount(0), currentInning(1){}
  /*
  * A public method accepting the result of an at-bat
  * @param {string} entry - The result of an at-bat 
  * Acceptable values: ('single', 'double', 'triple', 'homerun' or 'out') 
  */
  void addEntry(string entry);
  /*
  * A public method returning the current score
  * Format: "Home: [HOME_SCORE] Away: [AWAY_SCORE]"
  */
  string getScore();
private:
  std::bitset<8> bases;
  constexpr static unsigned NUM_INNINGS = 9;
  bool homeBatting, hasEnded;
  unsigned outCount, currentInning;
  unsigned HOME_SCORE, AWAY_SCORE;
  void nextTurn();  // Prepare for next turn. Switch teams, reset bases and outs.
  void nextInning();  // next inning. Check for win condition
  void score();     // update score after current at-bat
};
string ScoreCard::getScore(){
  return string("Home: ") 
    + std::to_string(HOME_SCORE) 
    + " Away: "
    + std::to_string(AWAY_SCORE);
}
void ScoreCard::addEntry(string entry){
  if (hasEnded) throw std::invalid_argument("Game has already ended");
  if(entry == "single"){
    bases <<= 1;
    bases.set(1);
  }
  else if (entry == "double"){
    bases <<= 2;
    bases.set(2);
  }
  else if (entry == "triple"){
    bases <<= 3;
    bases.set(3);
  }
  else if (entry == "homerun"){
    bases <<= 4;
    bases.set(4);
  }
  else if (entry == "out"){
    ++outCount;
    if (outCount == 3){   // next turn
      nextTurn();
      return;
    }
  }
  else throw std::invalid_argument("invalid at-bat result");
  score();
}
void ScoreCard::score(){
  constexpr std::bitset<8> outBits = 0xF0;          // players that have scored
  const unsigned points = (bases & outBits).count();  // number of players that have scored
  if (homeBatting) HOME_SCORE += points;
  else AWAY_SCORE += points;
  bases &= ~outBits;  // remove scored players from field;
}
void ScoreCard::nextTurn(){
  bases = 0;            // reset bases
  outCount = 0;         // reset out count
  homeBatting ^= true;  // switch fielding team
  if (!homeBatting) nextInning(); // if away team is batting next
}
void ScoreCard::nextInning(){
  currentInning += 1; 
  if (currentInning > NUM_INNINGS && // more than the specified innings
    HOME_SCORE != AWAY_SCORE) // not a draw
    hasEnded = true;  // game over
}
// test
#include <iostream>

int main(){
  ScoreCard sc;
  sc.addEntry("single");
  sc.addEntry("single");
  sc.addEntry("single");
  sc.addEntry("single");
  sc.addEntry("double");
  sc.addEntry("double");
  sc.addEntry("double");
  sc.addEntry("homerun");
  /*for (auto i = 0; i<100; ++i){
    try{sc.addEntry("out");}
    catch(...){
      std::cout << sc.getScore();
    }
  }*/
  std::bitset<7> test = 0x74;
  //test<<=4;
  std::cout << test;
  
}