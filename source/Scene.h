#pragma once
#include "SceneObject.h"
#include "Light.h"
#include "ShadowMap.h"
#include "Engine.h"

class Scene {

private:

    std::list<SceneObject*> objects;
    std::list<Light*> lights;

    DirectionalLight* light;

    Shader* shader;
    ShadowMap* shadowMap;

    Mat4 biasMatrix;

public:

    Scene(Shader* shader, ShadowMap* shadowMap, DirectionalLight* light) {

        this->shader = shader;

        biasMatrix.matrix[0] = 0.5f;
        biasMatrix.matrix[1] = 0.0f;
        biasMatrix.matrix[2] = 0.0f;
        biasMatrix.matrix[3] = 0.0f;

        biasMatrix.matrix[4] = 0.0f;
        biasMatrix.matrix[5] = 0.5f;
        biasMatrix.matrix[6] = 0.0f;
        biasMatrix.matrix[7] = 0.0f;

        biasMatrix.matrix[8] = 0.0f;
        biasMatrix.matrix[9] = 0.0f;
        biasMatrix.matrix[10] = 0.5f;
        biasMatrix.matrix[11] = 0.0f;

        biasMatrix.matrix[12] = 0.5f;
        biasMatrix.matrix[13] = 0.5f;
        biasMatrix.matrix[14] = 0.5f;
        biasMatrix.matrix[15] = 1.0f;

        this->shadowMap = shadowMap;
        this->light = light;

    }

    void addObject(SceneObject* object) {

        if (std::find(objects.begin(), objects.end(), object) == objects.end())
            objects.push_back(object);
    }

    void addLight(Light* light) {

        if (std::find(lights.begin(), lights.end(), light) == lights.end())
            lights.push_back(light);
    }

    Shader* getShader() {

        return shader;
    }

    void show(Mat4& camera, Mat4& projection) {

        shadowMap->use();

        shadowMap->setProjection(Math::ortho(-10,10,-10,10,-10,20));
        shadowMap->setCamera(Math::lookAt(light->getDirection(), Vector3f(), Vector3f(0, 1, 0)));

        for (auto object = objects.begin(); object != objects.end(); ++object) {

            shadowMap->setTranformation((*object)->getTransformationMatrix());
            shadowMap->sendToShader();
            (*object)->show(true);
        }

        shadowMap->stopUsing();

        shader->use();

        //shader->setUniformInt("nbrLight", (int) lights.size());

        int it = 0;

        /*for (auto item : lights)
            item->putLightInShader(shader, it++, true);*/

        light->putLightInShader(shader, 0, false);


        shader->setUniformInt("shadowMap", 1);
        shader->setUniformInt("tex", 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, shadowMap->getID());

        Mat4 MVPMatrix;
        Mat4 biasMVPMatrix;
        Mat4 VPMatrix = shadowMap->getVPMatrix();

        for (auto object : objects) {

            MVPMatrix = object->getTransformationMatrix() * camera * projection;
            biasMVPMatrix = object->getTransformationMatrix() * VPMatrix * biasMatrix;

            shader->setUniformMatrix4x4("MVPMatrix", 1, GL_FALSE, MVPMatrix.matrix);
            shader->setUniformMatrix4x4("transform", 1, GL_FALSE, object->getTransformationMatrix().matrix);
            shader->setUniformMatrix4x4("camera", 1, GL_FALSE, camera.matrix);
            shader->setUniformMatrix4x4("biasMVPMatrix", 1, GL_FALSE, biasMVPMatrix.matrix);

            object->show(false);
        }

        shader->stopUse();
    }
};