#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <nlohmann/json.hpp>
#include <Windows.h>
#include <thread>
#include <chrono>

#include "fileManager.h"
#include "listsManager.h"

using namespace std;

int AskListIndex();
Element createElement();
void clearConsole();
void equalsLines();
int CreateList();
void manageList(int listIndex);
void centerText(const std::string& texte);
int AskElementIndex(List list);

std::string equalSigns;
fileManager fileM;
Lists lists;
nlohmann::json listsData;


#endif
