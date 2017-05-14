#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


// Mat regionGrowing(Mat I, Point seed, double reg_maxdist)
// {
//   Mat J;
//   resize()
// }


//returns true if black
bool blackWhite(Mat chans[3], int y, int x)
{

	if (chans[0].at<unsigned char>(y, x) < 20 || chans[0].at<unsigned char>(y, x) > 120)
	{
		//25 seems to be the best choice
		//However 100 isolates just the letter 
		if (chans[1].at<unsigned char>(y, x)<22.5)
		{
			return true;
		}
		else
		{
			if (chans[2].at<unsigned char>(y, x) < 10 || chans[2].at<unsigned char>(y, x) > 255)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return true;
	}

}



//returns number of white pixels of a binary image
int numPixels(Mat& I)
{
	int num = 0;
	for (int i = 0; i < I.size().height; ++i)
	{
		for (int j = 0; j < I.size().width; ++j)
		{
			if (I.at<unsigned char>(i, j) == 255)
				num++;

		}
	}
	return num;
}

//returns segmented image
Mat sailencySegmentation(Mat& I)
{
	double t;

	t = (double)getTickCount();

	imshow("I", I);

	Mat hsvI;
	//Convert the color of the image to HSV
	cvtColor(I, hsvI, CV_RGB2HSV, 0);
	Mat chans[3];

	// may not actually be seperated as hsv order
	split(hsvI, chans);
	// imshow("hue",chans[0]);
	Mat filtered;

	medianBlur(chans[0], filtered, 7);//filters a single channel
	filtered.copyTo(chans[0]);
	merge(chans, 3, hsvI);//merges back into hsvI


	Mat norm_hsv;
	hsvI.convertTo(norm_hsv, CV_8UC3);//should probably check if this actually normalized the mat
									  // double min, max;
									  // cv::minMaxLoc(norm_hsv, &min, &max);
									  // cout << min << " " << max<<endl;
									  //to deterimine if normalized. nothing should be above 255



	split(norm_hsv, chans);
	//check each value of the split array than edit accordingly
	//turn norm_hsv to black or white

	//converts image to black and white based on criteria in blackWhite(Mat,int i,int j)
	for (int i = 0; i < chans[0].size().height; ++i)
	{
		for (int j = 0; j < chans[0].size().width; ++j)
		{
			// cout<<"i:"<<i <<",j:"<<j<<":";
			if (blackWhite(chans, i, j))
				// if(true)
			{
				chans[0].at<unsigned char>(i, j) = 0;
				// cout<<(int)chans[0].at<unsigned char>(i,j)<<endl;
			}
			else
			{
				chans[0].at<unsigned char>(i, j) = 255;
				// cout<<(int)chans[0].at<unsigned char>(i,j)<<endl;
			}
		}
	}
	// imshow("Binary",chans[0]);

	int numOfWhite = 256;
	vector<cv::Point> seeds;
	int num_w = cvFloor(((double)chans[0].rows) / 16);
	int num_h = cvFloor(((double)chans[0].cols) / 16);
	/*std::cout << "numW: " << num_w << endl;
	std::cout << "numH: " << num_h << endl;*/
	for (int i = 0; i < num_w; ++i)
	{
		for (int j = 0; j < num_h; ++j)
		{
			if (i == 0 && j == 0)
			{
				Mat small_J = chans[0](Rect(0, 0, 16, 16));
				int num_Pixels = numPixels(small_J);
				if (num_Pixels >= numOfWhite)
				{
					seeds.push_back(Point(8, 8));

				}
			}

			else if (j == 0 && ((i) * 16) < chans[0].rows)
			{
				Mat small_J = chans[0](Rect(0, ((i) * 16), 16, 16));
				int num_Pixels = numPixels(small_J);

				if (num_Pixels >= numOfWhite)
				{
					seeds.push_back(Point(16 * (i), 8));

				}
			}

			else if (i == 0 && (((j) * 16)) < chans[0].cols)
			{
				Mat small_J = chans[0](Rect(((j) * 16), 0, 16, 16));
				int num_Pixels = numPixels(small_J);

				if (num_Pixels >= numOfWhite)
				{
					seeds.push_back(Point(8, 16 * (j)));
				}
			}

			else if (((j) * 16) < chans[0].cols && ((i) * 16)< chans[0].rows)
			{
				//neeed to adjust the numbers of offset
				Mat small_J = chans[0](Rect(((j) * 16), ((i) * 16), 16, 16));
				int num_Pixels = numPixels(small_J);
				if (num_Pixels >= numOfWhite)
				{

					seeds.push_back(Point((16 * (j)), (16 * (i))));
				}
			}

		}
	}

	//draw seed points

	// for(int i =0; i < seeds.size();++i)
	// {
	//   // cout << "drawing point " << i << endl;
	//   circle(chans[0],seeds.at(i),1,Scalar(155,55,5),1,8,0);
	// }
	// imwrite("pointsonbinary.jpg",chans[0]);
	// find contours
	vector< vector<cv::Point> > contours;

	//CV_RETR_EXTERNAL removes the letter on the target.
	findContours(chans[0], contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	//find contour area
	vector<double> conAreas(contours.size());
	
	for (unsigned i = 0; i < contours.size(); ++i)
	{
		conAreas.at(i) = contourArea(contours.at(i));
	}
	//
	// //REMOVING CONTOURS WITH SIZE LESS THAN 60
	vector< vector<cv::Point> > useablecons;
	for (unsigned i = 0; i < conAreas.size(); ++i)
	{
		if (conAreas.at(i) >= 2*numOfWhite)//will need to adjust
		{
			useablecons.push_back(contours.at(i));

		}
	}

	//cout << "USable cons size: " << useablecons.size() << endl;
	
	Mat cons = Mat::zeros(chans[0].rows, chans[0].cols, CV_8UC3);
	Scalar white(255, 255, 255);
	Scalar green(0, 255, 0); //BGR

	vector<vector<Point> >hull(useablecons.size());
	for (unsigned i = 0; i < useablecons.size(); i++)
	{
		convexHull(Mat(useablecons[i]), hull[i], false);
	}


	//cout << "Before contours" << endl;
	drawContours(cons, useablecons, -1, white, 1, LINE_8, noArray());
	//cout << "After contours" << endl;

	//cout << "Seeds:" << seeds.size() << endl;
	//cout << "Hull: " << hull.size() << endl;
	//cout << "Cons:" << cons.size() << endl;

	// //finding centroids
	// vector< cv::Point > cntroids;
	// for(int i =0; i < seeds.size(); ++i)
	// {
	// Rect bRect = boundingRect(seeds.at(i));
	//
	// int x = bRect.x + (bRect.width / 2);
	// int y = bRect.y + (bRect.height / 2);
	// cntroids.push_back(Point(x,y));
	// }

	// flood fill
	//Rect ccomp;
	//int ffillMode = 1;
	//int loDiff = 0, upDiff = 0;
	//int lo = ffillMode == 0 ? 0 : loDiff;
	//int up = ffillMode == 0 ? 0 : upDiff;
	////cout << "Before contours again" << endl;
	//
	////TODO: Change to Hull points, instead of seed points? Seed points dont seem to work
	//for (unsigned i = 0; i < seeds.size(); ++i)
	//{
	//	// cout <<"FIlling "<<((double)i )/ seeds.size()<<endl;
	//	// cout <<lo <<","<<up<<endl;
	//	//cout << seeds[i].x << ","<<seeds[i].y<<endl;
	//	//cout << cons.at<unsigned char>(seeds[i].x, seeds[i].y) << " these points" << endl;
	//	
	//	if (cons.at<unsigned char>(seeds[i].x, seeds[i].y) > 0 && seeds[i].x >= 0 && seeds[i].x < cons.cols && seeds[i].y >= 0 && seeds[i].x < cons.rows)
	//	{
	//		cout << "in" << endl;
	//		floodFill(cons, seeds.at(i), white, &ccomp, Scalar(lo, lo, lo),
	//			Scalar(up, up, up), 4);
	//	}
	//	// floodFill(cons, seeds.at(i), white, &ccomp, Scalar(lo, lo, lo),
	//	//           Scalar(up, up, up), 4);
	//}

	drawContours(cons, hull, -1, green, 0.001, LINE_8, noArray());
	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();

	//cout << "After contours again" << endl;

	cout << "Time of segmenting image " << t << " milliseconds." << endl;

	//cout << "end" << endl;

	imwrite("cons.jpg", cons);
	//imshow("cons",cons);
	waitKey(0);

	// using split and merge you can filter a single channel atnd merge them
	return cons;

}

int main() {
	cout << "Please Enter FileName" << endl;
	string f;
	cin >> f;
	Mat I;

	I = imread(f, 1);
	if (!I.data)
	{
		cout << "Could not load image" << endl;
		waitKey(0);
		return -1;
	}

	Size size(800, 600);//the dst image size,e.g.100x100
	Mat dst;//dst image
			//Mat src;//src image
	resize(I, dst, size);//resize image

	//imshow("Original",dst);
	sailencySegmentation(dst);
	waitKey(0);
	return 0;
}
