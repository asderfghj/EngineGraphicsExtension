#include <memory>
#include <GL/glew.h>

namespace frontier
{
	class Shader;
	class RenderTexture;
	class Core;

	class RenderQuad
	{
	private:
		std::shared_ptr<Shader> m_attachedShader;
		std::shared_ptr<RenderTexture> m_attachedRenderTexture;
		GLuint m_VAO, m_vertVBO, m_texVBO;
		std::weak_ptr<Core> m_corePtr;

	public:
		void OnInit(std::weak_ptr<Core> _corePtr);
		void Draw();
		void AttachRendertexture(std::shared_ptr<RenderTexture> _renderTexture);
		void AttachShader(std::shared_ptr<Shader> _shader);
	};
}