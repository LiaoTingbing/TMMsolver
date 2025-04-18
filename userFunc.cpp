#include "userFunc.h"


rowvec vectornorm(cx_mat& X)
{

	// 每一列的norm
	rowvec S(X.n_cols );
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

void SconnectRight(Smatrix& G, Smatrix& S)
{
	cx_mat D = G.S12 * inv(Identity - S.S11 * G.S22);
	cx_mat F = S.S21 * inv(Identity - G.S22 * S.S11);
	G.S11 = G.S11 + D * S.S11 * G.S21;
	G.S12 = D * S.S12;
	G.S21 = F * G.S21;
	G.S22 = S.S22 + F * G.S22 * S.S12;
 
}

UserJson loadUserJson(string filename)
{
	// 读取 json
	//string filename = "content.json";
	string device_ = "device";
	string thickness_ = "thickness";
	string indexReal_ = "indexReal";
	string indexImag_ = "indexImag";
	string source_ = "source";
	string theta_ = "theta";
	string lambda_ = "lambda";

	string theta_min_ = "theta_min";
	string theta_max_ = "theta_max";
	string theta_points_ = "theta_points";
	string lambda_min_ = "lambda_min";
	string lambda_max_ = "lambda_max";
	string lambda_points_ = "lambda_points";

	ifstream fin(filename);
	json j;
	fin >> j;
	fin.close();


	// 源数据
	double theta_min = j[source_][theta_min_];
	double theta_max = j[source_][theta_max_];
	int theta_points = j[source_][theta_points_];

	double lambda_min = j[source_][lambda_min_];
	double lambda_max = j[source_][lambda_max_];
	int lambda_points = j[source_][lambda_points_];

	// 加载器件数据
	auto layersNum = j[device_].size();
	colvec thickness(layersNum);
	colvec indexReal(layersNum);
	colvec indexImag(layersNum);

	int i = 0;
	for (auto p : j[device_])
	{
		thickness(i) = p[thickness_];
		indexReal(i) = p[indexReal_];
		indexImag(i) = p[indexImag_];
		i++;
	}

	cx_colvec Index = indexReal + indexImag * I;

	UserJson dataIn{ Index , thickness ,
		theta_min, theta_max,theta_points ,
		lambda_min,lambda_max,lambda_points };

	return dataIn;

}
