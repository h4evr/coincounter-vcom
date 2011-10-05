#include "coincounter_gui.h"

class frmAbout : public AboutDialog {
	public:
		frmAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		void onOkClicked( wxCommandEvent& event );
};
