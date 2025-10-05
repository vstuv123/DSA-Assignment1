// header files
#include "uno.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

// internal card structure for storing color and value
struct CardInternal
{
    string color;
    string value;
    CardInternal(const string &c, const string &v) : color(c), value(v) {}
};

// internal class handling all game logic and data
class UNOGameInternal
{
public:
    vector<CardInternal> deck;            // deck of cards
    vector<vector<CardInternal>> players; // each player's hand
    vector<CardInternal> discardPile;     // pile of played cards
    int currentPlayer = 0;                // index of current player
    bool clockwise = true;                // direction of play
    int numPlayers = 2;                   // total number of players
    int winner = -1;                      // store winner index
    mt19937 rng;                          // random number generator

    // constructor to set number of players and random seed
    UNOGameInternal(int numP) : numPlayers(numP), rng(1234) {}

    // build a standard UNO deck (numbers + action cards)
    void buildDeck()
    {
        deck.clear();
        vector<string> colors = {"Blue", "Yellow", "Green", "Red"};
        vector<string> values = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
        vector<string> actions = {"Skip", "Reverse", "Draw Two"};

        for (const auto &color : colors)
        {
            deck.push_back(CardInternal(color, "0"));
            for (int i = 1; i <= 9; ++i)
            {
                deck.push_back(CardInternal(color, values[i]));
                deck.push_back(CardInternal(color, values[i]));
            }
            for (const auto &act : actions)
            {
                deck.push_back(CardInternal(color, act));
                deck.push_back(CardInternal(color, act));
            }
        }
    }

    // shuffle the deck using random generator
    void shuffleDeck() { shuffle(deck.begin(), deck.end(), rng); }

    // deal 7 cards to each player and start discard pile
    void dealCards()
    {
        players.clear();
        players.resize(numPlayers);
        for (int i = 0; i < 7; i++)
            for (int p = 0; p < numPlayers; p++)
            {
                players[p].push_back(deck.back());
                deck.pop_back();
            }
        discardPile.push_back(deck.back());
        deck.pop_back();
    }

    // check if a card can be played based on color/value/action
    bool isPlayable(const CardInternal &top, const CardInternal &c)
    {
        return top.color == c.color || top.value == c.value || c.value == "Skip" || c.value == "Reverse" || c.value == "Draw Two";
    }

    // get index of next player considering direction and skips
    int nextPlayerIndex(int skip = 0)
    {
        int step = clockwise ? 1 : -1;
        int idx = currentPlayer;
        for (int s = 0; s <= skip; s++)
            idx = (idx + step + numPlayers) % numPlayers;
        return idx;
    }

    // handle special action cards: Reverse, Skip, Draw Two
    void applyAction(const CardInternal &c)
    {
        if (c.value == "Reverse")
            clockwise = !clockwise; // change direction
        else if (c.value == "Skip")
            currentPlayer = nextPlayerIndex(); // skip next player
        else if (c.value == "Draw Two")
        { // next player draws two cards
            int next = nextPlayerIndex();
            for (int i = 0; i < 2 && !deck.empty(); i++)
            {
                players[next].push_back(deck.back());
                deck.pop_back();
            }
            currentPlayer = next;
        }
    }

    // check if any player has no cards left
    bool isGameOver() const
    {
        for (const auto &h : players)
            if (h.empty())
                return true;
        return false;
    }

    // return winner index if game is over
    int getWinner() const
    {
        for (int i = 0; i < numPlayers; i++)
            if (players[i].empty())
                return i;
        return -1;
    }

    // create a string showing game state (for display/logging)
    string getState() const
    {
        ostringstream out;
        out << "Player " << currentPlayer << "'s turn, Direction: "
            << (clockwise ? "Clockwise" : "Counter-clockwise")
            << ", Top: " << discardPile.back().color << " " << discardPile.back().value
            << ", Players cards: ";
        for (int i = 0; i < numPlayers; i++)
        {
            if (i > 0)
                out << ", ";
            out << "P" << i << ":" << players[i].size();
        }
        return out.str();
    }

    // play one full turn for the current player
    void playTurn()
    {
        auto &hand = players[currentPlayer];
        CardInternal top = discardPile.back();
        bool played = false;

        // try color match
        for (size_t i = 0; i < hand.size(); i++)
        {
            if (hand[i].color == top.color)
            {
                discardPile.push_back(hand[i]);
                CardInternal c = hand[i];
                hand.erase(hand.begin() + i);
                played = true;
                applyAction(c);
                break;
            }
        }

        // try value match if color match not found
        if (!played)
        {
            for (size_t i = 0; i < hand.size(); i++)
            {
                if (hand[i].value == top.value && hand[i].value != "Skip" && hand[i].value != "Reverse" && hand[i].value != "Draw Two")
                {
                    discardPile.push_back(hand[i]);
                    CardInternal c = hand[i];
                    hand.erase(hand.begin() + i);
                    played = true;
                    applyAction(c);
                    break;
                }
            }
        }

        // try action cards if still not played
        if (!played)
        {
            for (size_t i = 0; i < hand.size(); i++)
            {
                if (hand[i].value == "Skip" || hand[i].value == "Reverse" || hand[i].value == "Draw Two")
                {
                    discardPile.push_back(hand[i]);
                    CardInternal c = hand[i];
                    hand.erase(hand.begin() + i);
                    played = true;
                    applyAction(c);
                    break;
                }
            }
        }

        // draw a card if no playable card was found
        if (!played && !deck.empty())
        {
            CardInternal drawn = deck.back();
            deck.pop_back();
            hand.push_back(drawn);
            if (isPlayable(top, drawn))
            {
                discardPile.push_back(drawn);
                hand.pop_back(); // play it immediately
                played = true;
                applyAction(drawn);
            }
        }

        if (hand.size() == 1)
            cout << "Player " << currentPlayer << " says UNO!" << endl;

        // move to next player if game still running
        if (!isGameOver())
        {
            if (played && (discardPile.back().value == "Skip" || discardPile.back().value == "Draw Two"))
            {
                // special actions already handled above
            }
            else
                currentPlayer = nextPlayerIndex();
        }
    }
};

// global repository mapping each UNOGame object to its internal logic
static map<const UNOGame *, UNOGameInternal *> gameRepo;

// constructor: create internal game instance and store in map
UNOGame::UNOGame(int numPlayers)
{
    gameRepo[this] = new UNOGameInternal(numPlayers);
}

// initialize deck, shuffle, and deal cards
void UNOGame::initialize()
{
    gameRepo[this]->buildDeck();
    gameRepo[this]->shuffleDeck();
    gameRepo[this]->dealCards();
}

// handle one player’s turn
void UNOGame::playTurn() { gameRepo[this]->playTurn(); }

// check if game is over
bool UNOGame::isGameOver() const { return gameRepo[this]->isGameOver(); }

// return winner index if exists
int UNOGame::getWinner() const { return gameRepo[this]->getWinner(); }

// get readable game state for printing or debugging
string UNOGame::getState() const { return gameRepo[this]->getState(); }
