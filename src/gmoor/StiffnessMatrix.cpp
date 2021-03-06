#include "PCH.h"
#include "StiffnessMatrix.h"


StiffnessMatrix::StiffnessMatrix()
	: m_exist_analytical(false), m_exist_numerical(false), 
	m_time_init(0.0), m_disp_init_x(0.0), m_disp_init_y(0.0), m_disp_init_z(0.0), 
	m_rot_init_x(0.0), m_rot_init_y(0.0), m_rot_init_z(0.0),
	m_stiff_matrix_step_id(0), m_time_matrix(0.0),
	m_disp_matrix_x(0.0), m_disp_matrix_y(0.0), m_disp_matrix_z(0.0),
	m_rot_matrix_x(0.0), m_rot_matrix_y(0.0), m_rot_matrix_z(0.0),
	m_time_series(nullptr)
{
	m_K_tan.alloc(6, 6);
}

StiffnessMatrix::~StiffnessMatrix()
{
	m_K_tan.flush();
}


void StiffnessMatrix::calc_Kaux(Matrix& fairlead, const std::vector<double>& eul_ang, const double& hf, const double& vf, const double& alpha, Matrix& Fi, Matrix& Ki)
{
	double phip = eul_ang[0];
	double thetap = eul_ang[1];
	double psip = eul_ang[2];

	//Derivatives of the rotation matrix w/ respect to Euler's angles
	Matrix Rphi(3, 3);
	Rphi(0, 0) = 0.0;
	Rphi(0, 1) = sin(phip) * sin(psip) + cos(phip) * cos(psip) * sin(thetap);
	Rphi(0, 2) = cos(phip) * sin(psip) - cos(psip) * sin(phip) * sin(thetap);
	Rphi(1, 0) = 0.0;
	Rphi(1, 1) = -cos(psip) * sin(phip) + cos(phip) * sin(psip) * sin(thetap);
	Rphi(1, 2) = -cos(phip) * cos(psip) - sin(phip) * sin(psip) * sin(thetap);
	Rphi(2, 0) = 0.0;
	Rphi(2, 1) = cos(phip) * cos(thetap);
	Rphi(2, 2) = -cos(thetap) * sin(phip);

	Matrix Rthe(3, 3);
	Rthe(0, 0) = -cos(psip) * sin(thetap);
	Rthe(0, 1) = cos(psip) * cos(thetap) * sin(phip);
	Rthe(0, 2) = cos(phip) * cos(psip) * cos(thetap);
	Rthe(1, 0) = -sin(psip) * sin(thetap);
	Rthe(1, 1) = cos(thetap) * sin(phip) * sin(psip);
	Rthe(1, 2) = cos(phip) * cos(thetap) * sin(psip);
	Rthe(2, 0) = -cos(thetap);
	Rthe(2, 1) = -sin(phip) * sin(thetap);
	Rthe(2, 2) = -cos(phip) * sin(thetap);

	Matrix Rpsi(3, 3);
	Rpsi(0, 0) = -cos(thetap) * sin(psip);
	Rpsi(0, 1) = -cos(phip) * cos(psip) - sin(phip) * sin(psip) * sin(thetap);
	Rpsi(0, 2) = cos(psip) * sin(phip) - cos(phip) * sin(psip) * sin(thetap);
	Rpsi(1, 0) = cos(psip) * cos(thetap);
	Rpsi(1, 1) = -cos(phip) * sin(psip) + cos(psip) * sin(phip) * sin(thetap);
	Rpsi(1, 2) = sin(phip) * sin(psip) + cos(phip) * cos(psip) * sin(thetap);
	Rpsi(2, 0) = 0.0;
	Rpsi(2, 1) = 0.0;
	Rpsi(2, 2) = 0.0;

	//Second derivatives of the rotation matrix w / respect to Euler's anlges
	Matrix Rphiphi(3, 3);
	Rphiphi(0, 0) = 0.0;
	Rphiphi(0, 1) = cos(phip) * sin(psip) - cos(psip) * sin(phip) * sin(thetap);
	Rphiphi(0, 2) = -sin(phip) * sin(psip) - cos(phip) * cos(psip) * sin(thetap);
	Rphiphi(1, 0) = 0.0;
	Rphiphi(1, 1) = -cos(phip) * cos(psip) - sin(phip) * sin(psip) * sin(thetap);
	Rphiphi(1, 2) = cos(psip) * sin(phip) - cos(phip) * sin(psip) * sin(thetap);
	Rphiphi(2, 0) = 0.0;
	Rphiphi(2, 1) = -cos(thetap) * sin(phip);
	Rphiphi(2, 2) = -cos(phip) * cos(thetap);

	Matrix Rphithe(3, 3);
	Rphithe(0, 0) = 0.0;
	Rphithe(0, 1) = cos(phip) * cos(psip) * cos(thetap);
	Rphithe(0, 2) = -cos(psip) * cos(thetap) * sin(phip);
	Rphithe(1, 0) = 0.0;
	Rphithe(1, 1) = cos(phip) * cos(thetap) * sin(psip);
	Rphithe(1, 2) = -cos(thetap) * sin(phip) * sin(psip);
	Rphithe(2, 0) = 0.0;
	Rphithe(2, 1) = -cos(phip) * sin(thetap);
	Rphithe(2, 2) = sin(phip) * sin(thetap);

	Matrix Rphipsi(3, 3);
	Rphipsi(0, 0) = 0.0;
	Rphipsi(0, 1) = cos(psip) * sin(phip) - cos(phip) * sin(psip) * sin(thetap);
	Rphipsi(0, 2) = cos(phip) * cos(psip) + sin(phip) * sin(psip) * sin(thetap);
	Rphipsi(1, 0) = 0.0;
	Rphipsi(1, 1) = sin(phip) * sin(psip) + cos(phip) * cos(psip) * sin(thetap);
	Rphipsi(1, 2) = cos(phip) * sin(psip) - cos(psip) * sin(phip) * sin(thetap);
	Rphipsi(2, 0) = 0.0;
	Rphipsi(2, 1) = 0.0;
	Rphipsi(2, 2) = 0.0;

	Matrix Rthethe(3, 3);
	Rthethe(0, 0) = -cos(psip) * cos(thetap);
	Rthethe(0, 1) = -cos(psip) * sin(phip) * sin(thetap);
	Rthethe(0, 2) = -cos(phip) * cos(psip) * sin(thetap);
	Rthethe(1, 0) = -cos(thetap) * sin(psip);
	Rthethe(1, 1) = -sin(phip) * sin(psip) * sin(thetap);
	Rthethe(1, 2) = -cos(phip) * sin(psip) * sin(thetap);
	Rthethe(2, 0) = sin(thetap);
	Rthethe(2, 1) = -cos(thetap) * sin(phip);
	Rthethe(2, 2) = -cos(phip) * cos(thetap);

	Matrix Rthepsi(3, 3);
	Rthepsi(0, 0) = sin(psip) * sin(thetap);
	Rthepsi(0, 1) = -cos(thetap) * sin(phip) * sin(psip);
	Rthepsi(0, 2) = -cos(phip) * cos(thetap) * sin(psip);
	Rthepsi(1, 0) = -cos(psip) * sin(thetap);
	Rthepsi(1, 1) = cos(psip) * cos(thetap) * sin(phip);
	Rthepsi(1, 2) = cos(phip) * cos(psip) * cos(thetap);
	Rthepsi(2, 0) = 0.0;
	Rthepsi(2, 1) = 0.0;
	Rthepsi(2, 2) = 0.0;

	Matrix Rpsipsi(3, 3);
	Rpsipsi(0, 0) = -cos(psip) * cos(thetap);
	Rpsipsi(0, 1) = cos(phip) * sin(psip) - cos(psip) * sin(phip) * sin(thetap);
	Rpsipsi(0, 2) = -sin(phip) * sin(psip) - cos(phip) * cos(psip) * sin(thetap);
	Rpsipsi(1, 0) = -cos(thetap) * sin(psip);
	Rpsipsi(1, 1) = -cos(phip) * cos(psip) - sin(phip) * sin(psip) * sin(thetap);
	Rpsipsi(1, 2) = cos(psip) * sin(phip) - cos(phip) * sin(psip) * sin(thetap);
	Rpsipsi(2, 0) = 0.0;
	Rpsipsi(2, 1) = 0.0;
	Rpsipsi(2, 2) = 0.0;

	//Forces at the fairlead
	double fh = Fi(0,0);
	double fv = Fi(1,0);
	
	//Stiffness coefficients of the mooring line
	double khh = Ki(0, 0);
	double khv = Ki(0, 1);
	double kvh = Ki(1, 0);
	double kvv = Ki(1, 1);

	//String stiffness of the mooring line
	double khh_ = fh / hf;

	//Forces vector
	Matrix fo(3, 1);
	fo(0, 0) = fh * cos(alpha);
	fo(1, 0) = fh * sin(alpha);
	fo(2, 0) = -fv;

	//Second derivatives of fairlead's global position
	Matrix Pphiphi = Rphiphi * fairlead;
	Matrix Pphithe = Rphithe * fairlead;
	Matrix Pphipsi = Rphipsi * fairlead;
	Matrix Pthethe = Rthethe * fairlead;
	Matrix Pthepsi = Rthepsi * fairlead;
	Matrix Ppsipsi = Rpsipsi * fairlead;

	//Stiffness matrix partitions
	
	//Traslation - translation stiffness partition
	Matrix ktt(3, 3);
	ktt(0, 0) = khh * pow(cos(alpha), 2) + khh_ * pow(sin(alpha), 2);
	ktt(0, 1) = (khh - khh_) * sin(alpha) * cos(alpha);
	ktt(0, 2) = -khv * cos(alpha);
	ktt(1, 0) = ktt(0, 1);
	ktt(1, 1) = khh * pow(sin(alpha), 2) + khh_ * pow(cos(alpha), 2);
	ktt(1, 2) = -khv * sin(alpha);
	ktt(2, 0) = -kvh * cos(alpha);
	ktt(2, 1) = -kvh * sin(alpha);
	ktt(2, 2) = kvv;

	//Translation - rotation stiffness partition
	Matrix grad_R_p_col0(3);
	grad_R_p_col0 = Rphi * fairlead;
	Matrix grad_R_p_col1(3);
	grad_R_p_col1 = Rthe * fairlead;
	Matrix grad_R_p_col2(3);
	grad_R_p_col2 = Rpsi * fairlead;

	Matrix grad_R_p(3, 3);
	grad_R_p(0, 0) = grad_R_p_col0(0, 0);
	grad_R_p(1, 0) = grad_R_p_col0(1, 0);
	grad_R_p(2, 0) = grad_R_p_col0(2, 0);
	grad_R_p(0, 1) = grad_R_p_col1(0, 0);
	grad_R_p(1, 1) = grad_R_p_col1(1, 0);
	grad_R_p(2, 1) = grad_R_p_col1(2, 0);
	grad_R_p(0, 2) = grad_R_p_col2(0, 0);
	grad_R_p(1, 2) = grad_R_p_col2(1, 0);
	grad_R_p(2, 2) = grad_R_p_col2(2, 0);
	Matrix ktr(3, 3);
	ktr = ktt * grad_R_p;

	//Rotation - translation stiffness partition
	Matrix krt(3, 3);
	krt = transp(ktr);

	//Rotation - rotation stiffness partition
	Matrix A(3, 3);
	A(0, 0) = dot(Pphiphi, fo);
	A(0, 1) = dot(Pphithe, fo);
	A(0, 2) = dot(Pphipsi, fo);
	A(1, 0) = dot(Pphithe, fo);
	A(1, 1) = dot(Pthethe, fo);
	A(1, 2) = dot(Pthepsi, fo);
	A(2, 0) = dot(Pphipsi, fo);
	A(2, 1) = dot(Pthepsi, fo);
	A(2, 2) = dot(Ppsipsi, fo);
	
	Matrix krr(3, 3);
	krr = transp(grad_R_p) * ktr - A;

	//Stiffness matrix composition
	Matrix K_aux(6, 6);
	K_aux(0, 0) = ktt(0, 0);
	K_aux(0, 1) = ktt(0, 1);
	K_aux(0, 2) = ktt(0, 2);
	K_aux(1, 0) = ktt(1, 0);
	K_aux(1, 1) = ktt(1, 1);
	K_aux(1, 2) = ktt(1, 2);
	K_aux(2, 0) = ktt(2, 0);
	K_aux(2, 1) = ktt(2, 1);
	K_aux(2, 2) = ktt(2, 2);

	K_aux(0, 3) = ktr(0, 0);
	K_aux(0, 4) = ktr(0, 1);
	K_aux(0, 5) = ktr(0, 2);
	K_aux(1, 3) = ktr(1, 0);
	K_aux(1, 4) = ktr(1, 1);
	K_aux(1, 5) = ktr(1, 2);
	K_aux(2, 3) = ktr(2, 0);
	K_aux(2, 4) = ktr(2, 1);
	K_aux(2, 5) = ktr(2, 2);

	K_aux(3, 0) = krt(0, 0);
	K_aux(3, 1) = krt(0, 1);
	K_aux(3, 2) = krt(0, 2);
	K_aux(4, 0) = krt(1, 0);
	K_aux(4, 1) = krt(1, 1);
	K_aux(4, 2) = krt(1, 2);
	K_aux(5, 0) = krt(2, 0);
	K_aux(5, 1) = krt(2, 1);
	K_aux(5, 2) = krt(2, 2);

	K_aux(3, 3) = krr(0, 0);
	K_aux(3, 4) = krr(0, 1);
	K_aux(3, 5) = krr(0, 2);
	K_aux(4, 3) = krr(1, 0);
	K_aux(4, 4) = krr(1, 1);
	K_aux(4, 5) = krr(1, 2);
	K_aux(5, 3) = krr(2, 0);
	K_aux(5, 4) = krr(2, 1);
	K_aux(5, 5) = krr(2, 2);

	m_K_tan = m_K_tan + K_aux;
}

