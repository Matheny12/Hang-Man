#include <iostream>
#include "hangMan.h"

using namespace std;

int main() {
    while (true) {
        cout << "Welcome to Hangman!" << endl;
        cout << "=====================" << endl;
        cout << "Play: 1" << endl;
        cout << "Show Last Game: 2" << endl;
        cout << "Exit: 3" << endl << endl;

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
            game.showLastGame();
            cout << endl;
            break;
        }
        case 3: {
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