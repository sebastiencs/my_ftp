/*
** print_ptr.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 16 20:06:21 2013 chapui_s
** Last update Tue Mar 17 04:23:54 2015 chapui_s
*/

#include <stddef.h>
#include "my_printf.h"

void	my_put_size_t_nb(size_t nb, char *base)
{
  if (nb >= 16)
    my_put_size_t_nb(nb / 16, base);
  my_putchar(base[(int)(nb % 16)]);
}

void		my_put_adr(void *ptr, int precision, int is_add_0x)
{
  size_t	ptr_to_adr;

  ptr_to_adr = (size_t)ptr;
  if (is_add_0x == 0)
    my_putstr("0x");
  while (precision > 12)
  {
    my_putchar('0');
    precision = precision - 1;
  }
  my_put_size_t_nb(ptr_to_adr, "0123456789abcdef");
}

void	finish_ptr(t_tmp_arg *tmp, t_params *params,
		   unsigned int s_to_add, unsigned int s_to_print)
{
  int	is_add_0x;

  is_add_0x = 0;
  if (params->width >= params->precision && params->zero == 1
      && params->is_precision == 0 && params->less == 0
      && params->width > (signed)s_to_print)
  {
    if (params->plus == 1)
    {
      my_putchar('+');
      params->plus = 0;
    }
    my_putstr("0x");
    s_to_print = s_to_print - 1;
    is_add_0x = 1;
    add_zero(s_to_add);
  }
  else if (params->width >= (signed)s_to_print)
    add_space(s_to_add);
  if (params->less == 0)
  {
    if (params->plus == 1 && params->less == 0)
      my_putchar('+');
    my_put_adr(tmp->ptr, s_to_print, is_add_0x);
  }
}

unsigned int	print_ptr(t_tmp_arg *tmp, t_params *params,
			  unsigned int s_to_add, unsigned int s_to_print)
{
  unsigned int	chars_written;

  s_to_print = 12;
  if ((signed)s_to_print < params->precision)
    s_to_print = params->precision;
  if ((signed)s_to_print < params->width)
    s_to_add = params->width - s_to_print - 2;
  if (params->plus == 1 && params->less == 0 && s_to_add > 0)
    s_to_add = s_to_add - 1;
  chars_written = s_to_add + s_to_print;
  if (params->plus == 1 && params->less == 1)
  {
    my_putchar('+');
    s_to_add = s_to_add - 1;
  }
  if (params->space == 1 && params->plus == 0)
  {
    my_putchar(' ');
    s_to_add = s_to_add - 1;
  }
  if (params->less == 1)
    my_put_adr(tmp->ptr, s_to_print, 0);
  finish_ptr(tmp, params, s_to_add, s_to_print);
  return (chars_written);
}
