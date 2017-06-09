/*A famous casino is suddenly faced with a sharp decline of their revenues. They decide to offer Texas hold'em also online. Can you help them by writing an algorithm that can rank poker hands?

Task:

Create a poker hand that has a method to compare itself to another poker hand:
    Result compare (const PokerHand &player, const PokerHand &opponent);
A poker hand has a constructor that accepts a string containing 5 cards:
    PokerHand hand ("KS 2H 5C JD TD");
The characteristics of the string of cards are:
A space is used as card seperator
Each card consists of two characters
The first character is the value of the card, valid characters are: 
2, 3, 4, 5, 6, 7, 8, 9, T(en), J(ack), Q(ueen), K(ing), A(ce)
The second character represents the suit, valid characters are: 
S(pades), H(earts), D(iamonds), C(lubs)

The result of your poker hand compare can be one of these 3 options:
    enum class Result { Win, Loss, Tie };
Apply the Texas Hold'em rules for ranking the cards.
There is no ranking for the suits.*/
#include <cstring>
#include <array>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <set>	
#include <algorithm>
#include <functional>
#include <iostream>


using suit = char;
using rank = unsigned;
using card = std::pair<rank, suit>;
const std::unordered_map<char,rank> ranks{
 		{'2',2},{'3',3},{'4',4},{'5',5},{'6',6},{'7',7},{'8',8},{'9',9},
 		{'T',10},{'J',11},{'Q',12},{'K',13},{'A',14}
 };
const std::unordered_set<suit> suits{'S','H','D','C'};

struct PokerHand {
	
  PokerHand (const char* pokerhand){
  	if (strlen(pokerhand) != 14) throw std::invalid_argument("not 5 cards");
  	for (auto i = 0; i< 5; ++i){
  		const auto cardRank = ranks.find(pokerhand[3*i]);
  		if (cardRank == ranks.end()) throw std::invalid_argument("invalid rank");
  		const auto cardSuit = suits.find(pokerhand[3*i+1]);
  		if (cardSuit == suits.end()) throw std::invalid_argument("invalid suit");
  		auto newCard = std::make_pair(cardRank->second, *cardSuit);
  		// test case generates cheating hands, have to allow duplicate cards
  		//if (cards.find(newCard) == cards.end())
				cards.insert(newCard);
			//else throw std::invalid_argument("duplicate card");
  	}
  }
  PokerHand(const std::array<card,5> _cards){
  	for (const auto& nextCard: _cards)
  		cards.insert(nextCard);
  }
  PokerHand operator=(const PokerHand& obj) = delete;

	//std::set<card,std::greater<card>> cards;	//sorted by highest rank
	std::multiset<card,std::greater<card>> cards;	//workaround allowing duplicate cards
};

