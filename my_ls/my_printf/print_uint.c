/*
** print_uint.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 16 14:04:04 2013 chapui_s
** Last update Tue Mar 17 04:20:00 2015 chapui_s
*/

#include <stdint.h>
#include <stddef.h>
#include "my_printf.h"

unsigned long long	convert_uint_length(unsigned long long nb,
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
    return ((uintmax_t)nb);
  if (params->length == T)
    return ((ptrdiff_t)nb);
  return ((unsigned int)nb);
}

void	my_put_unsigned_nb(unsigned long long nb, int precision, char *base)
{
  int	size_base;
  int	size_nb;

  size_base = my_strlen(base);
  if (size_base == 10)
    size_nb = calc_uint(nb);
  else if (size_base == 16)
    size_nb = calc_hexa(nb);
  else if (size_base == 8)
    size_nb = calc_octal(nb);
  else if (size_base == 2)
    size_nb = calc_binary(nb);
  while (precision > size_nb)
  {
    my_putchar('0');
    precision = precision - 1;
  }
  if ((signed)nb >= size_base)
    my_put_unsigned_nb(nb / size_base, 0, base);
  my_putchar(base[(int)(nb % size_base)]);
}

unsigned int	print_uint(t_tmp_arg *tmp, t_params *params,
			   unsigned int s_to_add, unsigned int s_to_print)
{
  unsigned int	chars_written;

  chars_written = 0;
  tmp->uint = convert_uint_length(tmp->uint, params);
  s_to_print = calc_size_to_print(tmp, 'u');
  if ((signed)s_to_print < params->precision)
    s_to_print = params->precision;
  if ((signed)s_to_print < params->width)
    s_to_add = params->width - s_to_print;
  chars_written = s_to_print + s_to_add;
  if (params->less == 1)
    my_put_unsigned_nb(tmp->uint, s_to_print, "0123456789");
  if (params->width >= params->precision && params->zero == 1
      && params->is_precision == 0 && params->less == 0
      && params->width > (signed)s_to_print)
    add_zero(s_to_add);
  else if (params->width >= (params->precision)
	   && params->width > (signed)s_to_print)
    add_space(s_to_add);
  if (params->less == 0)
    my_put_unsigned_nb(tmp->uint, s_to_print, "0123456789");
  return (chars_written);
}
