#include "PCH.h"
#include "TouchdownZone.h"


TouchdownZone::TouchdownZone()
	: len_elem_tdp(0.0), x_a(0.0), x_f(0.0)
{}

TouchdownZone::TouchdownZone(TouchdownZone&& other) noexcept
	: len_elem_tdp(std::move(other.len_elem_tdp)), x_a(std::move(other.x_a)), x_f(std::move(other.x_f))
{}

TouchdownZone::~TouchdownZone()
{}

TouchdownZone& TouchdownZone::operator=(TouchdownZone&& other) noexcept
{
	len_elem_tdp = std::move(other.len_elem_tdp);
	x_a = std::move(other.x_a);
	x_f = std::move(other.x_f);
	tdz_a = std::move(other.tdz_a);
	tdz_f = std::move(other.tdz_f);

	return *this;
}


//Generates Touchdown Zone segment
void TouchdownZone::CreateTDZsegment(struct TDZ_segment& tdz_seg)
{
	double len_ratio = ( tdz_seg.len_elem_out ) / len_elem_tdp;

	//Calcula número de elementos (n) e da razão (q) da PG

	double f, f_deriv; //função a ser zerada (f) e sua derivada (f_deriv)
	double fi_newton, res; //função para o método de Newton e resíduo

	double n = 10; //valor inicial
	for (int cont = 0; cont < 1000; cont++) //Calcula número de elementos
	{
		f = len_elem_tdp * ( 1 - pow(len_ratio, n / ( n - 1.0 )) ) / ( 1 - pow(len_ratio, 1.0 / ( n - 1.0 )) ) - ( tdz_seg.Sn );
		f_deriv = ( log(len_ratio) * len_elem_tdp * pow(len_ratio, 1.0 / ( n - 1.0 )) * ( 1.0 - len_ratio ) ) / ( pow(len_ratio, 1.0 / ( n - 1.0 )) * ( 2.0 * pow(n, 2) + 2.0 - n * 4.0 ) - pow(n - 1.0, 2.0) * ( pow(len_ratio, 2.0 / ( n - 1.0 )) + 1.0 ) );
		fi_newton = n - f / f_deriv;

		res = sqrt(pow(fi_newton - n, 2.0));
		if (res < 1e-6) break;
		n = fi_newton;
	}
	int n_int = ( int )floor(n);
	double q_i = 2.0; //valor inicial

	tdz_seg.case_seg = 1;
	while (( tdz_seg.case_seg <= 3 ))
	{
		for (int cont = 0; cont < 1000; cont++) //Calcula razão
		{
			f = len_elem_tdp * ( 1.0 - pow(q_i, n_int) ) / ( 1.0 - q_i ) - ( tdz_seg.Sn );
			f_deriv = -len_elem_tdp * ( n_int )*pow(q_i, n_int - 1) / ( 1.0 - q_i ) + len_elem_tdp * ( 1.0 - pow(q_i, n_int) ) / pow(1.0 - q_i, 2.0);
			fi_newton = q_i - f / f_deriv;

			res = sqrt(pow(fi_newton - q_i, 2.0));
			if (res < 1e-10) break;
			q_i = fi_newton;
		}

		tdz_seg.dif_len = ( tdz_seg.Sn ) - ( len_elem_tdp * ( 1.0 - pow(q_i, n_int) ) / ( 1.0 - q_i ) );
		tdz_seg.dist_dif_len = ( tdz_seg.dif_len ) / ( n_int - 2.0 );
		double a = len_elem_tdp * pow(q_i, n_int - 2.0);
		if (( a + tdz_seg.dist_dif_len ) < ( len_ratio * len_elem_tdp ))
			break;
		else
		{
			if (( tdz_seg.case_seg == 1 ) || ( tdz_seg.case_seg == 3 ))
				tdz_seg.dist_dif_len = ( tdz_seg.dif_len ) / ( n_int - 1.0 );
			if (tdz_seg.case_seg == 2)
				n_int += 1;

			if (( a + tdz_seg.dist_dif_len ) < ( len_ratio * len_elem_tdp ))
			{
				tdz_seg.case_seg++;
				break;
			}
		}
		tdz_seg.case_seg++;
	}
	tdz_seg.n_elements = n_int;
	tdz_seg.q = q_i;
}

