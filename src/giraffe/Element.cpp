#include "PCH.h"
#include "Element.h"

Element::Element()
	: material(0), section(0), number(0), n_nodes(0), cs(0), 
	mark_segment_begin(false)
{}


Element::~Element()
{}
