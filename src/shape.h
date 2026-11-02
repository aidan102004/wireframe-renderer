#pragma once
#include <vector>
#include <cmath>
#include "point.h"


struct Shape {
    std::vector<Point> vertices;
    std::vector<std::pair<int,int>> edges;
};

inline Shape make_cube() {
    return {
        {   
            { 0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
            { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f},
            { 0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f},
            { 0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}
        },
        {   
            {0,1}, {0,2}, {1,3}, {2,3},
            {4,5}, {4,6}, {5,7}, {6,7},
            {0,4}, {1,5}, {2,6}, {3,7}
        }
    };
}

inline Shape make_triangle() {
    return {
        { {0.0f, 0.5f}, {-0.5f, -0.5f}, {0.5f, -0.5f} },
        { {0,1}, {1,2}, {2,0} }
    };
}

inline Shape make_polygon(int n, float radius = 0.5f) {
    Shape s;
    for (int i = 0; i < n; ++i) {
        float a = 2.0f * 3.14159265f * i / n;
        s.vertices.push_back({radius * std::cos(a), radius * std::sin(a)});
        s.edges.push_back({i, (i + 1) % n});
    }
    return s;
}

inline Shape make_pyramid() {
    return {
        {
            { 0.5f, -0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f},   
            {-0.5f, -0.5f, -0.5f}, { 0.5f, -0.5f, -0.5f},  
            { 0.0f,  0.5f,  0.0f}                           
        },
        {
            {0,1}, {1,2}, {2,3}, {3,0},  
            {0,4}, {1,4}, {2,4}, {3,4}  
        }
    };
}

inline Shape make_tetrahedron() {
    return {
        {
            { 0.5f,  0.5f,  0.5f}, { 0.5f, -0.5f, -0.5f},
            {-0.5f,  0.5f, -0.5f}, {-0.5f, -0.5f,  0.5f}
        },
        { {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3} }
    };
}

inline Shape make_octahedron() {
    const float r = 0.7f;
    return {
        {
            { r, 0, 0}, {-r, 0, 0},    //0, 1
            { 0, r, 0}, { 0,-r, 0},    //2, 3
            { 0, 0, r}, { 0, 0,-r}     //4, 5
        },
        {
            {0,2}, {0,3}, {0,4}, {0,5},
            {1,2}, {1,3}, {1,4}, {1,5},
            {2,4}, {2,5}, {3,4}, {3,5}
        }
    };
}

inline Shape make_triangular_prism() {
    return {
        {
            { 0.0f,  0.5f,  0.5f}, {-0.5f, -0.5f,  0.5f}, {0.5f, -0.5f,  0.5f},  //front
            { 0.0f,  0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}   //back
        },
        {
            {0,1}, {1,2}, {2,0},
            {3,4}, {4,5}, {5,3},
            {0,3}, {1,4}, {2,5}
        }
    };
}

inline Shape make_icosahedron() {
    const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;   //golden ratio
    const float s = 0.3f;                              //scale to fit the view
    const Point raw[12] = {
        {-1,  t, 0}, { 1,  t, 0}, {-1, -t, 0}, { 1, -t, 0},
        { 0, -1, t}, { 0,  1, t}, { 0, -1, -t}, { 0,  1, -t},
        { t,  0, -1}, { t,  0, 1}, {-t,  0, -1}, {-t,  0, 1}
    };

    Shape shape;
    for (const Point& p : raw)
        shape.vertices.push_back({p.x * s, p.y * s, p.z * s});

    for (int i = 0; i < 12; ++i) {
        for (int j = i + 1; j < 12; ++j) {
            float dx = raw[i].x - raw[j].x;
            float dy = raw[i].y - raw[j].y;
            float dz = raw[i].z - raw[j].z;
            if (std::fabs(dx*dx + dy*dy + dz*dz - 4.0f) < 0.01f)
                shape.edges.push_back({i, j});
        }
    }
    return shape;
}