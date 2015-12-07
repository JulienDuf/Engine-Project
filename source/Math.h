#pragma once
#include "Mat4.h"

namespace Math {

    Mat4 lookAt(Vector3f position ,Vector3f target, Vector3f up) {

        Vector3f side, forward;
        Mat4 returnMatrix;
        Mat4 transformationMatrix;

        glLoadIdentity();
        glTranslatef(-position.x, -position.y, -position.z);

        glGetFloatv(GL_MODELVIEW_MATRIX, transformationMatrix.matrix);

        forward = target - position;
        forward.normalize();

        side = forward.crossProduct(up);
        side.normalize();

        up = side.crossProduct(forward);


        returnMatrix.matrix[3] = returnMatrix.matrix[7] = returnMatrix.matrix[11] = returnMatrix.matrix[12] = returnMatrix.matrix[13] = returnMatrix.matrix[14] = 0;
        returnMatrix.matrix[15] = 1;

        returnMatrix.matrix[0] = side.x;
        returnMatrix.matrix[4] = side.y;
        returnMatrix.matrix[8] = side.z;

        returnMatrix.matrix[1] = up.x;
        returnMatrix.matrix[5] = up.y;
        returnMatrix.matrix[9] = up.z;

        returnMatrix.matrix[2] = -forward.x;
        returnMatrix.matrix[6] = -forward.y;
        returnMatrix.matrix[10] = -forward.z;

        returnMatrix = transformationMatrix * returnMatrix;

        return returnMatrix;
    }

    Mat4 ortho(double left, double right, double bottom, double top, double nearValue, double farValue) {

        Mat4 returnMatrix;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(left, right, bottom, top, nearValue, farValue);

        glGetFloatv(GL_PROJECTION_MATRIX, returnMatrix.matrix);
        glMatrixMode(GL_MODELVIEW);

        return returnMatrix;
    }

    Mat4 perspective(double left, double right, double bottom, double top, double nearValue, double farValue) {

        Mat4 returnMatrix;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(left, right, bottom, top, nearValue, farValue);

        glGetFloatv(GL_PROJECTION_MATRIX, returnMatrix.matrix);
        glMatrixMode(GL_MODELVIEW);

        return returnMatrix;
    }
}
