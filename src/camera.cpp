#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
    pos = position;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUp = up;
    this->pitch = pitch;
    this->yaw = yaw;

    fov = FOV_DEF;
    moveSpeed = SPEED;
    sens = SENS;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(pos, pos + front, up);
}

glm::vec3 Camera::get_pos()
{
    return pos;
}

glm::vec3 Camera::get_front()
{
    return front;
}

float Camera::FOV() const
{
    return fov;
}

void Camera::processKeyboard(CamMove direction, float deltaTime)
{
    float vel = moveSpeed * deltaTime;
    if (direction == CamMove::FORWARD)
    {
        pos += front * vel;
    }
    if (direction == CamMove::BACKWARD)
    {
        pos -= front * vel;
    }
    if (direction == CamMove::LEFT)
    {
        pos -= right * vel;
    }
    if (direction == CamMove::RIGHT)
    {
        pos += right * vel;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
    const float sens = 0.1;
    xoffset *= sens;
    yoffset *= sens;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.9)
    {
        pitch = 89.9;
    }
    if (pitch < -89.9)
    {
        pitch = -89.9;
    }
    updateCameraVectors();
}

void Camera::processScroll(float yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1)
    {
        fov = 1;
    }
    if (fov > 45)
    {
        fov = 45;
    }
}

void Camera::updateCameraVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
