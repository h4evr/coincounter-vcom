///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "coincounter_gui.h"

///////////////////////////////////////////////////////////////////////////

MyMainFrame::MyMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	btnLoadImage = new wxButton( this, wxID_ANY, wxT("Load Image"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnLoadImage, 0, wxALL, 5 );
	
	btnCountMoney = new wxButton( this, wxID_ANY, wxT("Count Money"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnCountMoney, 0, wxALL, 5 );
	
	
	bSizer2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnAbout = new wxButton( this, wxID_ANY, wxT("About"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( btnAbout, 0, wxALL, 5 );
	
	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );
	
	pnlBackground = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer1->Add( pnlBackground, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Detected Coins:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer4->Add( m_staticText1, 0, wxALL, 5 );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 4, 4, 0, 0 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("1 cent.:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer1->Add( m_staticText2, 0, wxALL, 5 );
	
	lbl1CentCoins = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	lbl1CentCoins->Wrap( -1 );
	gSizer1->Add( lbl1CentCoins, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("2 cent.:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gSizer1->Add( m_staticText4, 0, wxALL, 5 );
	
	lbl2CentCoins = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	lbl2CentCoins->Wrap( -1 );
	gSizer1->Add( lbl2CentCoins, 0, wxALL, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("5 cent.:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	gSizer1->Add( m_staticText6, 0, wxALL, 5 );
	
	lbl5CentCoins = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	lbl5CentCoins->Wrap( -1 );
	gSizer1->Add( lbl5CentCoins, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("10 cent.:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	gSizer1->Add( m_staticText8, 0, wxALL, 5 );
	
	lbl10CentCoins = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	lbl10CentCoins->Wrap( -1 );
	gSizer1->Add( lbl10CentCoins, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("20 cent.:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	gSizer1->Add( m_staticText11, 0, wxALL, 5 );
	
	lbl20CentCoins = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	lbl20CentCoins->Wrap( -1 );
	gSizer1->Add( lbl20CentCoins, 0, wxALL, 5 );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("50 cent.:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	gSizer1->Add( m_staticText13, 0, wxALL, 5 );
	
	lbl50CentCoins = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	lbl50CentCoins->Wrap( -1 );
	gSizer1->Add( lbl50CentCoins, 0, wxALL, 5 );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("1 euro:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	gSizer1->Add( m_staticText15, 0, wxALL, 5 );
	
	lbl1EuroCoins = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	lbl1EuroCoins->Wrap( -1 );
	gSizer1->Add( lbl1EuroCoins, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("2 euro:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	gSizer1->Add( m_staticText17, 0, wxALL, 5 );
	
	lbl2EuroCoins = new wxStaticText( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	lbl2EuroCoins->Wrap( -1 );
	gSizer1->Add( lbl2EuroCoins, 0, wxALL, 5 );
	
	bSizer4->Add( gSizer1, 0, 0, 5 );
	
	bSizer3->Add( bSizer4, 0, 0, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText19 = new wxStaticText( this, wxID_ANY, wxT("Total amount:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	m_staticText19->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer5->Add( m_staticText19, 0, wxALL, 5 );
	
	lblTotalAmount = new wxStaticText( this, wxID_ANY, wxT("0 €"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTotalAmount->Wrap( -1 );
	bSizer5->Add( lblTotalAmount, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	bSizer3->Add( bSizer5, 1, wxALIGN_BOTTOM, 5 );
	
	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	btnLoadImage->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyMainFrame::onLoadImageClicked ), NULL, this );
	btnCountMoney->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyMainFrame::onCountMoneyClicked ), NULL, this );
	btnAbout->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyMainFrame::onAboutClicked ), NULL, this );
}

MyMainFrame::~MyMainFrame()
{
	// Disconnect Events
	btnLoadImage->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyMainFrame::onLoadImageClicked ), NULL, this );
	btnCountMoney->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyMainFrame::onCountMoneyClicked ), NULL, this );
	btnAbout->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyMainFrame::onAboutClicked ), NULL, this );
}

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Coin Counter"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	m_staticText21->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer6->Add( m_staticText21, 0, wxALL, 15 );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, wxT("A coin detector (euro!) that aims to present \nthe total amount of money present in a picture. "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	bSizer6->Add( m_staticText26, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("Authors:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer6->Add( m_staticText22, 0, wxALL, 5 );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 2, 2, 0, 0 );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("Diogo Costa"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	gSizer2->Add( m_staticText23, 0, wxALL, 5 );
	
	m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("costa.h4evr@gmail.com"), wxT("mailto:costa.h4evr@gmail.com"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	gSizer2->Add( m_hyperlink1, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( this, wxID_ANY, wxT("Nuno Silva"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	gSizer2->Add( m_staticText25, 0, wxALL, 5 );
	
	m_hyperlink7 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("nufil.ss@gmail.com"), wxT("mailto:nufil.ss@gmail.com"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	gSizer2->Add( m_hyperlink7, 0, wxALL, 5 );
	
	bSizer6->Add( gSizer2, 1, wxEXPAND, 5 );
	
	btnOk = new wxButton( this, wxID_ANY, wxT("Ok!"), wxDefaultPosition, wxDefaultSize, 0 );
	btnOk->SetDefault(); 
	bSizer6->Add( btnOk, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer6 );
	this->Layout();
	bSizer6->Fit( this );
	
	// Connect Events
	btnOk->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::onOkClicked ), NULL, this );
}

AboutDialog::~AboutDialog()
{
	// Disconnect Events
	btnOk->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::onOkClicked ), NULL, this );
}
