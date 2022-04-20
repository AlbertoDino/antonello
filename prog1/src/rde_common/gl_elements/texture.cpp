#include <rdecommon.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "gltypes.h"
#include "texture.h"

namespace oglElements {

	const ImageDetail& Texture::createByFilename(gl_to& texture, GLenum target, const std::string& filename)
	{
		ImageDetail result;
		stbi_set_flip_vertically_on_load(1);

		int32 width = 0, height = 0, bpp = 0;
		
		unsigned char* image_data = stbi_load(filename.c_str(), &width, &height, &bpp, 0);

		if (!image_data) {
			throwError(format("Cannot load texture %s", filename.c_str()));
			return result;
		}

		texture.create();
		texture.bind(target);

		if (target == GL_TEXTURE_2D) {
			switch (bpp) {
			case 1:
				glTexImage2D(target, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, image_data);
				break;

			case 3:
				glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
				break;

			case 4:
				glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
				break;

			default:
				throwError(format("bpp texture [%i] not supported", bpp));
				return result;
			}
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

		texture.unbind();
		stbi_image_free(image_data);

		result.loadSuccessfully = true;
		result.width = width;
		result.height = height;

		return result;
	}

	bool8 Texture::createArrayByFilenames(gl_to& texture, int32 width, int32 height, const std::vector<std::string>& filenames)
	{
		texture.create();
		texture.bind(GL_TEXTURE_2D_ARRAY);

		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, filenames.size());

		stbi_set_flip_vertically_on_load(1);

		int32 arrayIndex = 0;
		for (auto filename : std::as_const(filenames)) 
		{
			int32 w = 0, h = 0, bpp = 0;

			unsigned char* image_data = stbi_load(filename.c_str(), &w, &h, &bpp, 0);

			glTextureSubImage3D(
				GL_TEXTURE_2D_ARRAY, 0, 0, 0, arrayIndex++, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
								
			stbi_image_free(image_data);
		}
		return true;
	}

	ImageDetail::ImageDetail() : loadSuccessfully (false)
		, width(0), height(0)
	{

	}
}