#ifndef PRINTF_H
#define PRINTF_H
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
/**
 * struct buffer - A buffer for our printf
 * @buf: Buffer to write characters
 * @format: The string passed to our printf
 * @bp: the current point in the buffer
 * @fp: the current point in the format
 * @size: the size of our buffer
 */
typedef struct buffer
{
	char *buf;
	const char *format;
	va_list ap;
	int bp;
	int fp;
	unsigned int size;
	unsigned int printed;
} buffer;
/**
 * struct tags - Format tags after %
 * @spec: the specifier
 * @length: the length
 * @prec: the precision
 * @width: the width
 * @flags: the flags
 */
typedef struct tags
{
	char spec;
	char length;
	int prec;
	int width;
	char flags[4];
	char scanned[100];
	int scan_i;
} tags;
/**
 * struct parse_table - Table used for parsing the %s
 * @c: character found
 * @number: number for width and precision
 * @level: which level from 5 (specification) to 1 (flags)
 */
typedef struct parse_table
{
	char c;
	int level;
	void (*tf)();
	void (*specf)();
} parse_table;
/* printf functions */
void _copy(buffer *);
int _printf(const char *format, ...);
void _parse(buffer *b_r);
void _create_tag(buffer *b_r, tags *t, parse_table *table);
void _spec_c(buffer *b_r, tags *t);
void _spec_s(buffer *b_r, tags *t);
void _spec_0(buffer *b_r, tags *t);
void _spec_pct(buffer *b_r);
void _spec_p(buffer *b_r, tags *t);
int __atoi(const char *s, int n);
void _write(buffer *b_r);
void _parse_tag(buffer *b_r, tags *t, parse_table *table);
int str_len(char *str);
void _revstr(char *s);
char *int_to_str(int n);
/* hexcalc functions */
char *_litoh(long int x);
/* printf_flag_helper functions */
int _isFlagMinus(tags *t);
int _isFlagPlus(tags *t);
int _isFlagSpace(tags *t);
int _isFlagHashtag(tags *t);
int _isFlagZero(tags *t);
/* parse helper functions */
void _found_spec(buffer *b_r, tags *t, parse_table *table, int i);
void _found_length(buffer *b_r, tags *t, parse_table *table, int i);
void _found_prec(buffer *b_r, tags *t, parse_table *table, int i);
void _found_width(buffer *b_r, tags *t);
void _found_flag(buffer *b_r, tags *t, parse_table *table, int i);
#endif
