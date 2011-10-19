/*
 * =====================================================================================
 *
 *       Filename:  circle_fitting.cpp
 *
 *    Description:  Algorithm to find a circle that best fits a set of points
 *
 *        Version:  1.0
 *        Created:  19-10-2011 16:52:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Diogo Costa (h4evr), costa.h4evr@gmail.com
 *
 * =====================================================================================
 */

#include "circle_fitting.h"
#include <cv.h>
#include <iostream>

using namespace cv;

void print_matrix(Mat& z) {
    for(int i = 0; i < z.rows; ++i) {
        for(int j = 0; j < z.cols; ++j) {
            std::cout << z.at<float>(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

/******************************************************************************/
/* Perform Gauss-Jordan elimination with row-pivoting to obtain the solution to 
 * the system of linear equations
 * A X = B
 * 
 * Arguments:
 * 		lhs		-	left-hand side of the equation, matrix A
 * 		rhs		-	right-hand side of the equation, matrix B
 * 		nrows	-	number of rows in the arrays lhs and rhs
 * 		ncolsrhs-	number of columns in the array rhs
 * 
 * The function uses Gauss-Jordan elimination with pivoting.  The solution X to 
 * the linear system winds up stored in the array rhs; create a copy to pass to
 * the function if you wish to retain the original RHS array.
 * 
 * Passing the identity matrix as the rhs argument results in the inverse of 
 * matrix A, if it exists.
 * 
 * No library or header dependencies, but requires the function swaprows, which 
 * is included here.
 *
 * CREDIT: http://www.dreamincode.net/code/snippet1312.htm (by jjhang)
 */


//  swaprows - exchanges the contents of row0 and row1 in a 2d array
void swaprows(Mat& arr, long row0, long row1) {
	Mat temp;
    temp = arr.row(row0);
    arr.row(row0) = arr.row(row1);
    arr.row(row1) = temp;
}

//	gjelim
// Gauss-Jordan Elimination
bool gjelim(Mat& lhs, Mat& rhs, Mat& out) {

	long nrows = lhs.size().height;
	long ncolsrhs = rhs.size().width;

    //	augment lhs array with rhs array and store in arr2
    Mat arr2(nrows, nrows + ncolsrhs, CV_32FC1);

    for (long row = 0; row < nrows; ++row) {
        for (long col = 0; col < nrows; ++col) {
            arr2.at<float>(row, col) = lhs.at<float>(row, col);
        }

        for (long col = nrows; col < nrows + ncolsrhs; ++col) {
            arr2.at<float>(row, col) = rhs.at<float>(row, col-nrows);
        }
    }

    //	perform forward elimination to get arr2 in row-echelon form
    for (long dindex = 0; dindex < nrows; ++dindex) {
        //	run along diagonal, swapping rows to move zeros in working position 
        //	(along the diagonal) downwards
        if ( (dindex==(nrows-1)) && (arr2.at<float>(dindex, dindex) == 0)) {
            return false; //  no solution
        } else if (arr2.at<float>(dindex, dindex) == 0) {
            swaprows(arr2, dindex, dindex + 1);
        }

        //	divide working row by value of working position to get a 1 on the
        //	diagonal
        if (arr2.at<float>(dindex, dindex) == 0.0) {
            return false;
        } else {
            double tempval = arr2.at<float>(dindex, dindex);
            for (long col = 0; col < nrows + ncolsrhs; ++col) {
                arr2.at<float>(dindex, col) /= tempval;
            }
        }

        //	eliminate value below working position by subtracting a multiple of 
        //	the current row
        for (long row = dindex + 1; row < nrows; ++row) {
            double wval = arr2.at<float>(row, dindex);
            for (long col = 0; col < nrows + ncolsrhs; ++col) {
                arr2.at<float>(row, col) -= wval * arr2.at<float>(dindex, col);
            }
        }
    }

    //	backward substitution steps
    for (long dindex = nrows-1; dindex >= 0; --dindex) {
        //	eliminate value above working position by subtracting a multiple of 
        //	the current row
        for (long row = dindex-1; row >= 0; --row) {
            double wval = arr2.at<float>(row, dindex);
            for (long col=0; col<nrows+ncolsrhs; ++col) {
                arr2.at<float>(row, col) -= wval * arr2.at<float>(dindex, col);
            }
        }
    }

    out = arr2;
    return true;
}

Point3f circle_fitting(std::vector<Point2f> points) {
    Point3f res;
    Mat MT, b;
    Mat c, z;

    Mat M(points.size(), 3, CV_32FC1);
    Mat y(points.size(), 1, CV_32FC1);

    float px, py;

    for(unsigned int i = 0; i < points.size(); ++i) {
        px = points[i].x;
        py = points[i].y;

        M.at<float>(i, 0) = px;
        M.at<float>(i, 1) = py;
        M.at<float>(i, 2) = 1.0f;

        y.at<float>(i, 0) = px * px + py * py;
    }

    MT = M.t();
    b = MT * M;
    c = MT * y;
    gjelim(b, c, z);

    // print_matrix(MT);
    // std::cout << std::endl;

    // print_matrix(y);
    // std::cout << std::endl;

    // print_matrix(b);
    // std::cout << std::endl;

    // print_matrix(c);
    // std::cout << std::endl;

    // print_matrix(z);
    // std::cout << std::endl;

    Mat lastCol = z.col(z.cols - 1);

    res.x = lastCol.at<float>(0, 0) * 0.5;
    res.y = lastCol.at<float>(1, 0) * 0.5;
    res.z = sqrt(lastCol.at<float>(2, 0) + res.x * res.x + res.y * res.y);

    return res;
}
