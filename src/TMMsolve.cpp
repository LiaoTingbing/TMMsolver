#include "../include/TMMsolve.h"
#include "../include/userFunc.h"


TMMsoler::TMMsoler(UserJson& dataIn)
{
	layers_num = dataIn.Index.size();
	index_list = dataIn.Index;
	thickness_list = dataIn.thickness;
	double theta_min = dataIn.theta_min * pi_constant / 180.0;
	double theta_max = dataIn.theta_max * pi_constant / 180.0;
	int theta_points = dataIn.theta_points  ;

	double lambda_min = dataIn.lambda_min;
	double lambda_max = dataIn.lambda_max;
	int lambda_points = dataIn.lambda_points;

	theta_list = linspace(theta_min, theta_max, theta_points);
	lambda_list = linspace(lambda_min, lambda_max, lambda_points);
	frequency_list = c_constant / lambda_list;
 

}

TMMsoler::TMMsoler()
{

}

TMMsoler::~TMMsoler()
{
}


void TMMsoler::showLayers()
{
	std::cout << "\nLayerNum\tthickness(um)\tIndex(Re)\tIndex(Im)\n";
	for (int i = 0; i < layers_num; i++)
	{
		std::cout << i + 1;
		std::cout << "\t\t";
		std::cout << thickness_list(i) * 1e6;
		std::cout << "\t\t";
		std::cout << index_list(i).real();
		std::cout << "\t\t";
		std::cout << index_list(i).imag();
		std::cout << endl;
	}
}

void TMMsoler::initialize(double theta  , double lambda)
{
	er_list = pow(index_list, 2.0);
	//ER.print();
	k0 = 2.0 * pi_constant / lambda;
	k_unit = { sin(theta) , 0 , cos(theta) };
	Global = { zero_matrix , identity_matrix , identity_matrix  ,zero_matrix };

	//k_unit.print();
	//Global.S22.print();
}

void TMMsoler::Incidence()
{
	er_inc = er_list(0);
	ur_inc = 1.0;
	//k0 = 2.0 * pi / Lambda;
	kinc = k0 * sqrt(er_inc * ur_inc);
	kinc_vector = kinc * k_unit;
	kx_ = kinc_vector(0) / k0;
	ky_ = kinc_vector(1) / k0;
	kz_inc = sqrt(ur_inc * er_inc - kx_ * kx_ - ky_ * ky_);
}

void TMMsoler::Gap()
{
	Qg = cx_mat(2, 2, fill::zeros);
	Qg(0, 0) = kx_ * ky_;
	Qg(0, 1) = 1.0 + ky_ * ky_;
	Qg(1, 0) = -(1.0 + kx_ * kx_);
	Qg(1, 1) = -(kx_ * ky_);
	//Qg.print();              // QG OK
	Vg = -complex_i * Qg;
	//Vg.print();           Vg  OK
}

void TMMsoler::ReflectionSolve()
{
	er_ref = er_inc;
	ur_ref = 1.0;

	kz_ref = sqrt(ur_ref * er_ref - kx_ * kx_ - ky_ * ky_);
	Qref = cx_mat(2, 2, fill::zeros);
	Qref(0, 0) = 1.0 / ur_ref * (kx_ * ky_);
	Qref(0, 1) = 1.0 / ur_ref * (er_ref * ur_ref - kx_ * kx_);
	Qref(1, 0) = 1.0 / ur_ref * (ky_ * ky_ - ur_ref * er_ref);
	Qref(1, 1) = 1.0 / ur_ref * (-kx_ * ky_);

	Qmega_ref = complex_i * kz_ref * identity_matrix;
	Vref = Qref * inv(Qmega_ref);

	Aref = identity_matrix + inv(Vg) * Vref;
	Bref = identity_matrix - inv(Vg) * Vref;

	Sref.S11 = -inv(Aref) * Bref;
	Sref.S12 = 2.0 * identity_matrix * inv(Aref);
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


	 SconnectRight(Global, Sref);

	//Global.S11.print();
	//Global.S12.print();
	//Global.S21.print();
	//Global.S22.print();

}

