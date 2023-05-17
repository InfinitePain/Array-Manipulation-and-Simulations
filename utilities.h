/*
=============================================================================
 Name        : utilities.h
 Author      : InfinitePain
 License     : Apache License 2.0
 Description : Header file for Ascii-Numeric Utility
=============================================================================
*/

#ifndef UTILITIES_H_
#define UTILITIES_H_
 
#include <stdbool.h>
#include <menu.h>

extern bool should_loop;
extern int error_line;

typedef struct {
    int value;
    int point;
} FloatInt;

#define get_int(FI) _get_int(&FI)
#define get_frac(FI) _get_frac(&FI)

void error_message(const char *message);
void func_exit();
void delete_menu();
ITEM *create_item(char *string1, char *string2);
MENU *create_menu(ITEM **items);
bool create_app_menu();
void print_menu();
void erase_menu(MENU *menu);
void custom_menu_driver(int key);
void scanInt(int max_digits, int* result);
void scanString(int max_chars, char *string);
void scanFloatInt(int int_max_digits, int frac_max_digits, FloatInt *FI);
int my_pow(int base, int exp);
void add_FloatInt(FloatInt *FI1, FloatInt *FI2, FloatInt *result);
void sub_FloatInt(FloatInt *FI1, FloatInt *FI2, FloatInt *result);
void mul_FloatInt(FloatInt *FI1, FloatInt *FI2, FloatInt *result);
void div_FloatInt(FloatInt *FI1, FloatInt *FI2, FloatInt *result, int extra_precision);

#endif /*UTILITIES_H_*/