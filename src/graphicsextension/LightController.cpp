#include "LightController.h"
#include <iostream>

#include "frontier/Core.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "frontier/Entity.h"

namespace frontier
{
	LightController::LightController(std::weak_ptr<Core> _corePtr)
	{
		m_corePtr = _corePtr;
	}

	void LightController::AddPointLight(std::weak_ptr<Entity> _newPointLight)
	{
		//if (_newPointLight.lock()->hasComponent<PointLight>())
		//{
			m_pointLights.push_back(_newPointLight);
		//}
		//else
		//{
		//	std::cout << "Does not contain point light, not added" << std::endl;
		//}
	}

	void LightController::SetDirectionalLight(std::weak_ptr<Entity> _directionalLight)
	{
		//if (_directionalLight.lock()->hasComponent<DirectionalLight>())
		//{
			m_directionalLight = _directionalLight;
		//}
		//else
		//{
		//	std::cout << "Does not contain directional light, not added" << std::endl;
		//}
	}

	void LightController::AddSpotLight(std::weak_ptr<Entity> _newSpotLight)
	{
		//if (_newSpotLight.lock()->hasComponent<SpotLight>())
		//{
		m_spotLights.push_back(_newSpotLight);
		//}
		//else
		//{
		//	std::cout << "Does not contain spotlight, not added" << std::endl;
		//}
	}

	void LightController::SetLightUniformValues(std::shared_ptr<Shader> _shader, std::string _directionalLightUniformID, std::string _pointLightUniformID, int _numOfPointLights, std::string _spotLightUniformID, int _numOfSpotLights)
	{
		if (!m_directionalLight.expired())
		{
			m_directionalLight.lock()->getComponent<DirectionalLight>()->SetLightUniform(_directionalLightUniformID, _shader);
		}
		for (int i = 0; i < _numOfPointLights && i < m_pointLights.size(); i++)
		{
			m_pointLights[i].lock()->getComponent<PointLight>()->SetLightUniform(_pointLightUniformID, _shader, i);
		}

	}

}