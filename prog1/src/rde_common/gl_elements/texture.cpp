#include <rdecommon.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "gltypes.h"
#include "texture.h"

namespace oglElements {

	Texture::Texture() : imageData(0),texture(0)
	{
		stbi_set_flip_vertically_on_load(1);
	}

	Texture::~Texture()
	{
		texture = 0;
		if (imageData)
		{
			stbi_image_free(imageData);
			imageData = 0;
		}
	}

	const ImageDetail& Texture::loadImageByFilename(const std::string& filename)
	{
		imageDetails = ImageDetail{};
		imageData = stbi_load(filename.c_str(), &imageDetails.width, &imageDetails.height, &imageDetails.bpp, 0);

		if (!imageData) {
			throwError(format("Cannot load texture %s", filename.c_str()));
			return imageDetails;
		}

		imageDetails.loadSuccessfully = true;
		return imageDetails;
	}

	void Texture::create(gl_to* textObject, GLenum target, int32 unit)
	{
		texture = textObject;
		texture->target = target;
		texture->unit = unit;
		glGenTextures(1, &texture->uId);
	}

	void Texture::bind()
	{		
		texture->activeBind();
	}

	void Texture::save()
	{
		if (texture->target == GL_TEXTURE_2D) {
			switch (imageDetails.bpp) {
			case 1:
				glTexImage2D(texture->target, 0, GL_RED, imageDetails.width, imageDetails.height, 0, GL_RED, GL_UNSIGNED_BYTE, imageData);
				break;

			case 3:
				glTexImage2D(texture->target, 0, GL_RGB, imageDetails.width, imageDetails.height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
				break;

			case 4:
				glTexImage2D(texture->target, 0, GL_RGBA, imageDetails.width, imageDetails.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
				break;

			default:
				throwError(format("bpp texture [%i] not supported", imageDetails.bpp));
			}
		}
	}

	void Texture::setFiltering(int32 magnification, int32 minification)
	{
		glTexParameteri(texture->target, GL_TEXTURE_MAG_FILTER, magnification);
		glTexParameteri(texture->target, GL_TEXTURE_MIN_FILTER, minification);
	}

	void Texture::setParameter(uint32 parameter, uint32 wrapMode)
	{
		glTexParameteri(texture->target, parameter, wrapMode);
	}

	void Texture::generateMipmap()
	{
		glGenerateMipmap(texture->target);
	}

	void Texture::unbind()
	{
		texture->unbind();
	}

	ImageDetail::ImageDetail() : loadSuccessfully (false)
		, width(0), height(0), bpp(0)
	{

	}
}