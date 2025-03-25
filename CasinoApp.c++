#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Structure to store user details
struct User {
    string username;
    string password;
    double age;
};

// ===== Function to handle user authentication =====
bool authenticateUser(vector<User>& users) {
    string user, pass, choice;

    cout << "Welcome! Do you want to Log in or Sign up? (Enter 'login' or 'signup'): ";
    cin >> choice;

    // Handle login functionality
    if (choice == "login") {
        cout << "Please log in!" << endl;
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        bool loggedIn = false;
        
        // Check if user exists and the credentials are correct
        for (const auto& u : users) {
            if (u.username == user && u.password == pass) {
                loggedIn = true;
                break;
            }
        }

        // If login is successful, return true
        if (loggedIn) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Invalid credentials. Please try again." << endl;
            return false;
        }
    } 
    // Handle sign-up functionality
    else if (choice == "signup") {
        string newUser, newPass;
        double age;
        cout << "Please enter your age: ";
        cin >> age;

        // Check if user is at least 18 years old
        if (age < 18) {
            cout << "You are not old enough to sign up. Must be 18 or older.\n";
            return false;
        }

        cout << "Please sign up!" << endl;
        cout << "Enter a new username: ";
        cin >> newUser;
        cout << "Enter a new password: ";
        cin >> newPass;

        // Add new user to the list
        users.push_back({newUser, newPass, age});

        // Save the new user details to a file
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
    } 
    // Invalid input (neither 'login' nor 'signup')
    else {
        cout << "Invalid option! Please restart the program and enter either 'login' or 'signup'." << endl;
        return false;
    }
}

