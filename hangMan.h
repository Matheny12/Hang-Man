#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Hangman {
private:
    string word;
    string hint;
    string guessedWord;
    string correctLetters;
    string wrongLetters;
    int maxWrongGuesses;
    int wrongGuesses;
    char doYou;
public:
    static bool gamePlayed;
    static string lastWord;
    static string lastGuessedWord;
    static string lastCorrectLetters;
    static string lastWrongLetters;
    static int lastWrongGuesses;
    void run();
    bool checkLetter(char letter);
    void displayWord();
    void displayCorrectLetters();
    void displayHangman(int wrongGuesses);
    void displayWrongLetters();
    void displayGameOver();
    void displayVictory();
    void alreadyUsed();
    void loadWord();
    void showLastGame();
	void loadWordHints();
    void runHints();
};

#endif