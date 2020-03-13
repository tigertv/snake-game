#include "OpenGlGraphics.h"
//#include <GL/glut.h>
//#include <GLES3/gl3.h>
#include <GL/freeglut.h>

OpenGlGraphics* OpenGlGraphics::self = nullptr;

OpenGlGraphics::OpenGlGraphics() {
    OpenGlGraphics::self = this;
}

void OpenGlGraphics::init() {
    int argc = 1;
    screenWidth = 800;
    screenHeight = 640;
    char *argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Snake");
    glutKeyboardFunc(OpenGlGraphics::keyPressed);
    glutSpecialFunc(OpenGlGraphics::specialKeyPressed);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glViewport(0, 0, screenWidth / 2, screenHeight / 2);
    
    float k = 4.0 * 3;
    glOrtho(0.0, screenWidth / k, screenHeight / k, 0.0, -1.0, 1.0);
    
    // init keys
    keys[GLUT_KEY_RIGHT] = Key::RIGHT;
    keys[GLUT_KEY_LEFT] = Key::LEFT;
    keys[GLUT_KEY_UP] = Key::UP;
    keys[GLUT_KEY_DOWN] = Key::DOWN;
    keys['1'] = Key::KEY_1;
    keys[0x1b] = Key::ESC;
}

void OpenGlGraphics::exit() {
    
}

void OpenGlGraphics::render() {
    glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

    Snake* snake = game->getSnake();
    BorderFrame* borderFrame = game->getBorderFrame();
    Food* food = game->getFood();

    // render snake
    std::deque<SnakeBodyPart> *parts = snake->getBodyParts();
    SnakeBodyPart* part = &(*parts)[0];
    
    const int cellSize = 1;
    
    // render head
    u_int color = 0x00ff10;
    this->renderBox(part->point.x, part->point.y, cellSize, color);

    // render body
    color = 0x00ea3c;
    int size = parts->size();
    for (int i = 1; i < size; i++) {
        part = &(*parts)[i];
        this->renderBox(part->point.x, part->point.y, cellSize, color);
    }

    // render boarders
    color = 0x0f3842;
    for(int x = borderFrame->x; x <= borderFrame->x + borderFrame->width; x++) {
        this->renderBox(x, borderFrame->y, cellSize, color);
        this->renderBox(x, borderFrame->y + borderFrame->height, cellSize, color);
    }
    for(int y = borderFrame->y; y <= borderFrame->y + borderFrame->height; y++) {
        this->renderBox(borderFrame->x, y, cellSize, color);
        this->renderBox(borderFrame->x + borderFrame->width, y, cellSize, color);
    }

    // render food
    color = 0xff0000;
    this->renderBox(food->x, food->y, cellSize, color);
    
    glFlush();
}

void OpenGlGraphics::processInput() {
    glutMainLoopEvent();
}

void OpenGlGraphics::keyPressed(unsigned char key, int mouseX, int mouseY) {
    (void)mouseX;
    (void)mouseY;
    
    if(self->keys.count(key)) {
        self->game->keyPressed(self->keys[key]);
    }
}

//void OpenGlGraphics::specialKeyPressed(int key, [[maybe_unused]] int mouseX, [[maybe_unused]] int mouseY) {
void OpenGlGraphics::specialKeyPressed(int key, int mouseX, int mouseY) {
    (void)mouseX;
    (void)mouseY;
    //[&mouseX]{}();
    //[&mouseY]{}();

    if(self->keys.count(key)) {
        self->game->keyPressed(self->keys[key]);
    }
}

void OpenGlGraphics::renderBox(int x, int y, int cellSize, u_int color) {
    float red = ((color >> 16) & 0xff) / 255.0f;
    float green = ((color >> 8) & 0xff) / 255.0f;
    float blue = (color & 0xff) / 255.0f;

    glColor3f(red, green, blue);
    
    /*
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + cellSize, y);
    glVertex2f(x + cellSize, y + cellSize);
    glVertex2f(x, y + cellSize);
    glEnd();
    //*/

    glRectf(x, y, x + cellSize, y + cellSize);
}