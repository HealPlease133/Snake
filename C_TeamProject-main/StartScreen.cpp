#include <ncurses.h>
#include <cctype>

char showStartScreen()
{
    clear();
    int titleWidth = 65; // 게임 제목의 너비
    int messageWidth = 28; // 게임 시작 메시지의 너비
    int screenWidth = COLS;
    int screenHeight = LINES;

    int startx = (screenWidth - titleWidth) / 2; // 화면 가운데 정렬
    int starty = (screenHeight - 10) / 2; // 화면 가운데 정렬

    // 컬러 쌍 정의
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);

    // 테두리 그리기
    attron(COLOR_PAIR(1));
    for (int i = startx - 1; i <= startx + titleWidth; ++i) {
        mvprintw(starty - 1, i, "-");
        mvprintw(starty + 10, i, "-");
    }
    for (int i = starty - 1; i <= starty + 10; ++i) {
        mvprintw(i, startx - 1, "|");
        mvprintw(i, startx + titleWidth, "|");
    }
    mvprintw(starty - 1, startx - 1, "+");
    mvprintw(starty - 1, startx + titleWidth, "+");
    mvprintw(starty + 10, startx - 1, "+");
    mvprintw(starty + 10, startx + titleWidth, "+");
    attroff(COLOR_PAIR(1));

    // 게임 제목
    attron(COLOR_PAIR(2));
    mvprintw(starty, startx, " _____  _   _   ___   _   __ _____   _____   ___  ___  ___ _____ ");
    mvprintw(starty + 1, startx, "/  ___|| \\ | | / _ \\ | | / /|  ___| |  __ \\ / _ \\ |  \\/  ||  ___|");
    mvprintw(starty + 2, startx, "\\ `--. |  \\| |/ /_\\ \\| |/ / | |__   | |  \\// /_\\ \\| .  . || |__  ");
    mvprintw(starty + 3, startx, " `--. \\| . ` ||  _  ||    \\ |  __|  | | __ |  _  || |\\/| ||  __| ");
    mvprintw(starty + 4, startx, "/\\__/ /| |\\  || | | || |\\  \\| |___  | |_\\ \\| | | || |  | || |___ ");
    mvprintw(starty + 5, startx, "\\____/ \\_| \\_/\\_| |_/\\_| \\_/\\____/   \\____/\\_| |_/\\_|  |_/\\____/ ");
    attroff(COLOR_PAIR(2));

    // 게임 시작 메시지
    int messageStartx = (screenWidth - messageWidth) / 2; // 메시지 중앙 정렬
    attron(COLOR_PAIR(1));
    mvprintw(starty + 7, messageStartx, "Press 'S' to start the game");
    mvprintw(starty + 8, messageStartx, "Press 'E' to exit");
    attroff(COLOR_PAIR(1));

    refresh();
    char ch;
    do {
        ch = std::tolower(getch());
    } while (ch != 's' && ch != 'e'); // 's' 또는 'e'가 입력될 때까지 대기

    return ch; // 입력된 문자를 반환
}