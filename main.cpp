
#include "common.h"
#include "Device.h"
#include "userFunc.h"

int main() {

	clock_t starttime = clock();

	string filename = "content.json";
	UserJson dataIn = loadUserJson(filename);
	Device device(dataIn);
	TMM(device);

	clock_t endtime = clock();
	cout << "Time consuming: " << double(endtime - starttime) / CLOCKS_PER_SEC ;
	cout << "s" << endl;

	return 0;
}