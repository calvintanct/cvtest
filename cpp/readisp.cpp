

// Created: Tuesday, July 31, 2018 (180731)
// Purpose: Read a raw disparity map cv::Mat from a file

#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ximgproc/disparity_filter.hpp"

#include <stdio.h>
#include <iostream>
#include <sstream>


static int ghistoWidth = 320;
static int ghistoHeight = 420;
static int gcountBins = 64;


class CDisparity {

public:
  CDisparity (int imHW, int imHH, int bins) {
    imgHistoWidth = imHW;
    imgHistoHeight = imHH;
    countBins = bins;
  }
  ~CDisparity () {};

public:

  void ReadFile (const char* fileName) {
    mDisp = cv::imread ( fileName, CV_LOAD_IMAGE_ANYDEPTH );
    return;
  }

  char* HistoWindowName () const {
    return (winHisto);
  } 

  void VisualizeDisparity () {
    applyColorMap (mDisp, mvizDisp, cv::COLORMAP_JET);
    cv::namedWindow ( winDisp, 0);
    imshow ( winDisp, mvizDisp );
    return;
  }

  void Histo () {
    // For laughs & giggles get the range
    cv::minMaxLoc (mDisp, &minDisp, &maxDisp);
    std::cout << " MinMax = (" << minDisp << ", " << maxDisp << ")" << std::endl;
    
    // Calculate the histogram for the disparity
    int dims = 1;
    int countImages = 1;
    cv::calcHist ( &mDisp, countImages, 0, cv::Mat(), mHisto, 1, &gcountBins, 0);
    
    // Create a matrix to hold and image of the histogram
    // Give it a grayish background ('124')
    imgHisto = cv::Mat::ones (imgHistoWidth, imgHistoHeight, CV_8U) * 124;

    // Normalize the histogram
    cv::normalize (mHisto, mHisto, 0, imgHisto.rows, cv::NORM_MINMAX, CV_32F);
    
    // Dram the histogram as rectangles on the histogram image
    int binW = cvRound ( (double)(imgHisto.cols)/ gcountBins );
    std::cout << " bin width = " << binW << " bins count ="  << gcountBins << " img cols = " << imgHisto.cols << std::endl;

    for ( int i = 0; i < gcountBins; i++ ) {
      cv::rectangle ( imgHisto, 
		      cv::Point (i*binW, imgHisto.rows),
		      cv::Point ((i+1)*binW, imgHisto.rows - cvRound (mHisto.at<float>(i))),
		      cv::Scalar::all(0), -1, 8, 0 );
    }
    cv::imshow ( winHisto, imgHisto);
    return;
  }
  
  void Threshold (const int type, const int pixelValue) {

    cv::Mat mClamped;
    int max_BINARY_value = 255;
    cv::threshold ( mDisp, mClamped, pixelValue , max_BINARY_value, type);

    cv::namedWindow ("Clamped", 0);
    cv::imshow ( "Clamped", mClamped );
    return;
  }

  // Note: static 'Cursor' will call 'ClassCursor'
  //
  static void Cursor (int Event, int x, int y, int flags, void *params);

  void ClassCursor (int Event, int x, int y, int flags, void *params) {
    
    if ( Event == cv::EVENT_RBUTTONUP ) {
      // From the 'x' value in the histogram image,
      // figure out the corresponding value of 'disparity'
      int disparity = (int)((x*255.0)/ghistoWidth);
      
      // Figure out the lower/upper limits of the corresponding bin
      double binW = (double)(imgHisto.cols)/gcountBins;
      int n = int(x/binW + 05);
      int nm1 = n-1;
      std::cout << "hx=" << x << " disp=" << disparity << "bin: " << nm1 << "/" << n << std::endl;

      Threshold (0, disparity );
    }
    
    /* THIS IS ON HOLD
       static cv::Point statLbDown (0,0);
       static cv::Point statLbUp (0,0);
       
       if ( Event == cv::EVENT_LBUTTONDOWN ) {
       std::cout << "lbd " << Event << std::endl;
       statLbDown = cv::Point (x,y);
       }
       
       if ( Event == cv::EVENT_LBUTTONUP ) {
       std::cout << "lbu " << Event << std::endl;
       statLbUp = cv::Point (x,y);
       
       std::cout << "Bin diff=" << statLbDown.x -statLbUp.x << std::endl;
       }
    */
    
  }

  void Mouse () {
    cv::setMouseCallback ( winHisto, Cursor );
    cv::waitKey();
  }
  
private:
  int imgHistoWidth;
  int imgHistoHeight;
  int countBins;

  double minDisp, maxDisp;

  cv::Mat mHisto;
  cv::Mat imgHisto;
  cv::Mat mDisp;
  cv::Mat imgDisparity;
  cv::Mat mvizDisp;
  static char* const winHisto;
  static char* const winDisp;
};

//--------------------------------------------------------------------------
// STATIC MEMBERS
char* const CDisparity::winHisto = "Histogram";
char* const CDisparity::winDisp = "Disparity";

void CDisparity::Cursor (int Event, int x, int y, int flags, void *params) {
  CDisparity* pcDisp = (CDisparity*) params;
  pcDisp->ClassCursor ( Event, x, y, flags, 0);
  return;
}
//
//--------------------------------------------------------------------------






void histo (cv::Mat mDisp, const int histoWidth, const int histoHeight) {
  // For laughs & giggles get the range
  double minVal, maxVal;
  cv::minMaxLoc (mDisp, &minVal, &maxVal);
  std::cout << " MinMax = (" << minVal << ", " << maxVal << ")" << std::endl;

  int countImages = 1;
  int dims = 1;

  cv::Mat matHisto;
  cv::calcHist ( &mDisp, countImages, 0, cv::Mat(), matHisto, 1, &gcountBins, 0);
  
  cv::Mat histImage = cv::Mat::ones (histoHeight, histoWidth, CV_8U)*255;
  cv::normalize (matHisto, matHisto, 0, histImage.rows, cv::NORM_MINMAX, CV_32F);
  
  histImage = cv::Scalar::all(255);
  int binW = cvRound ( (double)(histImage.cols)/ gcountBins );
  
  for ( int i = 0; i < gcountBins; i++ ) {
    cv::rectangle ( histImage, 
		    cv::Point (i*binW, histImage.rows),
		    cv::Point ((i+1)*binW, histImage.rows - cvRound (matHisto.at<float>(i))),
		    cv::Scalar::all(0), -1, 8, 0 );
  }
  cv::imshow ("Disparity Historgram", histImage);
  
  return;
}

int main (int argc, char* argv[]) {
  
  const char* fileName = "disparity.png"; // Default file name
  if ( argc == 2 ) {
    fileName = argv[1]; // User supplied file name
  }

  // Create a class for perform histogramming
  CDisparity cDisp (420, 320, 64);
  cDisp.ReadFile (fileName);
  cDisp.VisualizeDisparity ();
  cDisp.Histo ();
  
  // Set callback for mouse interaction
  cv::setMouseCallback ( cDisp.HistoWindowName (), cDisp.Cursor, &cDisp );

  // Now wait
  cv::waitKey();

  return (0);
}

