//
//  main.cpp
//
//  Created by Ricardo Gonzalez on 10/1/21.
//  Professor: Dale Reed
//  CS 141
//  Program #3
//

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <vector>     // Input file is stored in a vector
#include <cassert>    // For the assert statement used to validate file open
#include <cctype>     // Allows using the tolower() function
#include <iomanip>    // For setw() function
#include <ctime>      // For timer functions

using namespace std;

void readWordsIntoVector(vector <string> &myVector, bool isDictionary) {
    
    ifstream inStream;                          // Declare an input stream for reading
    
    if (isDictionary) {
        inStream.open("dictionary.txt");        // Open dictionary file
        assert( inStream.fail() == false );     // Ensure file open worked
        
    } else if (!isDictionary) {
        inStream.open("misspelledWords.txt");   // Open misspelledWords file
        assert( inStream.fail() == false );     // Ensure file open worked
    }
    
    // Clear vector in case we have to use it again
    myVector.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;
    while( inStream >> newWord) {               // While there is another word to be read
        myVector.push_back(newWord);            // Push back the word into myVector
    }
    
    inStream.close();                           // Close the dictionary file
}

void displayMenu() {
    
    cout << "Select a menu option: " << endl;
    cout << "   1. Spell commonly misspelled words (timed) " << endl;
    cout << "   2. Type random words from full dictionary (timed) " << endl;
    cout << "   3. Display some words from one of the lists " << endl;
    cout << "   4. Use binary search to lookup a word in full dictionary " << endl;
    cout << "   5. Set word length to use with full dictionary " << endl;
    cout << "   6. Exit the program " << endl;
}

// Display words from lowerBound to higherBound
void displaySomeWords(vector<string> &wordsVector) {
    
    int lowerBound;
    int higherBound;
    
    cin >> lowerBound;
    cin >> higherBound;
    
    int n = lowerBound;
    for (int i = lowerBound ; i <= higherBound; i++) {
        cout << setw(6) << "" << n << ". " << wordsVector.at(i) << endl;
        n++;
    }
    cout << endl;
}

void chooseListToDisplay(vector<string> &dictionary,
                         vector<string> &mispelledWordsCorrect,
                         vector<string> &mispelledWordsIncorrect) {
    
    char choice;
    
    do {
        cout << "Which words do you want to display?" << endl;
        
        cout << "      A. Dictionary of all words" << endl;
        cout << "      B. Wrongly spelled common misspelled words" << endl;
        cout << "      C. Correctly spelled common misspelled words" << endl;
        
        cin >> choice;
        choice = tolower(choice);                           // To ensure switch works with uppercase letters
        
        cout << "   Your choice --> " << endl;              // Comment for professor Reed: 'cout << "   Your choice --> " << choice << endl;' doesn't match Zybooks output
        
        switch (choice) {
                
            case 'a':
                cout << "   Enter the start and end indices between 0 and 263532: ";
                displaySomeWords(dictionary);               // Pass the dictionary vector
                
                break;
                
            case 'b':
                cout << "   Enter the start and end indices between 0 and 113: ";
                displaySomeWords(mispelledWordsIncorrect);  // Pass the vector of wrongly common misspelled words
                
                break;
                
            case 'c':
                cout << "   Enter the start and end indices between 0 and 113: ";
                displaySomeWords(mispelledWordsCorrect);    // Pass the vector of correctly common misspelled words
                
                break;
        }
        
    } while (choice < 'a' || choice > 'c'); // Repeat loop in case of an invalid input
}

long lookUpWord(vector<string> &dictionary, string word) {
    
    long low = 0;
    long high = dictionary.size() - 1;
    long mid;
    
    int n = 1;  // To display comparison number
    
    // Binary Search
    while (low <= high) {
        
        mid = (low + high) / 2;
        
        if (word == dictionary.at(mid)) {
            
            cout << setw(5) << "" << n << ". Comparing to: " << dictionary.at(mid) << endl;
            return mid;
            
        } else if (word < dictionary.at(mid)) {
            
            high = mid - 1;
            cout << setw(5) << "" << n << ". Comparing to: " << dictionary.at(mid) << endl;
            
        } else { // word > dictionary.at(mid)
            
            low = mid + 1;
            cout << setw(5) << "" << n << ". Comparing to: " << dictionary.at(mid) << endl;
        }
        n++;
    }
    return -1;
}

// Generate random words from the misspelled words list and push back the correct word into vector 'fiveWords'
void populateAndDisplayFiveWordVector(vector<string> &misspelledWordsIncorrect,
                                      vector<string> &misspelledWordsCorrect,
                                      vector<string> &fiveWords) {
    
    int index;
    for (int i = 0; i < 5; i++) {
        index = rand() % (misspelledWordsCorrect.size());     // Generate random index between 0 and 113
        fiveWords.push_back(misspelledWordsCorrect.at(index));  // Push back random correct word into fiveWords vector
        cout << misspelledWordsIncorrect.at(index) << " ";      // Display the corresponding incorrect word
    }
}

