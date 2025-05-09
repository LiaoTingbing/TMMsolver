 
#include "../include/TMMsolve.h"
#include "../include/userfunc.h"
 

int main() {
 
 

	auto starttime = clock();

	string filename = "E:/VisualStudioFiles/TMM/examples1/content.json";
	UserJson dataIn = loadUserJson(filename);
	TMMsoler device(dataIn);

	//device.TMM(15, 20e-6);
	//device.TMM(30, 1.5e-6);
	device.TMMsweep();

	auto endtime = clock();
	cout << "Time consuming: " << double(endtime - starttime) / CLOCKS_PER_SEC ;
	cout << "s" << endl;

	

	return 0;
}