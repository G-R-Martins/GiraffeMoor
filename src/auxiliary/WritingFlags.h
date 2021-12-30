#pragma once


struct WritingFlags
{
	bool m_mesh_flag;
	bool m_render_mesh_flag;
	bool m_rigid_contact_surfaces_flag;
	bool m_flexible_contact_surfaces_flag;
	bool m_constraints_flag;
	bool m_forces_flag;
	bool m_special_constraints_flag;
	bool m_contact_forces_flag;
	bool m_render_particles_flag;
	bool m_render_rigid_bodies_flag;

	
	/// 
	/// Constructors, destructor and assign operators
	/// 
	
	WritingFlags() : m_mesh_flag(true), m_render_mesh_flag(false),
		m_rigid_contact_surfaces_flag(false),
		m_flexible_contact_surfaces_flag(false),
		m_constraints_flag(false), m_forces_flag(false),
		m_special_constraints_flag(false),
		m_contact_forces_flag(false),
		m_render_particles_flag(false),
		m_render_rigid_bodies_flag(false) {};
	~WritingFlags() {};
	
	WritingFlags(bool mesh_flag, bool render_mesh_flag, bool rigid_contact_surfaces_flag,
		bool flexible_contact_surfaces_flag, bool constraints_flag, bool forces_flag,
		bool special_constraints_flag, bool contact_forces_flag, bool render_particles_flag,
		bool render_rigid_bodies_flag)
		: m_mesh_flag(mesh_flag), m_render_mesh_flag(render_mesh_flag),
		m_rigid_contact_surfaces_flag(rigid_contact_surfaces_flag), 
		m_flexible_contact_surfaces_flag(flexible_contact_surfaces_flag), 
		m_constraints_flag(constraints_flag), m_forces_flag(forces_flag), 
		m_special_constraints_flag(special_constraints_flag), 
		m_contact_forces_flag(contact_forces_flag), 
		m_render_particles_flag(render_particles_flag), 
		m_render_rigid_bodies_flag(render_rigid_bodies_flag)
	{}

	// MOVE
	WritingFlags(WritingFlags&& other) noexcept
		: m_mesh_flag(other.m_mesh_flag), m_render_mesh_flag(other.m_render_mesh_flag),
		m_rigid_contact_surfaces_flag(other.m_rigid_contact_surfaces_flag),
		m_flexible_contact_surfaces_flag(other.m_flexible_contact_surfaces_flag),
		m_constraints_flag(other.m_constraints_flag), m_forces_flag(other.m_forces_flag),
		m_special_constraints_flag(other.m_special_constraints_flag),
		m_contact_forces_flag(other.m_contact_forces_flag),
		m_render_particles_flag(other.m_render_particles_flag),
		m_render_rigid_bodies_flag(other.m_render_rigid_bodies_flag)
	{}
	WritingFlags& operator=(WritingFlags&& other) noexcept
	{
		m_mesh_flag = std::move(other.m_mesh_flag);
		m_render_mesh_flag = std::move(other.m_render_mesh_flag);
		m_rigid_contact_surfaces_flag = std::move(other.m_rigid_contact_surfaces_flag);
		m_flexible_contact_surfaces_flag = std::move(other.m_flexible_contact_surfaces_flag);
		m_constraints_flag = std::move(other.m_constraints_flag);
		m_forces_flag = std::move(other.m_forces_flag);
		m_special_constraints_flag = std::move(other.m_special_constraints_flag);
		m_contact_forces_flag = std::move(other.m_contact_forces_flag);
		m_render_particles_flag = std::move(other.m_render_particles_flag);
		m_render_rigid_bodies_flag = std::move(other.m_render_rigid_bodies_flag);

		return *this;
	}
	
	// COPY
	WritingFlags(const WritingFlags& other) = default;
	WritingFlags& operator=(const WritingFlags& other) = default;


	/// 
	/// SETTERS
	/// 

