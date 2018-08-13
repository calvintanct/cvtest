#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    Mat image;
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    // Split image into 3 planes B G R
    vector<Mat> bgr_planes;
    split(image, bgr_planes);

    // number of bins to categorize
    int histSize = 256;

    /// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ; //the upper boundary is exclusive
	const float* histRange = { range };

	// Set the bin to have the same size
	bool uniform = true; bool accumulate = false;

	// Create 3 matrix for 3 color histogram
	Mat b_hist, g_hist, r_hist;

	// Calculation of Histogram
    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    // Draw the histograms for R, G and B
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	// Rows is Heights (Y) and Columns is width (X)

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	// Normalize the result to [0, histImage.rows], spread the histogram Height result evenly to histImage later
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	// Draw for each channel
	for( int i = 1; i < histSize; i++ )
	{
		// line function to draw a line to image <histImage> from one point to one point with color (in Scalar) and other parameters
		// Point is (X, Y), Y is always counted from the top to bottom
		// for the correct interpretation the value must be total height minus b_hist value
	    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
	                     Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
	                     Scalar( 255, 0, 0), 2, 8, 0  );
	    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
	                     Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
	                     Scalar( 0, 255, 0), 2, 8, 0  );
	    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
	                     Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
	                     Scalar( 0, 0, 255), 2, 8, 0  );
	}

	namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    namedWindow("Histogram", WINDOW_AUTOSIZE );
    imshow("Histogram", histImage);
    waitKey(0);

    return 0;
}