#include "libraries.h"

// make more descriptive comments

void readIntoMap(std::ifstream &userInFile, std::map<std::string, User *> &userAccountData)
{
    std::string username, password;
    User *newUser;
    while (userInFile >> username)
    {
        userInFile >> password;
        newUser = new User(username, password);
        std::ifstream libraryInFile(username + ".txt");
        if (libraryInFile.good())
        {
            newUser->queue = new Queue(); // reserves space in memory to place the default queue for the specific newUser's existing playlist.
            Song tempSong;
            int librarySize;
            std::string buffer;
            libraryInFile >> librarySize;
            libraryInFile.ignore();
            for (int i = 0; i < librarySize; i++)
            {
                std::getline(libraryInFile, tempSong.songName);
                std::getline(libraryInFile, tempSong.artist);
                std::getline(libraryInFile, buffer);
                tempSong.minutes = stoi(buffer);
                newUser->addSongToLibrary(&tempSong);
                newUser->queue->addSongToDefaultQueue(&tempSong);
            }
        }

        libraryInFile.close();
        userAccountData[username] = newUser;
    }
    userInFile.close();
}

// reads from the map and prints out the user data into files.

void readFromMap(std::map<std::string, User *> &userAccountData)
{
    Database::iterator it;
    int i;
    std::ofstream userOutFile("accounts.txt");

    for (it = userAccountData.begin(); it != userAccountData.end(); it++) // updates the database with the current user base and each users library/playlist.
    {
        userOutFile << it->second->getUserName() << std::endl
                    << it->second->getPassWord() << std::endl;
        std::ofstream libraryOutFile(it->second->getUserName() + ".txt");
        libraryOutFile << it->second->getLibrarySize() << std::endl;
        for (i = 0; i < it->second->getLibrarySize(); i++)
        {
            libraryOutFile << it->second->getLibrarySong(i)->songName << std::endl;
            libraryOutFile << it->second->getLibrarySong(i)->artist << std::endl;
            libraryOutFile << it->second->getLibrarySong(i)->minutes << std::endl;
        }
        delete it->second; // removes all dynamically allocated memory.
    }
}

// this function keeps the main function clean from cluttering mess like this do-while loop.

User *accessAccount(User *currentUser, std::string username, std::map<std::string, User *> &userAccountData)
{
    int accountChoice;
    do
    {
        std::cout << "\n1. Create an account\n"
                  << "2. Login\n"
                  << "Choice: ";
        validateIntegerInput(accountChoice, 2, 1);

        if (accountChoice == 1)
            currentUser = createAccount(userAccountData, username);
        else
            currentUser = loginToExistingAccount(userAccountData);

    } while (!currentUser);

    return currentUser;
}

// creates accounts based off of availability.

User *createAccount(std::map<std::string, User *> &userAccountData, std::string old_username)
{
    std::string password;

    if (old_username == "") // if calling from main function
    {
        std::string new_username;
        std::cout << "New Username: ";
        std::cin >> new_username;
        while (!(userAccountData.find(new_username) == userAccountData.end())) // this while loops checks for uniqueness.
        {
            std::cout << "\nUsername taken\n"
                      << "New Username: ";
            std::cin >> new_username;
        }
        // comments added here
        std::cout << "\nNew Password: ";
        std::cin >> password;
        password = sha256(password);
        User *newUser = new User(new_username, password);
        userAccountData[new_username] = newUser;

        std::cout << "\nSuccesfully created your account!\n";
        return newUser;
    }

    else // calling from login function using logins "username" to make the new account
    {
        std::cout << "\nPassword: ";
        std::cin >> password;
        password = sha256(password);
        User *newUser = new User(old_username, password);
        userAccountData[old_username] = newUser;

        std::cout << "\nSuccesfully created your account!\n";
        return newUser;
    }
}

User *loginToExistingAccount(std::map<std::string, User *> &userAccountData)
{
    std::string username, password;
    char creationChoice;
    std::cout << "Username: ";
    std::cin >> username;

    if (userAccountData.find(username) == userAccountData.end()) // account does NOT actually exist.
    {
        std::cout << "No account was found under the username " << username
                  << "\nWould you like to create an account under " << username
                  << " instead? (y or n)\n"
                  << "Choice: ";

        validateAnswerInput(creationChoice);

        if (creationChoice == 'y')
            createAccount(userAccountData, username);
        else
            return NULL; // to main function.
    }

    else
    {
        // sign in normally
        std::cout << "\nPassword: ";
        std::cin >> password;
        password = sha256(password);

        while (password != userAccountData[username]->getPassWord())
        {
            std::cout << "\nIncorrect password\n"
                      << "Password: ";
            std::cin >> password;
            password = sha256(password);
        }

        std::cout << "\nWelcome " << username << "!\n";

        return userAccountData[username];
    }

    return NULL; // this will more than likely never get reached, but it is here as a failsafe.
}

