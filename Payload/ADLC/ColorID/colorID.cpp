#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

//returns RGB value
string colorID(Mat& im)
{
  vector <Mat> rgb;
  split(im,rgb);
  int histNum = 256;
  float range[] = {0,256};
  const float* histRange = {range};
  bool uniform = true; bool accumulate = false;
  Mat r_hist,g_hist,b_hist;
  calcHist( &rgb[0], 1, 0, Mat(), b_hist, 1, &histNum, &histRange, uniform, accumulate );
  calcHist( &rgb[1], 1, 0, Mat(), g_hist, 1, &histNum, &histRange, uniform, accumulate );
  calcHist( &rgb[2], 1, 0, Mat(), r_hist, 1, &histNum, &histRange, uniform, accumulate );

  int hist_w = 512; int hist_h = 400;
  int bin_w = cvRound( (double) hist_w/histNum );

  Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

  normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
//get the hightest
// double r,g,b;
for( int i = 1; i < histNum; i++ )
{
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
                     Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                     Scalar( 255, 0, 0), 2, 8, 0  );
    cout << cvRound(b_hist.at<float>(i-1))  <<"," << cvRound(b_hist.at<float>(i))  << " ";
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                     Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                     Scalar( 0, 255, 0), 2, 8, 0  );
                     cout << cvRound(b_hist.at<float>(i-1)) <<"," <<cvRound(b_hist.at<float>(i)) << " ";
    line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                     Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                     Scalar( 0, 0, 255), 2, 8, 0  );
                    cout << cvRound(b_hist.at<float>(i-1)) <<"," << cvRound(b_hist.at<float>(i)) << " ";
    cout << endl;
}

namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
imshow("calcHist Demo", histImage );

waitKey(0);

return 0;
}


int main()
{
  Mat im = imread("red.jpg");
  if(!im.data)
    return -1;
  cout << colorID(im) << endl;

  return 0;
}
