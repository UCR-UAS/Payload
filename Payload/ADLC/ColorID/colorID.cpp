#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

//returns RGB value
string HistorgramID(Mat& im)
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

void colorID( Mat &rgb ) {
    Mat channel[3];
	split(rgb, channel);

	//channel[0] = blue
	//channel[1] = green
	//channel[2] = red
	Scalar entireMat = mean(rgb);

	int B = entireMat[0];
	int G = entireMat[1];
	int R = entireMat[2];

    cout << R << " " << G << " " << B  << endl;

    for(;;) {
		//testing red
		if( (R>=100 && R<=255) && (G<30) && (B<30) ) {
		    cout << "Red" << endl;
            break;
		}

		//testing orange
		if( (R>=230 && R<=255) && (G>=83 && G<=129) && (B<=20) ) {
		    cout << "Orange" << endl;
            break;
		}

		//testing yellow
		if( (R>=200 && R<=255) && (G>=200 && G<=255) && (B>=0 && B<=125) ) {
		    cout << "Yellow" << endl;
            break;
		}

        //testing gray
        if( (R>=90 && R<=150) && (G>=90 && G<=150) && (B>=90 && G<=150) ) {
            cout << "Gray" << endl;
            break;
        }

		//testing green
		if( (R>=0 && R<=205) && (G>=100 && G<=255) && (B>=0 && B<=150) ) {
		    cout << "Green" << endl;
            break;
		}

		//testing light blue
		if( (R>=0 && R<=150) && (G>=150 && G<=255) && (B>=150 && B<=255) ) {
		    cout << "Light Blue" << endl;
            break;
		}

		//testing violet
		if( (R>=70 && R<=180) && (G>=0 && G<=100) && (B>=100 && B<=255) ) {
		    cout << "Violet" << endl;
            break;
		}

		//testing blue
		if( (R>=0 && R<=100) && (G>=0 && G<=180) && (B>=100 && B<=255) ) {
		    cout << "Blue" << endl;
            break;
		}

        //testing black
        if( (R>=0 && R<=60) && (G>=0 && G<=60) && (B>=0 && B<=60) ) {
            cout << "Black" << endl;
            break;
        }

        if( (R>=190 && R<=255) && (G>=190 && G<=255) && (B>=190 && B<=255) ) {
            cout << "White" << endl;
            break;
        }
    }
}

int main(int argc, char**argv)  {

	Mat RED  = imread("RED.png");
    Mat ORANGE = imread("ORANGE.jpg");
    Mat YELLOW = imread("YELLOW.png");
    Mat GREEN = imread("GREEN.jpg");
    Mat LIGHT_BLUE = imread("LIGHTBLUE.jpg");
    Mat BLUE = imread("BLUE.jpg");
    Mat VIOLET = imread("VIOLET.png");
    Mat BLACK = imread("BLACK.jpg");
    Mat GRAY = imread("GRAY.jpg");
    Mat WHITE = imread("WHITE.png");

	if(!RED.data)
	return -1;
	//cout << colorID(im) << endl;

    cout << "---------------Testing RED---------------" << endl;
    colorID(RED);
    cout << endl;

    cout << "---------------Testing ORANGE---------------" << endl;
    colorID(ORANGE);
    cout << endl;

    cout << "---------------Testing YELLOW---------------" << endl;
    colorID(YELLOW);
    cout << endl;

    cout << "---------------Testing GREEN---------------" << endl;
    colorID(GREEN);
    cout << endl;

    cout << "---------------Testing LIGHTBLUE---------------" << endl;
    colorID(LIGHT_BLUE);
    cout << endl;

    cout << "---------------Testing BLUE---------------" << endl;
    colorID(BLUE);
    cout << endl;

    cout << "---------------Testing VIOLET---------------" << endl;
    colorID(VIOLET);
    cout << endl;

    cout << "---------------Testing BLACK---------------" << endl;
    colorID(BLACK);
    cout << endl;

    cout << "---------------Testing GRAY---------------" << endl;
    colorID(GRAY);
    cout << endl;

    cout << "---------------Testing WHITE---------------" << endl;
    colorID(WHITE);
    cout << endl;



    return 0;
}
