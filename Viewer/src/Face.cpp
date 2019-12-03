#include "Face.h"

Face::Face(std::istream& issLine)
{
	vertexIndices =  { 0, 0, 0 };
	normalIndices =  { 0, 0, 0 };
	textureIndices = { 0, 0, 0 };

	char c;
	for (int i = 0; i < 3; i++)
	{
		issLine >> std::ws >> vertexIndices.at(i) >> std::ws;

		if (issLine.peek() != '/')
		{
			continue;
		}

		issLine >> c >> std::ws;

		if (issLine.peek() == '/')
		{
			issLine >> c >> std::ws >> normalIndices.at(i);
			continue;
		}
		else
		{
			issLine >> textureIndices.at(i);
		}

		if (issLine.peek() != '/')
		{
			continue;
		}

		issLine >> c >> normalIndices.at(i);
	}
}

Face::Face(std::vector<int> vertexIndices1)
{
	vertexIndices = { 0, 0, 0 };
	normalIndices = { 0, 0, 0 };
	textureIndices = { 0, 0, 0 };

	this->vertexIndices = vertexIndices1;
}

Face::~Face()
{

}

const int Face::getVertexIndex(int index)
{
	return vertexIndices[index];
}

const int Face::getNormalIndex(int index)
{
	return normalIndices[index];
}

const int Face::getTextureIndex(int index)
{
	return textureIndices[index];
}

const std::vector<int> Face::GetVertices() {
	return this->vertexIndices;
}