#pragma once
#include "SolutionStep.h"


class MoorSolution
{
private:
	// Before analysis
	unsigned int m_steps_to_set_model;
	
	// Optional step to establish the sea current
	std::shared_ptr<SolutionStep> m_sea_current_step_ptr;
	bool m_seacurrent_step_exist;

	// Optional dynamic relaxation step(s)
	// -> to find lines static configuration and/or to release vessel forces
	bool m_dyn_relax_exist;
	
	// Optional step to search for lines static configuration
	std::shared_ptr<DynRelaxLinesConfig> m_lines_configuration_ptr;
	bool m_lines_config_exist;
	
	// Analysis steps
	std::vector<SolutionStep> m_solution_steps;

public:

	MoorSolution();
	MoorSolution(const MoorSolution&) = default;
	MoorSolution(MoorSolution&&) noexcept = default;
	~MoorSolution();
	
	/// 
	/// Shared pointers initializers
	/// 
	inline std::shared_ptr<DynRelaxLinesConfig> InitDynRelaxLines();
	inline std::shared_ptr<SolutionStep> InitStepSeaCurrent();
	

	///
	/// SETTERS
	///

	void SetStepsBeforeAnalysis(unsigned int steps);
	void SetDynRelaxExist(bool exist);
	void SetDynRelax_LinesConfigExist(bool exist);


	SolutionStep* AddSolutionStep();
	void PushBackSolutionStep();

	///
	/// GETTERS
	///

	inline unsigned int GetStepsBeforeAnalysis() const					{ return this->m_steps_to_set_model; }

	// Get dynamic relaxation step to find lines static configuration
	inline std::shared_ptr<DynRelaxLinesConfig> GetStepDynRelaxLines()	{ return this->m_lines_configuration_ptr; }
	
	// Get step to establish sea current
	inline std::shared_ptr<SolutionStep> GetStepSeaCurrent()			{ return this->m_sea_current_step_ptr; }

	// Get the vector with all solution (anlysis) steps
	inline const std::vector<SolutionStep>& GetStepsVec() const			{ return this->m_solution_steps; }
	inline std::vector<SolutionStep>& GetStepsVec()						{ return this->m_solution_steps; }

	// Get a specific solution (analysis) step
	inline const SolutionStep& GetStep(const unsigned int& step) const		{ return this->m_solution_steps[step]; }

	// Getter-ish -> check booleans
	bool ExistDynamicRelaxation() const	{ return this->m_dyn_relax_exist; }
	bool ExistDynRelax_Lines() const	{ return this->m_lines_config_exist; }
	bool ExistSeaCurrentStep() const	{ return this->m_seacurrent_step_exist; }



	///
	/// Overloaded operators
	///

	MoorSolution& operator=(const MoorSolution&) = default;
	MoorSolution& operator=(MoorSolution&&) = default;
};




/// Inline initializer for shared pointers
std::shared_ptr<DynRelaxLinesConfig> MoorSolution::InitDynRelaxLines() {
	this->m_lines_configuration_ptr = std::make_shared<DynRelaxLinesConfig>(0.0, 0, 0, 0, false, 0.0, 0.0, 1.0, 1.0e-1, 1.0e-4, 1'000'000,
		0.0, 0.0, 0.0, 0.0);

	this->m_dyn_relax_exist = true;
	this->m_lines_config_exist = true;

	return this->m_lines_configuration_ptr;
}
std::shared_ptr<SolutionStep> MoorSolution::InitStepSeaCurrent() {
	this->m_sea_current_step_ptr = std::make_shared<SolutionStep>(0, true, 0.0, 1.0, 1.0, 1.0e-5, 1.0e0, false, 
		1'000'000, 0.0, 0.0, 0.0, 0.0);

	this->m_seacurrent_step_exist = true;

	return this->m_sea_current_step_ptr;
}