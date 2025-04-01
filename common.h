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

using arma::pow;
using arma::join_cols;
using arma::join_rows;
using arma::vecnorm;
using arma::mat;
using arma::cx_mat;
using arma::colvec;
using arma::cx_colvec;
using arma::rowvec;
using arma::cx_rowvec;
using arma::cx_double;
using arma::size;
using arma::inv;
using arma::fill::zeros;
using arma::fill::eye;
using arma::expmat;
using std::real;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using nlohmann::json;


const double pi = 3.1415926535897932384626433832795;
const double e = 2.7182818284590452353602874713527;
const cx_double I(0, 1);
const cx_mat Identity(2, 2, eye);
const cx_mat Zero(2, 2, zeros);
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
	double theta;
	double lambda;
};