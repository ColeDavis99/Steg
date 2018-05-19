/*====================================
  Developer: Cole Davis
  Date: 05-17-2018

  Goal: Finish Case 1

  Uses:
  1. ./exe Image1.png Image2.png
  2. ./exe Image1.png MyMessage.txt
  3. ./exe MyMessage.txt
=====================================*/
#include "CImg.h"
#include "custom_funcs.h"
#include "Dependencies.h"
using namespace cimg_library;

int main(int argc, char *argv[])
{
  //Pseudo random number seeding
  srand(time(NULL));

  //See which of 3 process user is trying to accomplish
  int which_process = CheckArgs(argc, argv);

  // .txt variables & streams
  ifstream inpStream;
  string line = "";
  string msgChar = "";
  string msgBinary = "";
  string txtPath = "";
  bool txtExists = false;

  // .jpg variables
  int numPixels = -1; //The number of pixels our images will have, and still be square
  int pixelDimension = -1; //This will be height and width, I make a square
  int extraPixels = -1; //The number of pixels that won't contain .txt data
  int area = -1;



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
     txtExists = openTxtFile(txtPath, inpStream);
     if(txtExists)
     {
       storeTxtFile(inpStream, line, msgChar); //Store text file in one string
       msgBinary = txtToBinary(msgChar, msgBinary); //Convert that string to binary

       //Get the number of pixels we're going to need to store the data
       numPixels = minNumPixels(msgChar.length());

       //Get the dimensions of our image
       pixelDimension = sideLen(numPixels);

       //Get the area of our image (This number includes every pixel, junk or not)
       area = pixelDimension*pixelDimension;

       //Get number of extra pixels tacked on to the bottom right of image to make it square
       extraPixels = junkPixels(pixelDimension, numPixels);

       //We'll make two images, original.jpg and steg.jpg.
       CImg<unsigned char> original(pixelDimension,pixelDimension,1,3);  // Define a pixDim x pixDim color image (3 channels).
       prettyColors(original);  //Randomize pixel RGB values

       //Copy construct steg.jpg
       CImg<unsigned char> steg(original);

       //Change the LSB of steg
       txtToImgs(original, steg, msgBinary, pixelDimension);

       //Print out every pixel
       matrixPrint(steg, original, pixelDimension);




       // original.save("original.jpg");
       // steg.save("steg.jpg");
       // display(steg);
       // display(original);


       cout<<endl<<"Message binary: "<<msgBinary<<endl;
     }
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
