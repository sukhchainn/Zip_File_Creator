//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//
//
//		Authors:
//		Jefferson dos Santos Felix
//		Felipe Ruiz Peixoto <feliperuiz.sax.eletronic@gmail.com>
//      Hongli Lai <hongli@telekabel.nl>
//      tkorrovi <tkorrovi@altavista.net> on 2002/02/26.
//      Andrew Westcott <ajwestco@users.sourceforge.net>
//      Michal Molhanec <michal@molhanec.net>
//
//		With this file, you can make programs using the conio.h
//		100% compatible with Windows and Gnu/Linux systems.
//      This header needs the NCURSES library to work on linux (libncurses-dev).

#ifndef WIN32

#ifndef __CONIO_H
#define __CONIO_H

#ifndef __CURSES_H
#include <curses.h>
#endif

#ifndef __NCURSES_H
#include <ncurses.h>
#endif

#undef printf
#define printf printw

#undef scanf
#define scanf scanw

#undef getch

#define BLACK         0
#define RED           1
#define GREEN         2
#define BROWN         3
#define BLUE          4
#define MAGENTA       5
#define CYAN          6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTRED      9
#define LIGHTGREEN    10
#define YELLOW        11
#define LIGHTBLUE     12
#define LIGHTMAGENTA  13
#define LIGHTCYAN     14
#define WHITE         15

// Commands supported by this file, used for initialize.
void initconio();
int endconio(void);
int clrscr(void);
int clreol(void);
int textcolor(int color);
int textbackground(int color);
int getche(void);
int getch(void);
int wherex(void);
int wherey(void);
int gotoxy(int x, int y);
int newline(void);
int textcr, backcr; // Used to close the ncurses, if textcr == backcr

short cur_pair, cur_bold;
int initialized = 0;

void initconio()
{
  short f, b, p;
  initscr();
  start_color();
  //cbreak();
  //noecho();
  p = 1;
  for(f = 0; f < 8; f++)
    for(b = 0; b < 8; b++, p++)
      init_pair(p, f, b);
  cur_pair = 57;
  cur_bold = 0;
  color_set(cur_pair, NULL);
  attroff(A_BOLD);
  initialized = 1;
}

int endconio(void)
{
  if(initialized == 0) initconio();
  echo();
  endwin();
  initialized == 0;
  return 0;
}

int clrscr(void)
{
  if(initialized == 0) initconio();
  else if(textcr==backcr) endconio();
  bkgdset(COLOR_PAIR(cur_pair));
  if(cur_bold == 0)
    attroff(A_BOLD);
  else
    attron(A_BOLD);
  clear();
  return 0;
}

int clreol(void)
{
  if(initialized == 0) initconio();
  int cur_x, x, y, maxx;
  color_set(cur_pair, NULL);
  getmaxyx(stdscr, y, maxx);
  cur_x = wherex();
  gotoxy(1, wherey());
  for(x = 1; x <= maxx; x++)
    printw(" ");
  gotoxy(cur_x, wherey() - 1);
  return 0;
}

int textcolor(int color)
{
  if(initialized == 0) initconio();
  short x, y, f, b, p = 1;
  pair_content(cur_pair, &f, &b);
  for(x = 0; x < 8; x++)
    for(y = 0; y < 8; y++, p++)
      if((x == (color%8))&&(y == b))
        cur_pair = p;
  color_set(cur_pair, NULL);
  if(color >= 8)
    cur_bold = 1;
  if(cur_bold == 0)
    attroff(A_BOLD);
  else
    attron(A_BOLD);
  return 0;
}

int textbackground(int color)
{
  if(initialized == 0) initconio();
  short x, y, f, b, p = 1;
  pair_content(cur_pair, &f, &b);
  for(x = 0; x < 8; x++)
    for(y = 0; y < 8; y++, p++)
      if((x == f)&&(y == (color%8)))
        cur_pair = p;
  color_set(cur_pair, NULL);
  return 0;
}

int getche(void)
{
  if(initialized == 0) initconio();
  int c;
  echo();
  c = wgetch(stdscr);
  return c;
}

int getch(void)
{
  if(initialized == 0) initconio();
  int c;
  noecho();
  c = wgetch(stdscr);
  return c;
}

int wherex(void)
{
  if(initialized == 0) initconio();
  int x, y;
  getyx(stdscr, y, x);
  return x + 1;
}

int wherey(void)
{
  if(initialized == 0) initconio();
  int x, y;
  getyx(stdscr, y, x);
  return y + 1;
}

int gotoxy(int x, int y)
{
  if(initialized == 0) initconio();
  move(y - 1, x - 1);
  return 0;
}

int newline(void)
{
  if(initialized == 0) initconio();
  gotoxy(1, wherey() + 1);
  return 0;
}

#endif

