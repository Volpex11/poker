#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <form.h>
#include <term.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
#define WIDTH 20
#define NCOLS 160
#define HEIGHT 20
#define NLINES 30
#define KEY_SPACE '\x20'
#define KEY_FRONTSLASH '\x2f'
#define KEY_BACKSLASH '\x5c'

using namespace std;

//in and out files
FILE* O = fopen("profiles", "w");
FILE* I = fopen("profiles", "r");
char buffer[200];

typedef struct _PANEL_DATA {
	int hide;	//TRUE if panel is hidden
	int x, y, w, h;
	char* label; 
	int label_color;
	PANEL *next;
}PANEL_DATA;

typedef struct _FIELD_DATA {
	char* user_data;	
	FIELD *next;
}FIELD_DATA;

const char *title_choices[5] = { 
	"Play",
	"Load Player Save",
	"New Player",
	"Edit Profile",
	"Exit",
};

const char *choices[5] = {
	"Raise",
	"Call",
	"Fold",
	"Save",
	"Exit",
};

int startx = 0;
int starty = 0;
int n_choices = ARRAY_SIZE(choices);
int n_choices_title = ARRAY_SIZE(title_choices);
int ch, rows, cols;
int choice = 0;
int scrnH, scrnW;

void win_border(WINDOW *win);
void func(char *name);	
void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char* label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, const char* str, chtype color);
void set_user_ptrs_panels(PANEL **panels, int n);

//main_menu
void print_mainmenu(WINDOW *menu_win, int highlight, int starty, int startx);
void report_choice(int mouse_x, int mouse_y, int *p_choice);

void init_ncurses() {	
	//Initialize curses
	initscr();
	start_color();
	cbreak();
	noecho();
}

void titlescreen(int scrnH, int scrnW);
void load_player_save();
void gameplay_view();
void game_options();
void edit_profile();
void new_player();

void load_player_save() {

}

void gameplay_view() {
	WINDOW *my_wins[3];
	PANEL  *my_panels[3];
	PANEL_DATA  *top;
	PANEL *stack_top;
	WINDOW *temp_win, *old_win;
	int newx, newy, neww, newh;
	int size = FALSE, move = FALSE;

	keypad(stdscr, TRUE);

	//Initialize all the colors
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	init_wins(my_wins, 3);

	//Attach a panel to each window			//Order is bottom up
	my_panels[0] = new_panel(my_wins[0]); 	//Push 0, order: stdscr-0
	my_panels[1] = new_panel(my_wins[1]); 	//Push 1, order: stdscr-0-1
	my_panels[2] = new_panel(my_wins[2]); 	//Push 2, order: stdscr-0-1-2

	set_user_ptrs_panels(my_panels, 3);
	//Update the stacking order. 2nd panel will be on top
	update_panels();

	//Show it on the screen
	attron(COLOR_PAIR(4));
	mvprintw(LINES - 3, 0, "Use 'm' for moving, 'r' for resizing");
	mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F1 to Exit)");
	attroff(COLOR_PAIR(4));
	doupdate();

	stack_top = my_panels[2];
	top = (PANEL_DATA *)panel_userptr(stack_top);
	newx = top->x;
	newy = top->y;
	neww = top->w;
	newh = top->h;
	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	case 9:		/* Tab */
			top = (PANEL_DATA *)panel_userptr(stack_top);
			top_panel(top->next);
			stack_top = top->next;
			top = (PANEL_DATA *)panel_userptr(stack_top);
			newx = top->x;
			newy = top->y;
			neww = top->w;
			newh = top->h;
			break;

			//if needed uncomment_out
			//=======================
			/*
			   case 'r':	// Re-Size
			   size = TRUE;
			   attron(COLOR_PAIR(4));
			   mvprintw(LINES - 4, 0, "Entered Resizing :Use Arrow Keys to resize and press <ENTER> to end resizing");
			   refresh();
			   attroff(COLOR_PAIR(4));
			   break;
			   case 'm':	//Move
			   attron(COLOR_PAIR(4));
			   mvprintw(LINES - 4, 0, "Entered Moving: Use Arrow Keys to Move and press <ENTER> to end moving");
			   refresh();
			   attroff(COLOR_PAIR(4));
			   move = TRUE;
			   break;
			   case KEY_LEFT:
			   if(size == TRUE)
			   {	--newx;
			   ++neww;
			   }
			   if(move == TRUE)
			   --newx;
			   break;
			   case KEY_RIGHT:
			   if(size == TRUE)
			   {	++newx;
			   --neww;
			   }
			   if(move == TRUE)
			   ++newx;
			   break;
			   case KEY_UP:
			   if(size == TRUE)
			   {	--newy;
			   ++newh;
			   }
			   if(move == TRUE)
			   --newy;
			   break;
			   case KEY_DOWN:
			   if(size == TRUE)
			   {	++newy;
			   --newh;
			   }
			   if(move == TRUE)
			   ++newy;
			   break;
			   case KEY_ENTER:	// Enter
			   move(LINES - 4, 0);
			   clrtoeol();
			   refresh();
			   if(size == TRUE)
			   {	old_win = panel_window(stack_top);
			   temp_win = newwin(newh, neww, newy, newx);
			   replace_panel(stack_top, temp_win);
			   win_show(temp_win, top->label, top->label_color); 
			   delwin(old_win);
			   size = FALSE;
			   }
			   if(move == TRUE)
			   {	move_panel(stack_top, newy, newx);
			   move = FALSE;
			   }
			   break;
			   */
		}
		attron(COLOR_PAIR(4));
		mvprintw(LINES - 3, 0, "Use 'm' for moving, 'r' for resizing");
		mvprintw(LINES - 2, 0, "Use tab to browse through the windows");
		attroff(COLOR_PAIR(4));
		refresh();	
		update_panels();
		doupdate();
	}
}

