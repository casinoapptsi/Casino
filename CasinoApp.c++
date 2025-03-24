#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct User {
    string username;
    string password;
    double age;
};

// =====Function to handle user authentication=====
bool authenticateUser(vector<User>& users) {
    string user, pass, choice;

    cout << "Welcome! Do you want to Log in or Sign up? (Enter 'login' or 'signup'): ";
    cin >> choice;

    if (choice == "login") {
        cout << "Please log in!" << endl;
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        bool loggedIn = false;
        for (const auto& u : users) {
            if (u.username == user && u.password == pass) {
                loggedIn = true;
                break;
            }
        }

        if (loggedIn) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Invalid credentials. Please try again." << endl;
            return false;
        }
    } else if (choice == "signup") {
        string newUser, newPass;
        double age;
        cout << "Please enter your age: ";
        cin >> age;

        if (age < 18) {
            cout << "You are not old enough to sign up. Must be 18 or older.\n";
            return false;
        }

        cout << "Please sign up!" << endl;
        cout << "Enter a new username: ";
        cin >> newUser;
        cout << "Enter a new password: ";
        cin >> newPass;

        users.push_back({newUser, newPass, age});

        ofstream outFile("credentials.txt", ios::trunc);
        if (outFile) {
            for (const auto& u : users) {
                outFile << u.username << endl;
                outFile << u.password << endl;
                outFile << u.age << endl;
            }
            outFile.close();
            cout << "Sign-up successful! Your credentials have been saved." << endl;
            return true;
        } else {
            cout << "Error: Could not save credentials!" << endl;
            return false;
        }
    } else {
        cout << "Invalid option! Please restart the program and enter either 'login' or 'signup'." << endl;
        return false;
    }
}

// ===== Function to change username =====
void changeUsername(User& currentUser, vector<User>& users) {
    string newUsername;
    cout << "Enter your new username: ";
    cin >> newUsername;
    currentUser.username = newUsername;
    cout << "Username changed successfully!\n";

    // Write updated user list to file
    ofstream outFile("credentials.txt", ios::trunc);
    if (outFile) {
        for (const auto& u : users) {
            outFile << u.username << endl;
            outFile << u.password << endl;
            outFile << u.age << endl;
        }
        outFile.close();
    } else {
        cout << "Error: Could not save credentials!" << endl;
    }
}

// ===== Function to change password =====
void changePassword(User& currentUser, vector<User>& users) {
    string newPassword;
    cout << "Enter your new password: ";
    cin >> newPassword;
    currentUser.password = newPassword;
    cout << "Password changed successfully!\n";

    // Write updated user list to file
    ofstream outFile("credentials.txt", ios::trunc);
    if (outFile) {
        for (const auto& u : users) {
            outFile << u.username << endl;
            outFile << u.password << endl;
            outFile << u.age << endl;
        }
        outFile.close();
    } else {
        cout << "Error: Could not save credentials!" << endl;
    }
}

// =====Function to delete the user account=====
void deleteAccount(string& storedUser, string& storedPass) {
    char confirm;
    cout << "Are you sure you want to delete your account? This action is irreversible. (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        ofstream outFile("credentials.txt", ios::trunc); // Clear credentials
        if (outFile) {
            outFile.close();
            storedUser = "";
            storedPass = "";
            cout << "Your account has been successfully deleted.\n";
            exit(0);  // Exit the program
        } else {
            cout << "Error: Could not delete account.\n";
        }
    } else {
        cout << "Account deletion canceled.\n";
    }
}

