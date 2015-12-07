#pragma once
#include "Vector3.h"

class Light  {

protected:

    Vector3f position;
    Vector3f intensities;

public:

    Light(Vector3f pos, Vector3f intense) {

        position = pos;
        intensities = intense;
    }

    Vector3f getPosition() {

        return position;
    }

    Vector3f getIntesities() {

        return intensities;
    }

    void setIntensities(Vector3f intensity) {

        intensities = intensity;
    }

    virtual void putLightInShader(Shader* shader, int index, bool array) {

        std::string tmp = "light";

        if(array)
            tmp += "s[" + std::to_string(index) + "]";

        std::string position = tmp + ".position";
        std::string intensity = tmp + ".intensities";

        shader->setUniformVector3(position.c_str(), this->position);
        shader->setUniformVector3(intensity.c_str(), this->intensities);
    }
};

class DirectionalLight : public Light{

private:

    float power;
    Vector3f direction;

public:

    DirectionalLight(Vector3f pos, Vector3f intense, float power, Vector3f direction) : Light(pos, intense) {

        this->power = power;
        this->direction = direction;
    }

    float getPower() {

        return power;
    }

    Vector3f getDirection() {

        Vector3f dir = position;
        dir.invert();

        return position;
    }

    void putLightInShader(Shader* shader, int index, bool array) {

        std::string tmp = "directionalLight";

        std::string intensity = tmp + ".intensities";
        std::string pos = tmp + ".position";


        shader->setUniformVector3(pos.c_str(), this->position);
        shader->setUniformVector3(intensity.c_str(), this->intensities);
        //shader->setUniformFloat(power.c_str(), this->power);

    }
};

