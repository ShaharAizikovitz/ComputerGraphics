#pragma once
#include <glm/glm.hpp>
#include <string>
#include "MeshModel.h"

/*
 * Utils class.
 * This class is consisted of static helper methods that can have many clients across the code.
 */
class Utils
{
public:
	glm::vec4 Homogeneous3to4(const glm::vec3 source);
	glm::vec3 Homogeneous4to3(const glm::vec4 source);
	glm::mat4 TranslationMatrix(const glm::vec3 translation);
	glm::mat4 scaleMat(const glm::vec3 scale);
	glm::mat4 rotateMat(const glm::vec3 angle);
	glm::mat4 setFullTransformMat(const glm::vec3 translation, const glm::vec3 scale, const glm::vec3 angle, glm::vec3 center, bool isLocal);
	static Vertex VertexFromStream(std::istream& issLine);
	static glm::vec3 Vec3fFromStream(std::istream& issLine);
	static glm::vec2 Vec2fFromStream(std::istream& issLine);
	static MeshModel LoadMeshModel(const std::string& filePath);

	static void createGrid();

	static glm::vec4 Centeroid(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3); 

private:
	static std::string GetFileName(const std::string& filePath);
};
