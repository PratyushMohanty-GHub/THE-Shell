#include "../global.h"
#include "input.h"

char get_input()
{
    // disableRawMode();
    struct termios raw_sec;

    tcgetattr(STDIN_FILENO, &raw_sec);
    raw_sec.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw_sec);

    int count;
    ioctl(0, FIONREAD, &count);

    tcgetattr(0, &raw_sec);
    raw_sec.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &raw_sec);
    // disableRawMode();

    return (count != 0) ? getchar() : '\0';
}
void die(const char *s)
{
    perror(s);
    exit(1);
}
void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}
char *read_cmdline_input()
{
    char *input = (char *)calloc(MAX_STR_LEN, sizeof(char));
    print_in_cyan;

    char ch;
    int input_len = 0;
    setbuf(stdout, NULL);
    enableRawMode();
    memset(input, '\0', 100);

    int pt = 0;
    int is_arrow = false;
    while (read(STDIN_FILENO, &ch, 1) == 1)
    {
        if (iscntrl(ch))
        {
            if (ch == 10)
                break;
            else if (ch == 27)
            {
                char buf[3];
                buf[2] = 0;
                if (read(STDIN_FILENO, buf, 2) == 2)
                { // length of escape code
                    if (buf[1] == 65)
                    {
                        is_arrow = true;
                        if (last_seen_idx == 20)
                        {
                            up_arrow_cmd();
                        }
                        else
                        {
                            for (int i = 0; i < strlen(history_list[last_seen_idx]); i++)
                            {
                                printf("\b \b");
                            }
                            up_arrow_cmd();
                        }
                    }
                }
            }
            else if (ch == 127)
            { // backspace
                if (pt > 0)
                {
                    if (input[pt - 1] == 9)
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            printf("\b");
                        }
                    }
                    input[--pt] = '\0';
                    printf("\b \b");
                }
            }
            else if (ch == 9)
            { // TAB character
                for (int i = 0; i < 8; i++)
                { // TABS should be 8 spaces
                    printf(" ");
                    input[pt++] = ' ';
                }
            }
            else if (ch == 4)
            {
                // If Ctrl + D is pressed.
                handle_ctrlD();
            }
            else
            {
                printf("%d\n", ch);
            }
        }
        else
        {
            input[pt++] = ch;
            printf("%c", ch);
        }
    }
    disableRawMode();

    printf("\n");
    // CHANGES MADE HERE START
    if (is_arrow == true)
    {
        strcat(up_last_input, input);
        strcpy(input, up_last_input);
        // printf("%s\n", input);
    }
    // CHANGES MADE HERE END
    print_in_white;
    return input;
}