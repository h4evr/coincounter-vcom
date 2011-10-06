/*****************************************************************************
 * Coin Counter - 1st project "Visão por Computador" @ FEUP
 * Authors:
 *  - Diogo Costa (costa.h4evr@gmail.com)
 *  - Nuno Silva (nufil.ss@gmail.com)
 *
 * License: MIT
 *****************************************************************************/

#include <wx/wx.h>
#include "frmMain.h"

/**
	The application class, responsable for loading the interface.
 */
class CoinCounterApp: public wxApp {
	/** Initialize the interface. */
    virtual bool OnInit();
};

IMPLEMENT_APP(CoinCounterApp)

/** Initialize the interface. */
bool CoinCounterApp::OnInit() {
	// Create a new main form
	frmMain *frame = new frmMain(NULL);
	
	// Show the form
	frame->Show(true);
	
	// Set as the main window for the application
	SetTopWindow(frame);
	return true;
} 