void game_options() {
	ITEM **my_items;
	MENU *my_menu;
	WINDOW *my_menu_win;
	int i;

	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);

	//Create items
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
		my_items[i] = new_item(choices[i], choices[i]);

	//Crate menu
	my_menu = new_menu((ITEM **)my_items);

	//Create the window to be associated with the menu
	my_menu_win = newwin(10, 40, 4, 4);
	keypad(my_menu_win, TRUE);

	//Set main window and sub window
	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

	//Set menu mark to the string " * "
	set_menu_mark(my_menu, " * ");

	//Print a border around the main window and print a title
	box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, 40, "Game Options", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);
	mvprintw(LINES - 2, 0, "F1 to exit");
	refresh();

	//Post the menu
	post_menu(my_menu);
	wrefresh(my_menu_win);

	while((ch = wgetch(my_menu_win)) != KEY_F(1)) {       
		switch(ch) {	
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
		}
		wrefresh(my_menu_win);
	}	

	//Unpost and free all the memory taken up
	unpost_menu(my_menu);
	free_menu(my_menu);
	for(i = 0; i < n_choices; ++i)
		free_item(my_items[i]);
}

void edit_profile() {
	fgets(buffer, 200, I);
	printf("%s", buffer);
}

void new_player() {
	FIELD *field[5];
	FORM  *my_form;
	WINDOW *my_form_win;
	WINDOW *my_form_dir;
	int rows, cols;
	keypad(stdscr, TRUE);

	//Initialize few color pairs
	init_pair(1, COLOR_RED, COLOR_WHITE);

	//Initialize the fields
	field[0] = new_field(1, 20, starty+2, startx+1, 0, 0);
	field[1] = new_field(1, 20, starty+5, startx+1, 0, 0);
	field[2] = new_field(5, 20, starty+8, startx+1, 0, 0);
	field[3] = new_field(5, 20, starty+14, startx+1, 0, 0);
	field[4] = NULL;
	
	//Set field options
	set_field_back(field[0], COLOR_PAIR(1));
	field_opts_off(field[0], O_AUTOSKIP); //Don't go to next field when this Field is filled up

	set_field_back(field[1], COLOR_PAIR(1)); 
	field_opts_off(field[1], O_AUTOSKIP);
	field_opts_off(field[1], O_PUBLIC);

	set_field_back(field[2], COLOR_PAIR(1));
	field_opts_off(field[2], O_AUTOSKIP);
	field_opts_off(field[2], O_WRAP);

	set_field_back(field[3], COLOR_PAIR(1)); 
	field_opts_off(field[3], O_AUTOSKIP);
	field_opts_off(field[3], O_WRAP);
	
	//Create the form and post it
	my_form = new_form(field);

	//Calculate the area required for the form
	scale_form(my_form, &rows, &cols);

	//Create the window to be associated with the form
	my_form_win = newwin(rows + 4, cols + 24, 4, 4);
	my_form_dir = newwin(10, 60, 4, 49);
	keypad(my_form_win, TRUE);

	//Set main window and sub window
	set_form_win(my_form, my_form_win);
	set_form_sub(my_form, derwin(my_form_win, rows, cols, 2, 23));
	
	//Print a border around the main window and print a title
	win_border(my_form_win);
	win_border(my_form_dir);
	print_in_middle(my_form_win, 1, 10, cols + 4, "New Profile", COLOR_PAIR(1));

	post_form(my_form);
	wrefresh(my_form_win);

	mvwprintw(my_form_dir, 2, 2, "%s", "Use Shift Tab to cycle through the fields");
	mvwprintw(my_form_dir, 4, 2, "%s", "Use Arrow keys to move the cursor around the fields");
	mvwprintw(my_form_dir, 6, 2, "%s", "Use Backspace to delete characters and");
	mvwprintw(my_form_dir, 7, 4, "%s", "Delete to clear a field and");
	mvwprintw(my_form_dir, 8, 4, "%s", "Space for spaces and Home when done");
	wrefresh(my_form_dir);
	
	mvprintw(7, 22, "Name: ");
	mvprintw(10, 18, "Password: ");
	mvprintw(13, 5, "Positive catch phrase: ");
	mvprintw(19, 5, "Negative catch phrase: ");
	refresh();

	//Loop through to get user requests
	while((ch = wgetch(my_form_win)) != KEY_F(1)) {	
		switch(ch) {
			case KEY_HOME:
				//fputs(field[0]* char*, O);
				//fclose(O);
				clear();
				titlescreen(scrnH, scrnW);
				break;
			case KEY_BACKSPACE:
				form_driver(my_form, REQ_LEFT_CHAR);
				form_driver(my_form, REQ_DEL_CHAR);
				break;
			case KEY_BTAB:
				//Go to next field
				form_driver(my_form, REQ_NEXT_FIELD);
				//Go to the end of the present buffer
				//Leaves nicely at the last character
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_DC: //delete key
				form_driver(my_form, REQ_CLR_FIELD);
				break;
			case KEY_SPACE:
				form_driver(my_form, REQ_RIGHT_CHAR);
				break;
			case KEY_DOWN:
				form_driver(my_form, REQ_UP_CHAR);
				break;
			case KEY_UP:
				form_driver(my_form, REQ_DOWN_CHAR);
				break;
			case KEY_LEFT:
				form_driver(my_form, REQ_LEFT_CHAR);
				break;
			case KEY_RIGHT:
				form_driver(my_form, REQ_RIGHT_CHAR);
				break;
			default:
				//If this is a normal character, it gets printed	
				form_driver(my_form, ch);
				break;
		}
	}

	//Unpost and free all the memory taken up
	unpost_form(my_form);
	free_form(my_form);
	for(int i = 0; i < 5; ++i)
		free_field(field[i]);


}

