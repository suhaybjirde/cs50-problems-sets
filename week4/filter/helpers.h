#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// sepia helpers
int calulate_gsepia(int red, int green, int blue);
int calulate_bsepia(int red, int green, int blue);
int calulate_rsepia(int red, int green, int blue);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// refelect helpers
void reverse(RGBTRIPLE array[], int len);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);
