#pragma once

#include <math.h>

struct point {
    int x, y;
};

void mat_mul_vec(float a[3][3], float b[3][1], float result[3][1]) {
    for(int i = 0; i < 3; i++) {
        float res = 0;
        for(int k = 0; k < 3; k++) {
            res += (a[i][k] * b[k][0]);
        }
        result[i][0] = res;
    }
}

void translate(struct point in, struct point t_factor, struct point *out) {
    float x = in.x, y = in.y;
    float tx = t_factor.x, ty = t_factor.y;
    
    float m[3][3] = {{1, 0, tx},
                     {0, 1, ty},
                     {0, 0, 1 }};
    
    float v[3][1] = {{x}, {y}, {1}};

    float output[3][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
}

void rotate(struct point in, double angle, struct point *out) {
    float x = in.x, y = in.y;
    
    double theta = angle * M_PI / 180.0f;

    float m[3][3] = {{cos(theta), -1*sin(theta), 0},
                     {sin(theta),    cos(theta), 0},
                     {         0,             0, 1}};
    
    float v[3][1] = {{x}, {y}, {1}};

    float output[3][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
}

void scale(struct point in, struct point s_factor, struct point *out) {
    float x = in.x, y = in.y;
    float sx = s_factor.x, sy = s_factor.y;
    
    float m[3][3] = {{sx,  0, 0},
                     { 0, sy, 0},
                     { 0,  0, 1}};
    
    float v[3][1] = {{x}, {y}, {1}};

    float output[3][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
}

void reflectx(struct point in, struct point *out) {
    float x = in.x, y = in.y;
    
    float m[3][3] = {{1,  0, 0},
                     {0, -1, 0},
                     {0,  0, 1}};
    
    float v[3][1] = {{x}, {y}, {1}};

    float output[3][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
}

void reflecty(struct point in, struct point *out) {
    float x = in.x, y = in.y;
    
    float m[3][3] = {{-1, 0, 0},
                     { 0, 1, 0},
                     { 0, 0, 1}};
    
    float v[3][1] = {{x}, {y}, {1}};

    float output[3][1];
    mat_mul_vec(m, v, output);
    
    out->x = output[0][0];
    out->y = output[1][0];
}