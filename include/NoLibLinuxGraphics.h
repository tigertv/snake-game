#ifndef NO_LIB_LINUX_GRAPHICS_H_
#define NO_LIB_LINUX_GRAPHICS_H_

#include "AbstractGraphics.h"

class NoLibLinuxGraphics : public AbstractGraphics {
private:
    void renderChar(int x, int y, char ch);
    bool kbhit();
    
public:
    NoLibLinuxGraphics();
    void init() override;
    void exit() override;
    void render() override;
    void processInput() override;
};

#endif