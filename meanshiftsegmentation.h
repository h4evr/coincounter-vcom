#ifndef __MEANSHIFT_SEGMENTATION_H__
#define __MEANSHIFT_SEGMENTATION_H__

/*
 * Used to bypass an error in OpenCV 2.1.0 (at least in Unix..)
 */

#include <cv.h>

void PyrMeanShiftFiltering( const CvArr* srcarr, CvArr* dstarr,  
                         	double sp0, double sr, int max_level = 1, 
                         	CvTermCriteria termcrit = cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS,5,1));

#endif
