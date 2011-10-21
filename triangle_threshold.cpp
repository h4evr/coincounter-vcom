#include "triangle_threshold.h"
#include <cv.h>
#include <iostream>

using namespace cv;

int TriangleThreshold(Mat& img) {
	//  Zack, G. W., Rogers, W. E. and Latt, S. A., 1977,
	//  Automatic Measurement of Sister Chromatid Exchange Frequency,
	// Journal of Histochemistry and Cytochemistry 25 (7), pp. 741-753
	//
	//  modified from Johannes Schindelin plugin
	// 
	
	if(!img.isContinuous()) {
		std::cerr << "Matrix is not continuous!" << std::endl;
		return 0;
	}
	
    // Calculate histogram
    // Added by Diogo Costa
	int datalength = 256;
    int size[] = {256};
    float rangeC0[] = {0.0f, 255.0f};
	const float* range[] = {rangeC0};
    int channels[] = {0};
    MatND hist;

    calcHist(&img, 1, &channels[0], Mat(),
             hist, 1, &size[0], range,
             true, false);

    float data[256];
    for(int i = 0; i < 256; ++i) {
        data[i] = hist.at<float>(i, 0);
    }

	// find min and max
	int min = 0, dmax=0, max = 0, min2=0;
	for (int i = 0; i < datalength; i++) {
		if (data[i]>0){
			min=i;
			break;
		}
	}
	if (min>0) min--; // line to the (p==0) point, not to data[min]

	// The Triangle algorithm cannot tell whether the data is skewed to one side or another.
	// This causes a problem as there are 2 possible thresholds between the max and the 2 extremes
	// of the histogram.
	// Here I propose to find out to which side of the max point the data is furthest, and use that as
	//  the other extreme.
	for (int i = 255; i >0; i-- ) {
		if (data[i]>0){
			min2=i;
			break;
		}
	}
	if (min2<255) min2++; // line to the (p==0) point, not to data[min]

	for (int i =0; i < 256; i++) {
		if (data[i] >dmax) {
			max=i;
			dmax=data[i];
		}
	}
	// find which is the furthest side
	//IJ.log(""+min+" "+max+" "+min2);
	bool inverted = false;
	if ((max-min)<(min2-max)){
		// reverse the histogram
		//IJ.log("Reversing histogram.");
		inverted = true;
		int left  = 0;          // index of leftmost element
		int right = 255; // index of rightmost element
		while (left < right) {
			// exchange the left and right elements
			int temp = data[left]; 
			data[left]  = data[right]; 
			data[right] = temp;
			// move the bounds toward the center
			left++;
			right--;
		}
		min=255-min2;
		max=255-max;
	}

	if (min == max){
		//IJ.log("Triangle:  min == max.");
		return min;
	}

	// describe line by nx * x + ny * y - d = 0
	double nx, ny, d;
	// nx is just the max frequency as the other point has freq=0
	nx = data[max];   //-min; // data[min]; //  lowest value bmin = (p=0)% in the image
	ny = min - max;
	d = sqrt(nx * nx + ny * ny);
	nx /= d;
	ny /= d;
	d = nx * min + ny * data[min];

	// find split point
	int split = min;
	double splitDistance = 0;
	for (int i = min + 1; i <= max; i++) {
		double newDistance = nx * i + ny * data[i] - d;
		if (newDistance > splitDistance) {
			split = i;
			splitDistance = newDistance;
		}
	}
	split--;

	if (inverted) {
		// The histogram might be used for something else, so let's reverse it back
		int left  = 0; 
		int right = 255;
		while (left < right) {
			int temp = data[left]; 
			data[left]  = data[right]; 
			data[right] = temp;
			left++;
			right--;
		}
		return (255-split);
	}
	else
		return split;
}
