#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;

string arrName[7] = {
    "ooo        ooooo  oooooooooooo  .oooooo..o   .oooooo..o  ",
    "`88.       .888'  `888'     `8  d8P'    `Y8  d8P'    `Y8 ",
    " 888b     d'888    888          Y88bo.       Y88bo.      ",
    " 8 Y88. .P  888    888oooo8      `'Y8888o.    `'Y8888o.  ",
    " 8  `888'   888    888    '          `'Y88b       `'Y88b ",
    " 8    Y     888    888       o  oo     .d8P  oo     .d8P ",
    "o8o        o888o  o888ooooood8  8''88888P'   8''88888P'  "};

string arrName2[9] = {
    "ooo        ooooo                                                                                                  .       .oooooo..o                          .                              ",
    "`88.       .888'                                                                                                .o8      d8P'    `Y8                        .o8                              ",
    " 888b     d'888   .oooo.   ooo. .oo.    .oooo.    .oooooooo  .ooooo.  ooo. .oo.  .oo.    .ooooo.  ooo. .oo.   .o888oo    Y88bo.      oooo    ooo  .oooo.o .o888oo  .ooooo.  ooo. .oo.  .oo.  ",
    " 8 Y88. .P  888  `P  )88b  `888P'Y88b  `P  )88b  888' `88b  d88' `88b `888P'Y88bP'Y88b  d88' `88b `888P'Y88b    888       `'Y8888o.   `88.  .8'  d88(  '8   888   d88' `88b `888P'Y88bP'Y88b ",
    " 8  `888'   888   .oP'888   888   888   .oP'888  888   888  888ooo888  888   888   888  888ooo888  888   888    888           `'Y88b   `88..8'   `'Y88b.    888   888ooo888  888   888   888 ",
    " 8    Y     888  d8(  888   888   888  d8(  888  `88bod8P'  888    .o  888   888   888  888    .o  888   888    888 .    oo     .d8P    `888'    o.  )88b   888 . 888    .o  888   888   888 ",
    "o8o        o888o `Y888''8o o888o o888o `Y888''8o `8oooooo.  `Y8bod8P' o888o o888o o888o `Y8bod8P' o888o o888o   '888'    8''88888P'      .8'     8''888P'   '888' `Y8bod8P' o888o o888o o888o",
    "                                                 d'     YD                                                                           .o..P'                                                  ",
    "                                                 'Y88888P'                                                                           `Y8P'                                                   "};

void GetDesktopResolution(int &horizontal, int &vertical)
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

void setScreenSizeRes()
{
    int horizontal = 0;
    int vertical = 0;
    GetDesktopResolution(horizontal, vertical);
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, horizontal, vertical, TRUE);
}

void maxWin()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
}

void fullScreenWin()
{
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

void disRestoreDown()
{
    HWND hwnd = GetConsoleWindow();
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

float screenBuffer()
{
    float size;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        cerr << "Cannot determine console size." << endl;
    }
    else
    {
        size = csbi.srWindow.Right - csbi.srWindow.Left;
    }
    return size;
}

int setwVal(string x)
{
    float size1;
    size1 = (screenBuffer() + x.length()) / 2;
    if (x == "Invalit choice, Try Again!")
    {
        return size1 + (x.length() / 2.8);
    }
    else
    {
        return size1;
    }
}

int len = screenBuffer() / 1.25;
char *dots = new char[len];
string xtring;

string colorize(const string &s, const string &color)
{
    return "\033[" + color + "m" + s + "\033[0m";
}

void setDots()
{
    for (int i = 0; i < len; i++)
    {
        dots[i] = '`';
    }
}

string convertToString(char *a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}

void spaces(int x)
{
    for (int j = 0; j < x; j++)
    {
        cout << endl;
    }
}

void getCurrentTimeDateDay(int &day, int &month, int &year, int &hours, int &minutes, int &seconds, string &dayName)
{
    // Get the current time
    time_t currentTime = time(nullptr);

    // Convert the time to a tm struct
    tm *localTime = localtime(&currentTime);

    // Get the current date
    day = localTime->tm_mday;
    month = localTime->tm_mon + 1;
    year = localTime->tm_year + 1900;

    // Get the current time
    hours = localTime->tm_hour;
    minutes = localTime->tm_min;
    seconds = localTime->tm_sec;

    // Get the current day of the week
    int dayOfWeek = localTime->tm_wday;
    switch (dayOfWeek)
    {
    case 0:
        dayName = "Sunday";
        break;
    case 1:
        dayName = "Monday";
        break;
    case 2:
        dayName = "Tuesday";
        break;
    case 3:
        dayName = "Wednesday";
        break;
    case 4:
        dayName = "Thursday";
        break;
    case 5:
        dayName = "Friday";
        break;
    case 6:
        dayName = "Saturday";
        break;
    default:
        break;
    }
}

void displayTime()
{
    int day, month, year, hours, minutes, seconds;
    string dayName;
    // Call the function to get the current date, time and day
    getCurrentTimeDateDay(day, month, year, hours, minutes, seconds, dayName);
    // Output the current date and time
    stringstream ss;
    ss << hours << ":" << minutes << " | " << dayName << " | " << day << "/" << month << "/" << year;
    string final_str = ss.str();
    cout << setw(setwVal(final_str)) << final_str << endl;
}

void heading()
{
    for (int i = 0; i < 7; i++)
    {
        cout << setw(setwVal(arrName[0])) << arrName[i] << endl;
    }
    for (int j = 0; j < 9; j++)
    {
        cout << setw(setwVal(arrName2[0])) << arrName2[j] << endl;
    }

    spaces(1);
    displayTime();
    spaces(1);
    setDots();
    xtring = convertToString(dots, len);
    spaces(3);
    cout << setw(setwVal(xtring)) << xtring;
    spaces(2);
}

int setwVal1(string x)
{
    // return x.length() + 30;
    // return x.length() + (len - x.length());
    // cout<<((len/2) - setwVal(x)) + x.length();
    // return ((len/2) - setwVal(x)) + x.length();
    // return (len/2) + x.length();

    // return x.length() + setwVal(xtring)/2;
    // int val = len - x.length();
    // return setwVal(val);
    return setwVal(xtring.erase(xtring.length(), x.length())) - (len - x.length());
}

string getCurrentMonth()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%B", &tstruct);
    return buf;
}