// Generate random words of length 'wordLength' from the dictionary and push them back into vector 'fiveWords'
void populateAndDisplayFiveWordVector(vector<string> &dictionary,
                                      vector<string> &fiveWords,
                                      int wordLength) {
    
    int index;
    int n = 0;
    
    while (n < 5) {
        index = rand() % (dictionary.size());              // Generate random index between 0 and 263533
        if(dictionary.at(index).size() == wordLength) {    // If the word's length equals the desired length
            fiveWords.push_back(dictionary.at(index));     // Push back that word into fiveWords vector
            cout << fiveWords.at(n) << " ";                // Display the random word
            n++;
        }
    }
}

// Get input of five words and store them into vector 'fiveWordInputVector'
void typeFiveWords(vector<string> &fiveWordInputVector) {
    
    string nextWord;
    for (int i = 0; i < 5; i++) {
        cin >> nextWord;
        fiveWordInputVector.push_back(nextWord);
    }
}

void calculateAndDisplayResults(vector<string> fiveRandomWordVector,
                                vector<string> fiveWordInputVector,
                                vector<int> &scores,
                                int numOfPointsPerWord,
                                int elapsedSeconds) {
    
    int incorrectWordCounter = 0;
    int correctWordCounter = 0;
    
    int score = 0;
    int bonus;
    int correctWordPointsTotal;
    
    int penaltyPerIncorrectWord;
    int incorrectWordsPenaltyTotal;
    int latePenalty;
    
    int numOfSecUnder15;
    int numOfSecOver15;
    
    // Count incorrect words
    for (int i = 0; i < 5; i++) {
        if (fiveWordInputVector.at(i) != fiveRandomWordVector.at(i)){
            incorrectWordCounter++;
        }
    }
    
    // Calculate correct words
    correctWordCounter = 5 - incorrectWordCounter;
    
    // Calculate points and penalty
    correctWordPointsTotal = correctWordCounter * numOfPointsPerWord;
    penaltyPerIncorrectWord = numOfPointsPerWord * 2;
    incorrectWordsPenaltyTotal = incorrectWordCounter * penaltyPerIncorrectWord;
    
    score = score + correctWordPointsTotal - incorrectWordsPenaltyTotal;    // Calculate preliminary score (not final score)
    
    // Display incorrect words
    if (incorrectWordCounter > 0) {
        cout << "   Misspelled words:" << endl;
        
        for (int i = 0; i < 5; i++) {
            if (fiveWordInputVector.at(i) != fiveRandomWordVector.at(i)){
                cout << setw(7) << "" << fiveWordInputVector.at(i) << " should be: " << fiveRandomWordVector.at(i) << endl;
            }
        }
    } else { // incorrectWordCounter = 0
        cout << "   No misspelled words!" << endl;
    }
    
    // Display elapsed time
    cout << "   Elapsed time: " << elapsedSeconds << " seconds. ";
    
    if (elapsedSeconds < 15) {              // Calculate bonus
        numOfSecUnder15 = 15 - elapsedSeconds;
        bonus = numOfSecUnder15 * 2;
        score = score + bonus;              // Update score
        cout << bonus << " point bonus for finishing " << numOfSecUnder15 << " seconds early." << endl;
    } else {                                // Calculate late penalty
        numOfSecOver15 = elapsedSeconds - 15;
        latePenalty = numOfSecOver15 * 3;
        score = score - latePenalty;        // Update score
        cout << endl;
    }
    
    cout << setw(3) << "" << correctWordPointsTotal << " points: " << correctWordCounter << " spelled correctly x " << numOfPointsPerWord << " points each" << endl;
    
    if (incorrectWordCounter > 0) {
        cout << setw(3) << "" << incorrectWordsPenaltyTotal << " point penalty: " << incorrectWordCounter << " spelled incorrectly x " << penaltyPerIncorrectWord << " points each" << endl;
    }
    
    scores.push_back(score);                // Store score in vector
    
    cout << "   Score: " << score << endl;
    cout << endl;
}

