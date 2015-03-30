/*
** check.c for my_printf in /home/chapui_s/travaux/my_printf/new
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sun Nov 17 00:26:04 2013 chapui_s
** Last update Sat Nov 30 12:29:50 2013 chapui_s
*/

int		is_parameter_number(const char *str)
{
  unsigned int	i;

  i = 0;
  if (str[i] == '%')
    i = i + 1;
  while (str[i] && str[i] >= '0' && str[i] <= '9')
    i = i + 1;
  if (i > 0 && str[i] == '$' && str[i - 1] != '%')
    return (i);
  return (0);
}

unsigned int	check_last_char(const char *str, unsigned int i)
{
  if (str[i] == 'h' || str[i] == 'l' || str[i] == 'z'
      || str[i] == 'j' || str[i] == 't')
    i = i + 1;
  if (str[i] == 'h' || str[i] == 'l')
    i = i + 1;
  if (i == 0 && str[1] == '$')
    return (0);
  if (str[i] == 'd' || str[i] == 's' || str[i] == 's' || str[i] == 'u'
      || str[i] == 'x' || str[i] == 'X' || str[i] == 'o' || str[i] == 'p'
      || str[i] == '%' || str[i] == 'i' || str[i] == 'b' || str[i] == 'S'
      || str[i] == 'n' || str[i] == 'c')
    return (i);
  return (0);
}

unsigned int	is_to_convert(const char *str)
{
  unsigned int	i;

  i = 0;
  if (str[i] == '%')
    i = i + 1;
  if (is_parameter_number(str) > 0)
    i = is_parameter_number(str) + 1;
  while (str[i] == '+' || str[i] == ' ' || str[i] == '-'
	 || str[i] == '#' || str[i] == '0')
    i = i + 1;
  if (str[i] == '*')
    i = i + 1;
  while (str[i] >= '0' && str[i] <= '9')
    i = i + 1;
  if (str[i] == '.')
  {
    i = i + 1;
    if (str[i] == '*')
      i = i + 1;
    while (str[i] >= '0' && str[i] <= '9')
      i = i + 1;
  }
  return (check_last_char(str, i));
}
