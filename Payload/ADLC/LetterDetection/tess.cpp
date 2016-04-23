#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main()
{
  int choice;
  //command passed into tesseract
  string command;
  //name of the image file
  string fileName;
  //name of the output file, do not need to input extension
  string outPutFile;\
  //result of classification 
  string result;

  cout << "is this a letter or word? \n enter 1 for letter  2 for word :";
  cin >> choice;
  cout << endl << "Enter a file name :";
  cin >> fileName;
  string image =  /* "/home/opera002/Desktop/" + */fileName ;
  cout << endl << "Enter the output file Name: ";
  cin >> outPutFile;
  if(choice == 1)
  {
  command = "tesseract " + image + " " + outPutFile  + " -psm 10" ;
  }
  else
  {
    command = "tesseract " + image + " " + outPutFile;
  }
  system(command.c_str());

  ifstream iFile;
  iFile.open((outPutFile + ".txt").c_str());
  if(!iFile.is_open())
  {
    return -1;
  }

  iFile >> result;
  iFile.close();
  cout << "the result is " << result << endl;





return 0;
}
