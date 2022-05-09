#pragma once
#include "gameobject.h"


namespace oglElements {

	class ShaderContext : public IRenderingCtx {
	public:

		ShaderContext(int32 rndContextId);
		~ShaderContext();

		void useShader() const;
		void add2Context(GameObject* sceneShaderObject);		

		virtual void init(oglElements::WinObj* window);
		virtual void render() const;
		virtual void end();

		oglElements::ShaderUniforms shader;
	private:
		
		std::vector<GameObject*> shaderObjects;
	};


}