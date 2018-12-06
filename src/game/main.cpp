#include <iostream>
#include <memory>
#include "frontier/MyEngine.h"
#include "graphicsextension/FrontierGraphics.h"
#include <exception>
#include "ProjectileBehavior.h"
#include "PlayerController.h"
#include "AsteroidBehavior.h"
#include "AsteroidSpawner.h"
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
	std::shared_ptr<frontier::Shader> DefaultModelShader = frontier::Shader::Create("../resources/fragmentshaders/fragmenttest.fs", "../resources/vertexshaders/vertextest.vs", { "aPos", "aNormal", "aTexCoords" }, _core->GetResources());

	std::shared_ptr<frontier::Texture> FighterTexture = frontier::Texture::Create("../resources/textures/fighter.png", _core->GetResources(), 1);

	std::shared_ptr<frontier::Texture> FighterSpecularTexture = frontier::Texture::Create("../resources/textures/fighterspecular.png", _core->GetResources(), 3);

	//std::shared_ptr<frontier::Texture> AsteroidTexture = frontier::Texture::Create("../resources/textures/astroid.jpg", _core->GetResources(), 3);

	//std::shared_ptr<frontier::Texture> MissileTexture = frontier::Texture::Create("../resources/textures/bronze.png", _core->GetResources(), 5);

	//std::shared_ptr<frontier::Texture> LivesImage = frontier::Texture::Create("../resources/textures/livesicon.png", _core->GetResources(), 4);

	//std::shared_ptr<frontier::Texture> GameOverTextImage = frontier::Texture::Create("../resources/textures/GameOverText.png", _core->GetResources(), 6);

	//std::shared_ptr<frontier::Texture> GameOverBackgroundImage = frontier::Texture::Create("../resources/textures/backgroundtexture.png", _core->GetResources(), 7);

	std::shared_ptr<frontier::Model> FighterModel = frontier::Model::Create("../resources/models/Fighter/fighter01.obj", _core->GetResources());

	//std::shared_ptr<frontier::Model> AsteroidModel = frontier::Model::Create("../resources/models/astroid/astroid.obj", _core->GetResources());

	//std::shared_ptr<frontier::Model> MissileModel = frontier::Model::Create("../resources/models/Missile.obj", _core->GetResources());

	//std::shared_ptr<frontier::Sound> shootsound = frontier::Sound::Create("../resources/sounds/laser.ogg", _core->GetResources());

	//std::shared_ptr<frontier::Sound> music = frontier::Sound::Create("../resources/sounds/music.ogg", _core->GetResources());

	//std::shared_ptr<frontier::Sound> crashSound = frontier::Sound::Create("../resources/sounds/crash.ogg", _core->GetResources());*/

	std::vector<std::string> faces =
	{
		"../resources/textures/skybox/right.png",
		"../resources/textures/skybox/left.png",
		"../resources/textures/skybox/top.png",
		"../resources/textures/skybox/bot.png",
		"../resources/textures/skybox/front.png",
		"../resources/textures/skybox/back.png",
	};

	std::shared_ptr<frontier::CubemapTexture> _cb1 = frontier::CubemapTexture::Create(faces, _core->GetResources(), 2);

	//skybox
	std::shared_ptr<frontier::Entity> skyBox = _core->AddEntity();

	skyBox->AddComponent<frontier::Skybox, std::shared_ptr<frontier::CubemapTexture>>(_cb1);


	//player
	std::shared_ptr<frontier::Entity> _ship1 = _core->AddEntity(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	_ship1->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(FighterModel);

	_ship1->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_ship1->getComponent<frontier::MeshRenderer>()->AttachTexture(FighterTexture, frontier::MeshRenderer::DIFFUSE);

	_ship1->getComponent<frontier::MeshRenderer>()->AttachTexture(FighterSpecularTexture, frontier::MeshRenderer::SPECULAR);

	std::shared_ptr<frontier::Entity> _ship2 = _core->AddEntity(glm::vec3(10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	_ship2->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(FighterModel);

	_ship2->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_ship2->getComponent<frontier::MeshRenderer>()->AttachTexture(FighterTexture, frontier::MeshRenderer::DIFFUSE);

	_ship2->getComponent<frontier::MeshRenderer>()->AttachTexture(FighterSpecularTexture, frontier::MeshRenderer::SPECULAR);

	std::shared_ptr<frontier::Entity> _ship3 = _core->AddEntity(glm::vec3(-10.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	_ship3->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(FighterModel);

	_ship3->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_ship3->getComponent<frontier::MeshRenderer>()->AttachTexture(FighterTexture, frontier::MeshRenderer::DIFFUSE);

	_ship3->getComponent<frontier::MeshRenderer>()->AttachTexture(FighterSpecularTexture, frontier::MeshRenderer::SPECULAR);

	std::shared_ptr<frontier::Entity> _directionalLight = _core->AddEntity();

	//_directionalLight->AddComponent<frontier::DirectionalLight, glm::vec3, glm::vec3, glm::vec3, glm::vec3>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.2f, -1.0f, -0.3f));

	std::shared_ptr <frontier::Entity> _pointLight1 = _core->AddEntity(glm::vec3(0.0f, -3.0f, -10.0f));

	_pointLight1->AddComponent<frontier::PointLight, glm::vec3, glm::vec3, glm::vec3, float, float, float>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.22f, 0.20f);

	std::shared_ptr <frontier::Entity> _pointLight2 = _core->AddEntity(glm::vec3(0.0f, 3.0f, -10.0f));

	_pointLight2->AddComponent<frontier::PointLight, glm::vec3, glm::vec3, glm::vec3, float, float, float>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.22f, 0.20f);

	std::shared_ptr <frontier::Entity> _pointLight3 = _core->AddEntity(glm::vec3(13.0f, 0, -10.0f));

	_pointLight3->AddComponent<frontier::PointLight, glm::vec3, glm::vec3, glm::vec3, float, float, float>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.22f, 0.20f);

	std::shared_ptr <frontier::Entity> _pointLight4 = _core->AddEntity(glm::vec3(-13.0f, 0.0f, -10.0f));

	_pointLight4->AddComponent<frontier::PointLight, glm::vec3, glm::vec3, glm::vec3, float, float, float>(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(3.0f, 3.0f, 3.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.22f, 0.20f);

	//camera positioning
	_core->GetMainCamera()->GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	_core->GetMainCamera()->GetEntity()->AddComponent<FPSCamera>();

	//glViewport(0, 0, 500, 400);

	_core->Start();

}