#ifndef CUSTOM_FUNCS_H
#define CUSTOM_FUNCS_H
#include "Dependencies.h"
#include "CImg.h"


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
bool openTxtFile(string txtPath, ifstream& inpStream);

//Returns true or false depending on if bmp file opened succesfully
bool openBmpFile(string imgPath);

//Reads in text file's information into one long string
void storeTxtFile(ifstream& inpStream, string line, string& msgChar);

//Converts strings into binary string version
string txtToBinary(string msgChar, string& msgBinary);

//Return num pixels needed to hold text info
int minNumPixels(int len);

//Recursively find two "squarest" ints that multiply to numPixels
void sideLen(int numPixels, int& height, int& width);

//Makes generated image randomized and pretty (for unsigned char images)
void prettyColors(cimg_library::CImg<unsigned char>& img);

//Easier syntax for displaying image
void display(cimg_library::CImg<unsigned char>& img);

//Change the LSB of steg (this is where the message is actally stegified into the images)
void txtToImgs(cimg_library::CImg<unsigned char>& orig, cimg_library::CImg<unsigned char>& steg, string msgBinary);

//Get the binary secret message from the two pictures
string bnryMsgFromImgs(cimg_library::CImg<unsigned char>& img1, cimg_library::CImg<unsigned char>& img2);

//TURN BINARY STRING INTO CHAR STRING
string bnryToChar(string msgBinary);

#endif
