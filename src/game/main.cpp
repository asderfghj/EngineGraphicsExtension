#include <iostream>
#include <memory>
#include "frontier/MyEngine.h"
#include "graphicsextension/FrontierGraphics.h"
#include <exception>
#include "ProjectileBehavior.h"
#include "PlayerController.h"
#include "AsteroidBehavior.h"
#include "AsteroidSpawner.h"
#include "LightMove.h"
#include "FPSCamera.h"


void safe_main();

int main()
{
	try
	{
		safe_main();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Something went wrong" << std::endl;
	}

	std::cin.get();
	
	return 0;
}

void safe_main()
{
	std::shared_ptr<frontier::Core> _core = std::make_shared<frontier::Core>();

	_core->Init(_core, 1000, 800);


	//resource initialisation
	std::shared_ptr<frontier::Shader> DefaultModelShader = frontier::Shader::Create("../resources/fragmentshaders/LightingNoSpecularMap.fs", "../resources/vertexshaders/LightingNoSpecularMap.vs", { "aPos", "aNormal", "aTexCoord" }, _core->GetResources());

	std::shared_ptr<frontier::Shader> PBRShader = frontier::Shader::Create("../resources/fragmentshaders/PBR.fs", "../resources/vertexshaders/PBR.vs", { "aPos", "aNormal", "aTexCoord" }, _core->GetResources());

	std::shared_ptr<frontier::Model> SphereModel = frontier::Model::Create("../resources/models/sphere/sphere.obj", _core->GetResources());

	std::shared_ptr<frontier::Model> PlaneModel = frontier::Model::Create("../resources/models/plane/plane.obj", _core->GetResources());

	std::shared_ptr<frontier::Model> HatchetModel = frontier::Model::Create("../resources/models/Hatchet/Hatchet.obj", _core->GetResources());

	std::shared_ptr<frontier::Texture> albedo = frontier::Texture::Create("../resources/textures/pavingPBR/albedo.jpg", _core->GetResources(), 1);

	std::shared_ptr<frontier::Texture> normal = frontier::Texture::Create("../resources/textures/pavingPBR/normal.jpg", _core->GetResources(), 2);

	std::shared_ptr<frontier::Texture> roughness = frontier::Texture::Create("../resources/textures/pavingPBR/roughness.jpg", _core->GetResources(), 4);


	std::shared_ptr<frontier::Texture> hatchetAlbedo = frontier::Texture::Create("../resources/textures/HatchetPBR/albedo.png", _core->GetResources(), 1);

	std::shared_ptr<frontier::Texture> hatchetNormal = frontier::Texture::Create("../resources/textures/HatchetPBR/normal.png", _core->GetResources(), 2);

	std::shared_ptr<frontier::Texture> hatchetMetallic = frontier::Texture::Create("../resources/textures/HatchetPBR/metallic.png", _core->GetResources(), 3);

	std::shared_ptr<frontier::Texture> hatchetRoughness = frontier::Texture::Create("../resources/textures/HatchetPBR/Roughness.png", _core->GetResources(), 4);

	std::shared_ptr<frontier::Texture> hatchetAO = frontier::Texture::Create("../resources/textures/HatchetPBR/ao.png", _core->GetResources(), 5);

	std::shared_ptr<frontier::Entity> _PBRPlane = _core->AddEntity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(10.0f));
	
	_PBRPlane->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(PlaneModel);

	_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachTexture(albedo, frontier::MeshRenderer::ALBEDO);

	_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachTexture(normal, frontier::MeshRenderer::NORMAL);

	//_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachTexture(metallic, frontier::MeshRenderer::METALLIC);

	_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachTexture(roughness, frontier::MeshRenderer::ROUGHNESS);

	//_PBRPlane->getComponent<frontier::MeshRenderer>()->AttachTexture(ao, frontier::MeshRenderer::AO);


	std::shared_ptr<frontier::Entity> _PBRHatchet = _core->AddEntity(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 45.0f, 90.0f), glm::vec3(1.0f));

	_PBRHatchet->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(HatchetModel);

	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetAlbedo, frontier::MeshRenderer::ALBEDO);

	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetNormal, frontier::MeshRenderer::NORMAL);

	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetMetallic, frontier::MeshRenderer::METALLIC);

	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetRoughness, frontier::MeshRenderer::ROUGHNESS);

	_PBRHatchet->getComponent<frontier::MeshRenderer>()->AttachTexture(hatchetAO, frontier::MeshRenderer::AO);

	std::shared_ptr<frontier::Entity> _directionalLight = _core->AddEntity(glm::vec3(10.0f, 0.0f, 10.0f));


	_directionalLight->AddComponent<frontier::DirectionalLight, glm::vec3, glm::vec3, glm::vec3, glm::vec3>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(5.0f, -5.0f, 5.0f));

	/*std::shared_ptr<frontier::Entity> _pointLight = _core->AddEntity(glm::vec3(5.0f, 2.0f, 0.0f));

	_pointLight->AddComponent<frontier::PointLight, glm::vec3, glm::vec3, glm::vec3, float, float, float>(glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0, 0.22, 0.20);*/


	//camera positioning
	_core->GetMainCamera()->GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	_core->GetMainCamera()->GetEntity()->AddComponent<FPSCamera>();

	_core->Start();

}