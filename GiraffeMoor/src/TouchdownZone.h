#pragma once


struct TDZ_segment
{
	/*unsigned int elem = 0, n_elements = 0;				//element that starts (or ends) the TDZ and the segment which contains this point
	int seg = 0;										//number of elements in the TDZ stretch
	unsigned int elements_out = 0;						//number of elements in the same segment before (or later) the TDZ
	double len_elem_out = 0.0;							//lenght of the element before (or later) the TDZ
	double Sn = 0.0, q = 0.0;							//geometric progression parameters
	double dif_len = 0.0;
	bool node_extreme_line = false;						//boolean to indicate if the TDZ reach the extrem of the line
	bool node_extreme_seg = false;						//boolean to indicate if the TDZ reach the extrem of the segment
	unsigned int case_seg = 0;
	double dist_dif_len = 0.0;*/
	
	unsigned int elem, n_elements;				//element that starts (or ends) the TDZ and the segment which contains this point
	unsigned int seg;	//unsigned?									//number of elements in the TDZ stretch
	unsigned int elements_out;						//number of elements in the same segment before (or later) the TDZ
	double len_elem_out;							//lenght of the element before (or later) the TDZ
	double Sn, q;							//geometric progression parameters
	double dif_len;
	bool node_extreme_line;						//boolean to indicate if the TDZ reach the extrem of the line
	bool node_extreme_seg;						//boolean to indicate if the TDZ reach the extrem of the segment
	unsigned int case_seg;
	double dist_dif_len;

	TDZ_segment() : elem(0), n_elements(0), seg(0), elements_out(0), len_elem_out(0.0),
		Sn(0.0), q(0.0), dif_len(0.0), node_extreme_line(false), node_extreme_seg(false),
		case_seg(0), dist_dif_len(0.0) {};
	TDZ_segment(TDZ_segment&& other) noexcept 
		: elem(std::move(other.elem)), n_elements(std::move(other.n_elements)), seg(std::move(other.seg)), 
		elements_out(std::move(other.elements_out)), len_elem_out(std::move(other.len_elem_out)),
		Sn(std::move(other.Sn)), q(std::move(other.q)), dif_len(std::move(other.dif_len)), 
		node_extreme_line(std::move(other.node_extreme_line)), node_extreme_seg(std::move(other.node_extreme_seg)),
		case_seg(std::move(other.case_seg)), dist_dif_len(std::move(other.dist_dif_len)) {};
	TDZ_segment(const TDZ_segment& other) = default;
	~TDZ_segment() {};
	TDZ_segment& operator=(TDZ_segment&& other) = default;
	TDZ_segment& operator=(const TDZ_segment& other) = default;
};

class TouchdownZone
{
public:
	TouchdownZone();
	TouchdownZone(TouchdownZone&& other) noexcept;
	TouchdownZone(const TouchdownZone& other) = default;
	~TouchdownZone();

	//Creates touchdown zone segment
	void CreateTDZsegment(struct TDZ_segment& tdz_seg);


	/*------------
	TDZ parameters
	-------------*/

	/*Touchdown zone segments 
		anchor -> TDP  |  TDP -> fairlead */
	TDZ_segment tdz_a, tdz_f;

	//Length of the element that contains the TDP (at the reference configuration)
	double len_elem_tdp;

	//Length at the reference configuration from anchor to TDZ beging
	double x_a;

	//Length at the reference configuration from TDZ end to fairlead
	double x_f;


	TouchdownZone& operator=(TouchdownZone&& other) noexcept;
	TouchdownZone& operator=(const TouchdownZone& other) = default;
};

