#pragma once

#include "Card.hpp"

#include <stack>

class Deck
{
private:
    std::stack<Card> contents;

    std::stack<Card> split(std::stack<Card>& mainstack);
    void riffle(std::stack<Card>& mainstack, std::stack<Card>& offStack); //Bottlenecked by allocation (stack is not an efficient structure for shuffling)
protected:

public:
    Deck();
    Deck(int cards);

    Card draw();
    Deck& putOnTop(Card newCard);
    Deck& putOnTop(Card newCard, unsigned int quantity);
    Deck& shuffle(); //performs a physically-modelled shuffle;
};

/*

Ideas for improvement:

 - Investigate the use of std::random_shuffle

*/
