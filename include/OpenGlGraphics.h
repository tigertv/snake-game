#ifndef OPEN_GL_GRAPHICS_H_
#define OPEN_GL_GRAPHICS_H_

#include <GL/gl.h> 
#include "AbstractGraphics.h"
class OpenGlGraphics;

class OpenGlGraphics : public AbstractGraphics {
private:
    static void keyPressed(unsigned char key, int mouseX, int mouseY);
    static void specialKeyPressed(int key, int mouseX, int mouseY);
    void renderBox(int x, int y, int cellSize, u_int color);
    static OpenGlGraphics* self;
    int screenWidth;
    int screenHeight;

public:
    OpenGlGraphics();
    void init() override;
    void exit() override;
    void render() override;
    void processInput() override;
};

#endif