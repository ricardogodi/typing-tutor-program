# Typing Tutor Program

## Description
Typing Tutor Program: Developed a C++ application designed to challenge users to type words accurately within specific time limits. The application features a menu-driven interface that offers options to practice with either commonly misspelled words or a random selection from a large dictionary. Key functionalities include word lookup using binary search and dynamic word length adjustments.

## Files Included
- **dictionary.txt**: Contains a large list of dictionary words used for the typing tests.
- **misspelledWords.txt**: Includes commonly misspelled words, paired with their correct spellings.
- **main.cpp**: The main program file which contains all the logic for the menu options, word handling, and game mechanics.
- **Makefile**: Simplifies the compilation process with targets for building and cleaning the project.

## How to Run
To compile the program, use the command:
```bash
make
```
To start the program, execute:
```bash
./app
```
## Menu Options
1. **Spell commonly misspelled words (timed)**: Challenges users to type pre-defined commonly misspelled words correctly within a time limit.
2. **Type random words from full dictionary (timed)**: Users type randomly selected words from the full dictionary file, with the word length increasing after each successful round.
3. **Display some words from one of the lists**: Allows users to display a range of words either from the full dictionary or the list of commonly misspelled words.
4. **Use binary search to lookup a word in full dictionary**: Implements a binary search algorithm to find if a specified word exists within the dictionary.
5. **Set word length to use with full dictionary**: Enables users to set the initial word length for the typing challenges that use the full dictionary.
6. **Exit the program**: Closes the application.

Each functionality leverages C++ programming constructs including vectors for data storage, file I/O for reading text files, and regular control structures for flow management.
