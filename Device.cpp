#include "Device.h"
#include "userFunc.h"


Device::Device(UserJson& dataIn)
{
	this->layersNum = dataIn.Index.size();
	this->Index = dataIn.Index;
	this->L = dataIn.thickness;
	this->theta = dataIn.theta * pi / 180.0;
	this->Lambda = dataIn.lambda;
	this->frequency = c0 / Lambda;

	//cout << Lambda;
	//cout << theta;
	//L.print();
	//Index.print();

}

Device::Device()
{

}

Device::~Device()
{
}


void Device::showLayers()
{
	std::cout << "\nLayerNum\tthickness(um)\tIndex(Re)\tIndex(Im)\n";
	for (int i = 0; i < layersNum; i++)
	{
		std::cout << i + 1;
		std::cout << "\t\t";
		std::cout << L(i) * 1e6;
		std::cout << "\t\t";
		std::cout << Index(i).real();
		std::cout << "\t\t";
		std::cout << Index(i).imag();
		std::cout << endl;
	}
}

void Device::initialize()
{
	ER = pow(Index, 2.0);
	//ER.print();
	k0 = 2.0 * pi / Lambda;
	k_unit = { sin(theta) , 0 , cos(theta) };
	//k_unit.print();
	//Global.S22.print();
}

void Device::Incidence()
{
	er_inc = ER(0);
	ur_inc = 1.0;
	//k0 = 2.0 * pi / Lambda;
	kinc = k0 * sqrt(er_inc * ur_inc);
	kinc_vector = kinc * k_unit;
	kx_ = kinc_vector(0) / k0;
	ky_ = kinc_vector(1) / k0;
	kz_inc = sqrt(ur_inc * er_inc - kx_ * kx_ - ky_ * ky_);
}

void Device::Gap()
{
	Qg = cx_mat(2, 2, zeros);
	Qg(0, 0) = kx_ * ky_;
	Qg(0, 1) = 1.0 + ky_ * ky_;
	Qg(1, 0) = -(1.0 + kx_ * kx_);
	Qg(1, 1) = -(kx_ * ky_);
	//Qg.print();              // QG OK
	Vg = -I * Qg;
	//Vg.print();           Vg  OK
}

void Device::ReflectionSolve()
{
	er_ref = er_inc;
	ur_ref = 1.0;

	kz_ref = sqrt(ur_ref * er_ref - kx_ * kx_ - ky_ * ky_);
	Qref = cx_mat(2, 2, zeros);
	Qref(0, 0) = 1.0 / ur_ref * (kx_ * ky_);
	Qref(0, 1) = 1.0 / ur_ref * (er_ref * ur_ref - kx_ * kx_);
	Qref(1, 0) = 1.0 / ur_ref * (ky_ * ky_ - ur_ref * er_ref);
	Qref(1, 1) = 1.0 / ur_ref * (-kx_ * ky_);

	Qmega_ref = I * kz_ref * Identity;
	Vref = Qref * inv(Qmega_ref);

	Aref = Identity + inv(Vg) * Vref;
	Bref = Identity - inv(Vg) * Vref;

	Sref.S11 = -inv(Aref) * Bref;
	Sref.S12 = 2.0 * Identity * inv(Aref);
	Sref.S21 = 0.5 * (Aref - Bref * inv(Aref) * Bref);
	Sref.S22 = Bref * inv(Aref);

	//Sref.S11.print();  
	//Sref.S12.print();
	//Sref.S21.print();
	//Sref.S22.print();

	//Global.S11.print();
	//Global.S12.print();
	//Global.S21.print();
	//Global.S22.print();


	Global = SconnectRight(Global, Sref);

	//Global.S11.print();
	//Global.S12.print();
	//Global.S21.print();
	//Global.S22.print();

}

