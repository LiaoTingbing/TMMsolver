#pragma once


//#include "common.h"
#include "Device.h"

rowvec vectornorm(cx_mat& X);
void TMM(Device& device);
Smatrix SconnectRight(Smatrix& G, Smatrix& S);