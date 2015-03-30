/*
** init_struc.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sun Nov 17 00:30:20 2013 chapui_s
** Last update Tue Mar 17 03:25:54 2015 chapui_s
*/

#include <stdarg.h>
#include "my_printf.h"

void	init_params_to_zero(t_params *params)
{
  params->is_other_param = 0;
  params->less = 0;
  params->plus = 0;
  params->space = 0;
  params->diez = 0;
  params->zero = 0;
  params->width = 0;
  params->is_width_in_arg = 0;
  params->is_precision = 0;
  params->precision = 0;
  params->is_precision_in_arg = 0;
  params->length = 0;
}

int	init_flags_width_prec(t_params *params,
			      const char *str, unsigned int i)
{
  while (str[i] == '+' || str[i] == ' ' || str[i] == '-'
         || str[i] == '#' || str[i] == '0')
  {
    (str[i] == '-') ? (params->less = 1) : 0;
    (str[i] == '+') ? (params->plus = 1) : 0;
    (str[i] == ' ') ? (params->space = 1) : 0;
    (str[i] == '#') ? (params->diez = 1) : 0;
    (str[i] == '0') ? (params->zero = 1) : 0;
    i = i + 1;
  }
  if (str[i] >= '0' && str[i] <= '9')
    params->width = my_atoi(str + i);
  while (str[i] >= '0' && str[i] <= '9')
    i = i + 1;
  if (str[i] == '*')
    params->is_width_in_arg = 1;
  if (str[i] == '*')
    i = i + 1;
  if (str[i] == '.')
    params->is_precision = 1;
  if (str[i] == '.' && str[i + 1] == '*')
    params->is_precision_in_arg = 1;
  else if (str[i] == '.')
    params->precision = my_atoi(str + i + 1);
  return (i);
}

int	init_length(t_params *params, const char *str, unsigned int i)
{
  while (str[i] == '.' || str[i] == '*'
	 || (str[i] >= '0' && str[i] <= '9'))
    i = i + 1;
  if (str[i] == 'h' && str[i + 1] == 'h')
  {
    params->length = HH;
    i = i + 2;
  }
  else if (str[i] == 'l' && str[i + 1] == 'l')
  {
    params->length = LL;
    i = i + 2;
  }
  else if (str[i] == 'h' || str[i] == 'l' || str[i] == 'j'
           || str[i] == 'z' || str[i] == 't')
  {
    (str[i] == 'h') ? (params->length = H) : (0);
    (str[i] == 'l') ? (params->length = L) : (0);
    (str[i] == 'j') ? (params->length = J) : (0);
    (str[i] == 'z') ? (params->length = Z) : (0);
    (str[i] == 't') ? (params->length = T) : (0);
    i = i + 1;
  }
  return (i);
}
