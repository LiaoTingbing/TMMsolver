#pragma once


//#include "common.h"
#include "TMMsolve.h"

//	计算每一列的norm2
//rowvec vectornorm(cx_mat& X);

//	计算链接散射矩阵 G=G*S
void SconnectRight(Smatrix& G, Smatrix& S);

//	加载器件数据json函数
UserJson loadUserJson(string filename);