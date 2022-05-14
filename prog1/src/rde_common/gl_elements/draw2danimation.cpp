#include <rdecommon.h>
#include <sstream>
#include "..\math\local.h"
#include "gltypes.h"
#include "renderingelement.h"
#include "draw2danimation.h"

namespace oglElements {

    Draw2DAnimation::Draw2DAnimation() :
        animCursor(0),
        currentFrameIndex(0),
        framesCount(0),
		animationType(AnimationType::None)
    {
    }

    void Draw2DAnimation::loadAnimationfromFile(const std::string& filename, AnimationType type)
    {
		animationType = type;

		FILE* fp = nullptr;
		const int bufferlen = 255;
		char line[bufferlen];

		fopen_s(&fp, filename.c_str(), "r");

		if (fp == nullptr)
		{
			tracelog("error in reading animation file");
		}
		else
		{
			while (fgets(line, bufferlen, fp))
			{
				std::vector<int> result;

				std::stringstream ss(line);
				std::string token;
				while (std::getline(ss, token, ','))
				{
					result.push_back(stoi(token));
				}

				func::CVector4f frame = func::CVector4f(result[0], result[1], result[2], result[3]);
				frames.push_back(frame);
			}
		}

		framesCount = (int)frames.size();

		fclose(fp);

    }

	void Draw2DAnimation::updateFrameUniform(
		int32 texture_width,
		int32 texture_height,
		gl_vertexObject& rectangle,
		float32 defaultSpeed,
		float32 deltatime)
	{
		animCursor += deltatime;

		if (animCursor > defaultSpeed)
		{
			currentFrameIndex = (currentFrameIndex + 1) % framesCount;
			animCursor = 0;
		}

		frameToRender = frames[currentFrameIndex];
		
		// normalization
		frameToRender[0] /= texture_width;
		frameToRender[1] /= (texture_height);
		frameToRender[2] /= texture_width;
		frameToRender[3] /= (texture_height);

		
		frameToRender[1] = 0;
		frameToRender[3] = 1;
		std::vector<glm::vec2> uv;

		uv = {
			glm::vec2(frameToRender[0] + frameToRender[2], frameToRender[1]),
			glm::vec2(frameToRender[0] + frameToRender[2], frameToRender[1] + frameToRender[3]),
			glm::vec2(frameToRender[0], frameToRender[1] + frameToRender[3]),

			glm::vec2(frameToRender[0], frameToRender[1] + frameToRender[3]),
			glm::vec2(frameToRender[0],frameToRender[1]),	
			glm::vec2(frameToRender[0] + frameToRender[2], frameToRender[1]),
		};

		glBindVertexArray(rectangle.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, rectangle.UVO);
		void* gpubuffer = nullptr;
		gpubuffer = glMapBufferRange(GL_ARRAY_BUFFER, 0, 6 * sizeof(glm::vec2), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		memcpy(gpubuffer, uv.data(), 6 * sizeof(glm::vec2));
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	AnimationType Draw2DAnimation::getAnimationType() const
	{
		return animationType;
	}
}