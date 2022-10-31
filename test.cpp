#include <iostream>
#include "imageio.h"

//stores all functions, tests, etc.

//PSEUDOCODE
//1- 

  //invert
	for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
      if(col >= w/2){
        invert[row][col] = 255 - img[row][col];
      }
      else{
        invert[row][col] = img[row][col];
      }
		}
	}
  //invertHalf
  for(int row = 0; row < h; row++) {
    for(int col = 0; col < w; col++) {
      if(col >= w/2){
        invertHalf[row][col] = 255 - img[row][col];
      }
      else{
        invertHalf[row][col] = img[row][col];
      }
    }
  }
  //box
  for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
      if((col >= w / 4 && col < 3 * w / 4) && (row >= h / 4 && row < 3 * h / 4)){
        box[row][col] = 255; //sets it all to white
      }
      else{
        box[row][col] = img[row][col]; //prints rest of the regular image
      }
		}
	}

  //frame
  for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
      if((row == h / 4 || row == (3 * h) / 4)){
        if(col >= w / 4 && col <= (3 * w) / 4){
          frame[row][col] = 255;                     
        }
        else{
          frame[row][col] = img[row][col];
        }
      }
      else if(col == w / 4 || col == (3 * w) / 4){
        if(row >= h / 4 && row <= (3 * h) / 4){
          frame[row][col] = 255;  
        }
        else{
          frame[row][col] = img[row][col];
        }
      }
      else{
        frame[row][col] = img[row][col];
      }
		}
	}

  //scale
  int a = 0;
	int factor = 2;
	h = h * factor;
	w = w * factor;

	for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
      a = img[row / 2][col / 2];
      scale[row][col] = a;
			scale[row][col + 1] = a;
			scale[row + 1][col + 1 ] = a;
			scale[row + 1][col] = a;
		}
	}

  //pixelate
  double b = 0;

	for(int row = 0; row < h; row += 2) {
		for(int col = 0; col < w; col += 2) {
      b = (double)(img[row][col] + img[row + 1][col] + img[row][col + 1] + img[row + 1][col + 1]) / 4;
      pixelate[row][col] = (int)round(a);
      pixelate[row + 1][col] = (int)round(a);
      pixelate[row][col + 1] = (int)round(a);
      pixelate[row + 1][col + 1] = (int)round(a);
		}
	}