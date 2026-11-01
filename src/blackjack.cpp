#include "blackjack.h"

#include <iostream>
#include <random>
#include <string>

#include "card.h"
#include "deck.h"
#include "hand.h"

namespace {

/// The first five cards of a deck as text. The deck is passed by value on
/// purpose: the copy is dealt from, and the caller's deck is left alone.
std::string top_five(Deck deck) {
  std::string text{};
  for (int i{0}; i < 5 && !deck.empty(); ++i) {
    if (i > 0) {
      text += ' ';
    }
    text += deck.deal().to_string();
  }
  return text;
}

} // namespace

// TODO(student): Lab 11. Replace this demonstration with the game. Keep the
// Lab 10 helper above if it is useful; delete it if it is not (an unused
// function in an unnamed namespace is a compiler warning).
void play_blackjack() {
  std::random_device device{};
  std::mt19937 gen{device()};
  
  // Sets the starting amount of money and bet amount
  int bankroll = 100;
  const int bet = 10;

  std::cout << "\n--- Blackjack ---\n";

  Deck deck;
  deck.shuffle(gen);
  
  // Money currently sets the loop
  while (bankroll > 0) {
    std::cout << "Bankroll: $" << bankroll << " | Current Bet: $" << bet << "\n";
    
    // Reshuffles the deck if low amount of cards
    if (deck.remaining() < 15) {
        std::cout << "Reshuffling deck...\n";
        deck = Deck{};
        deck.shuffle(gen);
    }
    
    // Constructs both player and dealer hand
    Hand player_hand;
    Hand dealer_hand;
    
    // Deals two cards to both player and dealer
    player_hand += deck.deal();
    dealer_hand += deck.deal();
    player_hand += deck.deal();
    dealer_hand += deck.deal();

    // Show hands, dealer has to show their first card
    std::cout << "Dealer shows: " << dealer_hand[0] << " [hidden]\n";
    std::cout << "Your hand:    " << player_hand << " (Value: " << player_hand.value() << ")\n";

    bankroll = 0;
  }

  if (deck.empty()) {
    std::cout << "The deck is empty. Write Deck() in deck.cpp first.\n";
    return;
  }

  std::cout << "Cards in a new deck: " << deck.remaining() << "\n";

  deck.shuffle(gen);

  const std::string before{top_five(deck)};

  Deck copy = deck;

  copy.shuffle(gen);
  const std::string copy_top{top_five(copy)};
  const std::string after{top_five(deck)};

  std::cout
      << "Original, top five:                 " << before << "\n"
      << "Shuffled copy, top five:            " << copy_top << "\n"
      << "Original after shuffling the copy:  " << after << "\n"
      << (before == after
              ? "The original did not change.\n"
              : "The original CHANGED. The copy shares memory with it!\n");
}
