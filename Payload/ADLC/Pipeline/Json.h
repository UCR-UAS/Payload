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
bool operator==(const Json& b) const{
  return ( type == b.type && lat == b.lat && lng == b.lng &&
           angle == b.angle && shape == b.shape && bck_color == b.bck_color
           && let == b.let && color == b.color);
}
Json & operator=(const Json&b);
};

#endif
