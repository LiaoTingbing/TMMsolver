#pragma once
#include "common.h"


class Device
{
private:
	// ≥ı ºªØ
	int layersNum;

	Source source;
	cx_colvec Index;
	cx_colvec ER;
	colvec L;
	double Lambda;
	double theta;
	cx_colvec k_unit ;

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

	// RT solve
	// colvec s , p ;
	// mat pol, esrc;
	// rowvec Exref, Eyref, Extrn, Eytrn;
	// cx_mat erf, etrn , Exref;


public:

	Device(Layer multilayer[], int layersNum, Source source);

	Device();
	~Device();
	void showLayers();

	void initialize();

	void Incidence();

	void Gap();

	void ReflectionSolve();

	void LayerSolve();

	void TransmissionSlove();

	void RTsolve();




};

