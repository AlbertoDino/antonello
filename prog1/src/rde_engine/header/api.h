#pragma once
#include <rde_common/lib.h>
#include <rde_engine/render/local.h>

namespace api {

	EXTERN_ uint32 getModelId(void* model);

	enum eRenderingContext : int32 {
		None = 0,
		UICxt,
		ShaderFlatCtx,
		LightShaderCtx,
		Light_temp_2,
	};


	EXTERN_	oglElements::IRenderingCtx*		getRenderingContext(eRenderingContext rndCtxId);
	EXTERN_ render::PixelReadContext*		getPixelReadContext();
	EXTERN_ const oglElements::gl_to&		getDefaultTexture();

}
