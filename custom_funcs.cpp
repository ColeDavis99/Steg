#include "Dependencies.h"
#include "custom_funcs.h"
using std::string;

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
bool openTxtFile(string txtPath, ifstream& line)
{
  line.open(txtPath);

  if(line)
    return true;

  else
  {
    cout<<"File does not exist at directory \""<<txtPath<<"\""<<endl;
    return false;
  }
}
