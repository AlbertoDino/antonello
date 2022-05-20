#pragma once
#include <rde_common/lib.h>
#include <rde_engine/render/local.h>

namespace api {

	enum eRenderingContext : int32 {
		None = 0,
		UICxt,
		ShaderFlat,
		ShaderLight,
		ShaderFlatTexture,
		ShaderNormalTextureLight,
		ShaderNormalTextureLightInstanced,
	};


	EXTERN_	oglElements::IRenderingCtx*		getRenderingContext(eRenderingContext rndCtxId);
	EXTERN_ render::PixelReadContext*		getPixelReadContext();
	EXTERN_ const oglElements::gl_to&		getDefaultTexture();

}
