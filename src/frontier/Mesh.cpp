#include "Mesh.h"
#include "Model.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
#include "Camera.h"
#include "Texture.h"
#include "graphicsextension/LightController.h"
#include <GL/glew.h>

namespace frontier
{
	void Mesh::SetupMesh()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_vertVBO);
		glGenBuffers(1, &m_normVBO);
		glGenBuffers(1, &m_texCoordVBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertices.size(), &m_vertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, m_normVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_normals.size(), &m_normals.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, m_texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_texCoords.size(), &m_texCoords.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::SetupMeshNoTexCoords()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_vertVBO);
		glGenBuffers(1, &m_normVBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertices.size(), &m_vertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, m_normVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_normals.size(), &m_normals.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals, std::vector<GLfloat> _texcoords)
	{
		m_vertices = _vertices;
		m_normals = _normals;
		m_texCoords = _texcoords;
		SetupMesh();
	}

	Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals)
	{
		m_vertices = _vertices;
		m_normals = _normals;
		SetupMeshNoTexCoords();
	}

	void Mesh::Draw(glm::mat4 _model, glm::mat4 _view, glm::mat4 _proj, TexturePack _textures, std::shared_ptr<Shader> _shader, glm::vec3 _cameraPos, std::vector<Material> _materials, std::shared_ptr<LightController> _lightController)
	{
		if (_textures.m_hasDiff)
		{
			_shader->SetUniform("material.diffuseMat", _textures.m_Diffuse);
			_textures.m_Diffuse->BindTexture();
		}

		if (_textures.m_hasSpec)
		{
			_shader->SetUniform("material.specularMat", _textures.m_Specular);
			_textures.m_Specular->BindTexture();
		}

		glUseProgram(_shader->GetID());

		_shader->SetUniform("model", _model);
		_shader->SetUniform("view", _view);
		_shader->SetUniform("projection", _proj);
		_shader->SetUniform("viewPos", _cameraPos);
		_shader->SetUniform("material.ambient", _materials[0].m_ambient);
		_shader->SetUniform("material.diffuse", _materials[0].m_diffuse);
		_shader->SetUniform("material.specular", _materials[1].m_specular);
		_shader->SetUniform("material.shininess", _materials[1].m_shininess);

		//TESTS
		/*_shader->SetUniform("dirlight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		_shader->SetUniform("dirlight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		_shader->SetUniform("dirlight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		_shader->SetUniform("dirlight.specular", glm::vec3(1.0f, 1.0f, 1.0f));*/

		/*_shader->SetUniform("pointlights[0].position", glm::vec3(0.0f, 10.0f, -10.0f));
		_shader->SetUniform("pointlights[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		_shader->SetUniform("pointlights[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		_shader->SetUniform("pointlights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		_shader->SetUniform("pointlights[0].constant", 1.0f);
		_shader->SetUniform("pointlights[0].linear", 0.09f);
		_shader->SetUniform("pointlights[0].quadratic", 0.032f);*/

		_lightController->SetLightUniformValues(_shader, "dirlight", "pointlights", 4, "", 0);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
		glBindVertexArray(0);
		glUseProgram(0);

	}
}