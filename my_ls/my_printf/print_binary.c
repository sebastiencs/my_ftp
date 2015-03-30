/*
** print_binary.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 16 22:47:10 2013 chapui_s
** Last update Tue Mar 17 04:22:15 2015 chapui_s
*/

#include "my_printf.h"

unsigned int	print_binary(t_tmp_arg *tmp, t_params *params,
			     unsigned int s_to_add,
			     unsigned int s_to_print)
{
  unsigned int	chars_written;

  chars_written = 0;
  tmp->uint = convert_uint_length(tmp->uint, params);
  s_to_print = calc_size_to_print(tmp, 'b');
  if ((signed)s_to_print < params->precision)
    s_to_print = params->precision;
  if ((signed)s_to_print < params->width)
    s_to_add = params->width - s_to_print;
  chars_written = s_to_print + s_to_add;
  if (params->less == 1)
    my_put_unsigned_nb(tmp->uint, s_to_print, "01");
  if (params->width >= params->precision && params->zero == 1
      && params->is_precision == 0 && params->less == 0
      && params->width > (signed)s_to_print)
    add_zero(s_to_add);
  else if (params->width >= (params->precision)
	   && params->width > (signed)s_to_print)
    add_space(s_to_add);
  if (params->less == 0)
    my_put_unsigned_nb(tmp->uint, s_to_print, "01");
  return (chars_written);
}
