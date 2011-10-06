#include "frmAbout.h"

/** Constructor. */
frmAbout::frmAbout( wxWindow* parent, wxWindowID id, const wxString& title, 
const wxPoint& pos, const wxSize& size, long style) :
AboutDialog(parent, id, title, pos, size, style) {
	// No configuration needed.
}
		
/** Close the window when the OK button is clicked. */		
void frmAbout::onOkClicked( wxCommandEvent& event ) {
	this->EndModal(0);
}

