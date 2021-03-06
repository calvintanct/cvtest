#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

    Mat image, img_gray;
    Mat dst, detected_edges;

    int edgeThresh = 1;
    int lowThreshold;
    int const max_lowThreshold = 100;
    int threshratio = 3;
    int kernel_size = 3;
    String window_name = "Edge Map";


void CannyThreshold(int, void*)
{
    // Reduce noise with a kernel 3x3 Blur
    // Blurring is very useful for smoothing the color between pixel so only the edges stands out
    blur( img_gray, detected_edges, Size(3,3) );

    // Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*threshratio, kernel_size );

    // Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);

    image.copyTo( dst, detected_edges);
    imshow( window_name, dst );
    namedWindow("Canny Direct Result", WINDOW_AUTOSIZE);
    imshow( "Canny Direct Result", detected_edges );
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
    // Create a matrix with the same size for final display
    dst.create( image.size(), image.type() );

    // For canny edges, it is important to set and change to grayscale color
    cvtColor( image, img_gray, COLOR_BGR2GRAY );

    // Create a window
    namedWindow( window_name, WINDOW_AUTOSIZE );

    // Create a Trackbar for user to enter threshold
    // Create Trackbar is running on a function, so it will be forever looping
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

    // Show the Image_Path
    CannyThreshold(0, 0);
    
    // Wait until user exit program by pressing a key
    waitKey(0);

    return 0;
}
