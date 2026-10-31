# Operators notes (Lab 11)

Fill this in as you work. Commit it with the code.

## 1. Test table for `Hand`

At least six hands. Work out each expected value from the rules **before** you run any code. At least one soft hand, one bust, and one blackjack must be in the table. Every row must also appear as a test in `tests/test_hand.cpp`.

| Hand | Expected `value()` | `is_bust()` | `is_blackjack()` |
| --- | --- | --- | --- |
|A,K |21 |No |Yes |
|A,A,Q |12 |No |No |
|2,9,J |21 |No |No |
|K,Q,5 |25 |Yes |No |
|7,5,K |22 |Yes |No |
|K,A,2 |13 |No |No |

## 2. Design artifacts

List the files you added and where they are in the repository.

- Updated class diagram (with `Hand` and its relationship to `Card`): docs/hand card relationship.png
- Flowchart for `Hand::value`: docs/hand_value.png
- Flowchart for the dealer's turn: docs/dealer turn.png

## 3. Ownership classification

For each relationship, write **composition**, **aggregation**, or **association**, then one sentence that says why. Use the test questions from class: if the whole is destroyed, does the part go too? Could the same part belong to two wholes? Does the class only store a reference to something it does not own? A complete answer states what happens to the part when the whole is destroyed, and whether anything else can still hold the part.

| Relationship | Composition, aggregation, or association | One-sentence justification |
| --- | --- | --- |
| `Hand` and its `Card`s |Composition |Hand holds cards as an array |
| The Blackjack game and its `Deck` and `Hand`s |Aggregation |The blackjack game holds deck and cards; doesn't destroy them if blackjack is destroyed |
| `Player` and the current `Room*` in the Dungeon |Association |Player contains a pointer to their current room, but are independent |

## 4. Checklist before you push

- [X] `cmake --build build` has no warnings
- [X] `ctest` passes, including your own `Hand` tests
- [X] A run under AddressSanitizer is clean (`-DENABLE_ASAN=ON`, separate build folder)
- [ ] `GDB_LOG.md`: each partner has written their own Week 11 section
- [ ] Commits use Conventional Commit messages, and both partners have commits