//		How to use:
//		Copy this file to the folder of your source codes, or to the
//		library directories of your system.
//
//		See in your source code the line: #include <conio.h>, and change it
//		to: #include "conio.h", if this file is in the directory of your
//		source codes.
//
//		Before start using the functions of the conio.h, be sure you was
//		initialized it, because some commands need it to work. To initialize
//		you can use the commands listed in the line 57-68 of this file.
//		To end the program, make the text color == background color, and
//		use the clrscr() function.
//		If you start your program with printf() or scanw() for example,
//		will make a segmentation fault. It is a little bug.
//
//		If your program is making errors, try to use the initconio(); function
//		on the begin of the program, and endconio(); function to end it, when
//		using this file.
//
//		If it stills making errors, go to the support pages below:
//		http://www.vivaolinux.com.br/script/Conio.h-para-Linux-%28Nova-versao%29

#endif
#ifdef WIN32

#ifndef _CONIO2_H_
#define _CONIO2_H_

#include <conio.h>
#ifdef UNICODE
    #include <windows.h>    // we need wchar_t
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Colors which you can use in your application.
 */
typedef enum
{
    BLACK,          /**< black color */
    BLUE,           /**< blue color */
    GREEN,          /**< green color */
    CYAN,           /**< cyan color */
    RED,            /**< red color */
    MAGENTA,        /**< magenta color */
    BROWN,          /**< brown color */
    LIGHTGRAY,      /**< light gray color */
    DARKGRAY,       /**< dark gray color */
    LIGHTBLUE,      /**< light blue color */
    LIGHTGREEN,     /**< light green color */
    LIGHTCYAN,      /**< light cyan color */
    LIGHTRED,       /**< light red color */
    LIGHTMAGENTA,   /**< light magenta color */
    YELLOW,         /**< yellow color */
    WHITE           /**< white color */
} COLORS;

/*@{*/
/**
 * This defines enables you to use all MinGW conio.h functions without
 * underscore.
 */
#define cgets   _cgets
#define cprintf _cprintf
#define cputs   _cputs
#define cscanf  _cscanf

#ifdef UNICODE
    #define cgetws   _cgetws
    #define getwch   _getwch
    #define getwche  _getwche
    #define putwch   _putwch
    #define ungetwch _ungetwch
    #define cputws   _cputws
    #define cwprintf _cwprintf
    #define cwscanf  _cwscanf
#endif
/*@}*/

/**
 * Define alias for _conio_gettext.
 * If you want to use gettext function from some other library
 * (e.g. GNU gettext) you have to define _CONIO_NO_GETTEXT_ so you won't get
 * name conflict.
 */
#ifndef _CONIO_NO_GETTEXT_
  #define gettext _conio_gettext
#endif

#define ScreenClear clrscr

/**
 * @anchor cursortypes
 * @name Cursor types
 * Predefined cursor types. */
/*@{*/
#define _NOCURSOR 0         /**< no cursor */
#define _SOLIDCURSOR 100    /**< cursor filling whole cell */
#define _NORMALCURSOR 20    /**< cursor filling 20 percent of cell height */
/*@}*/

/**
 * Structure holding information about screen.
 * @see gettextinfo
 * @see inittextinfo
 */
struct text_info {
    unsigned char curx;          /**< cursor coordinate x */
    unsigned char cury;          /**< cursor coordinate y */
    unsigned short attribute;    /**< current text attribute */
    unsigned short normattr;     /**< original value of text attribute after
                                      start of the application. If you don't
                                      called the <TT>inittextinfo</TT> on the
                                      beginning of the application, this always
                                      will be black background and light gray
                                      foreground */
    unsigned char screenwidth;   /**< screen width */
    unsigned char screenheight;  /**< screen height */
};

/**
 * Structure used by gettext/puttext.
 * @see _conio_gettext
 * @see puttext
 */
struct char_info {
#ifdef UNICODE
    wchar_t letter;        /**< character value */
#else
    char letter;           /**< character value */
#endif
    unsigned short attr;   /**< attribute value */
};

/**
 * Returns information of the screen.
 * @see text_info
 */
void gettextinfo (struct text_info * info);

/**
 * Call this if you need real value of normattr attribute in the text_info
 * structure.
 * @see text_info
 */
void inittextinfo (void);

/**
 * Clears rest of the line from cursor position to the end of line without
 * moving the cursor.
 */
void clreol (void);

/**
 * Clears whole screen.
 */
void clrscr (void);

/**
 * Delete the current line (line on which is cursor) and then moves all lines
 * below one line up. Lines below the line are moved one line up.
 */
void delline (void);

/**
 * Insert blank line at the cursor position.
 * Original content of the line and content of lines below moves one line down.
 * The last line is deleted.
 */
void insline (void);

