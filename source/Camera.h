#pragma once
#include <math.h>
#include "Vector3.h"
#include "EventManager.h"

class Camera : public EventObject {

private:

    Vector3f position,
            top,
            side,
            front;
    float sensibility;
    float hAngle;
    float vAngle;
    float viewMatrix[4][4];
    float matrix[16];

    void buildMatrix() {
        viewMatrix[0][0] = side.x;
        viewMatrix[1][0] = side.y;
        viewMatrix[2][0] = side.z;

        viewMatrix[0][1] = top.x;
        viewMatrix[1][1] = top.y;
        viewMatrix[2][1] = top.z;

        viewMatrix[0][2] = -front.x;
        viewMatrix[1][2] = -front.y;
        viewMatrix[2][2] = -front.z;

        glLoadIdentity();
        glMultMatrixf(&viewMatrix[0][0]);
        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
        glTranslatef(-position.x, -position.y, -position.z);
        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    }

    void buildVectors() {
        if (vAngle > 89)
            vAngle = 89;
        if (vAngle < -89)
            vAngle = -89;

        if (hAngle < 0)
            hAngle += 360;
        if (hAngle > 360)
            hAngle -= 360;

        float vAngleRadian = vAngle * M_PI / 180;
        float hAngleRadian = hAngle * M_PI / 180;
        float cos_vAngle = cos(vAngleRadian);

        front.x = cos_vAngle * sin(hAngleRadian);
        front.y = sin(vAngleRadian);
        front.z = cos_vAngle * cos(hAngleRadian);

        front.normalize();

        top = Vector3f(0, 1, 0);

        side = front.crossProduct(top);
        side.normalize();

        top = side.crossProduct(front);
        top.normalize();

        buildMatrix();
    }

public:

    Camera(Vector3f position , Vector3f top) {
        this->position = position;
        this->top = top;
        viewMatrix[3][0] = viewMatrix[3][1] = viewMatrix[3][2] = viewMatrix[0][3]= viewMatrix[1][3] = viewMatrix[2][3] = 0;
        viewMatrix[3][3] = 1;

        this->sensibility = 0.15;

        this->hAngle = 0;
        this->vAngle = 0;

        buildVectors();

        EventManager::getInstance().addObject(this);

        SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_ShowCursor(SDL_DISABLE);
    }

    Camera() : Camera(Vector3f(), Vector3f()) {}

    ~Camera() {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        SDL_ShowCursor(SDL_ENABLE);
    }

    bool reactToEvent(SDL_Event* event) {

        Vector3f vitesse = Vector3f();
        Vector3f frontTmp = front;
        Vector3f sideTmp = side;

        frontTmp.y = 0;
        sideTmp.y = 0;

        switch (event->type) {
            case SDL_MOUSEMOTION:
                hAngle -= event->motion.xrel * sensibility;
                vAngle -= event->motion.yrel * sensibility;
                buildVectors();
                break;
            case SDL_KEYDOWN:

                switch (event->key.keysym.scancode) {

                    case SDL_SCANCODE_S:

                        vitesse = frontTmp * .08;
                        vitesse.invert();
                        position += vitesse;
                        buildVectors();
                        break;

                    case SDL_SCANCODE_W:

                        vitesse = frontTmp * .08;
                        position += vitesse;
                        buildVectors();
                        break;

                    case SDL_SCANCODE_A:

                        vitesse = sideTmp * .08;
                        vitesse.invert();
                        position += vitesse;
                        buildVectors();
                        break;

                    case SDL_SCANCODE_D:

                        vitesse = sideTmp * .08;
                        position += vitesse;
                        buildVectors();
                        break;
                }

                break;
        }

        return false;
    }

    float* getMatrix() {

        return matrix;
    }

    Vector3f getPosition() {

        return position;
    }
};