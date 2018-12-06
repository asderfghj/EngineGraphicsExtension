#include <vector>
#include <memory>
#include <string>

namespace frontier
{
	class Core;
	class Entity;
	class Shader;

	class LightController
	{
	private:
		std::weak_ptr<Core> m_corePtr;
		std::vector<std::weak_ptr<Entity>> m_pointLights;
		std::weak_ptr<Entity> m_directionalLight;
		std::vector<std::weak_ptr<Entity>> m_spotLights;

	public:
		LightController(std::weak_ptr<Core> _corePtr);
		void AddPointLight(std::weak_ptr<Entity> _newPointLight);
		void SetDirectionalLight(std::weak_ptr<Entity> _directionalLight);
		void AddSpotLight(std::weak_ptr<Entity> _newSpotLight);
		void SetLightUniformValues(std::shared_ptr<Shader> _shader, std::string _directionalLightUniformID, std::string _pointLightUniformID, int _numOfPointLights, std::string _spotLightUniformID, int _numOfSpotLights);
	};

}