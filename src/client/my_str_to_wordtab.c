/*
** my_str_to_wordtab.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Thu Mar 19 16:49:31 2015 chapui_s
** Last update Thu Mar 19 16:51:27 2015 chapui_s
*/

#include "client.h"

static int	get_nb_word(char *s)
{
  int		nb;
  int		is_char;

  nb = 0;
  while (s && *s)
  {
    is_char = 0;
    while (*s && *s == ' ')
      s += 1;
    while (*s && *s != ' ' && ((is_char = 1)))
      s += 1;
    while (*s && *s == ' ')
      s += 1;
    if (is_char == 1)
      nb += 1;
  }
  return (nb);
}

static char	*get_this_word(char *s)
{
  char		*new;
  char		*end;
  int		size;
  int		i;

  end = s;
  while (*end && *end != ' ')
    end += 1;
  size = end - s;
  if ((new = (char*)malloc(size + 1)) == (char*)0)
    return ((char*)0);
  new[size] = 0;
  i = 0;
  while (i < size)
    new[i++] = *s++;
  new[i] = 0;
  return (new);
}

static int	get_words(char **tab, char *s)
{
  int		i;

  i = 0;
  while (s && *s)
  {
    while (*s && *s == ' ')
      s += 1;
    if ((tab[i++] = get_this_word(s)) == (char*)0)
      return (-1);
    while (*s && *s != ' ')
      s += 1;
    while (*s && *s == ' ')
      s += 1;
  }
  return (0);
}

char		**my_str_to_wordtab(char *s)
{
  char		**tab;
  int		nb_word;

  nb_word = get_nb_word(s);
  if ((tab = (char**)malloc(sizeof(char*) * (nb_word + 1))) == (char**)0
      || get_words(tab, s) == -1)
  {
    derror("error: malloc");
    return ((char**)0);
  }
  tab[nb_word] = (char*)0;
  return (tab);
}