// =====Function to display the settings menu=====
void settingsMenu(User& currentUser, vector<User>& users) {
    int settingsChoice;
    
    while (true) {
        cout << "\n----- Settings -----\n";
        cout << "1. Change username\n";
        cout << "2. Change password\n";
        cout << "3. Delete account\n";
        cout << "4. Return to main menu\n";
        cout << "Choose an option (1-4): ";
        cin >> settingsChoice;

        switch (settingsChoice) {
            case 1:
                changeUsername(currentUser, users);
                break;
            case 2:
                changePassword(currentUser, users);
                break;
            case 3:
                deleteAccount(currentUser.username, currentUser.username);
                break;
            case 4:
                return;  // Return to the main menu
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

// =====Function to perform currency exchange=====
void currencyExchange(int& balance) {
    vector<string> currencies = {"USD", "EUR", "CNY"};
    string currency;
    double coefficient = 0;

    cout << "What currency do you use (USD, EUR, CNY): ";
    cin >> currency;

    if (find(currencies.begin(), currencies.end(), currency) == currencies.end()) {
        cout << "Invalid currency. Exiting program.\n";
        return;
    }

    if (currency == "USD" || "usd" || "Usd") {
        coefficient = 1;
    } else if (currency == "EUR" || "eur" || "Eur") {
        coefficient = 0.93;
    } else if (currency == "CNY" || "cny" || "Cny") {
        coefficient = 0.72;
    }

    cout << "For " << currency << ", the coefficient is " << coefficient << " chips per unit.\n";

    double value;
    cout << "Enter the value of your currency: ";
    cin >> value;

    if (value >= coefficient) {
        int wholeChips = floor(value / coefficient);
        double remainingCurrency = value - (wholeChips * coefficient);

        cout << "This would be " << wholeChips << " chips.\n";
        cout << "Remaining currency: " << remainingCurrency << " " << currency << ".\n";
        
        balance += wholeChips;  
        cout << "Your new balance is: " << balance << " chips.\n";
    } else {
        cout << "Dear client, please add more money.\n";
    }
}

// =====Function to display Blackjack instructions=====
void displayBlackjackInstructions() {
    cout << "\n----- Blackjack Instructions -----\n";
    cout << "1. In Blackjack, you and the dealer are dealt two cards each.\n";
    cout << "2. The goal is to get as close to 21 as possible without going over.\n";
    cout << "3. You can choose to 'Hit' (draw another card) or 'Stand' (keep your current cards).\n";
    cout << "4. If your cards total over 21, you 'bust' and lose the game.\n";
    cout << "5. If the dealer's cards total over 21, you win.\n";
    cout << "6. If you have a higher total than the dealer, you win.\n";
    cout << "7. If you have the same total as the dealer, it's a tie.\n";
    cout << "Good luck!\n";
    cout << "\n";
}

// =====Function to play Blackjack=====
void blackjack(int& balance, int& gamesPlayed, int& gamesWon, int& gamesLost, int& bonusMultiplier) {
    srand(time(0));

    int bet;
    int dealerCard = 2 + (rand() % 9);
    int playerCard = 4 + (rand() % 18);
    int newCard = 2 + (rand() % 9);
    int option;

    // Apply bonus multiplier if any
    bet *= bonusMultiplier;
    cout << "Your game is Blackjack. Type 1 to start the game: ";
    cin >> option;

    if (option == 1) {
        cout << "Enter the bet amount: ";
        cin >> bet;

        if (bet > balance) {
            cout << "Insufficient balance.\n";
            return;
        }

        balance -= bet;
        cout << "Your bet is: " << bet << " chips.\n";
        cout << "Dealer's card: " << dealerCard << endl;
        cout << "Your card: " << playerCard << endl;

        if (playerCard != 21) {
            cout << "Not Blackjack! Hit or Stand? (1 for Hit, 0 for Stand): ";
            cin >> option;

            if (option == 1) {
                playerCard += newCard;
                cout << "Your new card: " << newCard << endl;
                cout << "Your total: " << playerCard << endl;
            }
        }

        // Dealer logic: Dealer stands on 17 or higher
        while (dealerCard < 17) {
            dealerCard += newCard;
        }

        cout << "Dealer's total: " << dealerCard << endl;

        if (playerCard > 21) {
            cout << "You busted! You lost.\n";
            gamesLost++;
        } else if (dealerCard > 21 || playerCard > dealerCard) {
            cout << "You win!\n";
            balance += 2 * bet;  // Double the bet for a win
            gamesWon++;
        } else if (playerCard == dealerCard) {
            cout << "It's a tie!\n";
            balance += bet;  // Return the bet amount for a tie
        } else {
            cout << "Dealer wins!\n";
            gamesLost++;
        }

        gamesPlayed++;
    }
}

// =====Function to handle bonuses=====
void handleBonuses(int gamesPlayed, int& balance, int& bonusMultiplier) {
    int bonusChoice;
    cout << "\nAvailable bonuses:\n";
    cout << "1. Extra 30 chips for 50 chips.\n";
    cout << "2. Double the bet for 100 chips (Next round only).\n";
    cout << "3. Extra card in Blackjack for 150 chips.\n";
    cout << "4. Refund half your lost bet for 200 chips.\n";
    cout << "Your balance: " << balance << " chips.\n";
    cout << "Choose a bonus (1-4), or 0 to cancel: ";
    cin >> bonusChoice;

    if (bonusChoice == 1) {
        if (balance >= 50) {
            balance -= 50;
            balance += 30;
            cout << "You bought 30 extra chips for 50 chips! New balance: " << balance << endl;
        } else {
            cout << "Not enough chips for this bonus.\n";
        }
    } else if (bonusChoice == 2) {
        if (balance >= 100) {
            balance -= 100;
            bonusMultiplier = 2;
            cout << "You bought the double bet bonus! Your next bet will be doubled.\n";
        } else {
            cout << "Not enough chips for this bonus.\n";
        }
    } else if (bonusChoice == 3) {
        if (balance >= 150) {
            balance -= 150;
            cout << "You bought the extra card bonus! You will get one more card in your next Blackjack game.\n";
        } else {
            cout << "Not enough chips for this bonus.\n";
        }
    } else if (bonusChoice == 4) {
        if (balance >= 200) {
            balance -= 200;
            cout << "You bought the refund bonus! You will get half your lost bet refunded after the next loss.\n";
        } else {
            cout << "Not enough chips for this bonus.\n";
        }
    }
}

// =====Function to display game statistics=====
void displayStats(int gamesPlayed, int gamesWon, int gamesLost, int balance) {
    cout << "\nGame Statistics:\n";
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    cout << "Games Lost: " << gamesLost << endl;
    cout << "Balance: " << balance << " chips\n";
    cout << "Bonuses: Right now you don't have any bonuses.\n";
}

// Available slot symbols
vector<string> symbols = {"Cherry", "Lemon", "Bell", "Seven", "Bar"};

// =====Function to spin the slot machine=====
void slotMachine(int& balance) {
    srand(time(0)); // Seed the random generator

    int wheels;
    cout << "Enter the number of wheels (3 to 5): ";
    cin >> wheels;

    if (wheels < 3 || wheels > 5) {
        cout << "Invalid number of wheels! Choose between 3 and 5.\n";
        return;
    }

    int bet;
    cout << "Enter your bet: ";
    cin >> bet;

    if (bet > balance) {
        cout << "Insufficient balance!\n";
        return;
    }

    balance -= bet;

    vector<string> results;
    cout << "Spinning...\n";

    // Spin each wheel and store the result
    for (int i = 0; i < wheels; i++) {
        int randIndex = rand() % symbols.size();
        results.push_back(symbols[randIndex]);
    }

    // Display results
    for (const string& symbol : results) {
        cout << "[" << symbol << "] ";
    }
    cout << endl;

    // Check if all wheels match
    bool win = true;
    for (int i = 1; i < wheels; i++) {
        if (results[i] != results[0]) {
            win = false;
            break;
        }
    }

    // Calculate payout
    if (win) {
        int multiplier = (wheels == 3) ? 3 : (wheels == 4) ? 5 : 10;
        int winnings = bet * multiplier;
        balance += winnings;
        cout << "Congratulations! You won " << winnings << " chips!\n";
    } else {
        cout << "You lost this round. Try again!\n";
    }

    cout << "Your new balance: " << balance << " chips.\n";
}

// =====Function to display the game menu=====
void gameMenu(int& balance, int& gamesPlayed, int& gamesWon, int& gamesLost, int& bonusMultiplier) {
    int gameChoice;
    
    while (true) {
        cout << "\n===== Games =====\n";
        cout << "1. Blackjack\n";
        cout << "2. Slot Machine\n";
        cout << "3. Return to main menu\n";
        cout << "Choose a game (1-3): ";
        cin >> gameChoice;

        switch (gameChoice) {
            case 1:
                displayBlackjackInstructions();  // Show instructions before starting the game
                cout<< "\n========== Game ==========\n";
                blackjack(balance, gamesPlayed, gamesWon, gamesLost, bonusMultiplier);
                break;
            case 2:
                cout<< "\n========== Game ==========\n";
                slotMachine(balance);
                break;
            case 3:
                return;  // Return to the main menu
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    vector<User> users;
    User currentUser;

    // Load user credentials from file if available
    ifstream inFile("credentials.txt");
    string storedUser;
    string storedPass;

    if (inFile) {
        while (getline(inFile, storedUser) && getline(inFile, storedPass)) {
            double age;
            inFile >> age;
            users.push_back({storedUser, storedPass, age});
        }
        inFile.close();
    } else {
        storedUser = "joe";
        storedPass = "2315";
        users.push_back({storedUser, storedPass, 20.0});  // default user
    }

    // Authenticate user
    if (!authenticateUser(users)) {
        return 1;  // Exit if authentication fails
    }

    // Initialize game variables
    int balance = 100;  // Starting balance
    int gamesPlayed = 0, gamesWon = 0, gamesLost = 0;
    int bonusMultiplier = 1;  // Default no bonus multiplier
    int choice;

    while (true) {
        // Display main menu
        cout << "\n=== Game Menu: ===\n";
        cout << "Balance: " << balance << " chips.\n";
        cout << "1. Game menu\n";
        cout << "2. View statistics\n";
        cout << "3. Currency exchange\n";
        cout << "4. Buy bonus\n";
        cout << "5. Settings\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                gameMenu(balance, gamesPlayed, gamesWon, gamesLost, bonusMultiplier); 
                break;  
            case 2:
                displayStats(gamesPlayed, gamesWon, gamesLost, balance);
                break;
            case 3:
                currencyExchange(balance);
                break;
            case 4:
                handleBonuses(gamesPlayed, balance, bonusMultiplier);
                break;
            case 5:
                settingsMenu(currentUser, users);  
                break;
            case 6:
                cout << "Exiting the game. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
