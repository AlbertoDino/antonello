#include <rdecommon.h>
#include "..\math\mathcommon.h"
#include "perspective.h"

using namespace func;

namespace oglElements {

    Perspective::Perspective()
        : type ( ftNone )

    {
        facScreenToView[0] = 0.0f;
        facScreenToView[1] = 0.0f;

        screenSize[0] = 0;
        screenSize[1] = 0;

        perspectiveSize[0] = 0.0f;
        perspectiveSize[1] = 0.0f;
    }

    Perspective::~Perspective()
    {
    }

    Perspective::Perspective(const Perspective& copy)
    {
        (*this) = copy;
    }

    Perspective& Perspective::operator=(const Perspective& other)
    {
        (*this) = other;
        return *this;
    }

    void Perspective::setScreenSize(int width, int height)
    {
        perspectiveSize[0] = (float32)(screenSize[0] = width);
        perspectiveSize[1] = (float32)(screenSize[1] = height);
    }

    void Perspective::setFrustum(float fFov, float fAspect, float fNear, float fFar)
    {
        facScreenToView[0] = 0.0;
        facScreenToView[1] = 0.0;

        float e = 1.0f / tanf((float32)(DEGREES_TO_RADIANT * fFov / 2.0f));
        float aspectInv = 1.0f / fAspect;
        float fovy = 2.0f * atanf(aspectInv / e);
        float xScale = 1.0f / tanf(0.5f * fovy);
        float yScale = xScale / aspectInv;

        projMatrix[0] = xScale;
        projMatrix[1] = 0.0f;
        projMatrix[2] = 0.0f;
        projMatrix[3] = 0.0f;

        projMatrix[4] = 0.0f;
        projMatrix[5] = yScale;
        projMatrix[6] = 0.0f;
        projMatrix[7] = 0.0f;

        projMatrix[8] = 0.0f;
        projMatrix[9] = 0.0f;
        projMatrix[10] = (fFar + fNear) / (fNear - fFar);
        projMatrix[11] = -1.0f;

        projMatrix[12] = 0.0f;
        projMatrix[13] = 0.0f;
        projMatrix[14] = (2.0f * fFar * fNear) / (fNear - fFar);
        projMatrix[15] = 0.0f;

        type = e_PerspectiveType::ftFrustum;
    }

    void Perspective::setOrthographic(float32 xMin, float32 xMax, float32 yMin, float32 yMax, float32 zMin, float32 zMax)
    {
        perspectiveSize[0] = -xMin + xMax;
        perspectiveSize[1] = -yMin + yMax;
        
        projMatrix.MakeOrthographicMatrix(xMin, xMax, yMin, yMax, zMin, zMax);

        projMatrix[15] = 1.0f;

        facScreenToView[0] = xMin * 2 / (this->screenSize[0]);
        facScreenToView[1] = yMin * 2 / (this->screenSize[1]);

        type = e_PerspectiveType::ftOrtho;
    }

    void Perspective::setOrthographic(int orthoWidth, int orthoHeigth)
    {
        setOrthographic(-(float32)(orthoWidth / 2), (float32)(orthoWidth / 2), -(float32)(orthoHeigth / 2), (float32)(orthoHeigth / 2), (float32)-200.0f, (float32)200.0f);
    }

    int Perspective::getOrtoScreen_X(int x) const
    {
        return func::ToInt(x - (perspectiveSize[0] / 2.0f));
    }

    int Perspective::getOrtoScreen_Y(int y) const
    {
        return func::ToInt((perspectiveSize[1] / 2.0f) - y);
    }
    void Perspective::getMatrix(CMatrix4f32& dst) const
    {
        dst = projMatrix;
    }

    e_PerspectiveType Perspective::getType() const
    {
        return type;
    }

    const CMatrix4f32* Perspective::getProjection() const
    {
        return &projMatrix;
    }
}