#ifndef JSON_H
#define JSON_H
#include <string>
using namespace std;
struct Json{
int number;
string type;
float lat;
float lng;
int angle;
string shape;
string bck_color;
char let;
string color;

void createJson();
bool operator==(const Json& b) const;

};

#endif
