#include "shell.h"

/**
 * is_chain - Check the current character in the buffer
 * @info: information
 * @buf: character
 * @p: size
 * Return: 1 if it is, 0 otherwise.
 */
int is_chain(ino_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	} else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	} else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	} else
	{
		return (0);
	}
	*p = j;
	return (1);
}

/**
 * check_chain - Check if we should continue chaining based on the last status.
 * @info: information
 * @buf: character
 * @p: size
 * @i: size
 * @len: length
 */
void check_chain(ino_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * replace_alias - Replace an alias in the tokenized strin
 * @info: - information
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(ino_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replace variables in the tokenized string
 * @info: information
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(ino_t *info)
{
	int i = 0;
	list_t *node;
	char *status_str = convert_number(info->status, 10, 0);

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]), _strdup(status_str));
			free(status_str);
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	} return (0);
}

/**
 * replace_string - Replace a string.
 * @old: address of old string
 * @new: address of new string
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

