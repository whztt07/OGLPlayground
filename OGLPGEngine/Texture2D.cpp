//Texture2D.cpp
#include "Texture2D.h"
#include "SOIL.h"

Texture2D::Texture2D(std::string filePath):_name(filePath)
{
	Initialize(filePath, GL_LINEAR, GL_LINEAR, false);
}
Texture2D::Texture2D(std::string filePath, GLenum minFilter, GLenum magFilter, bool generateMipMaps):_name(filePath)
{
	Initialize(filePath, minFilter, magFilter, generateMipMaps);
}
Texture2D::~Texture2D()
{
	if(glIsTexture(_texture))
	{
		glDeleteTextures(1, &_texture);
	}
}
void Texture2D::Initialize(std::string filePath, GLenum minFilter, GLenum magFilter, bool generateMipMaps)
{
	//Really basic image loading
	unsigned char* textureData = SOIL_load_image(_name.c_str(), &_width, &_height, &_channels, SOIL_LOAD_AUTO);
	if(textureData)
	{
		//Generate the texture
		glGenTextures(1, &_texture);

		//Bind it to the context
		glBindTexture(GL_TEXTURE_2D, _texture);

		GLenum format = _channels == 4 ? GL_RGBA : GL_RGB;

		if(generateMipMaps)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

		glTexImage2D( GL_TEXTURE_2D, 0, format, _width, _height, 0, format,
			GL_UNSIGNED_BYTE, textureData );

		//clean up
		SOIL_free_image_data(textureData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//else.. failure to load
}

GLuint Texture2D::GetTexture()const
{
	return _texture;
}
const std::string& Texture2D::GetName()const
{
	return _name;
}
int Texture2D::GetWidth()const
{
	return _width;
}
int Texture2D::GetHeight()const
{
	return _height;
}
int Texture2D::GetChannels()const
{
	return _channels;
}
std::vector<Color> Texture2D::GetImageData()
{
	std::vector<Color> imageData;
	GLuint* image = new GLuint[_width * _height];
	glBindTexture(GL_TEXTURE_2D, _texture);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, (GLvoid*)image);
	glBindTexture(GL_TEXTURE_2D, 0);
	for(int i = 0; i < (_width * _height); i++)
	{
		GLuint value = image[i];
		GLubyte r = (value & 0xFF000000) >> 24;
		GLubyte g = (value & 0x00FF0000) >> 16;
		GLubyte b = (value & 0x0000FF00) >> 8;
		GLubyte a = (value & 0x000000FF);
		imageData.push_back(Color(r,g,b,a));
	}
	delete [] image;
	return imageData;
}