// sprite.h

#ifndef _SPRITE_H_
#define _SPRITE_H_

struct pos {
    int yLoc;
    int xLoc;
    
    pos(int y, int x) {
        yLoc = y;
        xLoc = x;
    }
};

bool operator< (pos a, pos b){
    if(a.xLoc == b.xLoc)
        return a.yLoc < b.yLoc;
    else
        return a.xLoc< b.xLoc;
}

class sprite
{
    public:
        sprite(WINDOW * win, int y, int x, std::string c, std::string i, std::map<pos,bool> o);

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
        std::map<pos,bool> obstacle;
        WINDOW * curwin;
};

sprite::sprite(WINDOW * win, int y, int x, std::string c, std::string i, std::map<pos,bool> o) {
    curwin = win;
    yLoc = y;
    xLoc = x;
    getmaxyx(curwin, yMax, xMax);
    keypad(curwin, true);
    character = c;
    item = i;
    obstacle = o;
}

void sprite::mvup() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc -= 1;
    if (obstacle[pos(yLoc, xLoc)])
        yLoc += 1;
    if(yLoc < 1)
        yLoc = 1;
}

void sprite::mvdown() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    yLoc += 1;
    if (obstacle[pos(yLoc, xLoc)])
        yLoc -= 1;
    if(yLoc > yMax-2) // border is -1
        yLoc = yMax-2;
}

void sprite::mvleft() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc -= 2;
    if (obstacle[pos(yLoc, xLoc)])
        xLoc += 2;
    if(xLoc < 1)
        xLoc = 1;
}

void sprite::mvright() {
    mvwaddch(curwin, yLoc, xLoc, ' ');
    xLoc += 2;
    if (obstacle[pos(yLoc, xLoc)])
        xLoc -= 2;
    if(xLoc > xMax-3)
        xLoc = xMax-3;
}

void sprite::pickitem() {
    command = 'p';
    if (item == " ") {
        switch (xLoc)
        {
            case 15:
                item = "🍞";
                break;
            case 19:
                item = "🧀";
                break;
            case 23:
                item = "🍖";
                break;
            case 27:
                item = "🥑";
                break;
            case 31:
                item = "🍚";
                break;
            case 35:
                item = "🥒";
                break;
            case 39:
                item = "🍅";
                break;
        }
    }
}

void sprite::dropitem() {
    if (item != " ") {
        if (yLoc == 1 && xLoc < 10) { //kitchen loc
            command = 'k';
        }
        else if ((yLoc == 13 || yLoc == 12) && xLoc == 1) { //bin loc
            command = 'b';
        }
//        else if (xLoc == 47) { //server loc
//            command = 's';
//        }
    }
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
