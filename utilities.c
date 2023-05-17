/*
=============================================================================
 Name        : utilities.c
 Author      : InfinitePain
 License     : Apache License 2.0
 Description : Source file for Ascii-Numeric Utility
=============================================================================
*/

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include "aufgaben.h"

bool should_loop = true;

MENU *menu = NULL;
ITEM **items = NULL;

int error_line = 0;
char *choices[] = {
	"TI 1. Semester Prog 1 Uebungsblatt 2",
	"Aufgabe 1 - Minimum, Maximum und Mittelwert",
	"Aufgabe 2 - Ausgabe eines Zahlen-Arrays auf der Konsole",
	"Aufgabe 3 - Konsolen-Ausgabe der Summe eines Arrays",
	"Aufgabe 4 - Alea iacta est",
	"Aufgabe 5 - Muenzautomat",
	"Exit"};
int n_choices = sizeof(choices) / sizeof(char *);

void error_message(const char *message)
{
	error_line == 0 ? clear() : 0;
	char buf[BUFSIZ];
	snprintf(buf, sizeof(buf), "%s: %s", message, strerror(errno));
	strerror(errno);
	mvprintw(error_line, 0, "%s", buf);
	refresh();
	error_line++;
	sleep(1);
}

void func_exit()
{
	erase_menu(menu);
	delete_menu(menu);
	should_loop = false;
}

void delete_menu()
{
	if (items != NULL)
	{
		for (int i = 0; i < item_count(menu); i++)
		{
			free_item(items[i]);
			items[i] = NULL;
		}
	}
	if (menu != NULL)
	{
		free_menu(menu);
		menu = NULL;
	}
}

ITEM *create_item(char *string1, char *string2)
{
	ITEM *item = new_item(string1, string2);
	if (item == NULL)
	{
		error_message("ERROR: func create_item: new_item() failed");
		return NULL;
	}
	return item;
}

MENU *create_menu(ITEM **items)
{
	MENU *menu = new_menu(items);
	if (menu == NULL)
	{
		error_message("ERROR: func create_menu: new_menu() failed");
		return NULL;
	}
	return menu;
}

bool create_app_menu()
{
	items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	if (items == NULL)
	{
		error_message("ERROR: func create_game_menu: calloc() failed");
		return false;
	}

	for (int i = 0; i < n_choices; i++)
	{
		items[i] = create_item(choices[i], NULL);
		items[n_choices] = (ITEM *)NULL;
		if (items[i] == NULL)
		{
			delete_menu();
			return false;
		}
	}

	menu = create_menu(items);
	if (menu == NULL)
	{
		delete_menu();
		return false;
	}

	set_menu_mark(menu, "");
	set_menu_format(menu, LINES, 1);
	menu_opts_on(menu, O_NONCYCLIC);
	item_opts_off(items[0], O_SELECTABLE);
	void (*menu_functions[])() = {
		NULL, Aufgabe1, Aufgabe2, Aufgabe3, Aufgabe4, Aufgabe5, func_exit};
	for (int i = 0; i < n_choices; i++)
	{
		set_item_userptr(items[i], menu_functions[i]);
	}
	post_menu(menu);
	menu_driver(menu, REQ_DOWN_ITEM);
	return true;
}

void print_menu()
{
	post_menu(menu);
	refresh();
}

void erase_menu(MENU *menu)
{
	unpost_menu(menu);
	clear();
	refresh();
}

void custom_menu_driver(int key)
{
	if (key == -1)
	{
		return;
	}
	int n_choices = item_count(menu);
	int index = item_index(current_item(menu));
	void (*pfunc)() = NULL;
	switch (key)
	{
	case KEY_DOWN:
		index++;
		if (index == n_choices)
		{
			menu_driver(menu, REQ_FIRST_ITEM);
			menu_driver(menu, REQ_DOWN_ITEM);
		}
		else
		{
			menu_driver(menu, REQ_DOWN_ITEM);
		}
		print_menu();
		break;
	case KEY_UP:
		index--;
		if (index == 0)
		{
			menu_driver(menu, REQ_LAST_ITEM);
		}
		else
		{
			menu_driver(menu, REQ_UP_ITEM);
		}
		print_menu();
		break;
	case '\n':
		erase_menu(menu);
		pfunc = item_userptr(current_item(menu));
		pfunc();
		break;
	}
}

void shift_elements(char *input, int start, int end, int direction)
{
	if (direction < 0) // left shift
	{
		for (int i = start; i <= end; i++)
		{
			input[i] = input[i + 1];
		}
	}
	else // right shift
	{
		for (int i = end; i >= start; i--)
		{
			input[i + 1] = input[i];
		}
	}
}