void TMMsoler::LayerSolve()
{

	Q = cx_mat(2, 2, fill::zeros);
	for (size_t i = 0; i < layers_num; i++)
	{
		er_layer = er_list(i);
		ur_layer = 1.0;
		d = thickness_list(i);
		kz_ = sqrt(ur_layer * er_layer - kx_ * kx_ - ky_ * ky_);

		Q(0, 0) = 1.0 / ur_layer * (kx_ * ky_);
		Q(0, 1) = 1.0 / ur_layer * (ur_layer * er_layer - kx_ * kx_);
		Q(1, 0) = 1.0 / ur_layer * (ky_ * ky_ - ur_layer * er_layer);
		Q(1, 1) = 1.0 / ur_layer * (-kx_ * ky_);

		Omega = complex_i * kz_ * identity_matrix;
		V = Q * inv(Omega);
		A = identity_matrix + inv(V) * Vg;
		B = identity_matrix - inv(V) * Vg;
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

		  SconnectRight(Global, LayerS);

		//Global.S11.print();
		//Global.S12.print();
		//Global.S21.print();
		//Global.S22.print();

		//Ok
	}
}

void TMMsoler::TransmissionSlove()
{
 
	er_trn = er_list(layers_num - 1);
	ur_trn = 1.0;
	kz_trn = sqrt(ur_trn * er_trn - kx_ * kx_ - ky_ * ky_);
	Qtrn = cx_mat(2, 2, fill::zeros);
	Qtrn(0, 0) = 1.0 / ur_trn * (kx_ * ky_);
	Qtrn(0, 1) = 1.0 / ur_trn * (er_trn * ur_trn - kx_ * kx_);
	Qtrn(1, 0) = 1.0 / ur_trn * (ky_ * ky_ - ur_trn * er_trn);
	Qtrn(1, 1) = 1.0 / ur_trn * (-kx_ * ky_);
	Omega_trn = complex_i * kz_trn * identity_matrix;
	Vtrn = Qtrn * inv(Omega_trn);
	Atrn = identity_matrix + inv(Vg) * Vtrn;
	Btrn = identity_matrix - inv(Vg) * Vtrn;

	Strn.S11 = Btrn * inv(Atrn);
	Strn.S12 = 0.5 * (Atrn - Btrn * inv(Atrn) * Btrn);
	Strn.S21 = 2.0 * identity_matrix * inv(Atrn);
	Strn.S22 = -inv(Atrn) * Btrn;

	 SconnectRight(Global, Strn);

	//Global.S11.print();
	//Global.S12.print();
	//Global.S21.print();
	//Global.S22.print();
	//Ok
}

RTsp TMMsoler::RTsolve( double theta )
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
	//rowvec R = vectornorm(Eref);
	//rowvec T = vectornorm(Etrn) * real(kz_trn / ur_trn) / real(kz_inc / ur_inc);

	rowvec R = vecnorm(Eref);
	rowvec T = vecnorm(Etrn) * real(kz_trn / ur_trn) / real(kz_inc / ur_inc);

	double Rs = R(0);
	double Rp = R(1);

	double Ts = T(0);
	double Tp = T(1);

	//cout << "Result：" << endl;
	//cout << "Rs" << "+" << "Ts" << "=" << Rs << "+" << Ts << "=" << Rs + Ts << endl;
	//cout << "Rp" << "+" << "Tp" << "=" << Rp << "+" << Tp << "=" << Rp + Tp << endl;

	return RTsp{ Rp , Rs , Tp , Ts };
}

void TMMsoler::TMMsweep()
{
	//	角度波长数量
	size_t n_theta = theta_list.size();
	size_t n_lambda = lambda_list.size();

	//	存储结果
	mat Rs_sweep(n_lambda, n_theta);
	mat Rp_sweep(n_lambda, n_theta);
	mat Ts_sweep(n_lambda, n_theta);
	mat Tp_sweep(n_lambda, n_theta);

	double lambda, theta;
	RTsp  result;
	//	扫描角度
	for(size_t i = 0; i < n_theta; i++)
	{
		theta = theta_list(i);
		//cout << "theta : "  << theta << endl;
		//扫描波长
		for (size_t j = 0; j < n_lambda; j++)
		{
			 
			lambda = lambda_list(j);
			//cout << "lambda : " << lambda << endl;
			//	计算单频结果
			result=TMM(theta,  lambda);
			Rs_sweep(j, i) = result.Rs;
			Rp_sweep(j, i) = result.Rp;
			Ts_sweep(j, i) = result.Ts;
			Tp_sweep(j, i) = result.Tp;
		}
	}

	//	创建文件夹存储结果
	system("mkdir Output");

	Rs_sweep.save("Output/Rs.txt", raw_ascii);
	Rp_sweep.save("Output/Rp.txt", raw_ascii);
	Ts_sweep.save("Output/Ts.txt", raw_ascii);
	Tp_sweep.save("Output/Tp.txt", raw_ascii);

	//	存储参数
	theta_list = theta_list / pi_constant * 180;
	lambda_list = lambda_list / 1e-6;

	theta_list.save("Output/theta.txt", raw_ascii);
	lambda_list.save("Output/lambda.txt", raw_ascii);

}



