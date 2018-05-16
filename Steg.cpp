/*====================================
  Developer: Cole Davis
  Date: 05-15-2018

  Goal: Get started on Steg, learn 
  how to access the bits of an image
=====================================*/

#include "CImg.h"
using namespace cimg_library;

int main() 
{
  // Define a 640x400 color image with 8 bits per color component.
	CImg<unsigned char> img(640,400,1,3); 
	img.fill(0);
	
	// Set pixel values to 0 (color : black)
	unsigned char purple[] = { 255,0,255 };
	
  // Define a purple color
  img.draw_text(100,100,"Hello World",purple); // Draw a purple "Hello world" at coordinates (100,100).
	
  // Display the image in a display window.
  img.display("My first CImg code");
  return 0;
}
