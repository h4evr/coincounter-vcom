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
	event.Skip();
}

/** Show information about the application. */
void frmMain::onAboutClicked( wxCommandEvent& event ) {
	frmAbout* frm = new frmAbout(this);
	frm->ShowModal();
	delete frm;
}

