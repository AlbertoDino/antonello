#include <rdecommon.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "gltypes.h"
#include "texture.h"

namespace oglElements {

	bool8 Texture::createByFilename(gl_to& texture, GLenum target, const std::string& filename)
	{
		stbi_set_flip_vertically_on_load(1);

		int32 width = 0, height = 0, bpp = 0;
		
		unsigned char* image_data = stbi_load(filename.c_str(), &width, &height, &bpp, 0);

		if (!image_data) {
			throwError(format("Cannot load texture %s", filename.c_str()));
			return false;
		}

		glGenTextures(1, &texture.uId);

		texture.target = target;

		glBindTexture(target, texture.uId);

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
				return false;
			}
		}

		glTexParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(target, 0);
		stbi_image_free(image_data);
		return true;
	}
}