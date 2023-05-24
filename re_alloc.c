#include "main.h"

/**
 * _memryset - Entry func fills memory with a constant byte
 * @x: variable pointer to the memory area
 * @d: variable byte to fill *x with
 * @m: variable for  amount of bytes to be filled
 * Return: pointer to the memory area x
 */
char *_memryset(char *x, char d, unsigned int m)
{
	unsigned int j;

	for (j = 0; j < m; j++)
		x[j] = d;
	return (x);
}

/**
 * _freestr - Entry func frees a string of strings
 * @bb: variable string of strings
 */
void _freestr(char **bb)
{
	char **k = bb;

	if (!bb)
		return;
	while (*bb)
		free(*bb++);
	free(k);
}

/**
 * _realloca - Entry func reallocates a block of memory
 * @pt: variable pointer to previous malloc ated block
 * @ol_size: variable byte size of previous block
 * @nw_size: variable byte size of new block
 * Return: pointer to the ol block
 */
void *_realloca(void *pt, unsigned int ol_size, unsigned int nw_size)
{
	char *b;

	if (!pt)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(pt), NULL);
	if (nw_size == ol_size)
		return (pt);

	b = malloc(nw_size);
	if (!b)
		return (NULL);
	ol_size = ol_size < nw_size ? ol_size : nw_size;
	while (ol_size--)
		b[ol_size] = ((char *)pt)[ol_size];
	free(pt);
	return (b);
}
