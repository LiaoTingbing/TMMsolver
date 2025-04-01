

#include "common.h"
#include <armadillo>
#include "Device.h"
#include "userFunc.h"


Layer example[] {
	{1e-6 , 2 , 0.1 },
	{1e-6 , 3 , 0 }
}; 

Source source {30 , 1.55e-6};


int main() {

	Device device(example ,2, source);
	
	TMM(device);

	return 0;
}