#pragma once


class CoordinateSystem
{
	//ID of the CoordinateSystem object
	unsigned int number;
	
	//Versor
	std::array<double, 3> E1, E3;

	//======================================================================================================
public:
	CoordinateSystem();
	CoordinateSystem(unsigned int ID, const std::array<double, 3>& e1, const std::array<double, 3>& e3);
	~CoordinateSystem();

					/*----------+
					| Functions |
					+----------*/
	
	//Writes Giraffe model
	void WriteGiraffeModelFile(FILE *f);

	///
	/// Set/Get functions
	/// 

	//Set
	void SetCSID(unsigned int ID);
	void SetE1(const std::array<double, 3>& coordinates);
	void SetE3(const std::array<double, 3>& coordinates);
	void SetCoordinateSystem(const std::array<double, 3>& e1, const std::array<double, 3>& e3);
	//Get
	unsigned int GetCSID();
	double GetCoordinate(size_t versor_number, size_t coordinate);
	std::array<double, 3> const& GetVersor(size_t versor_number);
};

