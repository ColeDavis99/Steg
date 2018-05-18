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
  else if(arg1_ext == "txt" && arg2_ext == "jpg")
    return 2;
  else if(arg1_ext == "jpg" && arg2_ext == "jpg")
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


/*=====================================================
READS IN TEXT FILE'S INFORMATION INTO ONE LONG STRING
======================================================*/
void storeTxtFile(ifstream& inpStream, string line, string& msgChar)
{
  while(!inpStream.eof())
  {
    //Store entirety of message into var msgChar
    getline(inpStream, line);
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


/*===========================================
  RETURN NUM PIXELS NEEDED TO HOLD TEXT INFO
============================================*/
int minNumPixels(int len)
{
  return ceil(2.33333 * len);
}


/*===========================================
  RETURN SIDE LEN THE IMAGE NEEDS TO BE (It will be a square)
============================================*/
int sideLen(int numPixels)
{
  return ceil(sqrt(numPixels));
}

/*===========================================
  MAKES GENERATED IMAGE RANDOMIZED AND PRETTY (for unsigned char images)
============================================*/
void prettyColors(CImg<unsigned char>& img)
{
  int min = 1;
  int max = 255;

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
