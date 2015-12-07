#pragma once
#include "Vector3.h"

class Mat4 {

public:

    float matrix[16];

    Mat4() {

        matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0f;
        matrix[1] = matrix[2] = matrix[3] = 0.0f;
        matrix[4] = matrix[6] = matrix[7] = 0.0f;
        matrix[8] = matrix[9] = matrix[11] = 0.0f;
        matrix[12] = matrix[13] = matrix[14] = 0.0f;
    }

    Mat4(float* mat4) {

        for (int i = 0; i < 16; ++i) {

            matrix[i] = mat4[i];
        }
    }

    Mat4 operator* (Mat4& mat4) {

        Mat4 returnMatrix;
        unsigned short x;

        for (unsigned short i = 0; i < 4; ++i) {

            for (unsigned short j = 0; j < 4; ++j) {

                x = (unsigned short)4 * i;
                returnMatrix.matrix[x + j] = (matrix[x] * mat4.matrix[j]) + (matrix[x + 1] * mat4.matrix[j + 4]) + (matrix[x + 2] * mat4.matrix[8 + j]) + (matrix[x + 3] * mat4.matrix[12 + j]);
            }
        }

        return returnMatrix;
    }
};
