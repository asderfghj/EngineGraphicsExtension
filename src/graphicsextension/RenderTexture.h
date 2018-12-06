#include <GL/glew.h>
#include "frontier/Texture.h"

namespace frontier
{
	class RenderTexture
	{
	private:
		GLuint m_FBO, m_texID;
		int m_width, m_height, m_textureLocation;
	public:
		//static std::shared_ptr<RenderTexture> Create(int width, int height);
		RenderTexture(int width, int height, int textureLocation);
		GLuint GetRenderTextureID();
		void Clear();
		void BindRenderTexture();
		void UnbindRenderTexture();
		void BindTexture();
		GLuint getTextureID();
		int getTexLocation();
	};
}