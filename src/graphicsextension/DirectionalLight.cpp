#include "DirectionalLight.h"
#include "frontier/Shader.h"
#include "frontier/Entity.h"
#include "frontier/Transform.h"
#include "frontier/Core.h"
#include "LightController.h"

namespace frontier
{
	void DirectionalLight::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _direction)
	{
		Light::OnInit(_parent, _ambient, _diffuse, _specular);
		m_direction = _direction;
		_parent.lock()->GetCore()->GetLightController()->SetDirectionalLight(_parent);
	}

	void DirectionalLight::SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index)
	{
		std::string directionUniformID = _uniformName + ".direction";

		_shader.lock()->SetUniform(directionUniformID.c_str(), m_direction);

		std::string ambientUniformID = _uniformName + ".ambient";

		_shader.lock()->SetUniform(ambientUniformID.c_str(), m_ambient);

		std::string diffuseUniformID = _uniformName + ".diffuse";

		_shader.lock()->SetUniform(diffuseUniformID.c_str(), m_diffuse);

		std::string specularUniformID = _uniformName + ".specular";

		_shader.lock()->SetUniform(specularUniformID.c_str(), m_specular);

	}

}