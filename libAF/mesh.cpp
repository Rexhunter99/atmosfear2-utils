
#include "af2-mesh.h"

using namespace libAF2;


Mesh::Mesh()
{
	this->m_name = "";
}

Mesh::Mesh( const Mesh& mesh )
{
	this->m_name = mesh.m_name;
	this->m_vertices = mesh.m_vertices;
	this->m_triangles = mesh.m_triangles;
	this->m_bones = mesh.m_bones;
}

Mesh::~Mesh()
{
	this->m_vertices.clear();
	this->m_triangles.clear();
	this->m_bones.clear();
}

Mesh& Mesh::operator = (const Mesh& rhs)
{
	this->m_name = rhs.m_name;
	this->m_vertices = rhs.m_vertices;
	this->m_triangles = rhs.m_triangles;
	this->m_bones = rhs.m_bones;
	return (*this);
}

Mesh& Mesh::operator + (const Mesh& rhs)
{
	// WARNING: This operator is not complete! Triangles do not point to their correct vertices and vertices do not have correct bone assignments, nor do bones have correct linkage!
	// TODO: Make the new elements translate correctly by changing indices and linkage to match new vector sizes.
	this->m_vertices.insert(this->m_vertices.end(), rhs.m_vertices.begin(), rhs.m_vertices.end());
	this->m_triangles.insert(this->m_triangles.end(), rhs.m_triangles.begin(), rhs.m_triangles.end());
	this->m_bones.insert(this->m_bones.end(), rhs.m_bones.begin(), rhs.m_bones.end());
	return (*this);
}


std::string Mesh::getName() const
{
	return this->m_name;
}

void Mesh::setName( const std::string& name )
{
	this->m_name = name;
}

size_t	Mesh::getVertexCount() const
{
	return this->m_vertices.size();
}

size_t	Mesh::getTriangleCount() const
{
	return this->m_triangles.size();
}

size_t	Mesh::getBoneCount() const
{
	return this->m_bones.size();
}
