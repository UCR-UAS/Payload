#include <iostream>
#include <fstream>
#include "Json.h"
#include <sstream>
using namespace std;

void Json::createJson(){

ofstream json;
stringstream c;
c << number;
string n = c.str();
json.open(n.c_str());
json << "{"<< endl;
json << "    \"type\": \"" << type << "\", " << endl;
json << "    \"latitude\": \"" << lat << "\", " << endl;
json << "    \"longitude\": \"" << lng << "\", " << endl;
json << "    \"orientation\": \"" << angle  << "\", " << endl;
json << "    \"shape\": \"" << shape  << "\", " << endl;
json << "    \"background_color\": \"" << bck_color << "\", " << endl;
json << "    \"alphanumeric\": \"" << let << "\", " << endl;
json << "    \"alphanumeric_color\": \"" << color << "\", " << endl;
json << "}";
json.close();
return; 
}


bool Json::operator==(const Json& b) const {
	return (number == b.number && type == b.type && lat == b.lat && lng == b.lng && 
		angle == b.angle && shape == b.shape && bck_color == b.bck_color && let == b.let && color == b.color); 
}
