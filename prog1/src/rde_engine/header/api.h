#pragma once
#include <rde_common/lib.h>

namespace api {

	enum eRenderingContext : int32 {
		None = 0,
		UICxt,
		ShaderFlatCtx,
		LightShaderCtx,

	};


	EXTERN_	oglElements::IRenderingCtx* getRenderingContext(eRenderingContext rndCtxId);


}