rank highestRank(const PokerHand& player){ return player.cards.begin()->first;}
template<class ForwardIt, class BinaryPredicate>
bool adjacent_compare(ForwardIt first, ForwardIt last, BinaryPredicate p){
    ForwardIt next = first;
    for (++next; next != last; ++first, ++next)
        if (!p(*first, *next)) return false;
    return true;
}
std::array<rank,1> straight(PokerHand hand){
	auto sequential = [](card current, card next){return current.first == next.first+1;};
	auto isStraight = adjacent_compare(hand.cards.begin(),hand.cards.end(),sequential);
	// check low ace straight
	auto firstCard = hand.cards.cbegin();
	if (!isStraight && firstCard->first == 14){
		// workaround for cheating duplicate test
		//std::set<card,std::greater<card>> lowAceHand(++firstCard,hand.cards.cend());
		std::multiset<card,std::greater<card>> lowAceHand(++firstCard,hand.cards.cend());
		lowAceHand.insert(std::make_pair(1,'S'));
		isStraight = adjacent_compare(lowAceHand.begin(),lowAceHand.end(),sequential);
		return {(isStraight)?5u:0u};
	}
	return {(isStraight)?highestRank(hand):0u};
}
bool isFlush(const PokerHand& hand){
	auto suitOfFirst = hand.cards.begin()->second;
	for (const auto& nextCard: hand.cards)
		if (nextCard.second != suitOfFirst) return false;
	return true;
}
std::array<rank,1> straightFlush(std::array<rank,1> straightRank, bool isFlush){
	if (isFlush) return straightRank;
	return {};
}
// workaround for cheating test case
std::array<rank, 1> fiveOfAKind(const PokerHand& hand){
	auto same_rank = [](card current, card next){return current.first == next.first;};
	auto isQuintuple = adjacent_compare(hand.cards.begin(),hand.cards.end(),same_rank);
	return {(isQuintuple)?highestRank(hand):0u};
}
std::array<rank, 2> fourOfAKind(const PokerHand& hand){
	rank firstRank=0, secondRank=0;
	unsigned which = 0;
	for (const auto& nextCard: hand.cards){
		const rank nextRank = nextCard.first;
		if (!firstRank) firstRank = nextRank;
		else if (!which && nextRank == firstRank) which = 1;
		else if (which == 1 && nextRank == firstRank) continue;
		else if (!secondRank) secondRank = nextRank;
		else if (!which && nextRank == secondRank) which = 2;
		else if (which == 2 && nextRank == secondRank) continue;
		else return {0,0};
	}
	if (which == 2) std::swap(firstRank, secondRank);
	return {firstRank,secondRank};	//quad, kicker
}
std::array<rank,3> threeOfAKind(const PokerHand& hand){
	std::array<rank,3> cardRanks{};
	std::array<double,3> isDouble{};
	unsigned which = 0;
	for (const auto& nextCard: hand.cards){
		const rank nextRank = nextCard.first;
		for(auto i=0; i<3; ++i){
			if (!cardRanks[i]){cardRanks[i] = nextRank; break;}
			if (nextRank == cardRanks[i]){
				if (!isDouble[i]) isDouble[i]=true; 
				else if(!which && isDouble[i]) which = i+1;
				else return{};
				break;
			}
		}
	}
	if (!which) return{};	// no triple
	std::swap(cardRanks[0],cardRanks[which-1]);
	std::sort(cardRanks.begin()+1, cardRanks.end(),std::greater<rank>());
	return cardRanks;
}
std::array<rank,2> fullHouse(std::array<rank,3> tripleRanks){
	if (!tripleRanks[2]) 
		return {tripleRanks[0],tripleRanks[1]}; // tripple and double
	else return {0,0};
}
std::array<rank,3> twoPairs(std::array<rank,4> pairRanks){
	if(!pairRanks[3])
		return {pairRanks[0],pairRanks[1],pairRanks[2]};
	else return {0,0};
}
std::array<rank,4> pairs(const PokerHand& hand){
	using pair_type = std::pair<rank,bool>;
	std::array<pair_type,4> cardRanks;
	for (const auto& nextCard: hand.cards){
		const rank nextRank = nextCard.first;
		for (auto i=0; i<4; ++i){
			if(!cardRanks[i].first) {
				cardRanks[i].first = nextRank; 
				break;
			}
			else if(nextRank == cardRanks[i].first){
				if(!cardRanks[i].second) cardRanks[i].second = true;
				else return {};	//triples
				break;
			}
		}
	}
	// move doubles to the front
	auto pSingles = std::stable_partition(cardRanks.begin(),cardRanks.end(),
		[](pair_type pair){return pair.second;});
	// no doubles found
	if (pSingles == cardRanks.begin()) return {};
	return {cardRanks[0].first, cardRanks[1].first, cardRanks[2].first, cardRanks[3].first};
}

enum class Result { Win, Loss, Tie };
Result compareHighCard(const PokerHand& player, const PokerHand& opponent){
	auto pred = [](card pCard, card oCard){return pCard.first == oCard.first;};
	auto result = std::mismatch(player.cards.cbegin(),player.cards.cend(),
		opponent.cards.cbegin(), pred);
	// no mismach
	if (result.first == player.cards.cend()) return Result::Tie;
	// mismatch
	else if (*result.first > *result.second) return Result::Win;
	return Result::Loss;
}
Result compareHighestRank(const PokerHand& player, const PokerHand& opponent){
	const auto& playerRank = highestRank(player), opponentRank = highestRank(opponent);
	if (playerRank > opponentRank) return Result::Win;
	else if (playerRank == opponentRank) return Result::Tie;
	return Result::Loss;
}

