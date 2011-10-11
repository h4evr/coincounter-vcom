#include "imageCanvas.h"
#include <cv.h>
#include <highgui.h>

BEGIN_EVENT_TABLE(ImageCanvas, wxPanel)
// catch paint events
EVT_PAINT(ImageCanvas::paintEvent) 
END_EVENT_TABLE()

ImageCanvas::ImageCanvas(wxWindow* parent, wxWindowID id, 
const wxPoint& pos, const wxSize& size, long style, const wxString& name):
wxPanel(parent, id, pos, size, style, name)
{
}
 
/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
 
void ImageCanvas::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
}
  
/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void ImageCanvas::render(wxDC&  dc) {
	if(!image.IsOk())
		return;
	
	wxCoord w, h;
	this->GetSize(&w, &h);
	double scaleX = (double)w / (double)image.GetWidth();
	double scaleY = (double)h / (double)image.GetHeight();
	dc.SetUserScale(std::min(scaleX, scaleY), std::min(scaleX, scaleY));
	dc.DrawBitmap(image, 0, 0, false);
}

/** Set the image that is to be rendered. */
void ImageCanvas::SetImage(const cv::Mat& image) {
	cv::imwrite("imagecanvastmpimage.jpg", image);
	this->image.LoadFile(_("imagecanvastmpimage.jpg"), wxBITMAP_TYPE_JPEG);
	//::wxRemoveFile(_(".imagecanvastmpimage.jpg"));
}

