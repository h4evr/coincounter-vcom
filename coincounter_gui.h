///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __coincounter_gui__
#define __coincounter_gui__

#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/frame.h>
#include <wx/hyperlink.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyMainFrame
///////////////////////////////////////////////////////////////////////////////
class MyMainFrame : public wxFrame 
{
	private:
	
	protected:
		wxButton* btnLoadImage;
		wxButton* btnCountMoney;
		
		wxButton* btnAbout;
		wxPanel* pnlBackground;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText2;
		wxStaticText* lbl1CentCoins;
		wxStaticText* m_staticText4;
		wxStaticText* lbl2CentCoins;
		wxStaticText* m_staticText6;
		wxStaticText* lbl5CentCoins;
		wxStaticText* m_staticText8;
		wxStaticText* lbl10CentCoins;
		wxStaticText* m_staticText11;
		wxStaticText* lbl20CentCoins;
		wxStaticText* m_staticText13;
		wxStaticText* lbl50CentCoins;
		wxStaticText* m_staticText15;
		wxStaticText* lbl1EuroCoins;
		wxStaticText* m_staticText17;
		wxStaticText* lbl2EuroCoins;
		wxStaticText* m_staticText19;
		wxStaticText* lblTotalAmount;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onLoadImageClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCountMoneyClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAboutClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Coin Counter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 511,451 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MyMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialog
///////////////////////////////////////////////////////////////////////////////
class AboutDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText21;
		wxStaticText* m_staticText26;
		wxStaticText* m_staticText22;
		wxStaticText* m_staticText23;
		wxHyperlinkCtrl* m_hyperlink1;
		wxStaticText* m_staticText25;
		wxHyperlinkCtrl* m_hyperlink7;
		wxButton* btnOk;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onOkClicked( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~AboutDialog();
	
};

#endif //__coincounter_gui__
