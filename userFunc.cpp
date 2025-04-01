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