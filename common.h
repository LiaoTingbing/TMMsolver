#pragma once

#include <armadillo>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <complex>
#include <nlohmann/json.hpp>
#include <ctime>

using namespace std;
using namespace arma;
using namespace nlohmann;
 


const double pi = 3.1415926535897932384626433832795;
const double e = 2.7182818284590452353602874713527;
const cx_double I(0, 1);
const cx_mat Identity(2, 2,fill:: eye);
const cx_mat Zero(2, 2, fill::zeros);
const double c0 = 299792458;


//struct Result
//{
//	double Transmittion;
//	double Reflection;
//};

struct  Smatrix
{
	cx_mat  S11 = Zero;
	cx_mat  S12 = Identity;
	cx_mat  S21 = Identity;
	cx_mat  S22 = Zero;
};

struct UserJson
{
	cx_colvec Index;
	colvec thickness;
	//double theta;
	//double lambda;
	double theta_min, theta_max;
	int theta_points;
	double lambda_min, lambda_max;
	int lambda_points;
};

struct RTsp
{
	double Rp;
	double Rs;
	double Tp;
	double Ts;
};