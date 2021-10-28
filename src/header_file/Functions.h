#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>
#include <time.h>
using namespace std;

// construct a whole information for the target
string base_search(string tag_name);
// construct a vector of string including all the target information
void base_search(string tag_name, vector<string> &container);
// build for the npc load
vector<string> npc_seperator(ifstream&);


// randomly generate a name according to tag, target
string rand_name_generator(string);

// generate a number between 0~4
int rare_generator();

#endif // FUNCTIONS_H
