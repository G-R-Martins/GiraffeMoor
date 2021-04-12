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
	
	//Tensor de inércia
	std::array<double, 6> J_G;
	
	//Posição do baricentro
	std::array<double, 3> G;
	
	//Nome do arquivo CAD que tem a informação geométrica completa para renderização do corpo rígido
	std::string platform_name;

	//Comment
	std::string comment;
};

