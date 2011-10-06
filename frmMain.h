/*****************************************************************************
 * Coin Counter - 1st project "Visão por Computador" @ FEUP
 * Authors:
 *  - Diogo Costa (costa.h4evr@gmail.com)
 *  - Nuno Silva (nufil.ss@gmail.com)
 *
 * License: MIT
 *****************************************************************************/

#ifndef __FRMMAIN_H__
#define __FRMMAIN_H__

#include "coincounter_gui.h"
#include "frmAbout.h"

/**
	Main interface of the application.
 */
class frmMain : public MyMainFrame {
	public:
		/** Constructor */
		frmMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Coin Counter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 655,690 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		/** The user wishes to load an image. */
		void onLoadImageClicked( wxCommandEvent& event );
		
		/** The user wishes to load an image from a camera. */
		void onLoadFromCameraClicked( wxCommandEvent& event );
		
		/** If an image is loaded, start the process of counting the coins. */
		void onCountMoneyClicked( wxCommandEvent& event );
		
		/** Show information about the application. */
		void onAboutClicked( wxCommandEvent& event );
};

#endif

