#pragma once


class ConvergenceCriteria
{
	double force_tol;		//Fator aplicado � norma do vetor de for�as do sistema para estabelecer crit�rio de converg�ncia
	double moment_tol;		//Fator aplicado � norma do vetor de momentos do sistema para estabelecer crit�rio de converg�ncia
	
	double force_min;		//Valor de for�a considerado pequeno - usado quando h� somente for�as nulas - valor dimensional
	double moment_min;		//Valor de momento considerado pequeno - usado quando h� somente momentos nulos - valor dimensional
	double constraint_min;	//Valor de erro de constraint, considerado pequeno - sempre � utilizado quando h� joints

	double disp_tol;		//Fator aplicado � norma do vetor de deslocamentos incrementais do sistema para estabelecer crit�rio de converg�ncia
	double rot_tol;			//Fator aplicado � norma do vetor de rota��es incrementais do sistema para estabelecer crit�rio de converg�ncia
	double lag_tol;			//Fator aplicado � norma do vetor de multiplicadores de lagrange do sistema para estabelecer crit�rio de converg�ncia

	double disp_min;		//Valor de deslocamento considerado pequeno - usado quando h� somente deslocamentos nulos - valor dimensional
	double rot_min;			//Valor de rota��o considerado pequeno - usado quando h� somente rota��es nulos - valor dimensional
	double lag_min;			//Valor de multiplicador de lagrange considerado pequeno - usado quando h� somente multiplicadores de lagrange nulos - valor dimensional

	double divergence_ref;	//Valor bastante elevado que indica diverg�ncia do modelo

	//============================================================================

public:
	ConvergenceCriteria();
	~ConvergenceCriteria();

	//============================================================================

	/*-------
	Functions
	---------*/

	//Reads input file
	bool Read(FILE *f);	

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) const;


};

