/*
** test.c for printf in /home/chapui_s/travaux/my_printf
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Mon Nov 11 21:32:07 2013 chapui_s
** Last update Sat Nov 30 12:30:18 2013 chapui_s
*/

#include <stdarg.h>
#include <stdlib.h>
#include "my_printf.h"

unsigned int	find_good_param(t_params *params, va_list *arg_tmp,
				const char *str, unsigned int i)
{
  int		arg_cur;
  int		arg_to_find;

  i = i + 1;
  arg_cur = 0;
  params->is_other_param = 1;
  arg_to_find = my_atoi(str + i);
  while (arg_cur < arg_to_find - 1)
  {
    va_arg(*arg_tmp, void *);
    arg_cur = arg_cur + 1;
  }
  while (str[i] >= '0' && str[i] <= '9')
    i = i + 1;
  return (i);
}

unsigned int	calc_size_to_print(t_tmp_arg *tmp, char c)
{
  if (c == 'd' || c == 'i')
    return (calc_int(tmp->t_int));
  if (c == 'u')
    return (calc_uint(tmp->uint));
  if (c == 'o')
    return (calc_octal(tmp->uint));
  if (c == 'x' || c == 'X')
    return (calc_hexa(tmp->uint));
  if (c == 'b')
    return (calc_binary(tmp->uint));
  if (c == 's' || c == 'S')
    return (my_strlen(tmp->t_char));
  return (0);
}

unsigned int	print_it(t_tmp_arg *tmp, t_params *params, char c,
			 unsigned int chars_to_save)
{
  unsigned int	wt;

  wt = 0;
  (c == 'd') ? (wt = print_int(tmp, params, 0, 0)) : (0);
  (c == 'i') ? (wt = print_int(tmp, params, 0, 0)) : (0);
  (c == 'u') ? (wt = print_uint(tmp, params, 0, 0)) : (0);
  (c == 'x') ? (wt = print_little_hexa(tmp, params, 0, 0)) : (0);
  (c == 'X') ? (wt = print_large_hexa(tmp, params, 0, 0)) : (0);
  (c == 'n') ? (wt = save_chars(tmp, chars_to_save)) : (0);
  (c == 'o') ? (wt = print_octal(tmp, params, 0, 0)) : (0);
  (c == 'c') ? (wt = print_char(tmp, params, 0, 0)) : (0);
  (c == 's') ? (wt = print_str(tmp, params, 0, 0)) : (0);
  (c == '%') ? (wt = print_percent()) : (0);
  (c == 'S') ? (wt = print_all_str(tmp, params, 0, 0)) : (0);
  (c == 'p') ? (wt = print_ptr(tmp, params, 0, 0)) : (0);
  (c == 'b') ? (wt = print_binary(tmp, params, 0, 0)) : (0);
  return (wt);
}

unsigned int	organize_and_print(t_struct_arg *args, const char *str,
				   unsigned int i, unsigned chars_to_save)
{
  t_params	*params;
  t_tmp_arg	*tmp;
  unsigned int	chars_written;

  params = (t_params*)malloc(sizeof(*params));
  tmp = (t_tmp_arg*)malloc(sizeof(*tmp));
  if (params == NULL || tmp == NULL)
    return (i);
  init_params_to_zero(params);
  if (is_parameter_number(str + i))
    i = find_good_param(params, &(args->arg_tmp), str, i);
  i = init_flags_width_prec(params, str, i + 1);
  i = init_length(params, str, i);
  if (params->is_width_in_arg == 1)
    params->width = va_arg(args->arg, int);
  if (params->is_precision_in_arg == 1)
    params->precision = va_arg(args->arg, int);
  if (params->is_other_param == 1)
    stock_arg(&(args->arg_tmp), tmp, str[i]);
  else if (params->is_other_param == 0)
    stock_arg(&(args->arg), tmp, str[i]);
  chars_written = print_it(tmp, params, str[i], chars_to_save);
  free(params);
  free(tmp);
  return (chars_written);
}

int		my_printf(const char *format, ...)
{
  t_struct_arg	args;
  unsigned int	i;
  unsigned int	chars_written;

  i = 0;
  chars_written = 0;
  va_start(args.arg, format);
  while (format[i])
  {
    va_start(args.arg_tmp, format);
    if (format[i] == '%' && is_to_convert(format + i) != 0)
    {
      chars_written = chars_written
	+ organize_and_print(&args, format, i, chars_written) - 1;
      i = i + is_to_convert(format + i);
    }
    else
      my_putchar(format[i]);
    chars_written = chars_written + 1;
    va_end(args.arg_tmp);
    i = i + 1;
  }
  va_end(args.arg);
  return ((int)chars_written);
}
