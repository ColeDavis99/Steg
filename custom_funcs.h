#ifndef CUSTOM_FUNCS_H
#define CUSTOM_FUNCS_H
#include "Dependencies.h"
using std::string;
/*======================
  USER INPUT FUNCTIONS
========================*/
//Returns int 1, 2, 3, or 0 representing what process the user is wanting
//to do, or whether or not input is valid
int CheckArgs(int argc, char *argv[]);

//Parses out the string of characters after the last "." of the argument and
//returns true if there was a period somewhere in the argument
bool getFileExt(string& str1, string& ext);

//Print out proper use of program arguments
void printInstructions();

//Returns true or false depending on if txt file opened succesfully
bool openTxtFile(string txtPath, ifstream& line);

//Reads in text file's information into one long strings

//Converts strings into binary string version

#endif
