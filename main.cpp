
#include "common.h"
#include "Device.h"
#include "userFunc.h"

int main() {

	string filename = "content.json";
	UserJson dataIn = loadUserJson(filename);
	Device device(dataIn);
	TMM(device);

	return 0;
}