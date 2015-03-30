/*
** ls_str.c for my_ls in /home/chapui_s/travaux/my_ls
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Sat Nov 30 23:44:29 2013 chapui_s
** Last update Tue Mar 17 04:11:31 2015 chapui_s
*/

char	to_lower(char c)
{
  if (c >= 'A' && c <= 'Z')
    return (c + 32);
  return (c);
}

int	my_strcmp(char *s1, char *s2)
{
  int	i;
  int	is_change;

  i = 0;
  is_change = 0;
  while (s1[i] || s2[i])
  {
    while ((s1[i] == '#' || s1[i] == '-' || s1[i] == '.' || s1[i] == '_'
	    || s1[i] == '(' || s1[i] == ')' || s1[i] == ' ' || s1[i] == '['
	    || s1[i] == ']' || s1[i] == '~') && ++is_change)
      s1 = s1 + 1;
    while ((s2[i] == '#' || s2[i] == '-' || s2[i] == '.' || s2[i] == '_'
	    || s2[i] == '(' || s2[i] == ')' || s2[i] == ' ' || s2[i] == '['
	    || s2[i] == ']' || s2[i] == '~') && ++is_change)
      s2 = s2 + 1;
    if (to_lower(s1[i]) < to_lower(s2[i]))
      return (-1);
    if (to_lower(s1[i]) > to_lower(s2[i]))
      return (1);
    i = i + 1;
  }
  if (is_change > 0)
    return (1);
  return (0);
}

unsigned int	my_strlen(char *str)
{
  unsigned int	i;

  i = 0;
  while (str[i])
    i = i + 1;
  return (i);
}
