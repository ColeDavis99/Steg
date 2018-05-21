/*====================================
  Developer: Cole Davis
  Date: 05-17-2018


  Uses:
  1. ./exe MyMessage.txt
  2. ./exe MyMessage.txt Image1.bmp
  3. ./exe Image1.bmp Image2.bmp
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

  // .bmp variables
  int numPixels = -1; //The number of pixels our images will have, and still be square
  int area = -1;
  int height = -1;
  int width = -1;
  bool imgExists = false;
  string imgPath = "";


                                                        /*
  //Make image and viewing window
  CImg<unsigned char> image("pic2.bmp");
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
   case 1:   //Input: .txt   Output: img1.bmp img2.bmp
   {
     txtPath = argv[1];
     txtExists = openTxtFile(txtPath, inpStream);
     if(txtExists)
     {
       storeTxtFile(inpStream, line, msgChar); //Store text file in one string
       txtToBinary(msgChar, msgBinary); //Convert that string to binary

       //Get the number of pixels we're going to need to store the data
       numPixels = minNumPixels(msgChar.length());

       //Get the dimensions of our image
       sideLen(numPixels, height, width);

       //Get the area of our image (This number includes every pixel, junk or not)
       area = height * width;



       //We'll make two images, original.bmp and steg.bmp.
       CImg<unsigned char> original(width, height, 1, 3);  // Define a pixDim x pixDim color image (3 channels).
       prettyColors(original);  //Randomize pixel RGB values

       //Copy construct steg.bmp
       CImg<unsigned char> steg(original);

       //Change the LSB of steg
       txtToImgs(original, steg, msgBinary);

       //Save the newly generated images
       original.save("img1.bmp");
       steg.save("img2.bmp");
     }
     break;
   }

   case 2:    //Input: .txt and .bmp  Output: .bmp
   {
     txtPath = argv[1];
     imgPath = argv[2];
     txtExists = openTxtFile(txtPath, inpStream);
     imgExists = openBmpFile(imgPath);

     if(txtExists && imgExists)
     {
       storeTxtFile(inpStream, line, msgChar); //Store text file in one string
       txtToBinary(msgChar, msgBinary);

       //Make a copy of their input image && a steg copy that will actually be saved
       CImg<unsigned char> original(argv[2]);
       CImg<unsigned char> steg(original);

       //Get the area of the images
       area = original.height() * original.width();

       //See if there is enough space for steg to occur (possibly make the double steg here?)
       if(area * 3 >= msgBinary.length())
       {
         display(original);
         display(steg);

         //Change the LSB of steg
         txtToImgs(original, steg, msgBinary);

         //Save the images
         steg.save("steg.bmp");
       }
       else
       {
         cout<<"Your message is to large for one bit LSB steganography! "<<endl;
         cout<<"Your image's area must be at least "<<msgBinary.length()/3<<endl;
       }


     }
     break;
   }
   case 3:   //Input: .bmp and .bmp   Output: message.txt
   {
     //Copy in the image files from the directory
     CImg<unsigned char> img1(argv[1]);
     CImg<unsigned char> img2(argv[2]);

     //Extract msgBinary from two images
     msgBinary = bnryMsgFromImgs(img1, img2);

     //Turn the binary into the message
     msgChar = bnryToChar(msgBinary);

     cout<<"Secret message: "<<endl<<endl<<msgChar;
     break;
   }
 }



  return 0;
}
