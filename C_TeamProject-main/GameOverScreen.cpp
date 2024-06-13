#include <ncurses.h>
#include <cctype>

char showGameOverScreen()
{
    clear();
    int titleWidth = 90; // 게임 오버 메시지의 너비
    int messageWidth = 40; // 선택 메시지의 너비
    int screenWidth = COLS;
    int screenHeight = LINES;

    int startx = (screenWidth - titleWidth) / 2; // 화면 가운데 정렬
    int starty = (screenHeight - 12) / 2; // 화면 가운데 정렬, 높이를 12로 조정

    // 컬러 쌍 정의
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    // 테두리 그리기
    attron(COLOR_PAIR(1));
    for (int i = startx - 1; i <= startx + titleWidth; ++i) {
        mvprintw(starty - 1, i, "-");
        mvprintw(starty + 14, i, "-"); // 테두리 높이를 14으로 조정
    }
    for (int i = starty; i <= starty + 14; ++i) { // 테두리 높이를 14로 조정
        mvprintw(i, startx - 1, "|");
        mvprintw(i, startx + titleWidth, "|");
    }
    mvprintw(starty - 1, startx - 1, "+");
    mvprintw(starty - 1, startx + titleWidth, "+");
    mvprintw(starty + 12, startx - 1, "+");
    mvprintw(starty + 12, startx + titleWidth, "+");
    attroff(COLOR_PAIR(1));

    // 게임 오버 메시지
    attron(COLOR_PAIR(1));
    mvprintw(starty + 2, startx + 4, " #####     ###    ##   ##  #######            #####   ##   ##  #######  ######   ");
    mvprintw(starty + 3, startx + 4, "##   ##   ## ##   ### ###   ##   #           ### ###  ##   ##   ##   #   ##  ##  ");
    mvprintw(starty + 4, startx + 4, "##       ##   ##  #######   ##               ##   ##  ##   ##   ##       ##  ##  ");
    mvprintw(starty + 5, startx + 4, "## ####  ##   ##  ## # ##   ####             ##   ##   ## ##    ####     #####   ");
    mvprintw(starty + 6, startx + 4, "##   ##  #######  ##   ##   ##               ##   ##   ## ##    ##       ## ##   ");
    mvprintw(starty + 7, startx + 4, "##   ##  ##   ##  ##   ##   ##   #           ### ###    ###     ##   #   ## ##   ");
    mvprintw(starty + 8, startx + 4, " #####   ##   ##  ### ###  #######            #####     ###    #######  #### ##  ");
    attroff(COLOR_PAIR(1));

    // 선택 메시지
    int messageStartx = (screenWidth - messageWidth) / 2; // 메시지 중앙 정렬
    attron(COLOR_PAIR(2));
    mvprintw(starty + 11, messageStartx + 4, "Press 'R' to restart the game");
    mvprintw(starty + 12, messageStartx + 4, "Press 'E' to exit");
    attroff(COLOR_PAIR(2));

    refresh();
    char ch;
    do {
        ch = std::tolower(getch());
    } while (ch != 'r' && ch != 'e'); // 'r' 또는 'e'가 입력될 때까지 대기

    return ch; // 입력된 문자를 반환
}