#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "hangMan.h"
#include <algorithm>
#include <cctype>
#include <locale>

using namespace std;

static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

bool Hangman::gamePlayed = false;
string Hangman::lastWord = "";
string Hangman::lastGuessedWord = "";
string Hangman::lastCorrectLetters = "";
string Hangman::lastWrongLetters = "";
int Hangman::lastWrongGuesses = 0;

void Hangman::run() {
    loadWord();
    while (wrongGuesses < maxWrongGuesses && guessedWord != word) {
        displayWord();
        displayCorrectLetters();
        displayHangman(wrongGuesses);
        displayWrongLetters();
        cout << "Do you want to guess the word? (y/n): ";
        cin >> doYou;
        cout << endl;
        if (doYou == 'y' || doYou == 'Y') {
            string guess;
            cout << "Enter your guess (All Caps): ";
            cin >> guess;
            if (guess == word) {
                guessedWord = word;
                displayVictory();
                break;
            }
            else {
                cout << endl;
                cout << "Wrong guess!" << endl << endl;
                wrongGuesses++;
                continue;
            }
        }
        else if (doYou == 'n' || doYou == 'N') {
            char letter;
            cout << "Enter a letter (All Caps): ";
            cin >> letter;
            cout << endl;
            if (correctLetters.find(letter) != string::npos || wrongLetters.find(letter) != string::npos) {
                alreadyUsed();
                continue;
            }
            if (!checkLetter(letter)) {
                wrongGuesses++;
            }
        }
        if (wrongGuesses < maxWrongGuesses) {
            cout << "You have " << maxWrongGuesses - wrongGuesses << " guesses left." << endl;
        }
        if (wrongGuesses == maxWrongGuesses) {
            displayGameOver();
        }
        else if (guessedWord == word) {
            displayVictory();
        }
    }
    gamePlayed = true;
    lastWord = word;
    lastGuessedWord = guessedWord;
    lastCorrectLetters = correctLetters;
    lastWrongLetters = wrongLetters;
    lastWrongGuesses = wrongGuesses;
}

void Hangman::runHints() {
    loadWordHints();
    while (wrongGuesses < maxWrongGuesses && guessedWord != word) {
        cout << "Word: " << guessedWord << endl;
        cout << "Hint: " << hint << endl << endl;
        displayCorrectLetters();
        displayHangman(wrongGuesses);
        displayWrongLetters();
        cout << "Do you want to guess the word? (y/n): ";
        cin >> doYou;
        cout << endl;
        if (doYou == 'y' || doYou == 'Y') {
            string guess;
            cout << "Enter your guess (All Caps): ";
            cin >> guess;
            if (guess == word) {
                guessedWord = word;
                displayVictory();
                break;
            }
            else {
                cout << endl;
                cout << "Wrong guess!" << endl << endl;
                wrongGuesses++;
                continue;
            }
        }
        else if (doYou == 'n' || doYou == 'N') {
            char letter;
            cout << "Enter a letter (All Caps): ";
            cin >> letter;
            cout << endl;
            if (correctLetters.find(letter) != string::npos || wrongLetters.find(letter) != string::npos) {
                alreadyUsed();
                continue;
            }
            if (!checkLetter(letter)) {
                wrongGuesses++;
            }
        }
        if (wrongGuesses < maxWrongGuesses) {
            cout << "You have " << maxWrongGuesses - wrongGuesses << " guesses left." << endl;
        }
        if (wrongGuesses == maxWrongGuesses) {
            displayGameOver();
        }
        else if (guessedWord == word) {
            displayVictory();
        }
    }

    gamePlayed = true;
    lastWord = word;
    lastGuessedWord = guessedWord;
    lastCorrectLetters = correctLetters;
    lastWrongLetters = wrongLetters;
    lastWrongGuesses = wrongGuesses;
}

bool Hangman::checkLetter(char letter) {
    bool found = false;
    for (size_t i = 0; i < word.length(); i++) {
        if (word[i] == letter) {
            guessedWord[i] = letter;
            found = true;
        }
    }
    if (!found) {
        wrongLetters += letter;
    }
    else {
        correctLetters += letter;
    }
    return found;
}

void Hangman::displayWord() {
    cout << "Word: " << guessedWord << endl << endl;
}

void Hangman::displayCorrectLetters() {
    cout << "Correct letters: " << correctLetters << endl << endl;
}

void Hangman::displayHangman(int wrongGuesses) {
    if (wrongGuesses == 0) {
        cout << "    " << endl << endl;
    }
    else if (wrongGuesses == 1) {
        cout << "   O" << endl << endl;
    }
    else if (wrongGuesses == 2) {
        cout << "   O" << endl;
        cout << "   |" << endl << endl;
    }
    else if (wrongGuesses == 3) {
        cout << "   O" << endl;
        cout << "  /|" << endl << endl;
    }
    else if (wrongGuesses == 4) {
        cout << "   O" << endl;
        cout << "  /|\\" << endl << endl;
    }
    else if (wrongGuesses == 5) {
        cout << "   O" << endl;
        cout << "  /|\\" << endl;
        cout << "  /" << endl << endl;
    }
    else if (wrongGuesses == 6) {
        cout << "   O" << endl;
        cout << "  /|\\" << endl;
        cout << "  / \\" << endl << endl;
    }
}

void Hangman::displayWrongLetters() {
    cout << "Wrong letters: " << wrongLetters << endl << endl;
}

void Hangman::displayGameOver() {
    cout << "Game Over! The word was: " << word << endl << endl;
}

void Hangman::displayVictory() {
    cout << "Congratulations! You guessed the word: " << word << endl << endl;
}

void Hangman::alreadyUsed() {
    cout << "You have already used this letter." << endl << endl;
}

void Hangman::loadWord() {
    ifstream file("words.txt");
    if (!file) {
        cerr << "Error opening file." << endl;
        exit(1);
    }
    vector<string> wordsList;
    string line;
    while (getline(file, line)) {
        if (!line.empty())
            wordsList.push_back(line);
    }
    file.close();
    srand(time(0));
    int randomIndex = rand() % wordsList.size();
    word = wordsList[randomIndex];
    guessedWord = string(word.length(), '_');
    correctLetters = "";
    wrongLetters = "";
    wrongGuesses = 0;
    maxWrongGuesses = 6;
}

void Hangman::loadWordHints() {
    ifstream file("wordsHints.txt");
    if (!file) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    vector<pair<string, string>> wordsList;
    string wordLine, hintLine;

    while (getline(file, wordLine) && getline(file, hintLine)) {
        trim(wordLine);
        trim(hintLine);
        wordsList.push_back({ wordLine, hintLine });
    }
    file.close();

    if (wordsList.empty()) {
        cerr << "No words found in file." << endl;
        exit(1);
    }

    srand(time(0));
    int randomIndex = rand() % wordsList.size();

    this->word = wordsList[randomIndex].first;
    this->hint = wordsList[randomIndex].second;

    guessedWord = string(word.length(), '_');
    correctLetters = "";
    wrongLetters = "";
    wrongGuesses = 0;
    maxWrongGuesses = 6;
}

void Hangman::showLastGame() {
    if (!gamePlayed) {
        cout << "No game played yet." << endl;
        return;
    }
    cout << "Last game details:" << endl;
    cout << "Word: " << lastWord << endl;
    cout << "Guessed Word: " << lastGuessedWord << endl;
    cout << "Correct Letters: " << lastCorrectLetters << endl;
    cout << "Wrong Letters: " << lastWrongLetters << endl;
    cout << "Wrong Guesses: " << lastWrongGuesses << endl;
}