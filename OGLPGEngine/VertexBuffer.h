//VertexBuffer.h
#ifndef VERTEXBUFFER_H_INCLUDED
#define VERTEXBUFFER_H_INCLUDED

#include "Buffer.h"
#include <vector>

//A class to store the information used in each vertex attribute
class VertexAttributeInformation
{
public:
	VertexAttributeInformation(GLuint index, GLint size, GLenum type, GLboolean normalized, unsigned int stride, unsigned int offset);
	~VertexAttributeInformation();

	const GLuint GetIndex()const;
	const GLint GetSize()const;
	const GLenum GetType()const;
	const GLboolean GetIsNormalized()const;
	const unsigned int GetStride()const;
	GLvoid* GetOffset() const;

private:
	GLuint index;
	GLint size;
	GLenum type;
	GLboolean normalized;
	unsigned int stride;
	unsigned int offset;
};


class VertexBuffer: public Buffer
{
public:
	VertexBuffer(BufferType bufferType, BufferUsage bufferUsage,unsigned int elementSize, unsigned int numberOfElements, GLvoid* bufferData);
	virtual ~VertexBuffer();

	void AddVertexAttributeInformation(GLuint index, GLint size, GLenum type, GLboolean normalized,unsigned int stride, unsigned int offset);
	const VertexAttributeInformation& GetVertexAttributeInformation(int index)const;
	int GetNumberOfAttributeInfos()const;
private:
	std::vector<VertexAttributeInformation> _vertexAttributeInfo;
};
#endif //VERTEXBUFFER_H_INCLUDED