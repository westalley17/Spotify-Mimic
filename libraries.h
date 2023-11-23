#ifndef LIBRARIES_H
#define LIBRARIES_H

#include <iostream>

struct Song
{
    std::string songName, artist;
    int minutes;
};

#include <iomanip>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include "sha256.h"
#include "Queue.h"
#include "User.h"

using Database = std::unordered_map<std::string, User *>;

// function prototypes
void readIntoMap(std::ifstream &, Database &);
void readFromMap(Database &);
User *accessAccount(User *, std::string, Database &);
User *createAccount(Database &, std::string);
User *loginToExistingAccount(Database &);
void accessInnerFunctions(User *);
void accessMimicFunctions(User *);
void readSongsIntoLibrary(User *);
void validateAnswerInput(char &);
void validateIntegerInput(int &, int, int);

#endif