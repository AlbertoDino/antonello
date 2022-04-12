#pragma once
#include "sceneobject.h"


namespace oglElements {

	class ShaderContext : public IRenderingCtx {
	public:

		ShaderContext(int32 rndContextId);
		~ShaderContext();

		void useShader() const;
		void add2Context(SceneObject* sceneShaderObject);		

		virtual void init(oglElements::WinObj* window);
		virtual void render() const;
		virtual void end();

		oglElements::ShaderUniforms shader;
	private:
		
		std::vector<SceneObject*> shaderObjects;
	};


}