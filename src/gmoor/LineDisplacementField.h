#pragma once



class LineDisplacementField
{
private:
	size_t m_number;
	size_t m_step;
	
	bool m_is_harmonic;
	double m_amplitude;
	unsigned int m_mode;

public:
	
	/// Constructors and destructor
	LineDisplacementField();
	~LineDisplacementField();
	LineDisplacementField(const LineDisplacementField&) = default;
	LineDisplacementField(LineDisplacementField&&) = default;



	///				 
	/// SETTERS
	///				 
	
	void SetIDNumber(size_t number);
	void SetStep(size_t step);
	void SetAmplitude(double amplitude);
	void SetMode(unsigned int mode);
	void SetHarmonicOpt(bool is_harmonic);


	///				 
	/// GETTERS
	///				 

	size_t GetNumber() const		{ return m_number; }
	size_t GetStep() const			{ return m_step; }
	double GetAmplitude() const		{ return m_amplitude; }
	unsigned int GetMode() const	{ return m_mode; }
	bool IsHarmonic() const			{ return m_is_harmonic; }



	///
	/// Overloaded operators
	///

	friend bool operator<(const LineDisplacementField& disp1, const LineDisplacementField& disp2);
	friend bool operator>(const LineDisplacementField& disp1, const LineDisplacementField& disp2);
	friend bool operator==(const LineDisplacementField& disp1, const LineDisplacementField& disp2);
	friend bool operator!=(const LineDisplacementField& disp1, const LineDisplacementField& disp2);

	LineDisplacementField& operator=(const LineDisplacementField&) = default;
	LineDisplacementField& operator=(LineDisplacementField&&) = default;

	friend std::ifstream& operator>>(std::ifstream& input, LineDisplacementField* constraint);

};

