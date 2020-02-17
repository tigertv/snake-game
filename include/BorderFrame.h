#ifndef BORDER_FRAME_H_
#define BORDER_FRAME_H_

class BorderFrame {
public:
    int width;
    int height;
    int x;
    int y;
    BorderFrame(int x, int y, int width, int height);
    virtual ~BorderFrame() {}
    void update();
};

#endif
