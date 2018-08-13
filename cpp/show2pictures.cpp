#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat image_disp, image_left;

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

    namedWindow("ShowDisp", WINDOW_AUTOSIZE );
    imshow("ShowDisp", image_disp);
    imshow("ShowLeft", image_left);

    // Wait until user exit program by pressing a key
    waitKey(0);

    return 0;
}