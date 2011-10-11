/*****************************************************************************
 * Coin Counter - 1st project "Visão por Computador" @ FEUP
 * Authors:
 *  - Diogo Costa (costa.h4evr@gmail.com)
 *  - Nuno Silva (nufil.ss@gmail.com)
 *
 * License: MIT
 *****************************************************************************/

#include "frmMain.h"
#include "imageCanvas.h"
#include <wx/filedlg.h>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include "meanshiftsegmentation.h"

using namespace cv;

Mat image;

/** Constructor */
frmMain::frmMain( wxWindow* parent, wxWindowID id, const wxString& title, 
const wxPoint& pos, const wxSize& size, long style) :
MyMainFrame(parent, id, title, pos, size, style) {
	wxImage::AddHandler(new wxJPEGHandler());
}

/** The user wishes to load an image. */
void frmMain::onLoadImageClicked( wxCommandEvent& event ) {
	// Show a file dialog
	wxFileDialog diag(this);
	if(diag.ShowModal() == wxID_OK) {
		image = imread(std::string(diag.GetPath().mb_str(wxConvFile)));
		this->pnlBackground->SetImage(image);
		this->pnlBackground->Refresh();
	}
	diag.Destroy();
}

/** The user wishes to load an image from a camera. */
void frmMain::onLoadFromCameraClicked( wxCommandEvent& event ) {
	event.Skip();
}

/**
	Equalize the histogram of a colored image.
	This is done by equalizing the histograms of each channel and then
	merging them together.
 */
Mat equalize_color_histogram(Mat& image) {
	vector<Mat> channels;
	Mat dest;
	channels.reserve(3);
    split(image, channels);
    equalizeHist(channels[0], channels[0]);
    equalizeHist(channels[1], channels[1]);
    equalizeHist(channels[2], channels[2]);
    merge(channels, dest);
    
    return dest;
}

/**
	Normalize the energy of an image.
	This is not actually the correct implementation.
	To be accurate, this should be applied by blocks to the image, instead
	of dividing by the means of the while picture, but for the purpose of this
	project, this as proven to give best results.
	Check http://www.developerstation.org/2011/04/normalize-image-in-opencv.html
 */
Mat Normalize(const Mat& im) {
	Mat _tmp;
	Mat res;
	im.copyTo(res);

	//to store given mean and variance
	Scalar mean, std_deviation;
	
	//calculate mean and standard deviation
	meanStdDev(res, mean, std_deviation);
	convertScaleAbs(res, res, (1.0f / mean.val[0]), 0);	
	return res;
}

/*
 * Apply the mean-shift segmentation algorithm to an image
 */
Mat segmentate(const Mat& src) {	    
	CvMat _src = src;
	CvMat *_dest = cvCreateMat(_src.rows, _src.cols, _src.type);
	
	PyrMeanShiftFiltering(&_src, _dest, 20, 40, 1);
	
	return Mat(_dest);
}

/** If an image is loaded, start the process of counting the coins. */
void frmMain::onCountMoneyClicked( wxCommandEvent& event ) {
	
	// Normalize the energy of the image (reduces JPEG artifacts!)
	Mat img_norm = Normalize(image);
	
	// Equalize the histogram of the color image (to restore contrast taken by
	// the normalization).
	Mat img_eq = equalize_color_histogram(img_norm);
	
	// Blur the image to remove noise
	blur(img_eq, img_eq, Size(5,5));
	
	// Segmentate the image using the meanshift segmentation algorithm.
	Mat img_color = segmentate(img_eq);
	
	// Convert the image to grayscale
	Mat img_gray;
	cvtColor(img_color, img_gray, CV_BGR2GRAY);
	
	//Threshold to convert the image to black & white
	Mat img_bw;
	threshold(img_gray, img_bw, 64, 255, THRESH_BINARY);
	
	// Used only for visualization purposes.
	// Uses the same parameters as the hough transform.
	Mat edges;
	Canny(img_bw, edges, 100, 200, 3);
	
	// Apply the Hough transform to find existing circles
	vector<Vec3f> circles;
    HoughCircles(img_bw, circles, CV_HOUGH_GRADIENT, 3, 75, 200, (int)(2.0f*3.1415f*40.0f), 40);

	// Prepare image for visualization
	cvtColor(edges, img_color, CV_GRAY2BGR);
	
	// Draw the circles that were found
	for( size_t i = 0; i < circles.size(); i++ ) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// draw the circle center
		circle( img_color, center, 3, Scalar(0,255,0), -1, 8, 0 );
		// draw the circle outline
		circle( img_color, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}

	// Show the final image to the user
	this->pnlBackground->SetImage(img_color);
	this->pnlBackground->Refresh();
}

/** Show information about the application. */
void frmMain::onAboutClicked( wxCommandEvent& event ) {
	frmAbout* frm = new frmAbout(this);
	frm->ShowModal();
	delete frm;
}

