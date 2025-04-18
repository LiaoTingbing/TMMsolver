#pragma once


//#include "common.h"
#include "Device.h"

rowvec vectornorm(cx_mat& X);

 

void SconnectRight(Smatrix& G, Smatrix& S);

UserJson loadUserJson(string filename);