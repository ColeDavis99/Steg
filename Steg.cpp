/*====================================
  Developer: Cole Davis
  Date: 05-17-2018

  Goal: Detect which of 3 uses user
  is doing:
  1. Two photo decipher
  2. Photo and Text File
  3. Just Text file

  Uses:
  1. ./exe Image1.png Image2.png
  2. ./exe Image1.png MyMessage.txt
  3. ./exe MyMessage.txt
=====================================*/
#include "Dependencies.h"
#include "custom_funcs.h"
#include "CImg.h"

using namespace cimg_library;

int main(int argc, char *argv[])
{
  //See which of 3 process user is trying to accomplish
  int which_process = CheckArgs(argc, argv);

  // .txt variables & streams
  ifstream line;
  stringstream input_word;
  stringstream input_char;
  string msgBinary = "";
  string txtPath = "";
  bool txtExists = false;

  string wub = "";





                                                        /*
  //Make image and viewing window
  CImg<unsigned char> image("pic2.png");
  CImgDisplay disp1(image,"Before!");
  CImg<unsigned char> image2 = image;


  //Prints out 0-255 int of every R, every G, then every B
  cimg_for(image2,ptr,unsigned char)
  {
    cout<<(int)*ptr<<" ";
  }

  //This loop toggles the last bit
  cimg_for(image2,ptr,unsigned char)
  {
    if(stoi(bitset<8>(*ptr).to_string()) %2 == 1)
      *ptr = *ptr - 1;

    else
      *ptr = *ptr + 1;
  }

  cout<<endl<<endl<<endl;
  //This loop prints out the new toggled RGB value
  cimg_for(image2,ptr,unsigned char)
  {
    cout<<(int)*ptr<<" ";
  }



  //Show the before and after
  CImgDisplay disp2(image2,"After!");
  while (!disp1.is_closed() && !disp2.is_closed())
  {
      disp1.wait();
      disp2.wait();
      image.display(disp1);
      image2.display(disp2);
  }


  //Here's some binary to char to int examples etc...
  cout<<endl<<endl<<(int)'$'<<endl;
  cout<<(char)36<<endl;
  cout<<bitset<7>((int)'$')<<endl;
  cout<<bitset<7>("0100100").to_ulong()<<endl;
  cout<<(char)36<<endl;

                                                                    */
  //Check user's arguments

  switch(which_process)
  {
   case 1:
   {
     //One text file
     txtPath = argv[1];
     txtExists = openTxtFile(txtPath, line);

     break;
   }
    case 2:
   {
     //One text file and one image file

     break;
   }
    case 3:
   {
     //Two image files

     break;
   }
  }



  return 0;
}
