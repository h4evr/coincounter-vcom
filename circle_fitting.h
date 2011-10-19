/*
 * =====================================================================================
 *
 *       Filename:  circle_fitting.h
 *
 *    Description:  Algorithm to find a circle that best fits a set of points
 *
 *        Version:  1.0
 *        Created:  19-10-2011 16:53:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Diogo Costa (h4evr), costa.h4evr@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __CIRCLE_FITTING_H__
#define __CIRCLE_FITTING_H__

#include <cv.h>
using namespace cv;

Point3f circle_fitting(std::vector<Point2f> points);
//void print_matrix(float* M, int cols, int rows);
//float* transpose(float* M, int cols, int rows);
//float* multiply_matrix_by_matrix(float* M1, float* M2, int cols1, int rows1, int cols2, int rows2);

#endif
