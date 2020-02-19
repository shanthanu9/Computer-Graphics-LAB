#pragma once

#include <math.h>

struct point {
    float x, y, z;
};

void mat_mul_vec(float a[4][4], float b[4][1], float result[4][1]) {
    for(int i = 0; i < 4; i++) {
        float res = 0;
        for(int k = 0; k < 4; k++) {
            res += (a[i][k] * b[k][0]);
        }
        result[i][0] = res;
    }
}

void translate(struct point in, struct point t_factor, struct point *out) {
    float x = in.x, y = in.y, z = in.z;
    float tx = t_factor.x, ty = t_factor.y, tz = t_factor.z;
    
    float m[4][4] = {{1, 0, 0, tx},
                     {0, 1, 0, ty},
                     {0, 0, 1, tz},
                     {0, 0, 0, 0 }};
    
    float v[4][1] = {{x}, {y}, {z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
    out->z = output[2][0];
}

void rotatex(struct point in, double angle, struct point *out) {
    float x = in.x, y = in.y, z = in.z;
    
    double theta = angle * M_PI / 180.0f;

    float m[4][4] = {{1,          0,           0, 0},
                     {0, cos(theta), -sin(theta), 0},
                     {0, sin(theta),  cos(theta), 0},
                     {0,          0,           0, 1}};
    
    float v[4][1] = {{x}, {y}, {z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
    out->z = output[2][0];
}

void rotatey(struct point in, double angle, struct point *out) {
    float x = in.x, y = in.y, z = in.z;
    
    double theta = angle * M_PI / 180.0f;

    float m[4][4] = {{ cos(theta), 0, sin(theta), 0},
                     {          0, 1,          0, 0},
                     {-sin(theta), 0, cos(theta), 0},
                     {          0, 0,          0, 0}};
    
    float v[4][1] = {{x}, {y}, {z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
    out->z = output[2][0];
}

void rotatez(struct point in, double angle, struct point *out) {
    float x = in.x, y = in.y, z = in.z;
    
    double theta = angle * M_PI / 180.0f;

    float m[4][4] = {{cos(theta), -sin(theta), 0, 0},
                     {sin(theta),  cos(theta), 0, 0},
                     {         0,           0, 1, 0},
                     {         0,           0, 0, 0}};
    
    float v[4][1] = {{x}, {y}, {z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
    out->z = output[2][0];
}

void scale(struct point in, struct point s_factor, struct point *out) {
    float x = in.x, y = in.y, z = in.z;
    float sx = s_factor.x, sy = s_factor.y, sz = s_factor.z;
    
    float m[4][4] = {{sx,  0,  0, 0},
                     { 0, sy,  0, 0},
                     { 0,  0, sz, 0},
                     { 0,  0,  0, 1}};
    
    float v[4][1] = {{x}, {y}, {z}, {1}};

    float output[4][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
    out->z = output[2][0];
}

// void reflectx(struct point in, struct point *out) {
//     float x = in.x, y = in.y;
    
//     float m[3][3] = {{1,  0, 0},
//                      {0, -1, 0},
//                      {0,  0, 1}};
    
//     float v[3][1] = {{x}, {y}, {1}};

//     float output[3][1];
//     mat_mul_vec(m, v, output);
    
//     out->x = output[0][0];
//     out->y = output[1][0];
// }

// void reflecty(struct point in, struct point *out) {
//     float x = in.x, y = in.y;
    
//     float m[3][3] = {{-1, 0, 0},
//                      { 0, 1, 0},
//                      { 0, 0, 1}};
    
//     float v[3][1] = {{x}, {y}, {1}};

//     float output[3][1];
//     mat_mul_vec(m, v, output);
    
//     out->x = output[0][0];
//     out->y = output[1][0];
// }