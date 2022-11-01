#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <string>
#include <math.h>
 
using namespace std;

#include "imageio.h"

// Reads a PGM file.
// Notice that: height and width are passed by reference!
void readImage(std::string filename, int image[MAX_H][MAX_W], int &height, int &width) {
	char c;
	int x;
	ifstream instr;
	instr.open(filename);

	// read the header P2
	instr >> c;
	assert(c == 'P');
	instr >> c;
	assert(c == '2');

	// skip the comments (if any)
	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[row][col];
	instr.close();
	return;
}


// Writes a PGM file
// Need to provide the array data and the image dimensions
void writeImage(std::string filename, int image[MAX_H][MAX_W], int height, int width) {
	ofstream ostr;
	ostr.open(filename);
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	// print the header
	ostr << "P2" << endl;
	// width, height
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			ostr << image[row][col] << ' ';
			ostr << endl;
		}
	}
	ostr.close();
	return;
}

int main(){
  std::string input = "inImage.pgm";
  int img[MAX_H][MAX_W];
  int h, w;
  readImage(input, img, h, w); // read it from the file "image1.jpg"
  // h and w were passed by reference and
  // now contain the dimensions of the picture
  // and the 2-dimesional array img contains the image data
  
  // Now we can manipulate the image the way we like
  // for example we copy its contents into a new array
  int invert[MAX_H][MAX_W];
  int invertHalf[MAX_H][MAX_W];
  int box[MAX_H][MAX_W];
  int frame[MAX_H][MAX_W];
  int scale[MAX_H][MAX_W];
  int pixelate[MAX_H][MAX_W];

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
  writeImage("inImage.pgm",invert, h, w);
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
  writeImage("inImage.pgm",invertHalf, h, w);
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
  writeImage("inImage.pgm",box, h, w);
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
  writeImage("inImage.pgm",frame, h, w);
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
  writeImage("inImage.pgm",scale, h, w);
  //pixelate
  float b = 0;

	for(int row = 0; row < h; row += 2) {
		for(int col = 0; col < w; col += 2) {
      b = (double)(img[row][col] + img[row + 1][col] + img[row][col + 1] + img[row + 1][col + 1]) / 4;
      pixelate[row][col] = (int)round(a);
      pixelate[row + 1][col] = (int)round(a);
      pixelate[row][col + 1] = (int)round(a);
      pixelate[row + 1][col + 1] = (int)round(a);
		}
	}
  // and save this new image to file "outImage.pgm"
  writeImage("inImage.pgm",pixelate, h, w);
  
  return 0;
}