void scanInt(int max_digits, int *result)
{
	curs_set(1);
	char input[max_digits + 1];
	for (int i = 0; i < max_digits + 1; i++)
		input[i] = '\0';

	int pos = 0;
	int len = 0;
	int ch;
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	int y, x;
	getyx(stdscr, y, x);

	while (1)
	{
		ch = getch();

		if (ch >= '0' && ch <= '9' && len < max_digits)
		{
			if (x + len >= max_x)
			{
				beep();
				continue;
			}
			shift_elements(input, pos, len++, 1);
			input[pos++] = ch;
			for (int i = 0; i < len; i++)
				mvwaddch(stdscr, y, x + i, input[i]);
			move(y, x + pos);
		}
		else if (ch == KEY_BACKSPACE || ch == '\b' || ch == 127)
		{
			if (pos > 0)
			{
				shift_elements(input, --pos, --len, -1);
				mvwaddch(stdscr, y, x + len, ' ');
				for (int i = 0; i < len; i++)
					mvwaddch(stdscr, y, x + i, input[i]);
				move(y, x + pos);
			}
			else
				beep();
		}
		else if (ch == KEY_DC)
		{
			if (pos < len)
			{
				shift_elements(input, pos, --len, -1);
				mvwaddch(stdscr, y, x + len, ' ');
				for (int i = 0; i < len; i++)
					mvwaddch(stdscr, y, x + i, input[i]);
				move(y, x + pos);
			}
			else
				beep();
		}
		else if (ch == KEY_LEFT && pos > 0)
		{
			move(y, x + --pos);
		}
		else if (ch == KEY_RIGHT && pos < len)
		{
			move(y, x + ++pos);
		}
		else if (ch == '\n' || ch == '\r')
		{
			move(y + 1, 0);
			break;
		}
		else if (ch == 27)
		{
			*result = -1;
		}
		else
		{
			beep();
		}
		refresh();
	}
	refresh();
	curs_set(0);
	*result = atoi(input);
}

void scanString(int buffer_length, char *string)
{
	curs_set(1);
	for (int i = 0; i < buffer_length; i++)
		string[i] = '\0';

	int pos = 0;
	int len = 0;
	int ch;
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	int y, x;
	getyx(stdscr, y, x);

	while (1)
	{
		ch = getch();

		if (ch >= ' ' && ch <= '~' && len < buffer_length)
		{
			if (x + len >= max_x)
			{
				beep();
				continue;
			}
			shift_elements(string, pos, len++, 1);
			string[pos++] = ch;
			for (int i = 0; i < len; i++)
				mvwaddch(stdscr, y, x + i, string[i]);
			move(y, x + pos);
		}
		else if (ch == KEY_BACKSPACE || ch == '\b' || ch == 127)
		{
			if (pos > 0)
			{
				shift_elements(string, --pos, --len, -1);
				mvwaddch(stdscr, y, x + len, ' ');
				for (int i = 0; i < len; i++)
					mvwaddch(stdscr, y, x + i, string[i]);
				move(y, x + pos);
			}
			else
				beep();
		}
		else if (ch == KEY_DC)
		{
			if (pos < len)
			{
				shift_elements(string, pos, --len, -1);
				mvwaddch(stdscr, y, x + len, ' ');
				for (int i = 0; i < len; i++)
					mvwaddch(stdscr, y, x + i, string[i]);
				move(y, x + pos);
			}
			else
				beep();
		}
		else if (ch == KEY_LEFT && pos > 0)
		{
			move(y, x + --pos);
		}
		else if (ch == KEY_RIGHT && pos < len)
		{
			move(y, x + ++pos);
		}
		else if (ch == '\n' || ch == '\r')
		{
			move(y + 1, 0);
			break;
		}
		else if (ch == 27)
		{
			string[0] = '\0';
			break;
		}
		else
		{
			beep();
		}
	}

	curs_set(0);
}

