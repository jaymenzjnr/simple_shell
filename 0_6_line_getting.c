#include "shell.h"

/**
 * in_buf - buffers chained commands
 * @inf: parameter struct
 * @bf: address of buffer
 * @ln: address of length variable
 *
 * Return: (bytes read)
 */
ssize_t in_buf(info_t *inf, char **bf, size_t *ln)
{
	ssize_t r = 0;
	size_t ln_p = 0;

	if (!*ln) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)inf->cd_bf);*/
		free(*bf);
		*bf = NULL;
		signal(SIGINT, sgnlHndlr);
#if USE_GETLINE
		r = getline(bf, &ln_p, stdin);
#else
		r = _getline(inf, bf, &ln_p);
#endif
		if (r > 0)
		{
			if ((*bf)[r - 1] == '\n')
			{
				(*bf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			inf->lncnt_flg = 1;
			rem_cmmts(*bf);
			build_hstry_lst(inf, *bf, inf->hstcnt++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*ln = r;
				inf->cd_bf = bf;
			}
		}
	}
	return (r);
}

/**
 * get_inpt - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: (bytes read)
 */
ssize_t get_inpt(info_t *inf)
{
	static char *bf; /* the ';' command chain buffer */
	static size_t i, j, ln;
	ssize_t r = 0;
	char **bf_p = &(inf->ag), *p;

	_putchar(BUF_FLUSH);
	r = in_buf(inf, &bf, &ln);
	if (r == -1) /* EOF */
		return (-1);
	if (ln) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = bf + i; /* get pointer for return */

		check_chain(inf, bf, &j, i, ln);
		while (j < ln) /* iterate to semicolon or end */
		{
			if (is_chain(inf, bf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= ln) /* reached end of buffer? */
		{
			i = ln = 0; /* reset position and length */
			inf->cd_bf_typ = CMD_NORM;
		}

		*bf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*bf_p = bf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_bf - reads a buffer
 * @inf: parameter struct
 * @bf: buffer
 * @i: size
 *
 * Return: (r)
 */
ssize_t read_bf(info_t *inf, char *bf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(inf->rdfd, bf, READ_BF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _gln - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: (s)
 */
int _gln(info_t *inf, char **ptr, size_t *length)
{
	static char bf[READ_BF_SIZE];
	static size_t i, ln;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == ln)
		i = ln = 0;

	r = read_bf(inf, bf, &ln);
	if (r == -1 || (r == 0 && ln == 0))
		return (-1);

	c = _strchr(bf + i, '\n');
	k = c ? 1 + (unsigned int)(c - bf) : ln;
	new_p = _rlloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, bf + i, k - i);
	else
		_strncpy(new_p, bf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sgnlHndlr - blocks ctrl-C
 * @sngl_nm: the signal number
 *
 * Return: void
 */
void sgnlHndlr(__attribute__((unused))int sngl_nm)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