template<size_t N>
Result compareRanks(const typename std::array<rank,N>& pRanks, const typename std::array<rank,N>& oRanks){
	for (auto i = 0; i<N; ++i){
		if (pRanks[i] > oRanks[i]) return Result::Win;
		else if (pRanks[i] < oRanks[i]) return Result::Loss;
	}
	return Result::Tie;
}
template<size_t N>
std::pair<bool, Result> compareCategory(const typename std::array<rank,N>& pRanks, const typename std::array<rank,N>& oRanks){
	if (pRanks[0] && oRanks[0]) return {true, compareRanks(pRanks, oRanks)};
	else if (pRanks[0] && !oRanks[0]) return {true, Result::Win};
	else if (!pRanks[0] && oRanks[0]) return {true, Result::Loss};	
	else return {false, Result()};
}

Result compare (const PokerHand &player, const PokerHand &opponent) {

	const bool pFlush = isFlush(player), oFlush = isFlush(opponent);
	const auto pStraight = straight(player), oStraight = straight(opponent);
	const auto pStraightFlush = straightFlush(pStraight,pFlush),
						 oStraightFlush = straightFlush(oStraight,oFlush);
	const auto pQuint = fiveOfAKind(player), oQuint = fiveOfAKind(opponent);
	const auto pQuad = fourOfAKind(player), oQuad = fourOfAKind(opponent);
	const auto pTriple = threeOfAKind(player), oTriple = threeOfAKind(opponent);
	const auto pFullHouse = fullHouse(pTriple), oFullHouse = fullHouse(oTriple);
	// 0) Five of a kind (workaround for cheating test case)
	auto result = compareCategory(pQuint, oQuint);
	if (result.first) return result.second;
	// 1) Straight flush
	result = compareCategory(pStraightFlush, oStraightFlush);
	if (result.first) return result.second;
	// 2) Four of a kind 
	result = compareCategory(pQuad, oQuad);
	if (result.first) return result.second;
	// 3) Full house
	result = compareCategory(pFullHouse, oFullHouse);
	if (result.first) return result.second;
	// 4) Flush
	if (pFlush && oFlush) return compareHighCard(player, opponent);
	else if (pFlush && !oFlush) return Result::Win;
	else if (!pFlush && oFlush)return Result::Loss;
	// 5) Straight
	result = compareCategory(pStraight, oStraight);
	if (result.first) return result.second;
	// 6) Three of a kind
	result = compareCategory(pTriple, oTriple);
	if (result.first) return result.second;
	// 7) Two pairs
	const auto pPairs = pairs(player), oPairs = pairs(opponent);
	const auto pTwoPairs = twoPairs(pPairs), oTwoPairs = twoPairs(oPairs);
	result = compareCategory(pTwoPairs, oTwoPairs);
	if (result.first) return result.second;
	// 8) One Pair
	result = compareCategory(pPairs, oPairs);
	if (result.first) return result.second;
	// 9) High card
  return compareHighCard(player,opponent);
}

#include <fstream>
// test
void generate(std::ostream&);
template<typename stream>
stream& output_hand(const PokerHand&, stream&);
int main(){
	//std::ofstream os("log.txt");
	//generate(os);
	
	PokerHand player("KS JH JS JS JC"), opponent("JS JH JS JS JC");
	auto result = compare(player, opponent);
	//auto result = compareHighCard(player, opponent);
	if (result == Result::Win) std::cout << "Win";
	else if (result == Result::Loss) std::cout << "Loss";
	else std::cout << "Tie";
	std::cout << std::endl;
}

