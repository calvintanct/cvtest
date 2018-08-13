#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// For Thresholding Disparity
Mat image_disp, image_disp_gray;

Mat thresh_dst;

int disp_threshold= 44;
int disp_threshold_pixel = 5000;
int disp_threshold_min = 42;
int disp_threshold_max = 46;
int range = 5;

// For Canny Edges and Morphology
Mat image_left, image_left_gray;
Mat dst, detected_edges;
Mat opening, kernel;

int elmt_kernel_size=3;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int threshratio = 3;
int kernel_size = 3;
String window_name = "Edge Map";

int shape_mode=0;

// For Combination
Mat comb;
int flag =0;


void Combination(void)
{
    if (opening.data) 
    {
        if(thresh_dst.data)
        {
            bitwise_and(thresh_dst, opening, comb);

            imshow("Combination", comb);
        }
        
    }
    return;
}

void ThresholdMask(int, void*)
{
    // number of bins to categorize
    int histSize = 256;

    /// Set the ranges
    float bound_range[] = { 0, 256 } ; //the upper boundary is exclusive
    const float* histRange = { bound_range };

    // Set the bin to have the same size
    bool uniform = true; bool accumulate = false;

    // Create 3 matrix for 3 color histogram
    Mat disp_hist;

    // Calculation of Histogram
    calcHist( &image_disp_gray, 1, 0, Mat(), disp_hist, 1, &histSize, &histRange, uniform, accumulate);

    // Create a list of filtered histogram
    list<int> filtered_hist;

    // Start Filtering
    for (int i = 0; i < 256; i++)
    {
        if (disp_hist.at<float>(i) > disp_threshold_pixel)
        {
            filtered_hist.push_front(i);
        }
    }

    list<int>::iterator it = filtered_hist.begin();
    disp_threshold_max = *it;

    cout<<"List of filtered"<<endl;

    while(it != filtered_hist.end())
    {
        cout<<(*it)<<"  ";
        int i = 0;
        if (i > 10)
        {
            filtered_hist.erase(it);
        }
        else if(i <= 10 & (disp_threshold_max - *it) < 20)
        {
            disp_threshold_min = *it;
        }


        i++;
        it++;
    }

    cout<<endl;
    cout<<"List of final filtered list"<<endl;

    it = filtered_hist.begin();
    while(it != filtered_hist.end())
    {
        cout<<(*it)<<"  ";
        it++;
    }

    cout<<endl;
    cout<<"disp_threshold_min = "<< disp_threshold_min <<endl;
    cout<<"disp_threshold_max = "<< disp_threshold_max <<endl;


	// disp_threshold_min = disp_threshold;
	// disp_threshold_max = disp_threshold+range;

	if (disp_threshold_max>255)
	{
		disp_threshold_max=255;
	}
	
	threshold(image_disp_gray, thresh_dst, disp_threshold_max, 255, THRESH_TOZERO_INV);
	threshold(thresh_dst, thresh_dst, disp_threshold_min, 255, THRESH_BINARY);
	// threshold(thresh_dst, thresh_dst, disp_threshold_max, 255, THRESH_BINARY_INV);

	imshow("ThresholdMask", thresh_dst);

    // Combination
    Combination();

    // if (opening.data) 
    // {
    //     bitwise_and(thresh_dst, opening, comb);

    //     imshow("Combination", comb);
    // }
}

void CannyThreshold(int, void*)
{
    // Reduce noise with a kernel 3x3 Blur
    // Blurring is very useful for smoothing the color between pixel so only the edges stands out
    blur( image_left_gray, detected_edges, Size(3,3) );

    // Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*threshratio, kernel_size );

    // Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);

    // Copy the real image value to dst with masking of detected edges
    image_left.copyTo( dst, detected_edges);

    // Show the results

    imshow( window_name, dst );

    Combination();


}

void Morph(int, void*)
{
    // Creating a kernel
    Mat dilation_kernel = getStructuringElement(shape_mode , Size(3,3),Point(-1,-1));
    Mat kernel = getStructuringElement(shape_mode , Size(elmt_kernel_size+1,elmt_kernel_size+1),Point(-1,-1));

    // Morphological transformation dilate then open
    dilate(detected_edges, opening, dilation_kernel);
    morphologyEx(opening, opening, MORPH_CLOSE, kernel);
    
    // Show the results
    imshow("Dilation", opening);

    // Combination

    Combination();

    // if (thresh_dst.data) 
    // {
    //     bitwise_and(thresh_dst, opening, comb);

    //     imshow("Combination", comb);
    // }
    
}

int main(int argc, char** argv )
{
    if ( argc != 3 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    image_disp = imread( argv[1], 1 );
    if ( !image_disp.data )
    {
        printf("No image_disp data \n");
        return -1;
    }

    image_left = imread( argv[2], 1 );
    if ( !image_left.data )
    {
        printf("No image_left data \n");
        return -1;
    }

    // Create a matrix with the same size for final display
    dst.create( image_left.size(), image_left.type() );

    // It is important to set and change to grayscale color
    cvtColor( image_left, image_left_gray, COLOR_BGR2GRAY );
    cvtColor( image_disp, image_disp_gray, COLOR_BGR2GRAY );

    // Create windows
    namedWindow( window_name, WINDOW_AUTOSIZE );
    namedWindow( "Dilation", WINDOW_AUTOSIZE );
    namedWindow("ThresholdMask", WINDOW_AUTOSIZE);
    namedWindow("Combination", WINDOW_AUTOSIZE);

    // Create a Trackbar for user to enter threshold
    // Create Trackbar is running on a function, so it will be forever looping
    createTrackbar( "Min Canny Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
    createTrackbar( "Kernel Size Element:", "Dilation", &elmt_kernel_size, 100, Morph );
    createTrackbar( "Kernel Shape 1 Rect 2 Shape 3 Ellipse", "Dilation", &shape_mode, 2, Morph );

    // Create a Trackbar for user to enter disparity threshold
    createTrackbar( "Pixels Value ThresholdMask:", "ThresholdMask", &disp_threshold_pixel, 20000, ThresholdMask );
    // createTrackbar( "Disparity Range:", "ThresholdMask", &range, 50, ThresholdMask );

    // Initialize Threshold Function
    ThresholdMask(0,0);

    // Initialize CannyThreshold and Morph Function
    CannyThreshold(0, 0);
    Morph(0,0);

    // // Initialize Combining Function
    // Combination(0,0);

    // Wait until user exit program by pressing a key
    waitKey(0);

    return 0;
}