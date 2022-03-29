#include <rdecommon.h>
#include "framebuffer.h"


namespace oglElements
{
	void FrameBuffer::create_buffers(int32_t width, int32_t height)
	{
        Width = width;
        Height = height;

        if (FBO)
        {
            delete_buffers();
        }

        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glCreateTextures(GL_TEXTURE_2D, 1, &TexId);
        glBindTexture(GL_TEXTURE_2D, TexId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TexId, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &DepthId);
        glBindTexture(GL_TEXTURE_2D, DepthId);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, Width, Height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthId, 0);

        GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(TexId, buffers);

        unbind();

	}

    void FrameBuffer::delete_buffers()
    {
        if (FBO)
        {
            glDeleteFramebuffers(GL_FRAMEBUFFER, &FBO);
            glDeleteTextures(1, &TexId);
            glDeleteTextures(1, &DepthId);
            TexId = 0;
            DepthId = 0;
        }

    }

    void FrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glViewport(0, 0, Width, Height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void FrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    uint32_t FrameBuffer::get_texture()
    {
        return TexId;
    }
}
