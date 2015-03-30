/*
** calc_size.c for my_printf in /home/chapui_s/travaux/my_printf
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Thu Nov 14 13:30:17 2013 chapui_s
** Last update Sat Nov 30 12:29:39 2013 chapui_s
*/

unsigned int	calc_int(long long nb)
{
  unsigned int	size;

  size = 1;
  if (nb < 0)
  {
    size = 2;
    nb = -nb;
  }
  while (nb / 10 > 0)
  {
    size = size + 1;
    nb = nb / 10;
  }
  return (size);
}

unsigned int	calc_uint(unsigned long long nb)
{
  unsigned int	size;

  size = 1;
  while (nb / 10 > 0)
  {
    size = size + 1;
    nb = nb / 10;
  }
  return (size);
}

unsigned int	calc_octal(unsigned long long nb)
{
  unsigned int	size;

  size = 1;
  while (nb / 8 > 0)
  {
    nb = nb / 8;
    size = size + 1;
  }
  return (size);
}

unsigned int	calc_hexa(unsigned long long nb)
{
  unsigned int	size;

  size = 1;
  while (nb / 16 > 0)
  {
    nb = nb / 16;
    size = size + 1;
  }
  return (size);
}

unsigned int	calc_binary(unsigned long long nb)
{
  unsigned int	size;

  size = 1;
  while (nb / 2 > 0)
  {
    nb = nb / 2;
    size = size + 1;
  }
  return (size);
}
