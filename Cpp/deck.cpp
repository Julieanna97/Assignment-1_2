#include "deck.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iterator>

using namespace std;

/**
 * Help function to convert Suit enum to string
*/
const string SuitToString(Suit s) {
    switch (s) {
        case Suit::Hearts:
            return "H";
        case Suit::Diamonds:
            return "D";
        case Suit::Spades:
            return "S";
        case Suit::Clubs:
            return "C";
        case Suit::Joker:
            return "Joker";
    }
    return "";
}

Card::Card(int rank, Suit suit)
{
    this->rank = rank;
    this->suit = suit;
}

/**
 * Overload of << operator for Card class
*/
ostream & operator << (ostream &out, const Card &c)
{
    string r;
    switch(c.rank) {
        case 1:
            r = 'A';
            break;
        case 11:
            r = 'J';
            break;
        case 12:
            r = 'Q';
            break;
        case 13:
            r = 'K';
            break;
        case 14:
            break;
        default:
            r = to_string(c.rank);
            break;
    }

    out << r << SuitToString(c.suit);

    return out;
}

/**
 * Create a deck of 52 cards
*/
Deck::Deck() {
    for (Suit s = Suit::Hearts; s <= Suit::Clubs; s = Suit(s + 1)) {
        for (int r=1; r<14; r++) {
            cards.push_back(Card(r, s));
        }
    }
    for(int j = 0; j < 3; j++)
    {
        cards.push_back(Card(14, Joker));
    }
}

/**
 * Overload of << operator for Deck class
*/
ostream & operator << (ostream &out, const Deck &d)
{
    string separator;
    for (auto i: d.cards) {
        out << separator << i;
        separator = ", ";
    }

    return out;
}

/** 
 * Return number of cards in deck
 * 
*/
int Deck::size()
{
    return this->cards.size();
}

vector<Card>& Deck::get_cards()
{
    return this->cards;
}

/**
 * Shuffle all the cards in deck in ranom order. 
*/
void Deck::shuffle()
{
    auto rng = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(this->cards.begin(),this->cards.end(), rng);
}

/**
 * Sort the deck according to card rank. All aces, the all two's, then all threes, ...
*/
void Deck::sort()
{
    vector<Card> sorted_cards; // Empty temporary deck

    while (this->size() > 0) {
        // Go through the deck from left to right, insert the deck in the appropriate spot
        Deck::insert(sorted_cards, this->take()); //Take a card from the old deck, insert it into the new one
    }

    this->cards = sorted_cards;
}

/**
 * Take the top card from the deck 
*/
Card Deck::take() {
    Card c = this->cards.back();
    this->cards.pop_back();
    return c;
}

/**
 * Put a card on top of the deck 
*/
void Deck::put(Card card) {
    cards.push_back(card);
}

void Deck::insert(vector<Card> &cardlist, Card card) {

    // starting index from 0
    int count = 0;
    // find the index of the first card in the list that is >= to the card to insert
    for(count; count < cardlist.size(); ++count)
    {
        if (card < cardlist[count])
        break;
    }
    // insert the new card before that index
    cardlist.insert(cardlist.begin() + count, card);

    return;
}