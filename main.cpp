#include <wx/wx.h>
#include "coincounter_gui.h"

class CoinCounterApp: public wxApp {
    virtual bool OnInit();
};

IMPLEMENT_APP(CoinCounterApp)

bool CoinCounterApp::OnInit() {
	MyMainFrame *frame = new MyMainFrame(NULL);
	frame->Show(true);
	SetTopWindow(frame);
	return true;
} 