void accessInnerFunctions(User *currentUser)
{
    char exitAppChoice;
    do
    {
        if (currentUser->getLibrarySize() == 0)
            readSongsIntoLibrary(currentUser); // reads songs from a text file and allows the user to select which songs to add to their library from then on.
        else
        {
            char addChoice;
            std::cout << "Would you like to add more songs to your library? (y or n)\n"
                      << "Choice: ";
            validateAnswerInput(addChoice);
            if (tolower(addChoice) == 'y')
                readSongsIntoLibrary(currentUser);
        }

        accessMimicFunctions(currentUser);

        std::cout << std::endl
                  << std::setw(82) << std::right << "Logout and exit the application? (y or n)\n"
                  << std::setw(52) << std::right << "Choice: ";

        validateAnswerInput(exitAppChoice);

    } while (tolower(exitAppChoice) == 'n');
}

void accessMimicFunctions(User *currentUser)
{
    int menuChoice, numSongs, addChoice;
    std::string songChoice;
    do
    {
        std::cout << "What would you like to do next?\n"
                  << "1. Play next song\n"
                  << "2. Remove a song from queue\n"
                  << "3. Add a song to the queue\n"
                  << "4. Shuffle playlist\n"
                  << "5. Sort playlist by time length of songs (shortest -> longest)\n"
                  << "6. Leave this menu\n"
                  << "Choice: ";
        validateIntegerInput(menuChoice, 6, 1);

        switch (menuChoice)
        {
        case 1:
            currentUser->queue->dequeue();
            break;

        case 2:
            numSongs = currentUser->queue->printQueue();
            if (numSongs == 0)
                break;
            std::cout << "\nWhich song would you like to remove? Type the full name of the song\n"
                      << "Choice: ";
            std::cin.ignore();
            std::getline(std::cin, songChoice);
            while (!(currentUser->queue->validateSongChoice(songChoice)))
            {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "Must be one of these songs.\n"
                          << "Choice: ";
                std::getline(std::cin, songChoice);
            }
            if (!currentUser->queue->isEmpty())
                currentUser->queue->deleteSongFromQueue(songChoice);
            else
                std::cout << "\nQueue is empty!\n";
            break;

        case 3:
            currentUser->printLibrary();
            std::cout << "\nWhich song would you like to add to your queue?\n"
                      << "Choice: ";
            validateIntegerInput(addChoice, currentUser->getLibrarySize(), 1);

            currentUser->queue->addSongToManualQueue(currentUser->getLibrarySong(addChoice - 1));
            break;

        case 4:
            currentUser->shuffleLibrary(); // FIGURE OUT THE MOST EFFICIENT METHOD OF RANDOMLY SORTING THE LIBRARY ARRAY!
            break;

        case 5:
            currentUser->songLengthSort();
            currentUser->printLibrary();
            break;
        }
    } while (menuChoice != 6);
}

// reads songs from a text file and stores them into a temporary array that the user can use to select which songs they would like to add to their playlist.

void readSongsIntoLibrary(User *currentUser)
{
    int songListSize, songChoice, songLength;
    std::string buffer;
    char userChoice;
    Song **bufferArray; // temporary array to hold ALL songs that the user can then choose from.
    std::ifstream inFile("songs.txt");
    if (inFile.is_open())
    {
        inFile >> songListSize;
        inFile.ignore();
        bufferArray = new Song*[songListSize];

        for (int i = 0; i < songListSize; i++)
        {
            bufferArray[i] = new Song;
            std::getline(inFile, buffer);
            bufferArray[i]->songName = buffer;
            std::getline(inFile, buffer);
            bufferArray[i]->artist = buffer;
            std::getline(inFile, buffer);
            songLength = stoi(buffer);
            bufferArray[i]->minutes = songLength;
        }
        std::cout << std::endl;
        for (int i = 0; i < songListSize; i++)
            std::cout << i + 1 << ". " << bufferArray[i]->songName << std::endl;

        do
        {
            std::cout << "Which song would you like to add to your playlist?\n"
                      << "Song number: ";

            validateIntegerInput(songChoice, songListSize, 1);

            if (!currentUser->duplicateSong(bufferArray[songChoice - 1]))
            {
                currentUser->addSongToLibrary(bufferArray[songChoice - 1]);
                if (!currentUser->queue)
                    currentUser->queue = new Queue();
                currentUser->queue->addSongToManualQueue(bufferArray[songChoice - 1]);
            }
            else
                std::cout << "\nThis song is already in your library!\n";

            std::cout << "\nWant to add another song?\n"
                      << "Continue? (y or n): ";

            validateAnswerInput(userChoice);

        } while (tolower(userChoice) == 'y');
        
        for(int i = 0; i < songListSize; i++)
            delete bufferArray[i];
        delete[] bufferArray; // cleans up our temporary mess.
    }

    else
        std::cout << "A fatal error has occurred when trying to load songs from \"songs.txt\"" << std::endl;
}

void validateAnswerInput(char& userChoice)
{
    while (!(std::cin >> userChoice) || (tolower(userChoice) != 'y' && tolower(userChoice) != 'n')) // restrains the user from screwing up my hard work.
    {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "You must input y or n:\n"
                  << "Continue? (y or n): ";
    }
}

void validateIntegerInput(int& input, int highParam, int lowParam)
{
    while (!(std::cin >> input) || input > highParam || input < lowParam) // restrains the user from screwing up my hard work.
    {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "You must input a valid song choice:\n"
                  << "Choice: ";
    }
}