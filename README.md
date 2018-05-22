# Steg 1.0
This is my first project with steganography. I chose the most basic type of steganography, least significant bit. I developed this tutorial with the Linux OS in mind, but getting everything set up on Windows is similar. In it's current state, this program
requires basic command line skills. If Steg 2.0 pops up in the future, there may be a Qt GUI in the works.


/*==========================
        IMPORTANT
==========================*/
This program only works with .bmp files and .txt files in the current version (1.0).
If you wish to use other image types other than .bmp, you can't. You can easily change the file
format using this command in terminal though:

  "mogrify -format bmp <yourfile>.png"



/*==========================
     REQUIRED LIBRARIES
==========================*/
Short version: run "sudo apt-get install libx11-dev"

Xlib is required by CImg.h, so this command needs to be run: "sudo apt-get install libx11-dev"
This installs libx11 onto your system. 
For the curious: https://en.wikipedia.org/wiki/Xlib



/*==========================
    BUILDING EXECUTABLE
==========================*/
Open terminal, navigate to Steg, type "make".
The executable is named "stegify".



/*====================
      OVERVIEW
=====================*/
There are three use cases of the program:


(X= filename)
       |      Input         |      Output
=======|====================|======================
Case 1 |    X.txt           |   img1.bmp & img2.bmp
       |                    |
Case 2 |    X.bmp x2        |   secretmessage.txt
       |                    |
Case 3 |    X.txt & X.bmp   |   steg.bmp
=======|====================|======================



Case 1) IMAGES FROM .TXT
*  This case generates two images that

*  Create a .txt file and write your secret message that will be hidden in the two images.

*  In terminal, type "./stegify <filename>.txt"

*  This generates "img1.bmp" and "img2.bmp". These two images can be sent to whoever else has this
   program and then they can use the two images as input for case 2 to get your message.



Case 2) .TXT FROM IMAGES (not really a "case", it just generates the secret message)
*  This is the case that does the least significant bit comparison and generates the secret message.

*  In terminal, type "./stegify img1.bmp  img2.bmp" if you just used case 1

*  If you're deciphering images you generated with case 3, in terminal
   type "./stegify steg.bmp  <filename.bmp>"

*  The program generates "secretmessage.txt" which contains your original secret message.



Case 3)  .TXT TO PREEXISTING IMAGE
*  The last case is perhaps the coolest, it allows you to "stegify" any .bmp image of your choice
   instead of just having a randomly generated rainbow-ey image.

*  In terminal, type "./stegify <filename>.txt  <filename>.bmp"

*  One file was generated from this, "steg.bmp". This file looks identical to the .bmp you just this
   uploaded, but has been slightly modified to contain your message.

*  You can use use "steg.bmp" and the .bmp you used in the previous command
   in case 2 to generate "secretmessage.txt"





 /*===========================
       HOW TO USE (syntax)
 ============================*/
 There are a few files that come included, let's take a quick look at how to get stegifying.
 Before we get started, go to the Steg directory and type "make" to build the executable.

 Also, make sure you're only working with .bmp images.
 Here's a command to change file types:  "mogrify -format bmp <yourfile>.png"



 Case 1)
   Alright, I'll make these quick. Here's case 1 with the files I've included:

   1)  ./stegify ody.txt                    //Generate two .bmp files
   2)  ./stegify img1.bmp img2.bmp          //Generate secretmessage.txt from the .bmp files (this is same as case 2 A)



 Case 2) (This case is included in
   That was quick indeed. Here's the two different ways case 2 is used:

   A)  ./stegify img1.bmp img2.bmp                                        //If you used case1 to generate both .bmp files

   B)  ./stegify steg.bmp polyphemus.bmp   				//If you used case3 to generate one .bmp file



 Case 3)
   Speed. Here's case 3:

   1)  ./stegify ody.txt polyphemus.bmp         //Generate steg.bmp
   2)  ./stegify steg.bmp polyphemus.bmp        //Create secretmessage.txt steg.bmp and polyphemus.bmp (this is same as case 2 B)





Thanks for checking my repo out dawg.
