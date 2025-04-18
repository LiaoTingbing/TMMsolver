#pragma once
#include "common.h"


class Device
{
private:
	// 构造初始化
	size_t layersNum;
	cx_colvec Index;
	cx_colvec ER;
	colvec L;
	//double Lambda;
	//double theta;
	//double theta_min, theta_max, theta_points;
	//double lambda_min, lambda_max, lambda_points;
	//double frequency;

	vec theta_list,lambda_list,frequency_list;

	colvec k_unit;
	cx_double er_inc;
	cx_double ur_inc;
	double k0;
	cx_double kinc;
	cx_colvec kinc_vector;

	cx_double kx_;
	cx_double ky_;
	cx_double kz_inc;

	Smatrix Global;

	// GAP
	cx_mat Qg;
	cx_mat Vg;

	//REFLECTION
	cx_double er_ref;
	cx_double ur_ref;
	cx_double kz_ref;
	cx_mat Qref;
	cx_mat Qmega_ref;
	cx_mat Vref;
	cx_mat Aref;
	cx_mat Bref;
	Smatrix Sref;

	// Layer
	cx_double er_layer;
	cx_double ur_layer;
	double d;
	cx_double kz_;
	cx_mat Q;
	cx_mat Omega;
	cx_mat V;
	cx_mat A;
	cx_mat B;
	cx_mat X;
	cx_mat D;
	Smatrix LayerS;

	// TRANSMISSION
	cx_double er_trn;
	cx_double ur_trn;
	cx_double kz_trn;
	cx_mat Qtrn;
	cx_mat Omega_trn;
	cx_mat Vtrn;

	cx_mat Atrn;
	cx_mat Btrn;
	Smatrix Strn;


public:

	Device(UserJson& dataIn);
	Device();
	~Device();

	void showLayers();

	void initialize(double theta, double lambda);


	void Incidence();

	void Gap();

	void ReflectionSolve();

	void LayerSolve();

	void TransmissionSlove();

	RTsp RTsolve(double theta);
 

	// 内联
	RTsp TMM(  double theta , double lambda , double frequency = 0 )
	{

		
		 showLayers();

		 cout << "波长 ：" << lambda << endl;
		 cout << "角度 ：" << theta  << endl;

		 initialize( theta,  lambda);
		 Incidence();
		 Gap();
		 ReflectionSolve();
		 LayerSolve();
		 TransmissionSlove();
		 return RTsolve(theta);
	}

	void TMMsweep();

};