// ===== Function to change username =====
void changeUsername(User& currentUser, vector<User>& users) {
    string newUsername;
    cout << "Enter your new username: ";
    cin >> newUsername;

    // Update the username of the current user
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

    // Update the password of the current user
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

// ===== Function to delete the user account =====
void deleteAccount(string& storedUser, string& storedPass) {
    char confirm;
    cout << "Are you sure you want to delete your account? This action is irreversible. (y/n): ";
    cin >> confirm;

    // Confirm if the user really wants to delete the account
    if (confirm == 'y' || confirm == 'Y') {
        ofstream outFile("credentials.txt", ios::trunc); // Clear credentials file
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

// ===== Function to display the settings menu =====
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

        // Handle the user's choice from the settings menu
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
// ===== Function to perform currency exchange =====
void currencyExchange(int& balance) {
    vector<string> currencies = {"USD", "EUR", "CNY"};  // List of available currencies
    string currency;
    double coefficient = 0;  // Exchange coefficient

    // Prompt the user to enter their currency
    cout << "What currency do you use (USD, EUR, CNY): ";
    cin >> currency;

    // Check if the currency is valid
    if (find(currencies.begin(), currencies.end(), currency) == currencies.end()) {
        cout << "Invalid currency. Exiting program.\n";
        return;
    }

    // Set the exchange coefficient based on the chosen currency
    if (currency == "USD" || currency == "usd" || currency == "Usd") {
        coefficient = 1;  // USD is the base currency
    } else if (currency == "EUR" || currency == "eur" || currency == "Eur") {
        coefficient = 0.93;  // EUR to USD conversion rate
    } else if (currency == "CNY" || currency == "cny" || currency == "Cny") {
        coefficient = 0.72;  // CNY to USD conversion rate
    }

    // Display the exchange rate for the chosen currency
    cout << "For " << currency << ", the coefficient is " << coefficient << " chips per unit.\n";

    double value;
    cout << "Enter the value of your currency: ";
    cin >> value;

    // Check if the value is enough to convert into chips
    if (value >= coefficient) {
        int wholeChips = floor(value / coefficient);  // Calculate the whole number of chips
        double remainingCurrency = value - (wholeChips * coefficient);  // Calculate the remaining currency

        cout << "This would be " << wholeChips << " chips.\n";
        cout << "Remaining currency: " << remainingCurrency << " " << currency << ".\n";
        
        balance += wholeChips;  // Add chips to the balance
        cout << "Your new balance is: " << balance << " chips.\n";
    } else {
        cout << "Dear client, please add more money.\n";  // If the value is less than the coefficient
    }
}

// ===== Function to display Blackjack instructions =====
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

// ===== Function to play Blackjack =====
void blackjack(int& balance, int& gamesPlayed, int& gamesWon, int& gamesLost, int& bonusMultiplier) {
    srand(time(0));  // Seed the random number generator for random card values

    int bet = 0;
    int dealerCard = 2 + (rand() % 9);  // Generate dealer's card
    int playerCard = 4 + (rand() % 18);  // Generate player's initial card
    int newCard = 2 + (rand() % 9);  // New card to be drawn
    int option;

    // Apply bonus multiplier to the bet if applicable
    bet *= bonusMultiplier;
    cout << "Your game is Blackjack. Type 1 to start the game: ";
    cin >> option;

    if (option == 1) {
        cout << "Enter the bet amount: ";
        cin >> bet;

        // Check if the player has enough balance for the bet
        if (bet > balance) {
            cout << "Insufficient balance.\n";
            return;
        }

        balance -= bet;  // Deduct bet amount from balance
        cout << "Your bet is: " << bet << " chips.\n";
        cout << "Dealer's card: " << dealerCard << endl;
        cout << "Your card: " << playerCard << endl;

        // If player does not have Blackjack (21), offer the option to hit or stand
        if (playerCard != 21) {
            cout << "Not Blackjack! Hit or Stand? (1 for Hit, 0 for Stand): ";
            cin >> option;

            if (option == 1) {
                playerCard += newCard;  // Add a new card to the player's hand
                cout << "Your new card: " << newCard << endl;
                cout << "Your total: " << playerCard << endl;
            }
        }

        // Dealer logic: Dealer must stand on 17 or higher
        while (dealerCard < 17) {
            dealerCard += newCard;
        }

        cout << "Dealer's total: " << dealerCard << endl;

        // Check if the player busts (total over 21)
        if (playerCard > 21) {
            cout << "You busted! You lost.\n";
            gamesLost++;
        } else if (dealerCard > 21 || playerCard > dealerCard) {
            // Player wins if dealer busts or player's total is higher
            cout << "You win!\n";
            balance += 2 * bet;  // Player wins double the bet
            gamesWon++;
        } else if (playerCard == dealerCard) {
            cout << "It's a tie!\n";
            balance += bet;  // Tie, return the bet to the player
        } else {
            cout << "Dealer wins!\n";
            gamesLost++;
        }

        gamesPlayed++;  // Increment the number of games played
    }
}

// ===== Function to handle bonuses =====
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

    // Handle each bonus option
    if (bonusChoice == 1) {
        if (balance >= 50) {
            balance -= 50;
            balance += 30;  // Add 30 chips for 50 chips
            cout << "You bought 30 extra chips for 50 chips! New balance: " << balance << endl;
        } else {
            cout << "Not enough chips for this bonus.\n";
        }
    } else if (bonusChoice == 2) {
        if (balance >= 100) {
            balance -= 100;
            bonusMultiplier = 2;  // Set bonus multiplier to 2 for the next round
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

// ===== Function to display game statistics =====
void displayStats(int gamesPlayed, int gamesWon, int gamesLost, int balance) {
    cout << "\nGame Statistics:\n";
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    cout << "Games Lost: " << gamesLost << endl;
    cout << "Balance: " << balance << " chips\n";
    cout << "View Bonuses: \n";
}

// Available slot symbols
vector<string> symbols = {"Cherry", "Lemon", "Bell", "Seven", "Bar"};

// ===== Function to spin the slot machine =====
void slotMachine(int& balance) {
    srand(time(0));  // Seed the random number generator

    int wheels;
    cout << "Enter the number of wheels (3 to 5): ";
    cin >> wheels;

    // Check if the number of wheels is valid
    if (wheels < 3 || wheels > 5) {
        cout << "Invalid number of wheels! Choose between 3 and 5.\n";
        return;
    }

    int bet;
    cout << "Enter your bet: ";
    cin >> bet;

    // Check if the player has enough balance for the bet
    if (bet > balance) {
        cout << "Insufficient balance!\n";
        return;
    }

    balance -= bet;  // Deduct the bet from balance

    vector<string> results;
    cout << "Spinning...\n";

    // Spin each wheel and store the result
    for (int i = 0; i < wheels; i++) {
        int randIndex = rand() % symbols.size();
        results.push_back(symbols[randIndex]);
    }

    // Display the results of the spin
    for (const string& symbol : results) {
        cout << "[" << symbol << "] ";
    }
    cout << endl;

    // Check if all wheels match (win condition)
    bool win = true;
    for (int i = 1; i < wheels; i++) {
        if (results[i] != results[0]) {
            win = false;
            break;
        }
    }

    // Calculate the payout if all wheels match
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
// =====Function to play Roulette =====
void rouletteGame(int& balance, int& gamesPlayed, int& gamesWon, int& gamesLost) {
    int betAmount;
    cout << "Enter your bet amount: ";
    cin >> betAmount;

    // Check if the player has enough balance for the bet
    if (betAmount > balance) {
        cout << "You do not have enough chips to make this bet.\n";
        return;
    }

    string betType;
    cout << "Do you want to bet on a (1) Number, (2) Color (Red/Black), (3) Even/Odd, or (4) Green? (Enter 1, 2, 3, or 4): ";
    cin >> betType;

    int numberBet = 0;
    string colorBet = "";
    bool isEvenOddBet = false;
    bool isGreenBet = false;

    // Handle different types of bets
    if (betType == "1") {
        cout << "Enter a number between 0 and 36 to bet on: ";
        cin >> numberBet;
    } 
    else if (betType == "2") {
        cout << "Enter a color to bet on (Red/Black): ";
        cin >> colorBet;

        // Standardize the input color to Red or Black
        if (colorBet == "red" || colorBet == "Red" || colorBet == "RED") {
            colorBet = "Red";
        } else if (colorBet == "black" || colorBet == "Black" || colorBet == "BLACK") {
            colorBet = "Black";
        } else {
            cout << "Invalid color! Please enter Red or Black.\n";
            return;
        }
    } 
    else if (betType == "3") {
        cout << "Do you want to bet on (1) Even or (2) Odd? ";
        cin >> betType;

        // Standardize input for Even or Odd
        if (betType == "1" || betType == "even" || betType == "Even" || betType == "EVEN") {
            betType = "Even";
        } else if (betType == "2" || betType == "odd" || betType == "Odd" || betType == "ODD") {
            betType = "Odd";
        } else {
            cout << "Invalid choice! Please choose Even or Odd.\n";
            return;
        }

        isEvenOddBet = true;
    } 
    else if (betType == "4") {
        isGreenBet = true;  
    } else {
        cout << "Invalid option! Exiting game.\n";
        return;
    }

    srand(time(0));  // Seed the random number generator
    int rouletteSpin = rand() % 37;  // Spin the roulette wheel (0-36)
    string resultColor;
    bool isEven = rouletteSpin % 2 == 0;

    // Determine the color based on the spin result
    if (rouletteSpin == 0) {
        resultColor = "Green";
    } else if (rouletteSpin % 2 == 0) {
        resultColor = "Black";
    } else {
        resultColor = "Red";
    }

    cout << "The roulette spin landed on: " << rouletteSpin << " (" << resultColor << ")\n";

    // Check for winning conditions based on the player's bet
    if (betType == "1" && numberBet == rouletteSpin) {
        balance += betAmount * 36;  // Number bet wins 36 times the bet amount
        gamesWon++;
        cout << "You win! Your new balance: " << balance << endl;
    } 
    else if (betType == "2" && colorBet == resultColor) {
        balance += betAmount * 2;  // Color bet wins 2 times the bet amount
        gamesWon++;
        cout << "You win! Your new balance: " << balance << endl;
    } 
    else if (isEvenOddBet && betType == "Even" && isEven) {
        balance += betAmount * 2;  // Even bet wins 2 times the bet amount
        gamesWon++;
        cout << "You win! Your new balance: " << balance << endl;
    }
    else if (isEvenOddBet && betType == "Odd" && !isEven) {
        balance += betAmount * 2;  // Odd bet wins 2 times the bet amount
        gamesWon++;
        cout << "You win! Your new balance: " << balance << endl;
    } 
    else if (isGreenBet && rouletteSpin == 0) {
        balance += betAmount * 36;  // Green bet wins 36 times the bet amount
        gamesWon++;
        cout << "You win! Your new balance: " << balance << endl;
    } 
    else {
        balance -= betAmount;  // If the player loses, subtract the bet amount
        gamesLost++;
        cout << "You lose. Your new balance: " << balance << endl;
    }

    gamesPlayed++;  // Increment the number of games played
}

// =====Function to display the game menu=====
void gameMenu(int& balance, int& gamesPlayed, int& gamesWon, int& gamesLost, int& bonusMultiplier) {
    int gameChoice;
    
    while (true) {
        // Display the game menu for the user to choose a game
        cout << "\n----- Games -----\n";
        cout << "1. Blackjack\n";
        cout << "2. Slot Machine\n";
        cout << "3. Roulette\n";
        cout << "4. Return to main menu\n";
        cout << "Choose a game (1-3): ";
        cin >> gameChoice;

        switch (gameChoice) {
            case 1:
                displayBlackjackInstructions();  // Show instructions before starting the game
                cout<< "\n========== Game ==========\n";
                blackjack(balance, gamesPlayed, gamesWon, gamesLost, bonusMultiplier);  // Start Blackjack game
                break;
            case 2:
                cout<< "\n========== Game ==========\n";
                slotMachine(balance);  // Start Slot Machine game
                break;
            case 3:
                cout<< "\n========== Game ==========\n";
                rouletteGame(balance, gamesPlayed, gamesWon, gamesLost);  // Start Roulette game
                break;
            case 4:
                return;  // Return to the main menu
            default:
                cout << "Invalid choice. Please try again.\n";  // Handle invalid choice
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
        storedUser = "joe";  // Default user credentials
        storedPass = "2315";
        users.push_back({storedUser, storedPass, 20.0});  // default user
    }

    // Authenticate the user before proceeding
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
        cout << "\n----- Casino Main Menu: -----\n";
        cout << "Balance: " << balance << " chips.\n";
        cout << "1. Game menu\n";
        cout << "2. View statistics\n";
        cout << "3. Currency exchange\n";
        cout << "4. Buy bonus\n";
        cout << "5. Settings\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Main menu handling
        switch (choice) {
            case 1:
                gameMenu(balance, gamesPlayed, gamesWon, gamesLost, bonusMultiplier);  // Access the game menu
                break;  
            case 2:
                displayStats(gamesPlayed, gamesWon, gamesLost, balance);  // View game statistics
                break;
            case 3:
                currencyExchange(balance);  // Perform currency exchange
                break;
            case 4:
                handleBonuses(gamesPlayed, balance, bonusMultiplier);  // Handle bonuses
                break;
            case 5:
                settingsMenu(currentUser, users);  // Access settings menu
                break;
            case 6:
                cout << "Exiting the game. Goodbye!\n";  // Exit the game
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";  // Handle invalid option
        }
    }

    return 0;
}
