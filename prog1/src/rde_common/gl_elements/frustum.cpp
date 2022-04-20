#include <rdecommon.h>
#include "..\math\local.h"
#include "frustum.h"

using namespace func;

namespace oglElements {

	

	//====================================================================

    Frustum::Frustum()
    {
    }

    Frustum::~Frustum()
    {
    }

    void Frustum::calculateFrom(const CMatrix4f32& view, const CMatrix4f32& proj)
    {
		float   clip[16];// This will hold the clipping planes

		// Now that we have our modelview and projection matrix, if we combine these 2 matrices,
		// it will give us our clipping planes.  To combine 2 matrices, we multiply them.

		const float32* viewData = view.data;
		const float32* projData = proj.data;

		clip[0] = viewData[0] * projData[0] + viewData[1] * projData[4] + viewData[2] * projData[8] + viewData[3] * projData[12];
		clip[1] = viewData[0] * projData[1] + viewData[1] * projData[5] + viewData[2] * projData[9] + viewData[3] * projData[13];
		clip[2] = viewData[0] * projData[2] + viewData[1] * projData[6] + viewData[2] * projData[10] + viewData[3] * projData[14];
		clip[3] = viewData[0] * projData[3] + viewData[1] * projData[7] + viewData[2] * projData[11] + viewData[3] * projData[15];

		clip[4] = viewData[4] * projData[0] + viewData[5] * projData[4] + viewData[6] * projData[8] + viewData[7] * projData[12];
		clip[5] = viewData[4] * projData[1] + viewData[5] * projData[5] + viewData[6] * projData[9] + viewData[7] * projData[13];
		clip[6] = viewData[4] * projData[2] + viewData[5] * projData[6] + viewData[6] * projData[10] + viewData[7] * projData[14];
		clip[7] = viewData[4] * projData[3] + viewData[5] * projData[7] + viewData[6] * projData[11] + viewData[7] * projData[15];

		clip[8] = viewData[8] * projData[0] + viewData[9] * projData[4] + viewData[10] * projData[8] + viewData[11] * projData[12];
		clip[9] = viewData[8] * projData[1] + viewData[9] * projData[5] + viewData[10] * projData[9] + viewData[11] * projData[13];
		clip[10] = viewData[8] * projData[2] + viewData[9] * projData[6] + viewData[10] * projData[10] + viewData[11] * projData[14];
		clip[11] = viewData[8] * projData[3] + viewData[9] * projData[7] + viewData[10] * projData[11] + viewData[11] * projData[15];

		clip[12] = viewData[12] * projData[0] + viewData[13] * projData[4] + viewData[14] * projData[8] + viewData[15] * projData[12];
		clip[13] = viewData[12] * projData[1] + viewData[13] * projData[5] + viewData[14] * projData[9] + viewData[15] * projData[13];
		clip[14] = viewData[12] * projData[2] + viewData[13] * projData[6] + viewData[14] * projData[10] + viewData[15] * projData[14];
		clip[15] = viewData[12] * projData[3] + viewData[13] * projData[7] + viewData[14] * projData[11] + viewData[15] * projData[15];


		// Now we actually want to get the sides of the frustum.  To do this we take
		// the clipping planes we received above and extract the sides from them.
		// This will extract the RIGHT side of the frustum
		planes[0][0] = clip[3] - clip[0];
		planes[0][1] = clip[7] - clip[4];
		planes[0][2] = clip[11] - clip[8];
		planes[0][3] = clip[15] - clip[12];
		// Now that we have a normal (A,B,C) and a distance (D) to the plane,
		// we want to normalize that normal and distance.
		// Normalize the RIGHT side
		func::Normalize(planes[0]);


		// This will extract the LEFT side of the frustum
		planes[1][0] = clip[3] + clip[0];
		planes[1][1] = clip[7] + clip[4];
		planes[1][2] = clip[11] + clip[8];
		planes[1][3] = clip[15] + clip[12];
		// Normalize the LEFT side
		func::Normalize(planes[1]);

		// This will extract the BOTTOM side of the frustum
		planes[2][0] = clip[3] + clip[1];
		planes[2][1] = clip[7] + clip[5];
		planes[2][2] = clip[11] + clip[9];
		planes[2][3] = clip[15] + clip[13];
		// Normalize the BOTTOM side
		func::Normalize(planes[2]);

		// This will extract the TOP side of the frustum
		planes[3][0] = clip[3] - clip[1];
		planes[3][1] = clip[7] - clip[5];
		planes[3][2] = clip[11] - clip[9];
		planes[3][3] = clip[15] - clip[13];

		// Normalize the TOP side
		func::Normalize(planes[3]);

		// This will extract the BACK side of the frustum
		planes[4][0] = clip[3] - clip[2];
		planes[4][1] = clip[7] - clip[6];
		planes[4][2] = clip[11] - clip[10];
		planes[4][3] = clip[15] - clip[14];

		// Normalize the BACK side
		func::Normalize(planes[4]);

		// This will extract the FRONT side of the frustum
		planes[5][0] = clip[3] + clip[2];
		planes[5][1] = clip[7] + clip[6];
		planes[5][2] = clip[11] + clip[10];
		planes[5][3] = clip[15] + clip[14];

		// Normalize the FRONT side
		func::Normalize(planes[5]);
    }

    bool8 Frustum::isBoxInFrustrum(float32 x, float32 y, float32 z, float32 x2, float32 y2, float32 z2) const
    {
		// Go through all of the corners of the box and check then again each plane
		// in the frustum.  If all of them are behind one of the planes, then it most
		// like is not in the frustum.
		for (int i = 0; i < 6; i++)
		{
			if (planes[i][0] * x + planes[i][1] * y + planes[i][2] * z + planes[i][3] > 0)  continue;
			if (planes[i][0] * x2 + planes[i][1] * y + planes[i][2] * z + planes[i][3] > 0)  continue;
			if (planes[i][0] * x + planes[i][1] * y2 + planes[i][2] * z + planes[i][3] > 0)  continue;
			if (planes[i][0] * x2 + planes[i][1] * y2 + planes[i][2] * z + planes[i][3] > 0)  continue;
			if (planes[i][0] * x + planes[i][1] * y + planes[i][2] * z2 + planes[i][3] > 0)  continue;
			if (planes[i][0] * x2 + planes[i][1] * y + planes[i][2] * z2 + planes[i][3] > 0)  continue;
			if (planes[i][0] * x + planes[i][1] * y2 + planes[i][2] * z2 + planes[i][3] > 0)  continue;
			if (planes[i][0] * x2 + planes[i][1] * y2 + planes[i][2] * z2 + planes[i][3] > 0)  continue;

			// If we get here, it isn't in the frustum
			return false;
		}

		// Return a true for the box being inside of the frustum
		return true;
    }

    bool8 Frustum::isSphereInFrustrum(float32 x, float32 y, float32 z, float32 radius) const
    {
		// Go through all the sides of the frustum
		for (int i = 0; i < 6; i++)
		{
			// If the center of the sphere is farther away from the plane than the radius
			if ((planes[i][0] * x + planes[i][1] * y + planes[i][2] * z + planes[i][3]) <= -radius)
				// The distance was greater than the radius so the sphere is outside of the frustum
				return false;
		}
		// The sphere was inside of the frustum!
		return true;
    }
}