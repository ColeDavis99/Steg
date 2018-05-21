#include "Dependencies.h"
#include "custom_funcs.h"
#include "CImg.h"


using std::string;
using namespace cimg_library;

/*======================
  USER INPUT FUNCTIONS
========================*/
int CheckArgs(int argc, char *argv[])
{
  //Vars hold file extensions and indeces 1&2 of argv
  string arg1 = "", arg2 = "", arg1_ext = "", arg2_ext = "";


  //Exit if too many arguments or too few arguments
  if(argc > 3 || argc < 2)
  {
    printInstructions();
    return 0;
  }


  //Store one or two arguments and get file extensions
  //1st arg & extension
  arg1 = argv[1];
  if(getFileExt(arg1, arg1_ext) == false)
    return 0;
  //2nd arg & extension
  if(argc == 3)
  {
    arg2 = argv[2];
    if(getFileExt(arg2, arg2_ext) == false)
      return 0;
  }
  //Flip extension strings
  reverse(arg1_ext.begin(), arg1_ext.end());
  reverse(arg2_ext.begin(), arg2_ext.end());



  //Make sure user entered proper file type
  if(arg1_ext == "txt" && arg2_ext == "")
    return 1;
  else if(arg1_ext == "txt" && arg2_ext == "bmp")
    return 2;
  else if(arg1_ext == "bmp" && arg2_ext == "bmp")
    return 3;
  else
  {
    printInstructions();
    return 0;
  }
}//End of CheckArgs()


/*============================
    PARSE FILE EXTENSIONS
=============================*/
bool getFileExt(string& str, string& ext)
{
  if (str.find('.') != string::npos)
  {
    for(int i=str.length()-1; str[i] != '.'; i--)
      ext += str[i];
    return true;
  }
  else
  {
    cout<<"Don't forget to include file extensions on your argument(s)"<<endl;
    printInstructions();
    return false;
  }
}//End of getFileExt


/*============================
  PRINT OUT PROGRAM TUTORIAL
=============================*/
void printInstructions()
{
  cout<<"ERROR: Program arguments must fit of these three templates: \n"<<
		"1) [file.txt]\n"<<
		"2) [file.txt] [file.jpg]\n"<<
		"3) [file.jpg] [file.jpg]\n"<<endl;
  return;
}


/*==================
  OPEN TEXT FILE
===================*/
bool openTxtFile(string txtPath, ifstream& inpStream)
{
  inpStream.open(txtPath);

  if(inpStream)
    return true;

  else
  {
    cout<<"File does not exist at directory \""<<txtPath<<"\""<<endl;
    return false;
  }
}

/*=================
   OPEN BMP FILE
====================*/
bool openBmpFile(string imgPath)
{
  if(std::ifstream(imgPath))
    return true;
  else
  {
    cout<<"File does not exist at directory \""<<imgPath<<"\""<<endl;
    return false;
  }
}


/*=====================================================
READS IN TEXT FILE'S INFORMATION INTO ONE LONG STRING
======================================================*/
void storeTxtFile(ifstream& inpStream, string line, string& msgChar)
{
  while(!inpStream.eof())
  {
    //Store entirety of message into var msgChar
    getline(inpStream, line, '\r');
    msgChar += line;
  }
  return;
}


/*=============================
  CONVERTS STRING TO BINARY
==============================*/
string txtToBinary(string msgChar, string& msgBinary)
{
  for(auto character : msgChar)
    msgBinary += bitset<7>((int)character).to_string();

  return msgBinary;
}


/*============================================
  RETURN NUM PIXELS NEEDED TO HOLD TEXT INFO
=============================================*/
int minNumPixels(int len)
{
  double pxPerChar = 2.3333333333;

  //Return the number of pixels
  return ceil(pxPerChar * len);
}


/*===========================================
 Find two "squarest" ints that multiply and add up to numPixels
============================================*/
void sideLen(int numPixels, int& height, int& width)
{
  std::vector<int> allFactors;
  int testNum = 1;

  while(testNum <= numPixels)
  {
    if(numPixels % testNum == 0)
      allFactors.push_back(testNum);

    testNum++;
  }

  //I generate a list of all factors, increasing. Using this, I get the two
  //largest and "squarest" dimensions possible.
  width = allFactors[allFactors.size()/2];
  height = allFactors[allFactors.size()/2 -1];
  return;
}


/*===========================================
  MAKES GENERATED IMAGE RANDOMIZED AND PRETTY (for unsigned char images)
============================================*/
void prettyColors(CImg<unsigned char>& img)
{
  int min = 1;
  int max = 254;

  cimg_for(img,ptr,unsigned char)
  {
    *ptr = min + (rand() % static_cast<int>(max - min + 1));
  }
  return;
}

/*=================================
  Easier syntax for displaying image
==================================*/
void display(CImg<unsigned char>& img)
{
  CImgDisplay disp(img,"Sample Text");
  while (!disp.is_closed())
  {
      disp.wait();
      img.display(disp);
  }
}


/*================================
  Change the LSB of 2nd .jpg image
=================================*/
void txtToImgs(CImg<unsigned char>& orig, CImg<unsigned char>& steg, string msgBinary)
{
  int msgBinarySlider = 0;
  int height = orig.height();
  int width = orig.width();
  //Change the LSB of steg so comparing the two .jpg's results in the same 0 or 1 of msgBinary
  for(int c=0; c<3; c++)
  {
    for(int x=0; x<height; x++)
    {
      for(int y=0; y<width; y++)
      {
        //Don't change LSB of junk RGB values
        if(msgBinarySlider >= msgBinary.length())
          goto doneProcessing;

        //The if & else if are where the LSB is actually changed. I know I can increment steg w/o checking b/c RGB values are 1->254 inside of prettyColors()
        if(msgBinary[msgBinarySlider] == '0')
          if(((int)orig(y,x,c)%2) == ((int)steg(y,x,c)%2))
            steg(y,x,c)++;


        else if(msgBinary[msgBinarySlider] == '1')
          if(((int)orig(y,x,c)%2) != ((int)steg(y,x,c)%2))
            steg(y,x,c)++;

        msgBinarySlider++; //Increment every time
      }
    }
  }
  doneProcessing:
  return;
}


/*=============================================
    EXTRACT MESSAGE FROM TWO IMAGES
==============================================*/
string bnryMsgFromImgs(CImg<unsigned char>& img1, CImg<unsigned char>& img2)
{
  string retBinary = "";
  int height = img1.height();
  int width = img1.width();

  for(int c=0; c<3; c++)
  {
    for(int x=0; x<height; x++)
    {
      for(int y=0; y<width; y++)
      {
        retBinary += std::to_string(((int)img1(y,x,c)%2 == ((int)img2(y,x,c)%2) ));
      }
    }
  }
  return retBinary;
}


/*==================================
 TURN BINARY STRING INTO CHAR STRING
====================================*/
string bnryToChar(string msgBinary)
{
  string retStr = "";
  string bnryLetter = "";
  int mediator = -1;

  for(int i=0; i<msgBinary.length(); i++)
  {
    //Add new bit to bnryLetter to be parsed every 7 interations
    (msgBinary[i] == '0') ? bnryLetter+="0" : bnryLetter+="1";

    if(bnryLetter.length() == 7)
    {
      mediator = (char)bitset<7>(bnryLetter).to_ulong();
      retStr+=(char)mediator;
      bnryLetter = "";
    }
  }
  return retStr;
}
