#include "holberton.h"
/**
 * _spec_pct - sends a % into buffer
 * @b_r: a pointer to the buffer
 */
void _spec_pct(buffer *b_r)
{
	b_r->buf[b_r->bp++] = '%';
}