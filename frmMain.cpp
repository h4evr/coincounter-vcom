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
#include <highgui.h>
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

/** If an image is loaded, start the process of counting the coins. */
void frmMain::onCountMoneyClicked( wxCommandEvent& event ) {

	//Blur
	//blur(image, image, Size(5,5));
	
	Mat img_gray;
	//Convert to grayScale
	//cvtColor(image,img_gray,CV_RGB2GRAY);

	
	//Mat img_bw;
	//adaptiveThreshold(img_gray, img_bw, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 5, 0);

	//Reduce grain
	//Mat img_bw_edges;
 	//blur(img_bw, img_bw_edges, Size(2,2));
	//cv::compare(img_bw, img_bw_edges, img_bw_edges, cv::CMP_NE);
	//int upper = 200;
	//int lower = 80;
	//Canny(img_bw, img_bw_edges, lower, upper, 3);

	cvtColor(image, img_gray, CV_BGR2GRAY);

    	// smooth it, otherwise a lot of false circles may be detected
	//GaussianBlur( img_gray, img_gray, Size(15, 15), 2, 2 );
	equalizeHist( img_gray, img_gray );
	
//Threshold to convert to black & white
	Mat img_bw = img_gray > 150;

	vector<Vec3f> circles;
     	HoughCircles(img_bw, circles, CV_HOUGH_GRADIENT,1, img_bw.rows/10, 21, 100);


	Mat img_color;
	//Convert to color
	cvtColor(img_gray,img_color,CV_GRAY2RGB);

	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// draw the circle center
		circle( img_color, center, 3, Scalar(0,255,0), -1, 8, 0 );
		// draw the circle outline
		circle( img_color, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}


	this->pnlBackground->SetImage(img_bw);
	this->pnlBackground->Refresh();
	//event.Skip();
}

/** Show information about the application. */
void frmMain::onAboutClicked( wxCommandEvent& event ) {
	frmAbout* frm = new frmAbout(this);
	frm->ShowModal();
	delete frm;
}

