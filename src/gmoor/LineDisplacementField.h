#pragma once



class LineDisplacementField
{
private:
	unsigned int m_number;
	unsigned int m_step_id;
	
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
	
	void SetIDNumber(unsigned int number);
	void SetSolutionStep(unsigned int step_id);
	void SetAmplitude(double amplitude);
	void SetMode(unsigned int mode);
	void SetHarmonicOpt(bool is_harmonic);


	///				 
	/// GETTERS
	///				 

	unsigned int GetNumber() const		{ return m_number; }
	unsigned int GetStep() const			{ return m_step_id; }
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
};

