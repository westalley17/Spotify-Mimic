#ifndef LIBRARIES_H
#define LIBRARIES_H

// here lies all the shit needed to give me a headache...

#include <iostream>

struct Song
{
    std::string songName, artist;
    int minutes;
};

#include <iomanip>
#include <fstream>
#include <cctype>
#include <map>
#include "sha256.h"
#include "Queue.h"
#include "User.h"

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