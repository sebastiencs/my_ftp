/*
** print_little_hexa.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 16 16:35:20 2013 chapui_s
** Last update Tue Mar 17 04:21:36 2015 chapui_s
*/

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "my_printf.h"

unsigned long long	convert_hexa_length(unsigned long long nb,
					    t_params *params)
{
  if (params->length == HH)
    return ((unsigned char)nb);
  if (params->length == H)
    return ((unsigned short)nb);
  if (params->length == L)
    return ((unsigned long)nb);
  if (params->length == LL)
    return ((unsigned long long)nb);
  if (params->length == Z)
    return ((size_t)nb);
  if (params->length == J)
    return ((intmax_t)nb);
  if (params->length == T)
    return ((ptrdiff_t)nb);
  return ((unsigned int)nb);
}

void	finish_little_hexa(t_tmp_arg *tmp, t_params *params,
				  unsigned int s_to_add,
				  unsigned int s_to_print)
{
  if (params->less == 1)
  {
    if (params->diez == 1 && tmp->uint != 0)
      my_putstr("0x");
    my_put_unsigned_nb(tmp->uint, s_to_print, "0123456789abcdef");
  }
  if (params->width >= (signed)params->precision && params->zero == 1
      && params->is_precision == 0 && params->less == 0
      && params->width > (signed)s_to_print)
    add_zero(s_to_add);
  else if (params->width >= (params->precision)
	   && params->width > (signed)s_to_print)
    add_space(s_to_add);
  if (params->less == 0)
  {
    if (params->diez == 1 && tmp->uint != 0)
      my_putstr("0x");
    my_put_unsigned_nb(tmp->uint, s_to_print, "0123456789abcdef");
  }
}

unsigned int	print_little_hexa(t_tmp_arg *tmp, t_params *params,
				  unsigned int s_to_add,
				  unsigned int s_to_print)
{
  unsigned int	chars_written;

  chars_written = 0;
  tmp->uint = convert_hexa_length(tmp->uint, params);
  s_to_print = calc_size_to_print(tmp, 'x');
  if ((signed)s_to_print < params->precision)
    s_to_print = params->precision;
  if ((signed)s_to_print < params->width)
    s_to_add = params->width - s_to_print;
  chars_written = s_to_print + s_to_add;
  if (params->diez == 1)
    s_to_add = s_to_add - 2;
  if (params->diez == 1 && params->is_precision == 0
      && params->zero == 1)
  {
    my_putstr("0x");
    params->diez = 0;
  }
  finish_little_hexa(tmp, params, s_to_add, s_to_print);
  return (chars_written);
}
