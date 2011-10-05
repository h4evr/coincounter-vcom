#include "frmMain.h"

frmMain::frmMain( wxWindow* parent, wxWindowID id, const wxString& title, 
const wxPoint& pos, const wxSize& size, long style) :
MyMainFrame(parent, id, title, pos, size, style) {

}

void frmMain::onLoadImageClicked( wxCommandEvent& event ) {
	event.Skip();
}

void frmMain::onCountMoneyClicked( wxCommandEvent& event ) {
	event.Skip();
}

void frmMain::onAboutClicked( wxCommandEvent& event ) {
	frmAbout* frm = new frmAbout(this);
	frm->ShowModal();
	delete frm;
}

