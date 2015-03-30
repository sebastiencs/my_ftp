/*
** print.c for my_printf in /home/chapui_s/travaux/my_printf
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Thu Nov 14 19:00:28 2013 chapui_s
** Last update Tue Mar 17 04:17:26 2015 chapui_s
*/

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "my_printf.h"

long long	convert_int_length(long long nb, t_params *params)
{
  if (params->length == HH)
    return ((char)nb);
  if (params->length == H)
    return ((short)nb);
  if (params->length == L)
    return ((long)nb);
  if (params->length == LL)
    return ((long long)nb);
  if (params->length == Z)
    return ((size_t)nb);
  if (params->length == J)
    return ((intmax_t)nb);
  if (params->length == T)
    return ((ptrdiff_t)nb);
  return ((int)nb);
}

void	my_putnbr(long long nb, int precision, int is_space, int is_plus)
{
  int	size_nb;

  size_nb = calc_int(nb);
  if (nb < 0)
  {
    my_putchar('-');
    nb = -nb;
  }
  else if (nb >= 0 && (is_space == 1 || is_plus == 1))
  {
    if (is_plus == 1)
      my_putchar('+');
    precision = precision - 1;
  }
  while (precision > size_nb)
  {
    my_putchar('0');
    precision = precision - 1;
  }
  if (nb >= 10)
    my_putnbr(nb / 10, 0, size_nb, 0);
  my_putchar((nb % 10) + '0');
}

void	begin_int(t_tmp_arg *tmp, t_params *params,
		  unsigned int *s_to_add, unsigned int *s_to_print)
{
  tmp->t_int = convert_int_length(tmp->t_int, params);
  *s_to_print = calc_size_to_print(tmp, 'd');
  if ((signed)*s_to_print < params->precision)
    *s_to_print = params->precision;
  if (params->space == 1 && params->plus == 0 && tmp->t_int >= 0)
    my_putchar(' ');
  if (tmp->t_int < 0 && params->precision >= (signed)*s_to_print)
    *s_to_print = *s_to_print + 1;
  if ((params->plus == 1 || params->space == 1) && tmp->t_int >= 0)
    *s_to_print = *s_to_print + 1;
  if ((signed)*s_to_print < params->width)
    *s_to_add = params->width - *s_to_print;
  if (params->less == 1)
    my_putnbr(tmp->t_int, *s_to_print, params->space, params->plus);
}

void	inter_int(t_tmp_arg *tmp, t_params *params,
		  unsigned int *s_to_add, unsigned int *s_to_print)
{
  if (params->zero == 1 && params->is_precision == 0 && tmp->t_int < 0
      && params->less == 0)
  {
    my_putchar('-');
    tmp->t_int = -(tmp->t_int);
    *s_to_print = *s_to_print - 1;
    params->plus = 0;
  }
  else if (params->zero == 1 && params->plus == 1 && params->less == 0
    && tmp->t_int >= 0)
  {
    if (params->less == 1)
      my_putchar('+');
    if (params->less == 1)
      params->plus = 0;
    if (params->zero == 1 && params->plus == 0)
      *s_to_add = *s_to_add + 1;
    if (params->space == 0)
      *s_to_add = *s_to_add - 1;
  }
}

unsigned int	print_int(t_tmp_arg *tmp, t_params *params,
			  unsigned int s_to_add, unsigned int s_to_print)
{
  unsigned int	chars_written;

  chars_written = 0;
  begin_int(tmp, params, &s_to_add, &s_to_print);
  chars_written = s_to_print + s_to_add;
  inter_int(tmp, params, &s_to_add, &s_to_print);
  if (params->width >= params->precision && params->zero == 1
      && params->is_precision == 0 && params->less == 0
      && params->width > (signed)s_to_print)
    add_zero(s_to_add);
  else if (params->width >= (params->precision)
	   && params->width > (signed)s_to_print)
    add_space(s_to_add);
  if (params->less == 0)
    my_putnbr(tmp->t_int, s_to_print, params->space, params->plus);
  return (chars_written);
}