int main(int argc, const char * argv[]) {
    
    srand(1);                                   // Set the random seed equal to 1 to generate predictable numbers
    
    vector<string> dictionary;                  // Vector with full dictionary
    
    vector<string> misspelledWords;             // Vector with incorrect and correct words (doubled in size)
    vector<string> misspelledWordsIncorrect;    // Vector with incorrect words only
    vector<string> misspelledWordsCorrect;      // Vector with correct words only
    
    vector<string> fiveRandomWordVector;        // Vector used to store randomly generated words
    vector<string> fiveWordInputVector;         // Vector used to store user's five word input
    
    bool isDictionary = true;                               // To help determine which file to open inside function readWordsIntoVector
    readWordsIntoVector(dictionary, isDictionary);          // Populate dictionary vector
    readWordsIntoVector(misspelledWords, !isDictionary);    // Populate misspelledWords vector
    
    // Create two vectors, one for commonly misspelled incorrect words, the other for commonly misspelled correct words
    // Note: Incorrect words are stored in even indices and corrrect words are stored in odd indices
    for (int i = 0; i < misspelledWords.size()/2; i++) {
        misspelledWordsIncorrect.push_back(misspelledWords.at(2 * i));          // push-back words stored in even indices(incorrect words), starting at index 0
        misspelledWordsCorrect.push_back(misspelledWords.at(2 * i + 1));        // push-back words stored in odd indices(correct words), starting at index 1
    }
    
    // Display size of vectors
    cout << "There are " << dictionary.size() << " words in the full dictionary." << endl;
    cout << "There are " << misspelledWordsIncorrect.size() << " commonly misspelled words." << endl;
    cout << endl;
    
    int choice;
    int wordLength = 5;             // The function populateAndDisplayFiveWordVector() will start by displaying words of length 5
    int numberOfPointsPerWord;
    time_t startTime;
    int elapsedSeconds;
    vector<int> scores;             // This vector stores all the user scores
    
    scores.push_back(0);            // To make sure there is no out-of-range runtime error if the user exits the program in the very first run
    
    do {
        displayMenu();
        cin >> choice;
        
        cout << "Your choice --> " << endl;           // Comment for professor Reed: 'cout << "   Your choice --> " << choice << endl;' doesn't match Zybooks output
        
        // Clear both five word vectors in order to use them again
        fiveRandomWordVector.clear();
        fiveWordInputVector.clear();
        
        switch (choice) {
                
            case 1:  {  // Spell commonly misspelled words (timed)
                
                cout << "Using commonly misspelled words" << endl;
                
                populateAndDisplayFiveWordVector(misspelledWordsIncorrect, misspelledWordsCorrect, fiveRandomWordVector);
                
                cout << endl;
                cout << "Type in those words within goal of 15 seconds: " << endl;
                
                startTime = time( NULL);                                   // Set startTime equal to current time
                typeFiveWords(fiveWordInputVector);                        // Get five word input from user
                elapsedSeconds = difftime( time( NULL), startTime);        // Take the time difference as soon we finish getting the user's input
                
                numberOfPointsPerWord = 3;
                calculateAndDisplayResults(fiveRandomWordVector, fiveWordInputVector, scores, numberOfPointsPerWord, elapsedSeconds);
                
            }   break;
                
            case 2: {
                
                cout << "Using full dictionary" << endl;
                
                populateAndDisplayFiveWordVector(dictionary, fiveRandomWordVector, wordLength);
                
                cout << endl;
                cout << "Type in those words within goal of 15 seconds: " << endl;
                
                startTime = time( NULL);                                 // Set startTime equal to current time
                typeFiveWords(fiveWordInputVector);                      // Get five word input from user
                elapsedSeconds = difftime( time( NULL), startTime);      // Take the time difference as soon we finish getting the user's input
                
                numberOfPointsPerWord = wordLength - 4;
                calculateAndDisplayResults(fiveRandomWordVector, fiveWordInputVector, scores, numberOfPointsPerWord, elapsedSeconds);
                
                wordLength++;                                            // Each time we hit case 2, wordLength will increase by one
                
            }   break;
                
            case 3: {
                
                cout << "Displaying word list entries." << endl;
                chooseListToDisplay(dictionary, misspelledWordsCorrect, misspelledWordsIncorrect);  // Pass all vectors, since the choice is made inside the function
                
            }   break;
                
            case 4: {
                
                string word;
                cout << "Enter the word to lookup: ";
                cin >> word;
                
                long index;
                index = lookUpWord(dictionary, word);       // Function lookUpWord returns index >= 0 if it finds a word. Returns -1 otherwise
                
                if (index >= 0) {
                    cout << word << " was found. " << endl;
                } else { // n < 0
                    cout << word << " was NOT found. " << endl;
                }
                
            }   break;
                
            case 5: {
                
                cout << "Enter new wordLength: ";
                cin >> wordLength;                          // Reset wordLength to use with full dictionary
                cout << endl;
                
            }   break;
                
            default:
                break;
        }
        
    } while(choice != 6);
    
    cout << "Exiting program" << endl;
    
    // Search for the highest score in the score vector
    int maxScore = scores.at(0);
    for (int i = 0; i < scores.size(); i++) {
        
        if (scores.at(i) > maxScore ) {
            maxScore = scores.at(i);
        }
    }
    // Display highest score
    cout << "Best score was " << maxScore << endl;
}
