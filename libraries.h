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
void readIntoMap(std::ifstream &, std::map<std::string, User *> &);
void readFromMap(std::map<std::string, User *> &);
User *accessAccount(User *, std::string, std::map<std::string, User *> &);
User *createAccount(std::map<std::string, User *> &, std::string);
User *loginToExistingAccount(std::map<std::string, User *> &);
void accessInnerFunctions(User *);
void accessMimicFunctions(User *);
void readSongsIntoLibrary(User *);
void validateAnswerInput(char &);
void validateIntegerInput(int &, int, int);

#endif