/**
 * Gets text from the screen. If you haven't defined <TT>_CONIO_NO_GETTEXT_</TT>
 * prior to including <TT>conio2.h</TT> you can use this function also under
 * the <TT>gettext</TT> name.
 * @see char_info
 * @see puttext
 * @param left Left coordinate of the rectangle, inclusive, starting from 1.
 * @param top Top coordinate of the rectangle, inclusive, starting from 1.
 * @param right Right coordinate of the rectangle, inclusive, starting from 1.
 * @param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
 * @param buf You have to pass buffer of size
 * <TT>(right - left + 1) * (bottom - top + 1) * sizeof(char_info)</TT>.
 */
void _conio_gettext (int left, int top, int right, int bottom,
                     struct char_info * buf);

/**
 * Puts text back to the screen.
 * @see char_info
 * @see _conio_gettext
 * @param left Left coordinate of the rectangle, inclusive, starting from 1.
 * @param top Top coordinate of the rectangle, inclusive, starting from 1.
 * @param right Right coordinate of the rectangle, inclusive, starting from 1.
 * @param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
 * @param buf You have to pass buffer of size
 * <TT>(right - left + 1) * (bottom - top + 1) * sizeof(char_info)</TT>.
 */
void puttext (int left, int top, int right, int bottom, struct char_info * buf);

/**
 * Copies text.
 * @param left Left coordinate of the rectangle, inclusive, starting from 1.
 * @param top Top coordinate of the rectangle, inclusive, starting from 1.
 * @param right Right coordinate of the rectangle, inclusive, starting from 1.
 * @param bottom Bottom coordinate of the rectangle, inclusive, starting from 1.
 * @param destleft Left coordinate of the destination rectangle.
 * @param desttop Top coordinate of the destination rectangle.
 */
void movetext (int left, int top, int right, int bottom, int destleft,
              int desttop);

/**
 * Moves cursor to the specified position.
 * @param x horizontal position
 * @param y vertical position
 */
void gotoxy(int x, int y);

/**
 * Puts string at the specified position.
 * @param x horizontal position
 * @param y vertical position
 * @param str string
 */
void cputsxy (int x, int y, char * str);

/**
 * Puts char at the specified position.
 * @param x horizontal position
 * @param y vertical position
 * @param ch char
 */
void putchxy (int x, int y, char ch);

/**
 * Sets the cursor type.
 * @see @ref cursortypes
 * @param type cursor type, under Win32 it is height of the cursor in percents
 */
void _setcursortype (int type);

/**
 * Sets attribute of text.
 * @param _attr new text attribute
 */
void textattr (int _attr);

/**
 * Sets text attribute back to value it had after program start.
 * It uses text_info's normattr value.
 * @see text_info
 */
void normvideo (void);

/**
 * Sets text background color.
 * @see COLORS
 * @param color new background color
 */
void textbackground (int color);

/**
 * Sets text foreground color.
 * @see COLORS
 * @param color new foreground color
 */
void textcolor (int color);

/**
 * Reads the cursor X position.
 * @returns cursor X position
 */
int wherex (void);

/**
 * Reads the cursor Y position.
 * @returns cursor Y position
 */
int wherey (void);

/**
 * Reads password. This function behaves like cgets.
 *
 * @see cgets
 * @param prompt prompt which will be displayed to user
 * @param str string for the password. <TT>str[0]</TT> have to contain
 * length of the <TT>str</TT> - 3
 * @returns <TT>&str[2]</TT>, the password will be stored in <TT>str</TT>
 * beginning at <TT>str[2]</TT>, in <TT>str[1]</TT> will be length of the
 * string without <TT>\\0</TT>, at <TT>str[2 + str[1]]</TT> will be \\0.
 */
char * getpass (const char * prompt, char * str);

/**
 * Makes foreground colors light.
 * If the current foreground color is less than <TT>DARKGRAY</TT> adds
 * 8 to the its value making dark colors light.
 * @see COLORS
 * @see lowvideo
 */
void highvideo (void);

/**
 * Makes foreground colors dark.
 * If the current foreground color is higher than <TT>LIGHTGRAY</TT> substracts
 * 8 from its value making light colors dark.
 * @see COLORS
 * @see highvideo
 */
void lowvideo (void);

/*@{*/
/** Link with libmsvcr70.a or libmsvcr70d.a or libmsvcr71.a or libmsvcr71d.a
 *  if you want any of these functions. */
#ifdef UNICODE
_CRTIMP wchar_t * __cdecl         _cgetws(wchar_t *);
_CRTIMP unsigned short __cdecl    _getwch(void);
_CRTIMP unsigned short __cdecl    _getwche(void);
_CRTIMP unsigned short __cdecl    _putwch(wchar_t);
_CRTIMP unsigned short __cdecl    _ungetwch(unsigned short);
_CRTIMP int __cdecl               _cputws(const wchar_t *);
_CRTIMP int __cdecl               _cwprintf(const wchar_t *, ...);
_CRTIMP int __cdecl               _cwscanf(const wchar_t *, ...);
#endif
/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* _CONIO2_H_ */

#endif