template<typename stream, size_t N>
stream& output_result(const typename std::array<rank,N>& pRanks, stream& os){
	for (auto i = 0; i<N; ++i) os << pRanks[i] << " ";
	return os;
}
template<typename stream>
stream& output_hand(const PokerHand& hand, stream& os){
	for (const auto& nextCard: hand.cards)
		os << nextCard.first << nextCard.second << " ";
	return os;
}
void generate(std::ostream& os){
		std::string input;
		input.reserve(14);
		std::array<card,5> cards;
		card lowestCard = {2,'S'};
		std::fill_n(cards.begin(), 5, lowestCard);
		// iterate over all ranks
		while(true){
			++cards[0].first;
			for(size_t index=0; index<4 && cards[index].first > 14; ++index){//ripple carry		
				
				cards[index].first = 2;
				++cards[index+1].first;
				if (cards[4].first > 14) return;
			}
			PokerHand hand(cards);
			const bool pFlush = isFlush(hand);
			const auto pStraight = straight(hand);
			const auto pQuad = fourOfAKind(hand);
			const auto pTriple = threeOfAKind(hand); // returns nothing!!!
			const auto pFullHouse = fullHouse(pTriple);
			const auto pPairs = pairs(hand);
			const auto pTwoPairs = twoPairs(pPairs);
			
	
			if (pQuad[0]) {
				output_result(pQuad,os);
				os << " qud ";
				output_hand(hand,os);
				os << std::endl;
			}			
			else if (pFullHouse[0]) {
				output_result(pFullHouse,os);
				os << " fhs ";
				output_hand(hand,os);
				os << std::endl;
			}
			else if (pStraight[0]) {
				output_result(pStraight,os);
				os << " str ";
				output_hand(hand,os);
				os << std::endl;
			}
			else if (pTriple[0]) {
				output_result(pTriple,os);
				os << " trp ";
				output_hand(hand,os);
				os << std::endl;
			}
			else if (pTwoPairs[0]) {
				output_result(pTwoPairs,os);
				os << " tpr ";
				output_hand(hand,os);
				os << std::endl;
			}	
			else if (pPairs[0]) {
				output_result(pPairs,os);
				os << " opr ";
				output_hand(hand,os);
				os << std::endl;
			}
			else {
				output_hand(hand,os);
				os << std::endl;
			}
	
		}
	}

		
/*   Assert::That (run_test ("2H 3H 4H 5H 6H", "KS AS TS QS JS", Result::Loss)); // "Highest straight flush wins"
    Assert::That (run_test ("2H 3H 4H 5H 6H", "AS AD AC AH JD", Result::Win )); // "Straight flush wins of 4 of a kind"
    Assert::That (run_test ("AS AH 2H AD AC", "JS JD JC JH 3D", Result::Win )); // "Highest 4 of a kind wins"
    Assert::That (run_test ("2S AH 2H AS AC", "JS JD JC JH AD", Result::Loss)); // "4 Of a kind wins of full house"
    Assert::That (run_test ("2S AH 2H AS AC", "2H 3H 5H 6H 7H", Result::Win )); // "Full house wins of flush"
    Assert::That (run_test ("AS 3S 4S 8S 2S", "2H 3H 5H 6H 7H", Result::Win )); // "Highest flush wins"
    Assert::That (run_test ("2H 3H 5H 6H 7H", "2S 3H 4H 5S 6C", Result::Win )); // "Flush wins of straight"
    Assert::That (run_test ("2S 3H 4H 5S 6C", "3D 4C 5H 6H 2S", Result::Tie )); // "Equal straight is tie"
    Assert::That (run_test ("2S 3H 4H 5S 6C", "AH AC 5H 6H AS", Result::Win )); // "Straight wins of three of a kind"
    Assert::That (run_test ("2S 3H 4H 5S AC", "AH AC 5H 6H AS", Result::Win )); // "Low-ace straight wins of three of a kind"
    Assert::That (run_test ("2S 2H 4H 5S 4C", "AH AC 5H 6H AS", Result::Loss)); // "3 Of a kind wins of two pair"
    Assert::That (run_test ("2S 2H 4H 5S 4C", "AH AC 5H 6H 7S", Result::Win )); // "2 Pair wins of pair"
    Assert::That (run_test ("6S AD 7H 4S AS", "AH AC 5H 6H 7S", Result::Loss)); // "Highest pair wins"
    Assert::That (run_test ("2S AH 4H 5S KC", "AH AC 5H 6H 7S", Result::Loss)); // "Pair wins of nothing"?
    Assert::That (run_test ("2S 3H 6H 7S 9C", "7H 3C TH 6H 9S", Result::Loss)); // "Highest card loses"
    Assert::That (run_test ("4S 5H 6H TS AC", "3S 5H 6H TS AC", Result::Win )); // "Highest card wins"
    Assert::That (run_test ("2S AH 4H 5S 6C", "AD 4C 5H 6H 2C", Result::Tie )); // "Equal cards is tie"
*/