#pragma once
#include <math.h>
#include "Vecteur3.h"
#include "EventManager.h"

class Camera : public EventObject{
protected:
    Vector3d position,
            cible,
            haut,
            cote,
            devant;
    double sensibilite;
    double hAngle;
    double vAngle;
    float matriceVue[16];

    void construireMatrice() {
        matriceVue[0] = cote.x;
        matriceVue[1] = cote.y;
        matriceVue[2] = cote.z;

        matriceVue[4] = haut.x;
        matriceVue[5] = haut.y;
        matriceVue[6] = haut.z;

        matriceVue[8] = -devant.x;
        matriceVue[9] = -devant.y;
        matriceVue[10] = -devant.z;
    }


    void calculerVecteurs() {
        if (vAngle > 89)
            vAngle = 89;
        if (vAngle < -89)
            vAngle = -89;

        if (hAngle < 0)
            hAngle += 360;
        if (hAngle > 360)
            hAngle -= 360;

        double vAngleRadian = vAngle * M_PI / 180;
        double hAngleRadian = hAngle * M_PI / 180;
        double cos_vAngle = cos(vAngleRadian);

        devant.x = cos_vAngle * sin(hAngleRadian);
        devant.y = sin(vAngleRadian);
        devant.z = cos_vAngle * cos(hAngleRadian);

        devant.normaliser();

        haut = Vector3d(0, 1, 0);

        cote = devant.produitVectoriel(haut);
        cote.normaliser();

        haut = cote.produitVectoriel(devant);
        haut.normaliser();

        construireMatrice();
    }

    void defCible(Vector3d& cible) {
        this->cible = cible;
        construireMatrice();
    }

    void defHaut(Vector3d& haut) {
        this->haut = haut;
        construireMatrice();
    }

    Vector3d obtCible() { return cible; }

public:

    Camera(Vector3d position, Vector3d target, Vector3d top) {
        this->position = position;
        this->cible = target;
        this->haut = top;
        matriceVue[3] = matriceVue[7] = matriceVue[11] = matriceVue[12] = matriceVue[13] = matriceVue[14] = 0;
        matriceVue[15] = 1;
        construireMatrice();

        this->sensibilite = 0.15;

        this->hAngle = 0;
        this->vAngle = 0;

        calculerVecteurs();

        EventManager::getInstance().addObject(this);

        //SDL_SetRelativeMouseMode(SDL_TRUE);
        //SDL_ShowCursor(SDL_DISABLE);
    }

    Camera() : Camera(Vector3d(), Vector3d(), Vector3d()) {}

    ~Camera() {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        SDL_ShowCursor(SDL_ENABLE);
    }

    bool reactToEvent(SDL_Event* event) {

        if (event->type == SDL_MOUSEMOTION) {
            hAngle -= event->motion.xrel * sensibilite;
            vAngle -= event->motion.yrel * sensibilite;
            calculerVecteurs();
            return true;
        }
        return false;
    }

    float* getMatrix() {

        return matriceVue;
    }
};