#pragma once


namespace oglElements {

	class ImageDetail {
	public:

		ImageDetail();

		bool8 loadSuccessfully;
		int32 width;
		int32 height;
		int32 bpp;
	};

	class Texture {
		public:
			Texture();
			~Texture();
			const ImageDetail& loadImageByFilename(const std::string& filename);

			void create(gl_to* textObject, GLenum target, int32 unit);
			void bind();
			void save();
			void setFiltering(int32 magnification, int32 minification);
			void setParameter(uint32 parameter, uint32 wrapMode);
			void generateMipmap();
			void unbind();
		private:
			byte	*imageData;
			gl_to	*texture;
			ImageDetail imageDetails;
	};
}
