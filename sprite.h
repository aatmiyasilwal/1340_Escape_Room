// sprite.h

#ifndef _SPRITE_H_
#define _SPRITE_H_

class sprite
{
    public:
        sprite(WINDOW * win, int y, int x, std::string c, std::string i);

        void mvup();
        void mvdown();
        void mvleft();
        void mvright();
        void pickitem();
        void dropitem();
        int getmv();
        char display();
        int xLoc;
        int yLoc;
        char command;
        std::string item;

    private:
        int xMax, yMax;
        std::string character;
        WINDOW * curwin;
};

sprite::sprite(WINDOW * win, int y, int x, std::string c, std::string i) {
    curwin = win;
    yLoc = y;
    xLoc = x;
    getmaxyx(curwin, yMax, xMax);
    keypad(curwin, true);
    character = c;
    item = i;
}

void sprite::mvup() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc -= 1;
    if(yLoc < 1)
        yLoc = 1;
}

void sprite::mvdown() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc += 1;
    if(yLoc > yMax-2) // border is -1
        yLoc = yMax-2;
}

void sprite::mvleft() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc -= 1;
    if(xLoc < 1)
        xLoc = 1;
}

void sprite::mvright() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc += 1;
    if(xLoc > xMax-3)
        xLoc = xMax-3;
}

void sprite::pickitem() {
    if (item == " ") {
        switch (xLoc)
        {
            case 15:
                item = "🍞";
                break;
            case 20:
                item = "🧀";
                break;
            case 25:
                item = "🥓";
                break;
            case 30:
                item = "🥑";
                break;
            case 35:
                item = "🍆";
                break;
        }
    }
}

void sprite::dropitem() {
    if (yLoc == 1 && xLoc < 10) { //kitchen loc
        command = 'k';
    }
    else if (yLoc == 13 && xLoc == 1) { //bin loc
        command = 'b';
    }
    else if (xLoc == 47) { //server loc
        command = 's';    }
}

int sprite::getmv() {
    int choice = wgetch(curwin);
    switch(choice)
    {
        case KEY_UP:
            mvup();
            break;
        case KEY_DOWN:
            mvdown();
            break;
        case KEY_LEFT:
            mvleft();
            break;
        case KEY_RIGHT:
            mvright();
            break;
        case 'a':
            pickitem();
            break;
       
        case 'd':
            dropitem();
            break;
            
        default:
            break;
    }
    return choice;
}

char sprite::display() {
    mvwprintw(curwin, yLoc, xLoc, character.c_str());
    return command;
}

#endif
