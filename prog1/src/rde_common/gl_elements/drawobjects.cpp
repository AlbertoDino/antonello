#include <rdecommon.h>
#include "gltypes.h"
#include "renderingelement.h"
#include "drawobjects.h"

namespace oglElements {

	void DrawArrayObject::render() const
	{
		glBindVertexArray(vertexObject.VAO);
		glDrawArrays(vertexObject.drawMode, 0, vertexObject.count);
		glBindVertexArray(0);
	}

	void DrawElementObject::render() const
	{
		glBindVertexArray(vertexObject.VAO);
		glDrawElements(vertexObject.drawMode, vertexObject.count, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}


	DrawElementTextured::DrawElementTextured(const gl_to& texture)
	{
		textureObject = texture;
	}

	void DrawElementTextured::render() const
	{
		glActiveTexture(GL_TEXTURE0 + textureObject.unit);
		glBindTexture(textureObject.target, textureObject.uId);

		glBindVertexArray(vertexObject.VAO);
		glDrawElements(vertexObject.drawMode, vertexObject.count, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		glBindTexture(textureObject.target, 0);
		glActiveTexture(0);
	}

}