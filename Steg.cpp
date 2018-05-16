/*====================================
  Developer: Cole Davis
  Date: 05-15-2018

  Goal: Manipulate the RGB values of
  two images and toggle the LSB
=====================================*/

#include <iostream>
#include <bitset>
using std::cout;
using std::endl;
using std::bitset;

#include "CImg.h"
using namespace cimg_library;

int main()
{
<<<<<<< HEAD
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
  
  

  return 0;
}
