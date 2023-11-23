#include "libraries.h"

int main()
{
    // Before actually letting the user input anything, we must read in accounts from a textfile to validate uniqueness and to verify information.
    std::ifstream inFile("accounts.txt");
    if (inFile.is_open())
    {
        std::string username = "";
        std::map<std::string, User *> userAccountData; // uses the username as the KEY and the pointer to the User object as the VALUE.
        User *currentUser = NULL;
        readIntoMap(inFile, userAccountData); // takes the accounts file and makes Users to place into userAccountData-- our map.

        std::cout << "\n\n\n\n\n"
                  << std::setw(78) << std::string('#', 30) << std::endl
                  << std::setw(76) << "WELCOME TO THE SPOTIFY MIMIC!\n"
                  << std::setw(78) << std::string('#', 30) << std::endl;

        currentUser = accessAccount(currentUser, username, userAccountData);

        accessInnerFunctions(currentUser); // calls the bulk of the program

        readFromMap(userAccountData); // this function prints out all current user data to the text file and deletes the heaped data inside the map.
    }
    else
        std::cout << "A fatal error has occurred when trying to load account information from \"accounts.txt\"" << std::endl
                  << "Exiting application automatically...";
}