void Device::LayerSolve()
{

	Q = cx_mat(2, 2, zeros);
	for (size_t i = 0; i < layersNum; i++)
	{
		er_layer = ER(i);
		ur_layer = 1.0;
		d = L(i);
		kz_ = sqrt(ur_layer * er_layer - kx_ * kx_ - ky_ * ky_);

		Q(0, 0) = 1.0 / ur_layer * (kx_ * ky_);
		Q(0, 1) = 1.0 / ur_layer * (ur_layer * er_layer - kx_ * kx_);
		Q(1, 0) = 1.0 / ur_layer * (ky_ * ky_ - ur_layer * er_layer);
		Q(1, 1) = 1.0 / ur_layer * (-kx_ * ky_);

		Omega = I * kz_ * Identity;
		V = Q * inv(Omega);
		A = Identity + inv(V) * Vg;
		B = Identity - inv(V) * Vg;
		X = expmat(Omega * k0 * d);
		D = A - X * B * inv(A) * X * B;
		LayerS.S11 = inv(D) * (X * B * inv(A) * X * A - B);
		LayerS.S22 = LayerS.S11;
		LayerS.S12 = inv(D) * X * (A - B * inv(A) * B);
		LayerS.S21 = LayerS.S12;

		//LayerS.S11.print();
		//LayerS.S12.print();
		//LayerS.S21.print();
		//LayerS.S22.print();
		// OK

		Global = SconnectRight(Global, LayerS);

		//Global.S11.print();
		//Global.S12.print();
		//Global.S21.print();
		//Global.S22.print();

		//Ok
	}
}

void Device::TransmissionSlove()
{
	//Global.S11.print();
	//Global.S12.print();
	//Global.S21.print();
	//Global.S22.print();
	er_trn = ER(layersNum - 1);
	ur_trn = 1.0;
	kz_trn = sqrt(ur_trn * er_trn - kx_ * kx_ - ky_ * ky_);
	Qtrn = cx_mat(2, 2, zeros);
	Qtrn(0, 0) = 1.0 / ur_trn * (kx_ * ky_);
	Qtrn(0, 1) = 1.0 / ur_trn * (er_trn * ur_trn - kx_ * kx_);
	Qtrn(1, 0) = 1.0 / ur_trn * (ky_ * ky_ - ur_trn * er_trn);
	Qtrn(1, 1) = 1.0 / ur_trn * (-kx_ * ky_);
	Omega_trn = I * kz_trn * Identity;
	Vtrn = Qtrn * inv(Omega_trn);
	Atrn = Identity + inv(Vg) * Vtrn;
	Btrn = Identity - inv(Vg) * Vtrn;

	Strn.S11 = Btrn * inv(Atrn);
	Strn.S12 = 0.5 * (Atrn - Btrn * inv(Atrn) * Btrn);
	Strn.S21 = 2.0 * Identity * inv(Atrn);
	Strn.S22 = -inv(Atrn) * Btrn;

	Global = SconnectRight(Global, Strn);

	//Global.S11.print();
	//Global.S12.print();
	//Global.S21.print();
	//Global.S22.print();
	//Ok
}

void Device::RTsolve()
{
	colvec s = { 0,1,0 };
	colvec p = { -cos(theta) , 0 , sin(theta) };
	mat pol = join_rows(s, p);
	mat esrc = pol(0, 0, size(2, 2));
	//esrc.print(); Ok
	cx_mat erf = Global.S11 * esrc;
	cx_mat etrn = Global.S21 * esrc;

	cx_rowvec Exref = erf(0, 0, size(1, 2));

	cx_rowvec Eyref = erf(1, 0, size(1, 2));
	cx_rowvec Extrn = etrn(0, 0, size(1, 2));
	cx_rowvec Eytrn = etrn(1, 0, size(1, 2));

	cx_rowvec Ezref = -(kx_ * Exref + ky_ * Eyref) / kz_ref;
	cx_rowvec Eztrn = -(kx_ * Extrn + ky_ * Eytrn) / kz_trn;

	cx_mat Eref = join_cols(Exref, Eyref, Ezref);
	cx_mat Etrn = join_cols(Extrn, Eytrn, Eztrn);
	rowvec R = vectornorm(Eref);
	rowvec T = vectornorm(Etrn) * real(kz_trn / ur_trn) / real(kz_inc / ur_inc);

	double Rs = R(0);
	double Rp = R(1);

	double Ts = T(0);
	double Tp = T(1);

	cout << "Result£º" << endl;
	cout << "Rs" << "+" << "Ts" << "=" << Rs << "+" << Ts << "=" << Rs + Ts << endl;
	cout << "Rp" << "+" << "Tp" << "=" << Rp << "+" << Tp << "=" << Rp + Tp << endl;

}



