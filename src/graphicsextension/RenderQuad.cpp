#include "RenderQuad.h"
#include "frontier/Shader.h"
#include "frontier/Core.h"
#include "RenderTexture.h"
#include <vector>

namespace frontier
{
	void RenderQuad::OnInit(std::weak_ptr<Core> _corePtr)
	{
		glGenVertexArrays(1, &m_VAO);

		std::vector<GLfloat> quadVertices = {
			-1.0f,  1.0f,
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f
		};

		glGenBuffers(1, &m_vertVBO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * quadVertices.size(), &quadVertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

		std::vector<GLfloat> quadTexCoords = {
			0.0f,  0.0f,
			0.0f, -1.0f,
			1.0f, -1.0f,
			1.0f, -1.0f,
			1.0f,  0.0f,
			0.0f,  0.0f
		};

		glGenBuffers(1, &m_texVBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_texVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * quadTexCoords.size(), &quadTexCoords.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_corePtr = _corePtr;

		m_attachedShader = m_corePtr.lock()->getDefaultRenderQuadShader();

	}

	void RenderQuad::Draw()
	{
		glUseProgram(m_attachedShader->GetID());

		m_attachedRenderTexture->BindTexture();

		m_attachedShader->SetUniform("texture", m_attachedRenderTexture);
		


		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void RenderQuad::AttachRendertexture(std::shared_ptr<RenderTexture> _renderTexture)
	{
		m_attachedRenderTexture = _renderTexture;
	}

	void RenderQuad::AttachShader(std::shared_ptr<Shader> _shader)
	{
		m_attachedShader = _shader;
	}


}