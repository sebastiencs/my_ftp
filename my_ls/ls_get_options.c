/*
** ls_get_options.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Mon Nov 25 21:17:23 2013 chapui_s
** Last update Tue Mar 17 04:15:17 2015 chapui_s
*/

#include <stdlib.h>
#include "my_ls.h"

int	init_options(t_options **options)
{
  if ((*options = (t_options*)my_malloc(sizeof(t_options))) == NULL)
    return (1);
  (*options)->l = 0;
  (*options)->R = 0;
  (*options)->d = 0;
  (*options)->r = 0;
  (*options)->t = 0;
  (*options)->g = 0;
  return (0);
}

int	search_options(char *str, char c)
{
  int	i;

  i = 0;
  while (str[i])
  {
    if (str[i] == c)
      return (1);
    i = i + 1;
  }
  return (0);
}

int	search_bad_options(char *str)
{
  int	i;

  i = 0;
  while (str[i])
  {
    if (str[i] != '-' && str[i] != 'l' && str[i] != 'R' && str[i] != 'd'
        && str[i] != 'r' && str[i] != 't' && str[i] != 'g')
    {
      my_putstr_error("my_ls: invalid option -- '");
      my_putchar_error(str[i]);
      my_putstr_error("'\n");
      return (1);
    }
    i = i + 1;
  }
  return (0);
}

int	get_option(char *str, t_options **options)
{
  (search_options(str, 'l') == 1) ? ((*options)->l = 1) : (0);
  (search_options(str, 'R') == 1) ? ((*options)->R = 1) : (0);
  (search_options(str, 'd') == 1) ? ((*options)->d = 1) : (0);
  (search_options(str, 'r') == 1) ? ((*options)->r = 1) : (0);
  (search_options(str, 't') == 1) ? ((*options)->t = 1) : (0);
  (search_options(str, 'g') == 1) ? ((*options)->g = 1) : (0);
  if (search_bad_options(str) == 1)
    return (-1);
  return (0);
}
