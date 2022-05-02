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

	DrawArrayObjectWithTexture::DrawArrayObjectWithTexture(const gl_to& texture)
	{
		textureObject = texture;
	}

	void DrawArrayObjectWithTexture::render() const
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0 + textureObject.unit);
		glBindTexture(textureObject.target, textureObject.uId);

		glBindVertexArray(vertexObject.VAO);
		glDrawArrays(vertexObject.drawMode, 0, vertexObject.count);
		glBindVertexArray(0);

		glBindTexture(textureObject.target, 0);
		glActiveTexture(0);

		glDisable(GL_BLEND);
	}

	DrawElementTextured::DrawElementTextured(const gl_to& texture)
	{
		textureObject = texture;
	}

	void DrawElementTextured::render() const
	{

		textureObject.activeBind();

		glBindVertexArray(vertexObject.VAO);
		glDrawElements(vertexObject.drawMode, vertexObject.count, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		textureObject.unbind();
	}
}