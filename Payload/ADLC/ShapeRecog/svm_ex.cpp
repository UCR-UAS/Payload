#include<opencv2/opencv.hpp>
#include<opencv2/ml.hpp>
#include<iostream>
#include<utility>
#include<string>

using namespace std;
using namespace cv;

//Here we should probably return just the contour image
vector<uchar> preproccess(Mat img)
{
  int r = 200 / img.cols;
  Size dim = Size(200,(int)img.rows*r);

  Mat resized;
  resize(img,resized,dim,0,0,INTER_AREA);
  float ratio = img.rows / (float)resized.rows;
  Mat gray;
  cvtColor(resized,gray,COLOR_RGB2GRAY);
  GaussianBlur(gray,gray,Size(5,5),.2,.2);

  Mat thresh;
  threshold(gray,thresh,230,255,THRESH_BINARY);

  vector< vector <Point> > c;
  findContours(thresh,c,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_TC89_KCOS );
  //sd.detect(c,gray);
  drawContours(thresh,c,-1,(255,255,255),2);
  std::vector<uchar> array;
  if (thresh.isContinuous()) {
    array.assign(thresh.datastart, thresh.dataend);
  } else {
    for (int i = 0; i < thresh.rows; ++i) {
      array.insert(array.end(),thresh.ptr<uchar>(i), thresh.ptr<uchar>(i)+thresh.cols);
    }
    return array;
}
}

int main(int argc, char** argv)
{
  // data directory
  string training_path = "./Testing/results/";
  vector<vector<uchar>>training_data;
  vector<int> training_labels;

  //load images from directories and append with label
  cv::String circle_p = training_path+"Circle/*.jpg";
  cv::String Scircle_p = training_path+"Semicircle/*.jpg";
  cv::String Qcircle_p = training_path+"QuarterCircle/*.jpg";
  cv::String Diamond_p = training_path+"Diamond/*.jpg";
  cv::String Plus_p = training_path+"Plus/*.jpg";
  cv::String Rectangle_p = training_path+"Rectangle/*.jpg";
  cv::String Square_p = training_path+"Square/*.jpg";
  cv::String Star_p = training_path+"Star/*.jpg";
  cv::String Trapezoid_p = training_path+"Trapezoid/*.jpg";
  cv::String Triangle_p = training_path+"Triangle/*.jpg";
  vector<cv::String> fn;
  cv::glob(circle_p,fn,true); // recurse
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(0);
    }
  cv::glob(Scircle_p,fn,true); // recurse
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(1);
    }
  cv::glob(Qcircle_p,fn,true); // recurse
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(2);
    }

  cv::glob(Qcircle_p,fn,true); // recurse
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(2);
    }
  cv::glob(Diamond_p,fn,true); // recurse
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(3);
    }
  cv::glob(Plus_p,fn,true); // recurse
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(4);
    }
  cv::glob(Rectangle_p,fn,true); // recurse
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(5);
    }
  cv::glob(Square_p,fn,true); 
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(6);
    }
  cv::glob(Star_p,fn,true);
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(7);
    }
  cv::glob(Trapezoid_p,fn,true);
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(8);
    }
  cv::glob(Triangle_p,fn,true);
  for (size_t k=0; k<fn.size(); ++k)
    {
      cv::Mat im = cv::imread(fn[k]);
      if (im.empty()) continue; //only proceed if sucsessful
      // you probably want to do some preprocessing
      vector<uchar> d = preproccess(im);
      training_data.push_back(d);
      training_labels.push_back(9);
    }
  int height = training_data.size();
  std::vector<uchar> vectorData = training_data[0];
  int width = vectorData.size();

  cv::Mat* mat = new Mat(height,width, CV_32F);
  for(int i = 0; i < height; ++i)
    {
      for(int j = 0; j < width; ++j)
        {
          mat->at<float>(i,j) = training_data[i][j];
        }
      }

  height = training_labels.size();
  Mat responses(height,1,CV_32S);

  for(unsigned i = 0; i < height; i++)
    {
      responses.at<int>(i,0) = training_labels.at(i);
      }
  vector<vector<uchar>>(training_data).swap(training_data);

  cout << responses.cols <<"," << responses.rows << endl;
  cout << mat->cols <<"," << mat->rows << endl;
  Ptr<cv::ml::TrainData> td = cv::ml::TrainData::create(*mat,0,responses);
  td->setTrainTestSplitRatio(.75);

  Ptr<cv::ml::SVM> svm_classifier = cv::ml::SVM::create();
  svm_classifier->setType(ml::SVM::C_SVC);
  svm_classifier->setKernel(ml::SVM::RBF);
  svm_classifier->setGamma(3);
  svm_classifier->trainAuto(td);

  string s = "./circle1.jpg";
  cv::Mat testimg = cv::imread(s);
  vector<uchar> imgp = preproccess(testimg);

  Mat newImg(1,imgp.size(),CV_32F);
  for(unsigned i = 0; i < imgp.size(); i++)
  {
    newImg.at<float>(0,i) = imgp.at(i);
  }

  // Train the SVM
  float result = svm_classifier->predict(newImg);
  cout <<"Predicted class is "<< result << endl;
  svm_classifier->save("svm.xml");
  return 0;
}
