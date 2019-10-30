#include "GL/glew.h"
#include "Texture.h"

Texture::Texture(const std::string& name, const uint& id, const uint& width, const uint& height)
{
	this->name = name;
	this->id = id;
	this->width = width;
	this->height = height;
}

Texture::~Texture()
{

}