#pragma once


namespace oglElements {

	class Texture {
		public:

			bool8 createByFilename(gl_to& texture, GLenum target, const std::string& filename);
	};
}