void scanFloatInt(int int_max_digits, int frac_max_digits, FloatInt *FI)
{
	curs_set(1);
	char input[int_max_digits + frac_max_digits + 2];
	for (int i = 0; i < int_max_digits + frac_max_digits + 2; i++)
		input[i] = '\0';

	int pos = 0;
	int len = 0;
	int ch;
	int max_y, max_x;
	int point_pos = -1;
	getmaxyx(stdscr, max_y, max_x);

	int y, x;
	getyx(stdscr, y, x);

	while (1)
	{
		ch = getch();
		int int_len = point_pos == -1 ? len : point_pos;
		int frac_len = point_pos == -1 ? 0 : len - point_pos - 1;

		if (ch >= '0' && ch <= '9' && ((point_pos == -1 && int_len < int_max_digits) || (point_pos != -1 && frac_len < frac_max_digits)))
		{
			if (ch == '.' || ch == ',')
			{
				if (point_pos != -1 || len >= int_max_digits)
				{
					beep();
					continue;
				}
				point_pos = len;
			}

			if (x + len >= max_x)
			{
				beep();
				continue;
			}
			shift_elements(input, pos, len++, 1);
			input[pos++] = ch == ',' ? '.' : ch;
			for (int i = 0; i < len; i++)
				mvwaddch(stdscr, y, x + i, input[i]);
			move(y, x + pos);
		}
		else if (ch == '.' || ch == ',')
		{
			if (point_pos != -1 || len >= int_max_digits + frac_max_digits)
			{
				beep();
				continue;
			}
			point_pos = len;
			if (x + len >= max_x)
			{
				beep();
				continue;
			}
			shift_elements(input, pos, len++, 1);
			input[pos++] = '.';
			for (int i = 0; i < len; i++)
				mvwaddch(stdscr, y, x + i, input[i]);
			move(y, x + pos);
		}
		else if (ch == KEY_BACKSPACE || ch == '\b' || ch == 127)
		{
			if (pos > 0)
			{
				if (input[--pos] == '.')
					point_pos = -1;
				shift_elements(input, pos, --len, -1);
				mvwaddch(stdscr, y, x + len, ' ');
				for (int i = 0; i < len; i++)
					mvwaddch(stdscr, y, x + i, input[i]);
				move(y, x + pos);
			}
			else
				beep();
		}
		else if (ch == KEY_DC)
		{
			if (pos < len)
			{
				if (input[pos] == '.')
					point_pos = -1;
				shift_elements(input, pos, --len, -1);
				mvwaddch(stdscr, y, x + len, ' ');
				for (int i = 0; i < len; i++)
					mvwaddch(stdscr, y, x + i, input[i]);
				move(y, x + pos);
			}
			else
				beep();
		}
		else if (ch == KEY_LEFT && pos > 0)
		{
			move(y, x + --pos);
		}
		else if (ch == KEY_RIGHT && pos < len)
		{
			move(y, x + ++pos);
		}
		else if (ch == '\n' || ch == '\r')
		{
			move(y + 1, 0);
			break;
		}
		else if (ch == 27)
		{
			FI->value = -1;
			FI->point = -1;
			return;
		}
		else
		{
			beep();
		}
		refresh();
	}
	refresh();
	curs_set(0);

	char processed_input[int_max_digits + frac_max_digits + 1];
	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (input[i] != '.')
		{
			processed_input[j] = input[i];
			j++;
		}
	}
	processed_input[j] = '\0';

	FI->value = atoi(processed_input);
	FI->point = point_pos == -1 ? 0 : len - point_pos - 1;
}

int my_pow(int base, int exp)
{
	int result = 1;
	for (int i = 0; i < exp; i++)
	{
		if (result > INT_MAX / base)
		{
			error_message("Error: integer overflow during exponentiation.");
			return 0;
		}
		result *= base;
	}
	return result;
}

// FI1 + FI2 = Result
void add_FloatInt(FloatInt *FI1, FloatInt *FI2, FloatInt *Result)
{
	int point1 = FI1->point;
	int point2 = FI2->point;
	int value1 = FI1->value;
	int value2 = FI2->value;
	int point = point1 > point2 ? point1 : point2;
	int value = value1 * my_pow(10, point - point1) + value2 * my_pow(10, point - point2);
	Result->point = point;
	Result->value = value;
}

// FI1 - FI2
void sub_FloatInt(FloatInt *FI1, FloatInt *FI2, FloatInt *Result)
{
	int point1 = FI1->point;
	int point2 = FI2->point;
	int value1 = FI1->value;
	int value2 = FI2->value;
	int point = point1 > point2 ? point1 : point2;
	int value = value1 * my_pow(10, point - point1) - value2 * my_pow(10, point - point2);
	Result->point = point;
	Result->value = value;
}

// FI1 * FI2 = Result
void mul_FloatInt(FloatInt *FI1, FloatInt *FI2, FloatInt *Result)
{
	int point1 = FI1->point;
	int point2 = FI2->point;
	int value1 = FI1->value;
	int value2 = FI2->value;
	int point = point1 + point2;
	int value = value1 * value2;
	while (value % 10 == 0 && point > 0)
	{
		value /= 10;
		point--;
	}
	Result->point = point;
	Result->value = value;
}

// FI1 / FI2 = Result
void div_FloatInt(FloatInt *FI1, FloatInt *FI2, FloatInt *Result, int extra_precision)
{
	int point1 = FI1->point;
	int point2 = FI2->point;
	int value1 = FI1->value;
	int value2 = FI2->value;
	int point = point1 - point2 + extra_precision;
	int64_t scaled_value1;

	int scale_factor = my_pow(10, extra_precision);
	if (scale_factor == 0 && extra_precision != 0)
	{
		error_message("Error in div_FloatInt: integer overflow during exponentiation.");
		Result->point = 0;
		Result->value = 0;
		return;
	}

	if (value1 > 0 && value1 > INT64_MAX / scale_factor)
	{
		error_message("Error in div_FloatInt: integer overflow during scaling of value1.");
		Result->point = 0;
		Result->value = 0;
		return;
	}
	else
	{
		scaled_value1 = (int64_t)value1 * scale_factor;
	}

	if (value2 == 0)
	{
		error_message("Error in div_FloatInt: Division by zero is not allowed.");
		Result->point = 0;
		Result->value = 0;
		return;
	}
	else
	{
		int value = scaled_value1 / value2;

		while (value % 10 == 0 && point > 0)
		{
			value /= 10;
			point--;
		}

		Result->point = point;
		Result->value = value;
	}
}
