#pragma once


class ConvergenceCriteria
{
	double force_tol;		//Fator aplicado à norma do vetor de forças do sistema para estabelecer critério de convergência
	double moment_tol;		//Fator aplicado à norma do vetor de momentos do sistema para estabelecer critério de convergência
	
	double force_min;		//Valor de força considerado pequeno - usado quando há somente forças nulas - valor dimensional
	double moment_min;		//Valor de momento considerado pequeno - usado quando há somente momentos nulos - valor dimensional
	double constraint_min;	//Valor de erro de constraint, considerado pequeno - sempre é utilizado quando há joints

	double disp_tol;		//Fator aplicado à norma do vetor de deslocamentos incrementais do sistema para estabelecer critério de convergência
	double rot_tol;			//Fator aplicado à norma do vetor de rotações incrementais do sistema para estabelecer critério de convergência
	double lag_tol;			//Fator aplicado à norma do vetor de multiplicadores de lagrange do sistema para estabelecer critério de convergência

	double disp_min;		//Valor de deslocamento considerado pequeno - usado quando há somente deslocamentos nulos - valor dimensional
	double rot_min;			//Valor de rotação considerado pequeno - usado quando há somente rotações nulos - valor dimensional
	double lag_min;			//Valor de multiplicador de lagrange considerado pequeno - usado quando há somente multiplicadores de lagrange nulos - valor dimensional

	double divergence_ref;	//Valor bastante elevado que indica divergência do modelo

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

