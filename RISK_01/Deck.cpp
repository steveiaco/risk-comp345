#include "Deck.h"
#include <iterator>

//Constructor
/**Default constructor. Creates an empty deck for testing**/
Deck::Deck() {
	srand(time(NULL));
}
/**Creates a deck for a give map**/
Deck::Deck(Map* map) {
	srand(time(NULL));
	map->populateDeck(this);
}

//Destructor
/**Deck destructor. Deletes deck and cards in deck.*/
Deck::~Deck(){
	//Delete cards in deck
	for (Card* card : cards)
		delete card;
}

//Mutator
/**Add card to deck. Returns exception if card is already in deck.**/
void Deck::addCard(Card* card) {
	if (!cards.insert(card).second) //Insert card in deck. If card is already in deck, insert will fail and this if will trigger. In this case, throw exception.
		throw std::invalid_argument("This card has already been added to the deck.");
}

//Utility
/**Draw a card from the deck. Remove it from set of cards and return it.**/
Card* Deck::draw() {
	//first, lets get the size of the deck
	size_t size = cards.size();
	//Check if deck is empty
	if (size == 0)
		throw std::invalid_argument("Cannot draw card. Deck is empty.");
	//we must generate a random index between [0,size-1]
	int randomIndex = rand()%size;
	std::unordered_set<Card*>::const_iterator it(cards.begin());
	// 'advance' the iterator to the random index, remove and return the card at it
	std::advance(it, randomIndex);
	Card* toReturn = *it;
	cards.erase(toReturn);
	return toReturn;
}
/**Display contents of deck.**/
void Deck::display() const {
	std::cout << "Deck contains the following cards: \n";
	int index = 1;
	for (Card* card : cards) {
		std::cout << "  Card " << index << ": ";  
		card->display();
		index++;
	}
}

