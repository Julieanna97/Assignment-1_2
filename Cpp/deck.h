#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Suit {
    Hearts,
    Diamonds,
    Spades,
    Clubs,
    Joker
};

class Card
{
private:
    int rank;
    Suit suit;
public:
    Card(int rank, Suit suit);
    
    friend bool operator == (const Card &cd, const Card &cdr)
    {
        return cd.rank == cdr.rank;
    }

    friend bool operator < (const Card &cd, const Card &cdr)
    {
        return cd.rank < cdr.rank;
    }

    friend bool operator > (const Card &cd, const Card &cdr)
    {
        return cd.rank > cdr.rank;
    }

    friend ostream & operator << (ostream &out, const Card &c);
};

class Deck
{
private:
    vector<Card> cards;
public:
    Deck();
    friend ostream & operator << (ostream &out, const Deck &d);
    vector<Card>& get_cards();
    int size();
    void shuffle();
    void sort();
    Card take();
    void put(Card card);

    static void insert(vector<Card> &cardlist, Card card);
    void remove_jokers(vector<Card> & cardlist);
};