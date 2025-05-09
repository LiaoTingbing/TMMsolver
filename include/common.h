#pragma once

#include <armadillo>
#include <fstream>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ctime>

using namespace std;
using namespace arma;
using namespace nlohmann;
 


const double pi_constant = 3.1415926535897932384626433832795;	//PI常数
const double euler_constant = 2.7182818284590452353602874713527;	//自然数
const cx_double complex_i(0, 1);	//	虚数i
const cx_mat identity_matrix(2, 2,fill:: eye);	//2*2单位矩阵
const cx_mat zero_matrix(2, 2, fill::zeros);	//2*2全0矩阵
const double c_constant = 299792458;	//光速

//	散射矩阵结构体
struct  Smatrix
{
	cx_mat  S11 = zero_matrix;
	cx_mat  S12 = identity_matrix;
	cx_mat  S21 = identity_matrix;
	cx_mat  S22 = zero_matrix;
};

//	需要的数据
struct UserJson
{
	cx_vec Index;
	vec thickness;
	double theta_min, theta_max;
	int theta_points;
	double lambda_min, lambda_max;
	int lambda_points;
};

//	存储结果
struct RTsp
{
	double Rp;
	double Rs;
	double Tp;
	double Ts;
};