#include <iostream>
#include <vector>
#include "tgaimage.h"
#include "model.h"

const int width = 800;
const int heigth = 800;

const TGAColor red = TGAColor(255, 0, 0, 255);
TGAImage image(width, heigth, TGAImage::RGB);

void line(TGAImage &image,TGAColor color,int x1, int y1, int x2, int y2) {

    bool steep = false;
    if (abs(y2 - y1) > abs(x2 - x1)) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }
    if (x2 < x1) {
        std::swap(x2, x1);
        std::swap(y2, y1);
    }
    int eps = 0;
    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int yi = 1;
    int y = y1;
    if (y2 < y1) {
        yi = -1;
    }
    for (int x = x1; x <= x2;x++) {
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
        eps += dy;
        if ((eps << 1) >= dx) {
            y += yi;
            eps -= dx;
        }
    }
}

int main()
{

    Model* model = new Model("./obj/african_head.obj");

    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);

            int x1 = (v0.x + 1.0) * width / 2.0;
            int y1 = (v0.y + 1.0) * heigth / 2.0f;
            int x2 = (v1.x + 1.0) * width / 2.0;
            int y2 = (v1.y + 1.0) * heigth / 2.0f;

            line(image, red, x1, y1, x2, y2);
        }
    }
    image.flip_vertically();
    image.write_tga_file("./result.tga");
    return 0;
}

