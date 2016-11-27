#include "Deck.hpp"
#include "math.h"

Deck::Deck(): contents()
{

}

Deck::Deck(int cards): contents()
{
    putOnTop(Card(NullRole), 100);
    shuffle();
}

Card Deck::draw()
{
    Card tempCard = contents.top();
    contents.pop();

    return tempCard;
}

Deck& Deck::putOnTop(Card newCard)
{
    contents.push(newCard);

    return *this;
}

Deck& Deck::putOnTop(Card newCard, int quantity)
{
    for(int i = 0; i < quantity; i++)
    {
        contents.push(newCard);
    }


    return *this;
}

Deck& Deck::shuffle()
{
    int requiredShuffles = (1.5 * log(contents.size()) / log(2) + 0.5); //As per L. N. Trefethen and L. M. Trefethen's "How Many Shuffles to Randomize a Deck of Cards?"

    for (int i = 0; i < requiredShuffles; i++)
    {
        std::stack<Card> offstack = split(contents); //WORKS
        riffle(contents, offstack);
    }

    return *this;
}

std::stack<Card> Deck::split(std::stack<Card>& mainstack) //WORKS
{
    int totalCards = mainstack.size();
    std::stack<Card> offstack;
    for (int i = 0; i < totalCards / 2; i++)
    {
        offstack.push(mainstack.top());
        mainstack.pop();
    }

    return offstack;
}

void Deck::riffle(std::stack<Card>& mainstack, std::stack<Card>& offstack)

{
    int totalCards = (mainstack.size() + offstack.size());
    int remainingCards = totalCards;
    std::stack<Card> newstack;
    while(remainingCards)
    {
        if ((rand() % remainingCards) < mainstack.size())
        {
            newstack.push(mainstack.top());
            mainstack.pop();
        }
        remainingCards = (mainstack.size() + offstack.size());

        if (remainingCards && (rand() % remainingCards) < offstack.size())
        {
            newstack.push(offstack.top());
            offstack.pop();
        }
        remainingCards = (mainstack.size() + offstack.size());
    }

    mainstack = newstack; //Possibly expensive to rewrite; consider using pointer instead?
}
