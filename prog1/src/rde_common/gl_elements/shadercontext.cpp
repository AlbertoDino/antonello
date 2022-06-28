#include <rdecommon.h>
#include "shader.h"
#include "irenderingctx.h"
#include "shadercontext.h"

namespace oglElements {



	ShaderContext::ShaderContext(int32 rndContextId)
	{
		contextId = rndContextId;
	}

	ShaderContext::~ShaderContext() {

	}

	void ShaderContext::useShader() const {
		shader.useShader();
	}

	void ShaderContext::add2Context(GameObject* sceneShaderObject)
	{
		shaderObjects.push_back(sceneShaderObject);
	}

	void ShaderContext::init(oglElements::WinObj* window)
	{

	}

	void ShaderContext::render() const
	{
		if (shaderObjects.size() == 0) return;

		useShader();
		for (auto const& shaderObject : std::as_const(shaderObjects)) {
			shaderObject->render();
		}

	}

	void ShaderContext::end()
	{
	}

	void ShaderContext::reset()
	{
		shaderObjects.clear();
	}


}