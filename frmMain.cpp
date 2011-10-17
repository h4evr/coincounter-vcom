/*****************************************************************************
 * Coin Counter - 1st project "Visão por Computador" @ FEUP
 * Authors:
 *  - Diogo Costa (costa.h4evr@gmail.com)
 *  - Nuno Silva (nufil.ss@gmail.com)
 *
 * License: MIT
 *****************************************************************************/

#include "frmMain.h"
#include "imageCanvas.h"
#include <wx/filedlg.h>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include "meanshiftsegmentation.h"
#include <sstream>

using namespace cv;

Mat image;

typedef enum {
    ONE_CENT = 0,
    TWO_CENT,
    FIVE_CENT,
    TEN_CENT,
    TWENTY_CENT,
    FIFTY_CENT,
    ONE_EURO,
    TWO_EURO,
    NO_COIN
} COINS;

// Coin diameter in millimeters * 100
const int coin_sizes[] = {
    1625, // ONE_CENT
    1875, // TWO_CENT
    2125, // FIVE_CENT
    1975, // TEN_CENT
    2225, // TWENTY_CENT
    2425, // FIFTY_CENT
    2325, // ONE_EURO
    2575  // TWO_EURO
};

const std::string coin2str[] = {
    "1c",
    "2c",
    "5c",
    "10c",
    "20c",
    "50c",
    "1e",
    "2e"
};

const double largest_coin_radius = (2575.0 / 100.0 / 2.0);
const double smallest_coin_radius = (1625.0 / 100.0 / 2.0);

/** Constructor */
frmMain::frmMain( wxWindow* parent, wxWindowID id, const wxString& title, 
const wxPoint& pos, const wxSize& size, long style) :
MyMainFrame(parent, id, title, pos, size, style) {
	wxImage::AddHandler(new wxJPEGHandler());
}

/** The user wishes to load an image. */
void frmMain::onLoadImageClicked( wxCommandEvent& event ) {
	// Show a file dialog
	wxFileDialog diag(this);
	if(diag.ShowModal() == wxID_OK) {
		image = imread(std::string(diag.GetPath().mb_str(wxConvFile)));
		this->pnlBackground->SetImage(image);
		this->pnlBackground->Refresh();
	}
	diag.Destroy();
}

/** The user wishes to load an image from a camera. */
void frmMain::onLoadFromCameraClicked( wxCommandEvent& event ) {
	event.Skip();
}

/**
	Equalize the histogram of a colored image.
	This is done by equalizing the histograms of each channel and then
	merging them together.
 */
Mat equalize_color_histogram(Mat& image) {
	vector<Mat> channels;
	Mat dest;
	channels.reserve(3);
    split(image, channels);
    equalizeHist(channels[0], channels[0]);
    equalizeHist(channels[1], channels[1]);
    equalizeHist(channels[2], channels[2]);
    merge(channels, dest);
    
    return dest;
}

/**
	Normalize the energy of an image.
	This is not actually the correct implementation.
	To be accurate, this should be applied by blocks to the image, instead
	of dividing by the means of the while picture, but for the purpose of this
	project, this as proven to give best results.
	Check http://www.developerstation.org/2011/04/normalize-image-in-opencv.html
 */
Mat Normalize(const Mat& im) {
	Mat _tmp;
	Mat res;
	im.copyTo(res);

	//to store given mean and variance
	Scalar mean, std_deviation;
	
	//calculate mean and standard deviation
	meanStdDev(res, mean, std_deviation);
	convertScaleAbs(res, res, (1.0f / mean.val[0]), 0);	
	return res;
}

/*
 * Apply the mean-shift segmentation algorithm to an image
 */
Mat segmentate(const Mat& src) {	    
	CvMat _src = src;
	CvMat *_dest = cvCreateMat(_src.rows, _src.cols, _src.type);
	
	PyrMeanShiftFiltering(&_src, _dest, 3, 80, 1);
	
	return Mat(_dest);
}

