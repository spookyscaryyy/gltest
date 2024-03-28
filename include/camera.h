#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CamMove
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
    private:
    static constexpr float YAW = -90;
    static constexpr float PITCH = 0;
    static constexpr float SPEED = 2.5;
    static constexpr float SENS = 0.1;
    static constexpr float FOV_DEF = 45;

    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float fov;

    float pitch;
    float yaw;
    float moveSpeed;
    float sens;
    void updateCameraVectors();

    public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    glm::mat4 getViewMatrix();
    float FOV() const;
    void processKeyboard(CamMove direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    void processScroll(float yoffset);
    glm::vec3 get_pos();
    glm::vec3 get_front();
};

#endif
