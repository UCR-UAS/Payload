#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <string>
#include <assert.h>

using namespace std;
using namespace cv::ml;
using namespace cv;

/*
string colorID(Mat& inputImage) {

    vector<Mat> rgb;
    split(inputImage, rgb); //Splits Mat into r g b mats
    int histNum = 256;
    float range[] = {0, 256};
    const float *histRange = {range};
    bool uniform = true;
    bool accumulate = false;
    Mat r_hist, g_hist, b_hist; //Instances of r g b histograms

    //Populating r g b histograms
    calcHist( &rgb[0], 1, 0, Mat(), b_hist, 1, &histNum, &histRange, uniform, accumulate );
    calcHist( &rgb[1], 1, 0, Mat(), g_hist, 1, &histNum, &histRange, uniform, accumulate );
    calcHist( &rgb[2], 1, 0, Mat(), r_hist, 1, &histNum, &histRange, uniform, accumulate );

    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histNum );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0) );

    //Normalize the r g b mats
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for(int i=1; i<histNum; i++) {

        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
                         Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                         Scalar( 255, 0, 0 ), 2, 8, 0);

        cout << cvRound(b_hist.at<float>(i-1)) << "," << cvRound(b_hist.at<float>(i)) << " ";

        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
                         Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                         Scalar( 0, 0, 255 ), 2, 8, 0);

        cout << cvRound(b_hist.at<float>(i-1)) << "," << cvRound(b_hist.at<float>(i)) << " ";

        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
                         Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                         Scalar( 255, 0, 0 ), 2, 8, 0);

        cout << cvRound(b_hist.at<float>(i-1)) << "," << cvRound(b_hist.at<float>(i)) << " ";
        cout << endl;
    }

    namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
    imshow("calcHist Demo", histImage);

    waitKey(0);
}
*/

string colorID(Mat src) {

  Mat samples(src.rows * src.cols, 3, CV_32F);
 for( int y = 0; y < src.rows; y++ )
   for( int x = 0; x < src.cols; x++ )
     for( int z = 0; z < 3; z++)
       samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];


 int clusterCount = 8;
 Mat labels;
 int attempts = 5;
 Mat centers;//holds colors for each cluster
 kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers );


 Mat new_image( src.size(), src.type() );
 // Mat new_image;
 // src.copyTo(new_image);
 for( int y = 0; y < src.rows; y++ )
   for( int x = 0; x < src.cols; x++ )
   {
     int cluster_idx = labels.at<int>(y + x*src.rows,0); // labels are stored in a 1d array and represents a 2d array
    //  cout << "y:" << y << " x: " << x << " x* scr.rows" << x*src.rows << endl;
     new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
     new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
     new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
   }

 imshow( "clustered image", new_image );
 // imshow("orignal",centers );
 // cout << "centers" << centers << endl;


 Mat matTrainFeatures(2,src.rows * src.cols,CV_32F);
 // x,y 2 coordinates and src.rows * scr.cols number of pixels
 // Mat matSample(0,number_of_sample_elements,CV_32F);

 Mat matTrainLabels(1,labels.rows,CV_32S);
 // Mat matSampleLabels(0,number_of_sample_elements,CV_32F);

 Mat matResults;

 //etcetera code for loading data into Mat variables suppressed
 for(int y = 0; y < new_image.rows * new_image.cols;y++)
 {
  matTrainFeatures.at<float>(1,y)= y%new_image.rows;
  // cout << "y:"<<y << endl;
 }

 for(int x = 0; x <  new_image.rows * new_image.cols;x++)
 {
  //  cout << "x: " << x << endl;
  matTrainFeatures.at<float>(0,x)= x%new_image.cols;
 }
 // cout << "trainlabel rows" << matTrainLabels.rows << "cols" << matTrainLabels.cols << endl;
 // cout << "label rows" << labels.rows << "cols" << labels.cols << endl;
 // cout << matTrainLabels <<endl;
 for(int i =0; i < labels.rows; i++)
 {
  //  cout <<"i" <<i <<endl;
  // cout <<"labels[0] = "<<labels.at<int>(i,0) << endl;
   matTrainLabels.at<int>(0,i) =labels.at<int>(0,i);
 }
cout << "here" << endl;
// cout << matTrainFeatures << endl;
 Ptr<TrainData> trainingData;
 Ptr<KNearest> kclassifier=KNearest::create();

 trainingData=TrainData::create(matTrainFeatures,
                         SampleTypes::COL_SAMPLE,matTrainLabels);