Mat find_corners_and_adjust_image(Mat& im, bool* found_boundary=NULL, Mat* transform_matrix=NULL) {
    // Normalize the image energy
    Mat norm = Normalize(im);
    Mat img_gray;
    Mat edges;

    // Where the contours will be saved
    vector<vector<Point> > contours;

    // Convert to grayscale and normalize the histogram 
    cvtColor(norm, img_gray, CV_BGR2GRAY);
    equalizeHist(img_gray, img_gray);

    // Apply a very high threshold to keep only the white areas
    threshold(img_gray, img_gray, 250, 255, THRESH_BINARY);

    // Apply canny algo to pass only edges to the contour finding algorithm
    Canny(img_gray, edges, 0, 128, 5);

    // Find the contours!
    findContours(edges, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    //Mat vis;
    //cvtColor(edges, vis, CV_GRAY2BGR);
    //vector<vector<Point> > new_contours;

    // The boundary square will be kept here
    vector<Point> boundary;

    // Analyze contour
    for(size_t i = 0; i < contours.size(); ++i) {

        // Approximate the contour to polygon
        vector<Point> result;
        approxPolyDP(Mat(contours[i]), result, arcLength(Mat(contours[i]), true) * 0.02, true);

        //new_contours.push_back(result);
        //std::cout << result.size() << ", " << contourArea(Mat(result)) << std::endl;

        // If the polygon has more than 4 vertices, try to simplify it.
        if(result.size() >= 4) {
            // Get the (rotated) rectangle with the minimum area that encloses the polygon.
            RotatedRect r = minAreaRect(Mat(result));

            // If the polygon area is big enough, we have our square!
            if(r.size.area() >= 10000) {
                // Set the boundary as the new found polygon and exit

                // The RotatedRect needs to be converted to vector of points.
                // Trigonometry time!

                // Empty the boundary
                boundary = vector<Point>();

                // Angle of the RotatedRect is in degrees and
                // starts counting from the Y axis. Subtract from 90º to rectify.
                double cAng = cos((90-r.angle) * 0.0174532925);
                double sAng = sin((90-r.angle) * 0.0174532925);
                double halfW = r.size.width / 2;
                double halfH = r.size.height / 2;

                // Calculate each point of the rectangle and push it to the boundary.
                boundary.push_back(Point(r.center.x + (cAng * (-halfW) - sAng * (halfH)), 
                                         r.center.y + (sAng * (-halfW) + cAng * (halfH))));
                boundary.push_back(Point(r.center.x + (cAng * (-halfW) - sAng * (-halfH)), 
                                         r.center.y + (sAng * (-halfW) + cAng * (-halfH))));
                boundary.push_back(Point(r.center.x + (cAng * (halfW) - sAng * (-halfH)), 
                                         r.center.y + (sAng * (halfW) + cAng * (-halfH))));
                boundary.push_back(Point(r.center.x + (cAng * (halfW) - sAng * (halfH)), 
                                         r.center.y + (sAng * (halfW) + cAng * (halfH))));

                // Boundary is set, we're done here!
                break;
            }
        }
	}

    // for(size_t i = 0; i < new_contours.size(); ++i) {
    //     if(new_contours[i].size() >= 4 && contourArea(Mat(new_contours[i])) > 1000) {
    //         std::cout << "BAH --> " << i << ", " << contourArea(Mat(new_contours[i])) << std::endl;
    //         vector<vector<Point> > cn;
    //         cn.push_back(new_contours[i]);
    //         drawContours(vis, cn, -1, Scalar( 255 / new_contours.size() * i, 255, 0), 1);
    //     }
    // }

    // cvNamedWindow("teste");
    // imshow("teste", vis);

    // If a boundary was detected, apply a perspective transform,
    // or else, return the original image.
    if(boundary.size() > 0) {
        // Map the found boundary
        Point2f src[] = {
            boundary[0],
            boundary[1],
            boundary[2],
            boundary[3]
        };

        // to the full area of the image
        Point2f dst[] = {
            Point2f(0.0f, 0.0f),
            Point2f(im.cols, 0.0f),
            Point2f(im.cols, im.cols),
            Point2f(0.0f, im.cols)
        };

        // Calculate the transform matrix between the 4 pairs of points
        Mat transform = getPerspectiveTransform(src, dst);

        // Apply the transformation to the image
        Mat corrected;
        warpPerspective(im, corrected, transform, Size(im.cols, im.cols));

        if(transform_matrix) {
            *transform_matrix = transform;
        }

        if(found_boundary) {
            *found_boundary = true;
        }

        // Return the new image!
        return corrected;
    } else {
        if(found_boundary) {
            *found_boundary = false;
        }

        // No boundary detected, so return the original image.
        return im;
    }
}

COINS match_coin(int x, int y, int radius, double factor) {
    int diameter = (int)(radius * factor * 200.0);
    int epsilon = smallest_coin_radius * 100 / 10;

    int diff[] = {0, 0, 0, 0, 0, 0, 0, 0};

    for(int i = ONE_CENT; i < NO_COIN; ++i) {
        diff[i] = abs(diameter - coin_sizes[i]);
    }

    int min_index = 0;
    int min_val = diff[0];

    for(int i = ONE_CENT; i < NO_COIN; ++i) {
        if(diff[i] < min_val) {
            min_val = diff[i];
            min_index = i;
        }
    }

    //std::cout << "Coin diameter: " << diameter << std::endl
    //          << "Lowest diff: " << min_val << std::endl
    //          << "Epsilon: " << epsilon << std::endl
    //          << std::endl;

    if(min_val <= epsilon)
        return (COINS)min_index;
    else
        return NO_COIN;
}

int get_number_of_supporting_pixels(const Mat& img, int x, int y, int radius) {
    int counter = 0;
    int pX, pY;

    for(double angle = 0.0; angle <= 2.0 * 3.14159; angle += 0.0174532925) {
        pX = x + radius * cos(angle);
        pY = y + radius * sin(angle);
        if(pX >= 0 && pX < img.cols &&
           pY >= 0 && pY < img.rows) {
            uchar pixel = img.at<uchar>(pY, pX);
            if(pixel != 0) {
                ++counter;
            }
        }
    }

    return counter;
}

void cluster_circles(const Mat& img, vector<Vec3f>& circles) {
    vector<std::pair<int,Vec3f> > analysis;
    vector<Vec3f> result;

    int min_dist = 81;

    for(size_t i = 0; i < circles.size(); ++i) {
        analysis.push_back(std::pair<int,Vec3f>(get_number_of_supporting_pixels(img, 
                                            circles[i][0], circles[i][1], circles[i][2]),
                                           circles[i]));
    }

    int maximum = -1;
    int best_index = -1;

    vector<bool> marked;
    marked.reserve(analysis.size());
    for(size_t i = 0; i < analysis.size(); ++i) {
        marked[i] = false;
    }

    for(size_t i = 0; i < analysis.size(); ++i) {
        if(marked[i]) continue;

        maximum = analysis[i].first;

        float x = analysis[i].second[0];
        float y = analysis[i].second[1];

        for(size_t j = 0; j < analysis.size(); ++j) {
            if(j == i || marked[j]) continue;

            float dx = (analysis[j].second[0] - x);
            dx *= dx;

            float dy = (analysis[j].second[1] - y);
            dy *= dy;

            float dist = sqrt(dx + dy);

            if(dist <= min_dist) {
                if(analysis[j].first > maximum) {
                    maximum = analysis[j].first;
                    marked[i] = true;
                } else {
                    marked[j] = true;
                }
            }
        }

        std::cout << maximum << std::endl;
    }

    for(size_t i = 0; i < analysis.size(); ++i) {
        if(marked[i]) continue;
        result.push_back(analysis[i].second);
    }

    circles = result;
}

/** If an image is loaded, start the process of counting the coins. */
void frmMain::onCountMoneyClicked( wxCommandEvent& event ) {
	
    
	// Normalize the energy of the image (reduces JPEG artifacts!)
	//Mat img_norm = Normalize(image);
	
    //blur(image, image, Size(5,5));

	// Equalize the histogram of the color image (to restore contrast taken by
	// the normalization).
	//Mat img_eq = equalize_color_histogram(image);
	
	// Blur the image to remove noise
	
	// Segmentate the image using the meanshift segmentation algorithm.
	Mat img_color = segmentate(image);

    bool found_boundary = true;
    Mat perspective_transform;

    // Uncomment to stop if no  boundary is detected.
    img_color = find_corners_and_adjust_image(img_color/*, &found_boundary*/, NULL, &perspective_transform);

    if(!found_boundary) {
        wxMessageBox(_("No boundary detected, so detection method will not work.\nTry another image, please!"), _("Error"), wxOK | wxICON_ERROR);
        return;
    }

	// Convert the image to grayscale
	Mat img_gray;
	cvtColor(img_color, img_gray, CV_BGR2GRAY);

	// TODO: Implement a routine to calculate an automatic threshold
    int canny_param = 80;
	
	//Threshold to convert the image to black & white
	Mat img_bw;
	threshold(img_gray, img_bw, canny_param, 255, THRESH_TOZERO);
	
	// Used only for visualization purposes.
	// Uses the same parameters as the hough transform.
	Mat edges;
		
	Canny(img_bw, edges, canny_param >> 1, canny_param, 3);
	
    // Calculate the scaling factor
    double factor = 195.0 / (double)edges.cols;

    // Calculate the minimum and maximum radius of a coin in pixels
    int max_radius = largest_coin_radius / factor;
    int min_radius = smallest_coin_radius / factor;
    int allowed_offset = 1.5/*mm*/ / factor;

    std::cout << "Largest coin radius: " << max_radius << std::endl
              << "Smallest coin radius: " << min_radius << std::endl;

	// Apply the Hough transform to find existing circles
	vector<Vec3f> circles;
	
    HoughCircles(img_bw, circles, CV_HOUGH_GRADIENT, 1, 
                1,//min_radius - allowed_offset, // Min dist between circle centers
                canny_param, // Higher threshold on canny
                (min_radius - allowed_offset) / 2, // Number of required votes
                min_radius - allowed_offset, // Minimum radius
                max_radius + allowed_offset); // Maximum radius

	// Prepare image for visualization
    //Mat original_image_cropped;
    //warpPerspective(image, original_image_cropped, perspective_transform, Size(image.rows, image.rows));
    //img_color = original_image_cropped;
    cvtColor(edges, img_color, CV_GRAY2BGR);

    int coin_amounts[] = {0, 0, 0, 0, 0, 0, 0, 0};

    cluster_circles(edges, circles);

	// Draw the circles that were found
	for( size_t i = 0; i < circles.size(); i++ ) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

		COINS detected_coin = match_coin(center.x, center.y, radius, factor);
        if(detected_coin != NO_COIN) {
            // draw the circle center
            circle( img_color, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // draw the circle outline
            circle( img_color, center, radius, Scalar(0,0,255), 1, 8, 0 );

            std::stringstream radiusStr;
            radiusStr << coin2str[detected_coin] << " ("
                      << (int)(radius * factor * 200.0) << ")";

            putText(img_color, radiusStr.str(), center, FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 0), 3);

            coin_amounts[(int)detected_coin]++;
        } else {
            // draw the circle center
            circle( img_color, center, 3, Scalar(0,255,255), -1, 8, 0 );
            // draw the circle outline
            circle( img_color, center, radius, Scalar(255,0,255), 1, 8, 0 );

            std::stringstream radiusStr;
            radiusStr << (int)(radius * factor * 200.0);

            putText(img_color, radiusStr.str(), center, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 255));
        }
	}

    // Update the UI
    this->lbl1CentCoins->SetLabel(wxString::Format(_("%d"), coin_amounts[ONE_CENT]));
    this->lbl2CentCoins->SetLabel(wxString::Format(_("%d"), coin_amounts[TWO_CENT]));
    this->lbl5CentCoins->SetLabel(wxString::Format(_("%d"), coin_amounts[FIVE_CENT]));
    this->lbl10CentCoins->SetLabel(wxString::Format(_("%d"), coin_amounts[TEN_CENT]));
    this->lbl20CentCoins->SetLabel(wxString::Format(_("%d"), coin_amounts[TWENTY_CENT]));
    this->lbl50CentCoins->SetLabel(wxString::Format(_("%d"), coin_amounts[FIFTY_CENT]));
    this->lbl1EuroCoins->SetLabel(wxString::Format(_("%d"), coin_amounts[ONE_EURO]));
    this->lbl2EuroCoins->SetLabel(wxString::Format(_("%d"), coin_amounts[TWO_EURO]));

    double sum = (coin_amounts[ONE_CENT] 
               + 2 * coin_amounts[TWO_CENT]
               + 5 * coin_amounts[FIVE_CENT]
               + 10 * coin_amounts[TEN_CENT]
               + 20 * coin_amounts[TWENTY_CENT]
               + 50 * coin_amounts[FIFTY_CENT]
               + 100 * coin_amounts[ONE_EURO]
               + 200 * coin_amounts[TWO_EURO])
               / 100.0;

    this->lblTotalAmount->SetLabel(wxString::Format(_("%.2f €"), sum));

	// Show the final image to the user
	this->pnlBackground->SetImage(img_color);
    this->Layout();
    this->Refresh();
}

/** Show information about the application. */
void frmMain::onAboutClicked( wxCommandEvent& event ) {
	frmAbout* frm = new frmAbout(this);
	frm->ShowModal();
	delete frm;
}


