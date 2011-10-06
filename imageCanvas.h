#ifndef __IMAGE_CANVAS_H__
#define __IMAGE_CANVAS_H__

#include <wx/wx.h>
#include <wx/sizer.h>
#include <cv.h>
#include <highgui.h>

/** Allows the drawing of an OpenCV file in wxWidgets panel. */
class ImageCanvas : public wxPanel {
	public:
		/** Constructor */
		ImageCanvas(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = _("panel"));
		
		/** Handle the paint event. */
		void paintEvent(wxPaintEvent & evt);
		
		/** Do the actual rendering */		
		void render(wxDC& dc);

		/** Set the image that is to be rendered. */
		void SetImage(const cv::Mat& image);
	
	private:
		wxBitmap image;
	
	DECLARE_EVENT_TABLE()	
};

#endif