cout << "here1" << endl;


 kclassifier->setIsClassifier(true);
 kclassifier->setAlgorithmType(KNearest::Types::BRUTE_FORCE);
 kclassifier->setDefaultK(9);
 Mat matSample(2,2,CV_32F);
 matSample.at<float>(0,0) = 1;
 matSample.at<float>(0,1) = 1;
 matSample.at<float>(1,0) = src.rows/2;
 matSample.at<float>(1,1) = src.cols/2;
 // cout << "Responses" << endl;
 // cout << trainingData->getTrainResponses() << endl;
 // cout << trainingData << endl
 kclassifier->train(trainingData);
 kclassifier->findNearest(matSample,kclassifier->getDefaultK(),matResults);
 // cout <<centers.at<float>(matResults.at<int>(0),0)<<endl;
 // cout <<centers.at<float>(matResults.at<int>(0),1)<<endl;
 // cout <<centers.at<float>(matResults.at<int>(0),2)<<endl;
 //
 // cout <<centers.at<float>(matResults.at<int>(1),0)<<endl;
 // cout <<centers.at<float>(matResults.at<int>(1),1)<<endl;
 // cout <<centers.at<float>(matResults.at<int>(1),2)<<endl;
 //Just checking the settings
// cout<<"Training data: "<<endl
//     <<"getNSamples\t"<<trainingData->getNSamples()<<endl
//     <<"getSamples\n"<<trainingData->getSamples()<<endl
//     <<endl;
//
// cout<<"Classifier :"<<endl
//     <<"kclassifier->getDefaultK(): "<<kclassifier->getDefaultK()<<endl
//     <<"kclassifier->getIsClassifier()   : "<<kclassifier->getIsClassifier()<<endl
//     <<"kclassifier->getAlgorithmType(): "<<kclassifier->getAlgorithmType()<<endl
//     <<endl;
//
// //confirming sample order
// cout<<"matSample: "<<endl
//     <<matSample<<endl
//     <<endl;

//displaying the results
cout<<"matResults: "<<endl
    <<matResults<<endl
    <<endl;
 // cout << (int)(src.at<Vec3b>(1,1)[0]) << endl;
 // cout << (int)(src.at<Vec3b>(1,1)[1]) << endl;
 // cout << (int)(src.at<Vec3b>(1,1)[2]) << endl;
 // cout << (int)(src.at<Vec3b>(src.rows/2,src.cols/2)[0]) << endl;
 // cout << (int)(src.at<Vec3b>(src.rows/2,src.cols/2)[1]) << endl;
 // cout << (int)(src.at<Vec3b>(src.rows/2,src.cols/2)[2]) << endl;

 // Mat dst;
 // addWeighted( src, .5, new_image, .5, 0.0, dst);
 // imshow("overlay",dst);

 // imshow("Labels",labels);
 waitKey( 0 );
  //   const int MAX_CLUSTERS = 5;
	// 	Mat grey;
	// 	cvtColor(img,grey,CV_BGR2GRAY);
  //   Scalar colorTab[] = {
  //       Scalar(0, 0, 255),          //Red #FF0000
  //       Scalar(0, 255, 0),
	// 	Scalar(255,0,0),				//Green #00FF00
  //       Scalar(255, 100, 100),      //Lime #64FF00
  //       Scalar(255, 0, 255),        //Pink? #FF00FF I have a history of color blindness. Please don't hurt me.
  //       Scalar(0, 255, 255)         //Yellow #FFFF00
  //   };
	// string colors[] ={
	// "red",
	// "green",
	// "blie",
	// "lime",
	// "magenta",
	// "yellow"
  //
	// };
  //   RNG rng(12345);
  //
  //
  //       int k, clusterCount = rng.uniform(2, MAX_CLUSTERS+1);
  //       int i, sampleCount = rng.uniform(1, 10000);
  //       Mat points(sampleCount, 1, CV_32FC2), labels;
  //
  //       clusterCount = MIN(clusterCount, sampleCount);
  //       Mat centers;
  //
  //       // Generate random sample from multigaussian distribution
  //       for( k=0; k<clusterCount; k++ ) {
  //           Point center;
  //           center.x = rng.uniform(0, img.cols);
  //           center.y = rng.uniform(0, img.rows);
  //           Mat pointChunk = points.rowRange(k*sampleCount/clusterCount,
  //                                            k == clusterCount-1 ? sampleCount :
  //                                            (k+1)*sampleCount/clusterCount);
  //           rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
  //       }
  //
  //       randShuffle(points, 1, &rng);

  //
  //       img = Scalar::all(0);
  //       for( i=0; i<sampleCount; i++ ) {
  //           int clusterIdx = labels.at<int>(i);
  //           Point ipt = points.at<Point2f>(i);
  //           circle( grey, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA );
  //       }
  //
  //       imshow("clusters", grey);
  //
  //       char key = (char)waitKey();
  //       // if( key == 27 || key == 'q' || key == 'Q' ) // ESC
  //       //     break;

return " ";
}


int main(int argc, char**argv) {
    assert(argc > 1);

    string input(argv[1]);
    Mat im = imread(input);
    resize(im,im,Size(800,600));
    if(!im.data)
        return -1;
    cout << colorID(im) << endl;

    return 0;
}
