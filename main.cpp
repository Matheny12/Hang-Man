#include <iostream>
#include "hangMan.h"

using namespace std;

int main() {
    while (true) {
        cout << "Welcome to Hangman!" << endl;
        cout << "=====================" << endl;
        cout << "Play: 1" << endl;
		cout << "Play with Hints: 2" << endl;
        cout << "Show Last Game: 3" << endl;
        cout << "Exit: 4" << endl << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1: {
            Hangman game;
            game.run();
            cout << endl;
            break;
        }
        case 2: {
            Hangman game;
            game.runHints();
            cout << endl;
            break;
        }
        case 3: {
            Hangman game;
            game.showLastGame();
            cout << endl;
            break;
        }
        case 4: {
            cout << "Goodbye!" << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl << endl;
            break;
        }
        }
    }
    return 0;
}