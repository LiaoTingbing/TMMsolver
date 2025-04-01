#include "userFunc.h"


rowvec vectornorm(cx_mat& X)
{
	rowvec S(X.n_cols, zeros);
	double sum;
	for (int i = 0; i < X.n_cols;i++)
	{
		sum = 0;
		for (int j = 0;j < X.n_rows;j++)
		{
			sum += pow(abs(X(j, i)), 2.0);
		}
		S(i) = sum;
	}
	return S;

}



void TMM(Device& device)
{
	device.showLayers();
	device.initialize();
	device.Incidence();
	device.Gap();
	device.ReflectionSolve();
	device.LayerSolve();
	device.TransmissionSlove();
	device.RTsolve();
}

Smatrix SconnectRight(Smatrix& G, Smatrix& S)
{
	cx_mat D = G.S12 * inv(Identity - S.S11 * G.S22);
	cx_mat F = S.S21 * inv(Identity - G.S22 * S.S11);
	G.S11 = G.S11 + D * S.S11 * G.S21;
	G.S12 = D * S.S12;
	G.S21 = F * G.S21;
	G.S22 = S.S22 + F * G.S22 * S.S12;
	return G;
}

UserJson loadUserJson(string filename)
{

	//string filename = "content.json";
	string device_ = "device";
	string thickness_ = "thickness";
	string indexReal_ = "indexReal";
	string indexImag_ = "indexImag";
	string source_ = "source";
	string theta_ = "theta";
	string lambda_ = "lambda";

	ifstream fin(filename);
	json j;
	fin >> j;
	fin.close();

	double theta = j[source_][theta_];
	double lambda = j[source_][lambda_];

	auto layersNym = j[device_].size();
	colvec thickness(layersNym, zeros);
	colvec indexReal(layersNym, zeros);
	colvec indexImag(layersNym, zeros);

	int i = 0;
	for (auto p : j[device_])
	{
		thickness(i) = p[thickness_];
		indexReal(i) = p[indexReal_];
		indexImag(i) = p[indexImag_];
		i++;
	}

	cx_colvec Index = indexReal + indexImag * I;

	UserJson dataIn{ Index , thickness , theta , lambda };

	return dataIn;

}
