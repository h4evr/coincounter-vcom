/*****************************************************************************
 * Coin Counter - 1st project "Visão por Computador" @ FEUP
 * Authors:
 *  - Diogo Costa (costa.h4evr@gmail.com)
 *  - Nuno Silva (nufil.ss@gmail.com)
 *
 * License: MIT
 *****************************************************************************/

#ifndef __FRMABOUT_H__
#define __FRMABOUT_H__

#include "coincounter_gui.h"

/**
	A dialog that shows information about the application.
 */
class frmAbout : public AboutDialog {
	public:
		/** Constructor */
		frmAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		
		/** Close the window when the OK button is clicked. */	
		void onOkClicked( wxCommandEvent& event );
};

#endif