void titlescreen(int scrnH, int scrnW) {

	//Try to put the window in the middle of screen
	startx = (scrnW/2);
	starty = (scrnH/2);

	ITEM **my_items;
	MENU *my_menu;
	WINDOW *my_menu_win;
	WINDOW *banner_win;
	int i;

	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);

	//Create items
	n_choices_title = ARRAY_SIZE(title_choices);
	my_items = (ITEM **)calloc(n_choices_title, sizeof(ITEM *));
	for(i = 0; i < n_choices_title; ++i)
		my_items[i] = new_item(title_choices[i], title_choices[i]);

	//Crate menu
	my_menu = new_menu((ITEM **)my_items);

	//Create the window to be associated with the menu
	my_menu_win = newwin(10, 22, 2, 2);
	banner_win = newwin(15, 40, 2, 26);
	keypad(my_menu_win, TRUE);

	//Set main window and sub window
	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 6, 20, 3, 1));
	set_menu_format(my_menu, 5, 1);
	
	//Set menu mark to the string " * "
	set_menu_mark(my_menu, " * ");

	//Print a border around the main window and print a title
	win_border(my_menu_win);
	win_border(banner_win);
	print_in_middle(my_menu_win, 1, 0, 22, "Main Menu", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, '+');
	mvwhline(my_menu_win, 2, 1, '-', 20);
	mvwaddch(my_menu_win, 2, 21, '+');
	mvprintw(LINES - 2, 0, "If you are new to the game go to new player and create a profile");
	refresh();

	//Post the menu
	post_menu(my_menu);
	wrefresh(my_menu_win);

	while((ch = wgetch(my_menu_win)) != 'q') {       
		switch(ch) {	
			case 10:
				if(current_item(my_menu) == my_items[2]) {
					clear();
					new_player();				
				}
				if(current_item(my_menu) == my_items[3]) {
					clear();
					endwin();
					refresh();
					edit_profile();
				}
				break;
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			default:
				break;
		}
		wrefresh(my_menu_win);
	}	

	//Unpost and free all the memory taken up
	unpost_menu(my_menu);
	free_menu(my_menu);
	for(i = 0; i < n_choices_title; ++i)
		free_item(my_items[i]);

}

