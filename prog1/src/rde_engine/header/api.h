#pragma once
#include <rde_common/lib.h>

namespace api {

	enum eRenderingContext : int32 {
		None = 0,
		UICxt,
		ShaderFlatCtx,
		LightShaderCtx,
		Light_temp_2

	};


	EXTERN_	oglElements::IRenderingCtx* getRenderingContext(eRenderingContext rndCtxId);


}