void StiffnessMatrix::check_Ktan()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (abs(m_K_tan(i, j)) < MIN_NON_ZERO)
				m_K_tan(i, j) = 0.0;
		}
	}
}

void StiffnessMatrix::FprintKtan(const std::string& file)
{
	this->m_K_tan.fprint(file.c_str());
}

void StiffnessMatrix::SetAnalyticalStiffnessOpt(bool option)
{
	m_exist_analytical = option;
}
void StiffnessMatrix::SetNumericalStiffnessOpt(bool option)
{
	m_exist_numerical = option;
}




std::ostream& operator<<(std::ostream& out, const StiffnessMatrix& mat)
{
	out << "\n";
	for (long i = 0; i < mat.m_K_tan.getLines(); ++i)
	{
		out << "| ";
		for ( long j = 0; j < mat.m_K_tan.getColumns(); ++j )
		{
			if ( mat.m_K_tan.GetItem(i, j) > 1 || mat.m_K_tan.GetItem(i, j) < -1 )
				out << " " << mat.m_K_tan.GetItem(i, j) << "\t";
			else
				out << "      0     \t";
		}
		out << "|\n";
	}
	out << "\n";

	return out;
}
std::ostream& operator<<(std::ostream& out, StiffnessMatrix* mat)
{
	out << std::setprecision(5) << "\n";
	for (long i = 0; i < mat->m_K_tan.getLines(); ++i)
	{
		out << "| ";
		for ( long j = 0; j < mat->m_K_tan.getColumns(); ++j )
		{
			if ( mat->m_K_tan.GetItem(i, j) > 1 || mat->m_K_tan.GetItem(i, j) < -1 )
				out << " " << mat->m_K_tan.GetItem(i, j) << "\t";
			else
				out << "      0     \t";
		}
		out << "|\n";
	}
	out << std::setprecision(8) << "\n";

	return out;
}