void func(char *name) {	
	move(20, 0);
	clrtoeol();
	mvprintw(20, 0, "Item selected is : %s", name);
}	

//Put all the windows
void init_wins(WINDOW **wins, int n)
{	int x, y, i;
	char* label;

	y = 2;
	x = 10;
	for(i = 0; i < n; ++i)
	{	wins[i] = newwin(NLINES, NCOLS, y, x);
		sprintf(label, "Window Number %d", i + 1);
		win_show(wins[i], label, i + 1);
		y += 3;
		x += 7;
	}
}

//Show the window with a border and a label
void win_show(WINDOW *win, char* label, int label_color)
{	int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);

	print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, const char* str, chtype color)
{	int x, y;
	size_t length;
	double temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(str);
	temp = (width - (int)length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", str);
	wattroff(win, color);
	refresh();
}

void print_mainmenu(WINDOW *menu_win, int highlight, int starty, int startx)
{
	int x, y, i;	

	x = startx+2;
	y = starty+2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices_title; ++i)
	{	if(highlight == i + 1)
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", title_choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", title_choices[i]);
		++y;
	}
	wrefresh(menu_win);
}

//Set the FIELD_DATA structures for individual panels
/*void set_user_ptrs_panels(FIELD **fields, int n, char ch)
{	FIELD_DATA *ptrs;
	WINDOW *win;

	ptrs = (FIELD_DATA *); //struct stuff

	for(int i = 0; i < n; ++i)
	{	win = field_window(fields[i]);
		if(i + 1 == n)
			ptrs[i].next = NULL;
		else
			ptrs[i].next = fields[i + 1];
		set_field_userptr(fields[i], &ptrs[i]);
	}
}*/
//Set the PANEL_DATA structures for individual panels
void set_user_ptrs_panels(PANEL **panels, int n)
{	PANEL_DATA *ptrs;
	WINDOW *win;

	char* label;
	int x, y, w, h, i;
	char temp[80];

	ptrs = (PANEL_DATA *)calloc(n, sizeof(PANEL_DATA));

	for(i = 0;i < n; ++i)
	{	win = panel_window(panels[i]);
		getbegyx(win, y, x);
		getmaxyx(win, h, w);
		ptrs[i].x = x;
		ptrs[i].y = y;
		ptrs[i].w = w;
		ptrs[i].h = h;
		sprintf(temp, "Window Number %d", i + 1); //change to Window title and number in the stack of panels
		strcpy(ptrs[i].label, temp);
		ptrs[i].label_color = i + 1;
		if(i + 1 == n)
			ptrs[i].next = panels[0];
		else
			ptrs[i].next = panels[i + 1];
		set_panel_userptr(panels[i], &ptrs[i]);
	}
}

void win_border(WINDOW *win) {
	 wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
}
