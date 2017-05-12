#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>
#include <string>
#include <assert.h>

using namespace std;
using namespace cv::ml;
using namespace cv;

string colorClassify(float r, float g, float b){
  if(r > 230 && g > 230 && b > 230){
     return  "white";
   }
   else if (r < 30 && g < 30 && b < 30){
     return "black";
   }
   else if( ( r <= 255 && r > 191) && ( g < 229 && g > 55 ) && ( b >= 0 && b < 215 )){
      return "orange";
   }

   else if ((r <= 255 && r > 171 ) && (g <=255 && g > 175 ) && (b >= 5 && b < 90 ) )
   {
    return "yellow";
   }

   else if((r <=255 && r > 134) && (g < 55 && g >=0 ) && (b >=0  && b < 47)){
     return "red";
   }

   else if(( r >= 0 && r < 30 ) && (g < 120 && g > 30 ) && ( b <=255 && b > 171 ) ){
     return "blue";
   }

   else if(( r > 30 && r < 80 ) && (g > 74 && g <= 255 ) && ( b >= 0 && b < 50  ) ){
     return "green";
   }

   else if((r > 110 && r < 234 )&& ( g > 10 && g < 230 ) && (b > 100 && b <=255 )){
     return "purple";
   }
   return "NaN";
 }

string colorID(Mat src) {

  GaussianBlur(src,src,Size(7,7), .1,.1);

  //imshow("blur", src);
  //waitKey(0);

  Mat samples(src.rows * src.cols, 3, CV_32F);
 for( int y = 0; y < src.rows; y++ )
   for( int x = 0; x < src.cols; x++ )
     for( int z = 0; z < 3; z++)
       samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];


 int clusterCount = 2;
 Mat labels;
 int attempts = 2;
 Mat centers;//holds colors for each cluster
 kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers );

 //cout << "centers:"<<endl << centers << endl << endl;
 Mat new_image( src.size(), src.type() );
 // Mat new_image;
 // src.copyTo(new_image);
 for( int y = 0; y < src.rows; y++ )
   for( int x = 0; x < src.cols; x++ )
   {
     int cluster_idx = labels.at<int>(y + x*src.rows,0);
     new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
     new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
     new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
   }

 //imshow( "clustered image", new_image );



 Mat matTrainFeatures(2,src.rows * src.cols,CV_32F);


 Mat matTrainLabels(1,labels.rows,CV_32S);


 Mat matResults;

 //etcetera code for loading data into Mat variables suppressed
 for(int y = 0; y < new_image.rows * new_image.cols;y++)
 {
  matTrainFeatures.at<float>(1,y)= y%new_image.rows;

 }

 for(int x = 0; x <  new_image.rows * new_image.cols;x++)
 {

  matTrainFeatures.at<float>(0,x)= x%new_image.cols;
 }

 for(int i =0; i < labels.rows; i++)
 {

   matTrainLabels.at<int>(0,i) =labels.at<int>(0,i);
 }
//cout << "here" << endl;

 Ptr<TrainData> trainingData;
 Ptr<KNearest> kclassifier=KNearest::create();

 trainingData=TrainData::create(matTrainFeatures,
                         SampleTypes::COL_SAMPLE,matTrainLabels);
//cout << "here1" << endl;


 kclassifier->setIsClassifier(true);
 kclassifier->setAlgorithmType(KNearest::Types::BRUTE_FORCE);
 kclassifier->setDefaultK(9);
 Mat matSample(1,2,CV_32F);
 matSample.at<float>(0,0) = src.rows/2;
 matSample.at<float>(0,1) = src.cols/2;
 //matSample.at<float>(1,0) = 1;
 //matSample.at<float>(1,1) = 1;

 kclassifier->train(trainingData);
 float value = kclassifier->findNearest(matSample,kclassifier->getDefaultK(),matResults);
 //cout << matResults << endl;

 Vec3b color;
 color[0] = centers.at<float>(value,0);
 color[1] = centers.at<float>(value,1);
 color[2] = centers.at<float>(value,2);

 float r = (float)color[2];
 float g = (float)color[1];
 float b = (float)color[0];

 string classified  = colorClassify(r,g,b);
 return classified;
}
int main(int argc, char**argv) {
    assert(argc > 1);

    string input(argv[1]);
    Mat im = imread(input);
    resize(im,im,Size(800,600));
    if(!im.data)
        return -1;
    cout << colorID(im) << endl;
    //waitKey(0);

    return 0;
}
