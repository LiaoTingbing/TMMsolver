#pragma once
#include "common.h"


class TMMsoler
{
private:
	// 构造初始化
	size_t layers_num;	//层数
	cx_vec index_list;	//折射率列表
	cx_vec er_list;		//相对介电常数列表
	vec thickness_list;				//每一层的厚度列表
	//double Lambda;
	//double theta;
	//double theta_min, theta_max, theta_points;
	//double lambda_min, lambda_max, lambda_points;
	//double frequency;

	vec theta_list,lambda_list,frequency_list;
	
	//	平面波变量
	vec k_unit;
	cx_double er_inc;
	cx_double ur_inc;
	double k0;
	cx_double kinc;
	cx_vec kinc_vector;

	cx_double kx_;
	cx_double ky_;
	cx_double kz_inc;

	Smatrix Global;

	// 空气区变量
	cx_mat Qg;
	cx_mat Vg;

	//反射区变量
	cx_double er_ref;
	cx_double ur_ref;
	cx_double kz_ref;
	cx_mat Qref;
	cx_mat Qmega_ref;
	cx_mat Vref;
	cx_mat Aref;
	cx_mat Bref;
	Smatrix Sref;

	// 结构变量
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

	// 透射区变量
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

	TMMsoler(UserJson& dataIn);	//加载数据
	TMMsoler();
	~TMMsoler();

	void showLayers();

	void initialize(double theta, double lambda);	//初始化


	void Incidence();

	void Gap();

	void ReflectionSolve();

	void LayerSolve();

	void TransmissionSlove();

	RTsp RTsolve(double theta);
 

	// 传输矩阵法求解函数
	RTsp TMM(  double theta , double lambda , double frequency = 0 )
	{
		 //showLayers();
		 //cout << "波长 ：" << lambda << endl;
		 //cout << "角度 ：" << theta  << endl;

		 initialize( theta,  lambda);	//初始化
		 Incidence();					//计算入射波
		 Gap();							//计算GAP参数
		 ReflectionSolve();				//计算反射区
		 LayerSolve();					//计算层
		 TransmissionSlove();			//计算透射区
		 return RTsolve(theta);			//计算透射率
	}

	//	多角度波长求解
	void TMMsweep();
};

