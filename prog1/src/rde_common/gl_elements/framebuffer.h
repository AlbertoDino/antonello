#pragma once



namespace oglElements {

	class FrameBuffer
	{
    public:
        FrameBuffer() : FBO{ 0 }, DepthId{ 0 }
        {}

        void create_buffers(int32_t width, int32_t height) ;

        void delete_buffers();

        void bind();

        void unbind();

        uint32_t get_texture();
    protected:
        uint32_t FBO = 0;
        uint32_t TexId = 0;
        uint32_t DepthId = 0;
        int32_t Width = 0;
        int32_t Height = 0;
	};

}