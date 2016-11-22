#include "holberton.h"
/**
 * _isFlagMinus - Bool check for if the stuct has a minus flag
 * @t: tags structure to check
 */
int _isFlagMinus(tags *t)
{
	int i;

	for (i = 0; t->flags[i] != '\0'; i++)
		if (t->flags[i] == '-')
			return (1);
	return (0);
}
/**
 * _isFlagPlus - Bool check for if the stuct has a plus flag
 * @t: tags structure to check
 */
int _isFlagPlus(tags *t)
{
	int i;

	for (i = 0; t->flags[i] != '\0'; i++)
		if (t->flags[i] == '+')
			return (1);
	return (0);
}
/**
 * _isFlagSpace - Bool check for if the stuct has a space flag
 * @t: tags structure to check
 */
int _isFlagSpace(tags *t)
{
	int i;

	for (i = 0; t->flags[i] != '\0'; i++)
		if (t->flags[i] == ' ')
			return (1);
	return (0);
}
/**
 * _isFlagHashtag - Bool check for if the stuct has a hashtag flag
 * @t: tags structure to check
 */
int _isFlagHashtag(tags *t)
{
	int i;

	for (i = 0; t->flags[i] != '\0'; i++)
		if (t->flags[i] == '#')
			return (1);
	return (0);
}
/**
 * _isFlagZero - Bool check for if the stuct has a zero flag
 * @t: tags structure to check
 */
int _isFlagZero(tags *t)
{
	int i;

	for (i = 0; t->flags[i] != '\0'; i++)
		if (t->flags[i] == '0')
			return (1);
	return (0);
}