// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

#pragma region Public methods
// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	mat3 part1 = mat3(cos(glm::radians(degrees)));

	mat3 part2 = glm::transpose(mat3(pow(axis.x, 2), axis.x * axis.y, axis.x * axis.z,
									 axis.x * axis.y, pow(axis.y, 2), axis.y * axis.z,
									 axis.x * axis.z, axis.y * axis.z, pow(axis.z, 2)))
		* (1.0f - cos(glm::radians(degrees)));

	mat3 part3 = glm::transpose(mat3(0, -axis.z, axis.y,
									 axis.z, 0, -axis.x,
									 -axis.y, axis.x, 0))
		* sin(glm::radians(degrees));

	return part1 + part2 + part3;
}

void Transform::left(float degrees, vec3& eye, vec3& up)
{
	vec3 axis = glm::normalize(up);
	eye = rotate(degrees, axis) * eye;
	up = rotate(degrees, axis) * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
	vec3 axis = glm::normalize(glm::cross(eye, up));

	eye = rotate(degrees, axis) * eye;
	up = rotate(degrees, axis) * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up)
{
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 rot = glm::transpose(mat4(u.x, u.y, u.z, 0,
								   v.x, v.y, v.z, 0,
								   w.x, w.y, w.z, 0,
								   0, 0, 0, 1));

	mat4 trans = mat4();
	trans[3][0] = -eye.x;
	trans[3][1] = -eye.y;
	trans[3][2] = -eye.z;

	return rot * trans;
}
#pragma endregion

Transform::Transform()
{

}

Transform::~Transform()
{

}
