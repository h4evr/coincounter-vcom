#include "coincounter_gui.h"
#include "frmAbout.h"

class frmMain : public MyMainFrame {
	public:
		frmMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Coin Counter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 511,451 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		void onLoadImageClicked( wxCommandEvent& event );
		void onCountMoneyClicked( wxCommandEvent& event );
		void onAboutClicked( wxCommandEvent& event );
};

