#pragma once

namespace oglElements {

	enum eFboTarget : uint32 {

		fboDraw = GL_DRAW_FRAMEBUFFER,
		fboRead = GL_READ_FRAMEBUFFER,
		fboFrameBufeer = GL_FRAMEBUFFER
	};

	enum eFBOAttachment : ulong {

		glAttachment_Depth = GL_DEPTH_ATTACHMENT,
		glAttachment_Stencil = GL_STENCIL_ATTACHMENT,
		glAttachment_Color0 = GL_COLOR_ATTACHMENT0,
		glAttachment_Color1 = GL_COLOR_ATTACHMENT0,
		glAttachment_Color2 = GL_COLOR_ATTACHMENT1,
		glAttachment_Color3 = GL_COLOR_ATTACHMENT2

	};

	// Texture Object
	class gl_to
	{
	public:
		gl_to() : uId(0), target(0), unit(0), fboAttachment(0), fboBitmapLevel(0) {}
		uint32 uId;
		uint32 target;
		uint32 unit;
		uint32 fboAttachment;
		int32  fboBitmapLevel;
	};

	// Buffer Object
	class gl_bo
	{
	public:
		uint32 uId;
		uint32 size;	//size of type  glVertexAttribPointer
		uint32 type;	//type es GL_Float
		uint32 target;	//interpretation of buffer es. GL_ARRAY_BUFFER, GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER, GL_TEXTURE_BUFFER, GL_TRANSFORM_FEEDBACK_BUFFER, or GL_UNIFORM_BUFFER.

		void create();
		void create(uint32 target);
		void bind();
		void bind(uint32 target);

		void unbind();
		void unbind(uint32 target);

	};

	// Render Buffer Object
	class gl_rbo
	{
	public:
		gl_rbo() : uId(0), target(0), internalFormat(0), attachment(0) {};
		uint32 uId;
		uint32 target;	//interpretation of buffer es. GL_RENDERBUFFER
		uint32 internalFormat; //format buffer GL_DEPTH_COMPONENT32 , GL_COLOR_ATTACHMENT0
		uint32 attachment; //Used when attached to fbo

		void create();
		void bind();
		void unbind();

		void setPropeties(eFBOAttachment attachment, uint32 internalFormat);
		void setRenderBufferStorage(uint32 width, uint32 height);
		void destroy();
	};

	class gl_vertexObject
	{
	public:
		gl_vertexObject() : VBO{ 0 }, VAO{ 0 }, IBO{ 0 }, count{ 0 }, drawMode{ GL_TRIANGLES }{}
		GLsizei count;
		GLsizei drawMode;
		GLuint VAO;  // Vertex Array Object
		GLuint VBO;  // Vertex Buffer Object		
		GLuint IBO;	 // Index Buffer Object
	};

	class gl_facts
	{
	public:
		gl_facts() : sFactor(0), dFactor(0) {}
		uint32 sFactor;
		uint32 dFactor;

	};

	class gl_clientstate
	{
	public:
		gl_clientstate() : target(0) {}

		gl_facts funcs;	//functions associated
		uint32	target;	//Client State target  es GL_DEPTH_TEST	
		//bool8	reverse;//if (true) Disable -> Enable
	};

	// Frame Buffer Object
	class gl_fbo
	{
	public:
		gl_fbo() : uId(0), target(0) {}

		uint32 uId;
		uint32 target;	//interpretation of buffer : GL_DRAW_FRAMEBUFFER or GL_READ_FRAMEBUFFER

		void create(eFboTarget target);
		void bind();
		void unbind();
		void attachTexture(gl_to& to);
		void attachRenderBuffer(gl_rbo& rbo);
	};

}