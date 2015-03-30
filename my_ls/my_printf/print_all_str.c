/*
** print_all_str.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 16 23:02:25 2013 chapui_s
** Last update Tue Mar 17 04:20:28 2015 chapui_s
*/

#include "my_printf.h"

unsigned int	put_n_all_str(char *str, unsigned int n)
{
  unsigned int	i;
  unsigned int	chars_written;

  i = 0;
  while (str[i] && i < n)
  {
    if (str[i] >= 32 && str[i] <= 126)
    {
      chars_written = chars_written + 1;
      my_putchar(str[i]);
    }
    else
    {
      chars_written = chars_written + 4;
      my_putchar('\\');
      my_put_unsigned_nb(str[i], 3, "01234567");
    }
    i = i + 1;
  }
  return (chars_written);
}

unsigned int	print_all_str(t_tmp_arg *tmp, t_params *params,
			      unsigned int s_to_add,
			      unsigned int s_to_print)
{
  unsigned int	chars_written;

  chars_written = 0;
  if (params->is_precision == 1
      && params->precision <= (signed)my_strlen(tmp->t_char))
    s_to_print = params->precision;
  else
    s_to_print = my_strlen(tmp->t_char);
  if ((signed)s_to_print < params->width)
    s_to_add = params->width - s_to_print;
  if (params->less == 1)
    chars_written = put_n_all_str(tmp->t_char, s_to_print);
  if (params->width >= (signed)s_to_print)
    add_space(s_to_add);
  if (params->less == 0)
    chars_written = put_n_all_str(tmp->t_char, s_to_print);
  return (chars_written);
}
