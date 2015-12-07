#pragma once

class ShadowMap {

private:

    GLuint frameBuffer;
    GLuint ID;
    Shader* shader;

    Mat4 projection;
    Mat4 camera;
    Mat4 transformation;

public:

    ShadowMap(Shader* shader) {

        this->shader = shader;

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 1600, 1600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ID, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Error : Shadow Map initialisation has failed";

    }

    GLuint getID() {

        return ID;
    }

    void use() {

        glCullFace(GL_FRONT);

        glViewport(0,0,1600,1600);

        shader->use();

        glBindTexture(GL_TEXTURE_2D, ID);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        glDrawBuffer(GL_NONE);
    }

    void stopUsing() {

        glCullFace(GL_BACK);

        glViewport(0,0, 1920, 1080);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        shader->stopUse();

        glDrawBuffer(GL_DRAW_BUFFER);
    }

    void sendToShader() {

        Mat4 depthMatrix = transformation * camera * projection;
        shader->setUniformMatrix4x4("depthMatrix", 1, GL_FALSE, depthMatrix.matrix);
    }

    void setProjection(Mat4 projection) {

        this->projection = projection;
    }

    void setCamera(Mat4 camera) {

        this->camera = camera;
    }

    void setTranformation(Mat4 transform) {

        transformation = transform;
    }

    Mat4 getMatrices() {

        return transformation * camera * projection;
    }

    Mat4 getVPMatrix () {

        return camera * projection;
    }

    Shader* getShader() {

        return shader;
    }
};
