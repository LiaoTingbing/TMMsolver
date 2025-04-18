
#include "common.h"
#include "Device.h"
#include "userFunc.h"

int main() {

	clock_t starttime = clock();

	string filename = "Input/content.json";
	UserJson dataIn = loadUserJson(filename);
	Device device(dataIn);

	//device.TMM(15, 20e-6);
	//device.TMM(30, 1.5e-6);
	device.TMMsweep();

	clock_t endtime = clock();
	cout << "Time consuming: " << double(endtime - starttime) / CLOCKS_PER_SEC ;
	cout << "s" << endl;

	return 0;
}