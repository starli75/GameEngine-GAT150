#include "pch.h"
#include "Model.h"

namespace nu
{
	void Model::CalculateRadius()
	{
		m_radius = 0.0f;

		for (const auto& mesh : m_meshes)
		{
			//Get mesh radius
			float radius = mesh.GetRadius();
			//If radius is larger than current radius, radius is now radius
			if (radius > m_radius)
				m_radius = radius;
		}
	}
}