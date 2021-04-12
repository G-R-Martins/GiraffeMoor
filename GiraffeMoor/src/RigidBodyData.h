#pragma once

class RigidBodyData
{
public:
	RigidBodyData();
	~RigidBodyData();

	//Writes Giraffe file
	void WriteGiraffeModelFile(FILE *f) const;
	
	//ID
	unsigned int number;
	
	//Massa
	double mass;
	
	//Tensor de in�rcia
	std::array<double, 6> J_G;
	
	//Posi��o do baricentro
	std::array<double, 3> G;
	
	//Nome do arquivo CAD que tem a informa��o geom�trica completa para renderiza��o do corpo r�gido
	std::string platform_name;

	//Comment
	std::string comment;
};

