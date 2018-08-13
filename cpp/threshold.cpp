#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat image, image_gray;
Mat thresh_dst;

int disp_threshold= 44;
int disp_threshold_min = 42;
int disp_threshold_max = 46;
int range = 5;


void ThresholdMask(int, void*)
{
	disp_threshold_min = disp_threshold;
	disp_threshold_max = disp_threshold+range;

	if (disp_threshold_max>255)
	{
		disp_threshold_max=255;
	}
	
	threshold(image_gray, thresh_dst, disp_threshold_max, 255, THRESH_TOZERO_INV);
	threshold(thresh_dst, thresh_dst, disp_threshold_min, 255, THRESH_BINARY);
	// threshold(thresh_dst, thresh_dst, disp_threshold_max, 255, THRESH_BINARY_INV);

	imshow("ThresholdMask", thresh_dst);
}

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    image = imread( argv[1], 1 );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    cvtColor( image, image_gray, COLOR_BGR2GRAY );

    namedWindow("ThresholdMask", WINDOW_AUTOSIZE);
    createTrackbar( "Value ThresholdMask:", "ThresholdMask", &disp_threshold, 245, ThresholdMask );
    createTrackbar( "Disparity Range:", "ThresholdMask", &range, 50, ThresholdMask );

    // Initialize Function
    ThresholdMask(0,0);

    // Wait until user exit program by pressing a key
    waitKey(0);

    return 0;
}