/*
** stock_args.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sun Nov 17 00:35:25 2013 chapui_s
** Last update Tue Mar 17 03:25:07 2015 chapui_s
*/

#include <stdarg.h>
#include <stddef.h>
#include "my_printf.h"

void	stock_arg(va_list *arg, t_tmp_arg *tmp, char c)
{
  tmp->uint = 0;
  tmp->t_int = 0;
  tmp->t_char = NULL;
  tmp->ptr = NULL;
  tmp->chars_to_save = NULL;

  if (c == 's' || c == 'S')
    tmp->t_char = va_arg(*arg, char *);
  else if (c == 'p')
    tmp->ptr = va_arg(*arg, void *);
  else if (c == 'c' || c == 'd' || c == 'i')
    tmp->t_int = va_arg(*arg, long long);
  else if (c == 'n')
    tmp->chars_to_save = va_arg(*arg, unsigned int *);
  else
    tmp->uint = va_arg(*arg, unsigned long long);
}
