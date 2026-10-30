#include "hand.h"

// TODO(student): Lab 11. Every function below compiles but returns a wrong
// answer on purpose, so the tests in tests/test_hand.cpp fail until you write
// it. Name the parameters when you replace the bodies. Keep `const` wherever
// the declaration in hand.h has it.

Hand::Hand() : m_cards{}, m_count{0} {}

Hand &Hand::operator+=(const Card &card) { 
    m_cards[m_count] = card;
    ++m_count;
    return *this; 
}

const Card &Hand::operator[](int index) const { 
    return m_cards[index]; 
}

int Hand::count() const { 
    return m_count; 
}

int Hand::value() const { 
   // If there are no cards in hand
   if (m_count == 0) {
     return 0;
   }
   int total = 0;
   int ace_count = 0;

   // Searches through the hand
   for (int i = 0; i < m_count; ++i) {
     int rank = m_cards[i].rank();
     if (rank == 1) {
       ace_count++; // Increases ace count if there is one in hand
       total += 11;
     } else if (rank >= 10) {
         total += 10; // Checks for kings, queens and jacks which are 10
     } else {
         total += rank; // Adds up every other number card
     }
   }
   // If over 21/bust, checks for aces and substracts 10 to make ace = 1
   while (total > 21 && ace_count > 0) {
     total -= 10;
     ace_count--;
   }
   return total;
}

bool Hand::is_blackjack() const { return false; }

bool Hand::is_bust() const { return false; }

void Hand::clear() {}

std::ostream &operator<<(std::ostream &out, const Hand &) { return out; }
