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

    // Check for blackjack if drawn at the start
    if (player_hand.is_blackjack()) {
        std::cout << "Blackjack!\n";
        bankroll += bet;
        continue;
    }

    // Player turn
    bool player_bust = false;
    char blackjack_choice = ' ';
    while (true) {
        std::cout << "Hit (h) or Stand (s)? ";
        std::cin >> blackjack_choice;

        if (blackjack_choice == 'h' || blackjack_choice == 'H') {
            player_hand += deck.deal();
            std::cout << "Your hand: " << player_hand << " (Value: " << player_hand.value() << ")\n";
            if (player_hand.is_bust()) {
                std::cout << "Bust! You went over 21.\n";
                player_bust = true;
                break;
            }
        } else if (blackjack_choice == 's' || blackjack_choice == 'S') {
            break;
        } else {
            std::cout << "Invalid choice. Please enter 'h' or 's'.\n";
        }
    }
    // Dealer turn (if the player didn't bust)
    bool dealer_bust = false;
    if (!player_bust) {
        std::cout << "Dealer's hand: " << dealer_hand << " (Value " << dealer_hand.value() << ")\n";
        while (dealer_hand.value() < 17) {
            dealer_hand += deck.deal();
            std::cout << "Dealer hits " << dealer_hand << " (Value " << dealer_hand.value() << ")\n";
        }
        if (dealer_hand.is_bust()) {
            std::cout << "Dealer busts!\n";
            dealer_bust = true;
        }
    }
    // Determine what happens after
    int player_value = player_hand.value();
    int dealer_value = dealer_hand.value();

    if (player_bust) {
        std::cout << "You lose $" << bet << ".\n";
        bankroll -= bet;
    } else if (dealer_bust) {
        std::cout << "You win $" << bet << "!\n";
        bankroll += bet;
    } else if (player_value > dealer_value) {
        std::cout << " You win $" << bet << "! (" << player_value << " vs " << dealer_value << ")\n";
        bankroll += bet;
    } else if (player_value < dealer_value) {
        std::cout << "Dealer wins. You lose $" << bet << ". (" << dealer_value << player_value << "(\n";
        bankroll -= bet;
    } else {
        std::cout << "Push (Tie). Your bet is returned.\n";
    }

    if (bankroll <= 0) {
        std::cout << "\nYou are out of money! Game over.\n";
        break;
    }

    // Ask to play another round
    char play_again;
    std::cout << "Play another round? (y/n): ";
    std::cin >> play_again;
    if (play_again != 'y' && play_again != 'Y') {
        std::cout << "Thanks for playing! Final bankroll: $" << bankroll << "\n";
        break;
    }
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
