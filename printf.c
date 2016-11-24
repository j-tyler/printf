#include "holberton.h"
/**
 * _printf - Recreate stdio's printf
 * @format: Formatted string to print to stdout
 *
 * Return: Number of chars printed
 */
int _printf(const char *format, ...)
{
	/* Create buffer structure b_r and initalize */
	buffer b_r;

	_init_buffer(&b_r, format);
	va_start(b_r.ap, format);

	/* Main loop to create buffer from format string */
	while (b_r.format[b_r.fp] != '\0')
	{
		_copy(&b_r);
		if (b_r.format[b_r.fp] != '\0')
			_parse(&b_r);
	}

	write(1, b_r.buf, b_r.bp);
	b_r.printed += b_r.bp;

	va_end(b_r.ap);
	free(b_r.buf);
	free(b_r.tmpbuf);
	return (b_r.printed);
}
/**
 * _copy - directly copy from format to buffer
 * @b_r: the buffer structure
 */
void _copy(buffer *b_r)
{
	while (b_r->format[b_r->fp] != '%' && b_r->format[b_r->fp] != '\0')
		_write(b_r, b_r->format[b_r->fp++]);

}
/**
 * _parse - take string from % and parse tags into correct string for buffer
 * @b_r: the buffer structure
 */
void _parse(buffer *b_r)
{
	int i;
	tags t;
	parse_table table[] = {
	{'d', 5, _found_spec, _spec_i_d}, {'i', 5, _found_spec, _spec_i_d},
	{'c', 5, _found_spec, _spec_c}, {'s', 5, _found_spec, _spec_s},
	{'u', 5, _found_spec, _spec_u}, {'o', 5, _found_spec, _spec_o},
	{'x', 5, _found_spec, _spec_x}, {'X', 5, _found_spec, _spec_X},
	{'b', 5, _found_spec, _spec_b}, {'S', 5, _found_spec, _spec_S},
	{'p', 5, _found_spec, _spec_p}, {'R', 5, _found_spec, _spec_R},
	{'r', 5, _found_spec, _spec_r}, {'%', 5, _found_spec, _spec_pct},
	/* Default */ {'\0', 5, _broken, _spec_nil},
	{'h', 4, _found_length, _broken}, {'l', 4, _found_length, _broken},
	{'.', 3, _found_prec, _broken},
	{'1', 2, _found_width, _broken}, {'2', 2, _found_width, _broken},
	{'3', 2, _found_width, _broken}, {'4', 2, _found_width, _broken},
	{'5', 2, _found_width, _broken}, {'6', 2, _found_width, _broken},
	{'7', 2, _found_width, _broken}, {'8', 2, _found_width, _broken},
	{'9', 2, _found_width, _broken}, {'-', 1, _found_flag, _broken},
	{'+', 1, _found_flag, _broken}, {' ', 1, _found_flag, _broken},
	{'#', 1, _found_flag, _broken}, {'0', 1, _found_flag, _broken},
	/* We found nothing */ {'\0', -1, _broken, _broken}
	};

	/* We only parse at %! */
	if (b_r->format[b_r->fp] != '%')
		write(1, "Error: Parsing when not at '%'\n", 31);
	b_r->tp = 0;
	b_r->tmpbuf[b_r->tp++] = '%';
	b_r->fp++;

	_init_tag(&t);
	_parse_tag(b_r, &t, table);

	/* Call the specifier function matching the specifier found */
	i = 0;
	while (table[i].level == 5)
	{
		if (table[i].c == t.spec)
			table[i].specf(b_r, &t);
		i++;
	}
}

/**
 * _parse_tag - Build out the tags struct with tags found
 * @b_r: the buffer structure
 * @table: Parsing table to read the '%___' from format
 * @t: tags to send to our specifier function
 */
void _parse_tag(buffer *b_r, tags *t, parse_table *table)
{
	int currentLevel, i, j;

	currentLevel = i = j = 0;
	while (table[i].level >= currentLevel && currentLevel < 5)
	{
		if (table[i].c == b_r->format[b_r->fp])
		{
			currentLevel = table[i].level;
			if (table[i].level == 2)
				table[i].tf(b_r, t);
			else
				table[i].tf(b_r, t, table, i);
			i = -1;
		}
		i++;
	}
}
