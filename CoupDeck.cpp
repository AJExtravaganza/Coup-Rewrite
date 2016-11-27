#include "CoupDeck.hpp"

// FEATURE (Backbox#1#): Add different initialisation for two-player mode
CoupDeck::CoupDeck(): Deck()
{
    putOnTop(Card(DUKE), 3);
    putOnTop(Card(ASSASSIN), 3);
    putOnTop(Card(AMBASSADOR), 3);
    putOnTop(Card(CAPTAIN), 3);
    putOnTop(Card(CONTESSA), 3);

    shuffle();
}
