#include "Camera2D.h"


Camera2D::Camera2D(): 
	_position(0,0), 
	_cameraMatrix(1.0f),
	_scale(1.0f),
	_needsMatrixUpdate(true), 
	_orthoMatrix(1.0f),
	_screenWidth(500),_screenHeight(500)
{

}

glm::vec2 Camera2D::convertScreenToWorl(glm::vec2 screenScoords) {
	screenScoords.y = _screenHeight - screenScoords.y;
	screenScoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
	screenScoords /= _scale;
	screenScoords += _position;
	return screenScoords;
}

bool Camera2D::isBoxInView(const glm::vec2& position, const glm::vec2& dimension) {
	glm::vec2 scaleScreenDimension = glm::vec2(_screenWidth, _screenHeight) / _scale;
	const float MIN_DISTANCE_X = dimension.x / 2.0f + scaleScreenDimension.x;
	const float MIN_DISTANCE_Y = dimension.y / 2.0f + scaleScreenDimension.y;

	glm::vec2 centerPos = _position + dimension / 2.0f;
	glm::vec2 centerCameraPos = _position + glm::vec2(scaleScreenDimension.x / 2.0f, 
														scaleScreenDimension.y / 2.0f);
	glm::vec2 distVec = centerPos - centerCameraPos;
	float xdepth = MIN_DISTANCE_X - abs(distVec.x);
	float ydepth = MIN_DISTANCE_Y - abs(distVec.y);

	if (xdepth > 0 || ydepth > 0) {
		return true;
	}
}

void Camera2D::init(int screenWidth, int screenHeight) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera2D::update() {
	if(_needsMatrixUpdate){
		/*glm::vec3 translate(-_position.x, -_position.y, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);
		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(_cameraMatrix,scale);
		*/

		glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight/2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);

		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		_needsMatrixUpdate = false;
	}
}

Camera2D::~Camera2D()
{
}
