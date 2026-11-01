# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most. Each partner writes their own section.

## Week 11 (Lab 11)

Partner name: (wasn't assigned a partner)

### Predict before you run

Before running `hand_bug`, which hands from the Aces Table do you expect it to get wrong, and why?

- It would get my hands of "A A Q" and "K A 2" wrong
- The ace check is placed at the beginning of the loop before a card is drawn
- If the card drawn puts the value over 21, it doesn't properly change the ace
- thus you get a value over 21 when an ace is supposed to be 1

### Build and run

```
cmake -S . -B build
cmake --build build --target hand_bug
./build/hand_bug
```

Hands whose total differs from your Aces Table (hand number, printed total, correct total):
- Hand 2 "A A Q", 22, 12
- Hand 6, "K A 2", 23, 12

### The GDB session on `Hand::value`
Record the commands in the order you typed them. For each, one line on what it did.

- Conditional breakpoint command (stop only when the hand has three cards):
    + break Hand:: value if m_count == 3
- `display` commands you set:
    + display total
    + display aces_as_eleven
- Values shown at the failing step (the running total and the number of aces counted as 11 after each `next`):
    "K, A, 2":
    + Start: total = 0, aces_as_eleven = 0
    + After Card 1 (K), total = 10, aces_as_eleven = 0
    + After Card 2 (A): total = 21, aces_as_eleven = 1
    + After Card 3 (2): total = 23, aces_as_eleven = 1
    + After Card 3 should've counted the ace as 1 instead of 11
- What `print *this` showed:
    + m_cards = {
        {m_rank = 13}
        {m_rank = 1}
        {m_rank = 2}
      }
      m_count = 3
- What `finish` returned for the failing hand, and the correct value:
    "K, A, 2":
    + Finish returned 23 (incorrect)
    + Correct value from my table: 13

    "A, A, Q":
    + Finish returned 22 (incorrect)
    + Correct value from my table: 12
### Cause and fix

- The line that is wrong, and what it does instead of what it should:
    + if (total > 21 && aces_as_eleven > 0)
    + It is placed at the top of the loop so it checks the previous
    + instead of after the card has been added to the total
- The change you made:
    + place the if condition on the bottom and changed if to while
- How you checked it (which hands, which result):
    + checked each hand, with the results mattering being
    + hand 2 and hand 6 which both failed
