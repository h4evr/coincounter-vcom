#include <cv.h>
#include <highgui.h>

#define WINDOW_NAME "Cam Capture CMOV"

int smooth_neighbors = 3, tmp_smooth_neighbors = 3;
int threshold_val = 89;
int method = 0;

void only_odd_neighbors(int val) {
	if(val > 0 && val % 2 == 0) {
		cvSetTrackbarPos("Neighbors", WINDOW_NAME, val + 1);
	} else {
		smooth_neighbors = val;
	}
}

int main (int argc, char **argv) {
	CvCapture* capture;
	IplImage* img, *gray, *threshold, *smooth;
	int width, height;
		
	// Open capture device (webcam)
	capture = cvCreateCameraCapture(0);
	
	if(capture == NULL)
		return 1;
	
	// Create a window
	cvNamedWindow(WINDOW_NAME, CV_WINDOW_AUTOSIZE);
	
	//
	cvCreateTrackbar("Method", WINDOW_NAME, &method, 2, NULL);
	cvCreateTrackbar("Threshold", WINDOW_NAME, &threshold_val, 255, NULL);
	cvCreateTrackbar("Neighbors", WINDOW_NAME, &tmp_smooth_neighbors, 25, only_odd_neighbors);
	
	// Grab a frame to retrieve frame size
	if((img = cvQueryFrame(capture)) == NULL) {
		cvDestroyWindow(WINDOW_NAME);
		return 1;
	}
	
	// Create holder for the grayscale image
	gray = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	smooth = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	threshold = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	
	// Grab each frame
	while((img = cvQueryFrame(capture)) != NULL) {
		// Flip the image horizontally
		cvFlip(img, NULL, 1);
		
		// Convert to grayscale
		cvCvtColor(img, gray, CV_BGR2GRAY);
		
		if(smooth_neighbors > 0 && method < 2)
			cvSmooth(gray, smooth, CV_MEDIAN, smooth_neighbors, 0, 0.0, 0);
		else
			cvCopy(gray, smooth, NULL);
			
		// Threshold
		if(method == 0)
			cvThreshold(smooth, threshold, threshold_val, 255, CV_THRESH_BINARY);
		else if(method == 1)
			cvAdaptiveThreshold(smooth, threshold, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 3, 0);
		else if(method == 2)
			cvCanny(smooth, threshold, 1, threshold_val, smooth_neighbors);
		
		// Update the image on the window
		cvShowImage(WINDOW_NAME, threshold);		
	
		// If the ESC key is pressed, exit
		if( cvWaitKey(25) == 27 )
			break;
	}
	
	// Release everything 
	cvReleaseImage(&threshold);
	cvReleaseImage(&smooth);
	cvReleaseImage(&gray);
	cvReleaseImage(&img);
	cvReleaseCapture(&capture);
	cvDestroyWindow(WINDOW_NAME);
	
	return 0;
}
