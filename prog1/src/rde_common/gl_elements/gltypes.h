#pragma once

namespace oglElements {

	class gl_vertexObject
	{
	public:
		gl_vertexObject() : VBO{ 0 }, VAO{ 0 }, IBO{ 0 }, count{0}, drawMode{ GL_TRIANGLES }{}
		GLsizei count;
		GLsizei drawMode;
		GLuint VAO;  // Vertex Array Object
		GLuint VBO;  // Vertex Buffer Object		
		GLuint IBO;	 // Index Buffer Object
		//GLuint UVO;  // UV Coortdinate Object
	};

	class gl_facts
	{
		public:
			gl_facts() : sFactor(0), dFactor(0) {}
		uint32 sFactor;
		uint32 dFactor;

	};

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

	class gl_clientstate
	{
		public:
			gl_clientstate() : target(0) {}

		gl_facts funcs;	//functions associated
		uint32	target;	//Client State target  es GL_DEPTH_TEST	
		//bool8	reverse;//if (true) Disable -> Enable
	};

}