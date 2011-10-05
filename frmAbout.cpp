#include "frmAbout.h"

frmAbout::frmAbout( wxWindow* parent, wxWindowID id, const wxString& title, 
const wxPoint& pos, const wxSize& size, long style) :
AboutDialog(parent, id, title, pos, size, style) {

}
		
void frmAbout::onOkClicked( wxCommandEvent& event ) {
	this->EndModal(0);
}

