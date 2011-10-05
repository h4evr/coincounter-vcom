#include <wx/wx.h>
#include "frmMain.h"

class CoinCounterApp: public wxApp {
    virtual bool OnInit();
};

IMPLEMENT_APP(CoinCounterApp)

bool CoinCounterApp::OnInit() {
	frmMain *frame = new frmMain(NULL);
	frame->Show(true);
	SetTopWindow(frame);
	return true;
} 

