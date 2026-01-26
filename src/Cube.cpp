#include "Cube.h"
#include <cstring>

Cube::Cube()
{
    float v[8][3] = {
        {-20,-20,-20},{20,-20,-20},{20,20,-20},{-20,20,-20},
        {-20,-20, 20},{20,-20, 20},{20,20, 20},{-20,20, 20}
    };
    memcpy(vertices, v, sizeof(v));

    unsigned int i[36] = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        0,4,7, 7,3,0,
        1,5,6, 6,2,1,
        3,2,6, 6,7,3,
        0,1,5, 5,4,0
    };
    memcpy(indices, i, sizeof(i));

    for (int j = 0; j < 8; j++)
    {
        colors[j][0] = (j & 1) ? 1.f : 0.f;
        colors[j][1] = (j & 2) ? 1.f : 0.f;
        colors[j][2] = (j & 4) ? 1.f : 0.f;
    }

    // LAB 11 – najprostsze współrzędne tekstur
    float t[8][2] = {
        {0,0},{1,0},{1,1},{0,1},
        {0,0},{1,0},{1,1},{0,1}
    };
    memcpy(texCoords, t, sizeof(t));
}

void Cube::draw()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