	void SetMeshFlag(bool mesh_flag)											{ m_mesh_flag = mesh_flag ; }
	void SetRenderMeshFlag(bool render_mesh_flag)								{ m_render_mesh_flag = render_mesh_flag ; }
	void SetRigidContactSurfacesFlag(bool rigid_contact_surfaces_flag)			{ m_rigid_contact_surfaces_flag = rigid_contact_surfaces_flag ; }
	void SetFlexibleContactSurfacesFlag(bool flexible_contact_surfaces_flag)	{ m_flexible_contact_surfaces_flag = flexible_contact_surfaces_flag ; }
	void SetConstraintsFlag(bool constraints_flag)								{ m_constraints_flag = constraints_flag ; }
	void SetForcesFlag(bool forces_flag)										{ m_forces_flag = forces_flag ; }
	void SetSpecialConstraintsFlag(bool special_constraints_flag)				{ m_special_constraints_flag = special_constraints_flag ; }
	void SetContactForcesFlag(bool contact_forces_flag)							{ m_contact_forces_flag = contact_forces_flag ; }
	void SetRenderParticlesFlag(bool render_particles_flag)						{ m_render_particles_flag = render_particles_flag ; }
	void SetRenderRigidBodiesFlag(bool render_rigid_bodies_flag)				{ m_render_rigid_bodies_flag = render_rigid_bodies_flag ; }
	void SetAllFlags(bool flag_option) { 
		m_mesh_flag = flag_option;
		m_render_mesh_flag = flag_option;
		m_rigid_contact_surfaces_flag = flag_option;
		m_flexible_contact_surfaces_flag = flag_option;
		m_constraints_flag = flag_option;
		m_forces_flag = flag_option;
		m_special_constraints_flag = flag_option;
		m_contact_forces_flag = flag_option;
		m_render_particles_flag = flag_option;
		m_render_rigid_bodies_flag = flag_option;
	};


	/// 
	/// GETTERS
	/// 
	
	inline bool GetMeshFlag() const						{ return m_mesh_flag; }
	inline bool GetRenderMeshFlag() const				{ return m_render_mesh_flag; }
	inline bool GetRigidContactSurfacesFlag() const		{ return m_rigid_contact_surfaces_flag; }
	inline bool GetFlexibleContactSurfacesFlag() const	{ return m_flexible_contact_surfaces_flag; }
	inline bool GetConstraintsFlag() const				{ return m_constraints_flag; }
	inline bool GetForcesFlag() const					{ return m_forces_flag; }
	inline bool GetSpecialConstraintsFlag() const		{ return m_special_constraints_flag; }
	inline bool GetContactForcesFlag() const			{ return m_contact_forces_flag; }
	inline bool GetRenderParticlesFlag() const			{ return m_render_particles_flag; }
	inline bool GetRenderRigidBodiesFlag() const		{ return m_render_rigid_bodies_flag; }

	
	/// 
	/// Overloaded operators
	/// 
	
	friend std::ostream& operator<<(std::ostream& out, const WritingFlags& flags)
	{
		out << 
			"\n\tWriteMesh " << flags.m_mesh_flag <<
			"\n\tWriteRenderMesh " << flags.m_render_mesh_flag <<
			"\n\tWriteRigidContactSurfaces " << flags.m_rigid_contact_surfaces_flag <<
			"\n\tWriteFlexibleContactSurfaces " << flags.m_flexible_contact_surfaces_flag <<
			"\n\tWriteForces " << flags.m_forces_flag <<
			"\n\tWriteConstraints " << flags.m_constraints_flag <<
			"\n\tWriteSpecialConstraints " << flags.m_special_constraints_flag <<
			"\n\tWriteContactForces " << flags.m_contact_forces_flag <<
			"\n\tWriteRenderRigidBodies " << flags.m_render_rigid_bodies_flag <<
			"\n\tWriteRenderParticles " << flags.m_render_particles_flag << "\n";

		return out;
	}
};
