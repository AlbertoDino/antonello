#include <rdecommon.h>
#include "gltypes.h"

namespace oglElements {


    void gl_fbo::create(eFboTarget target)
    {
        target = target;
        glGenFramebuffers(1, &uId);
    }

    void gl_fbo::bind()
    {
        glBindFramebuffer(target, uId);
    }

    void gl_fbo::unbind()
    {
        glBindFramebuffer(target, 0);
    }
    void gl_fbo::attachTexture(gl_to& to)
    {
        glFramebufferTexture2D(target, to.fboAttachment, to.target, to.uId, to.fboBitmapLevel);

    }
    void gl_fbo::attachRenderBuffer(gl_rbo& rbo)
    {
        glFramebufferRenderbuffer(target, rbo.attachment, rbo.target, rbo.uId);

    }

    //------------------------------------------------------------

    void gl_rbo::create()
    {
        glGenRenderbuffers(1, &uId);
        target = GL_RENDERBUFFER;
    }

    void gl_rbo::bind()
    {
        glBindRenderbuffer(target, uId);
    }

    void gl_rbo::unbind()
    {
        glBindRenderbuffer(target, 0);
    }

    void gl_rbo::setPropeties(eFBOAttachment _attachment, uint32 internalFormat)
    {
        attachment = (ulong)_attachment;
        internalFormat = internalFormat;
    }

    void gl_rbo::setRenderBufferStorage(uint32 width, uint32 height)
    {
        glRenderbufferStorage(target, internalFormat, width, height);
    }

    void gl_rbo::destroy()
    {
        glDeleteFramebuffers(1, &uId);
    }

    //------------------------------------------------------------

    void gl_bo::create()
    {
        glGenBuffers(1, &uId);
    }

    void gl_bo::create(uint32 _target)
    {
        target = _target;
        create();
    }

    void gl_bo::bind()
    {
        glBindBuffer(target, uId);
    }

    void gl_bo::bind(uint32 _target)
    {
        target = _target;
        glBindBuffer(_target, uId);
    }

    void gl_bo::unbind()
    {
        glBindBuffer(target, 0);
    }

    void gl_bo::unbind(uint32 _target)
    {
        glBindBuffer(_target, 0);
    }
}