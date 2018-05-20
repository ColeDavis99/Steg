/*====================================
  Developer: Cole Davis
  Date: 05-17-2018

  Goal:(Make the case1 generated images rectangular
  if need be, remove all junk pixels from existance)

  Uses:
  1. ./exe MyMessage.txt
  2. ./exe MyMessage.txt Image1.png
  3. ./exe Image1.png Image2.png
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
  string secretMessage = "";

  // .jpg variables
  int numPixels = -1; //The number of pixels our images will have, and still be square
  int extraRGBVals = -1; //The it's possible 1 or 2 of the bottomrightmost pixel's value is junk
  int area = -1;
  int height = -1;
  int width = -1;



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

       //Get the number of extra RGB values in the bottom right pixel of steg.jpg
       extraRGBVals = extraRGB(msgChar.length());

       //Get the dimensions of our image
       sideLen(numPixels, height, width);

       //Get the area of our image (This number includes every pixel, junk or not)
       area = height * width;




       //We'll make two images, original.jpg and steg.jpg.
       CImg<unsigned char> original(width, height,1,3);  // Define a pixDim x pixDim color image (3 channels).
       prettyColors(original);  //Randomize pixel RGB values

       //Copy construct steg.jpg
       CImg<unsigned char> steg(original);

       //Change the LSB of steg
       txtToImgs(original, steg, msgBinary);

       display(original);
       display(steg);
       //Save the newly generated images
       original.save("original.jpg");
       steg.save("steg.jpg");

       cout<<"We're going to need "<<area<<" pixels."<<endl;
       cout<<"Height is: "<<height<<endl;
       cout<<"Width is: "<<width<<endl;
       cout<<"There will be "<<extraRGBVals<<" extra RGB values."<<endl;

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
     //Copy in the image files from the directory
     CImg<unsigned char> img1(argv[1]);
     CImg<unsigned char> img2(argv[2]);

     //Extract msgBinary from two images
     msgBinary = bnryMsgFromImgs(img1, img2, extraRGBVals);  //One or both of these two are a lil bit off

     //Turn the binary into the message
     msgChar = bnryToChar(msgBinary);  //One or both of these two are a lil bit off

     cout<<"Secret message: "<<msgChar<<endl<<endl;
     cout<<endl<<"Message binary: "<<msgBinary<<endl;
     break;
   }
 }



  return 0;
}
