#include <iostream> 
#include <stdlib.h>
#include "Network.h"

using namespace std;

int main( int argc, char *argv[])
{
	if(argc != 4)
	{
		cout << "Error: Use ./main [hostname] [port] [isServer]" << endl;
		return 1;
	}

	bool s = false;
	if(string(argv[3]) == "1")
		s=true;

	cout << "Port string: " << argv[2] << endl;
	cout << "Port int: " << atoi(argv[2]) << endl;

	Network n = Network(argv[1], atoi(argv[2]), s);
	return 0;
}