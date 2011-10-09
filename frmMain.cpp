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
	blur(image, image, Size(5,5));
	
	Mat im_gray;
	//Convert to grayScale
	cvtColor(image,im_gray,CV_RGB2GRAY);

	//Threshold to convert to black & white
	Mat img_bw = im_gray > 10;

	//Reduce grain
	Mat img_bw_contorns;
 	blur(img_bw, img_bw_contorns, Size(2,2));
	cv::compare(img_bw, img_bw_contorns, img_bw_contorns, cv::CMP_NE);

	this->pnlBackground->SetImage(img_bw_contorns);
	this->pnlBackground->Refresh();
	event.Skip();
}

/** Show information about the application. */
void frmMain::onAboutClicked( wxCommandEvent& event ) {
	frmAbout* frm = new frmAbout(this);
	frm->ShowModal();
	delete frm;
}

