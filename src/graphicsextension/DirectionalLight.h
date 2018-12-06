#include "Light.h"
#include "glm.hpp"
#include <string>

namespace frontier
{

	class DirectionalLight : public Light
	{

	private:
		glm::vec3 m_direction;
	public:
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _direction);
		void SetLightUniform(std::string _uniformName, std::weak_ptr<Shader> _shader, int _index = -1) override;

	};

}