#pragma once


namespace oglElements {

	class ImageDetail {
	public:

		ImageDetail();

		bool8 loadSuccessfully;
		int32 width;
		int32 height;
	};

	class Texture {
		public:

			const ImageDetail& createByFilename(gl_to& texture, GLenum target, const std::string& filename);

			bool8 createArrayByFilenames(gl_to& texture,int32 width,int32 height, const std::vector<std::string>& filenames);
	};
}
