#Title: YUV image operations, including crop and scale

Given a "4160x3120.nv21" yuv image 
1. load the *.nv21 image 
2. do center crop and keep the FOV as 2560*1920  
   downscale the center cropped image to 640*480
4. save the crop and scale image to 640*480.nv21
please refer to convert.jpg

#Standard Input
 4608x3456.nv21 yuv image

#Constraints:
 none

#Standard Output
 640x480.nv21 yuv image

#Sample
 none


Output
 You can use YUView to double check the crop and scale yuv imag

//////////////////////////
#NOTE:
a. compiling command: gcc convert.c
b. running command: ./a.out
//////////////////////
