/*
** get_next_line.h for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 10:39:01 2015 chapui_s
** Last update Tue Mar 17 22:32:10 2015 chapui_s
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# include <string.h>

# define BUF_SIZE	42

typedef struct	s_fd
{
  char		*str;
  int		fd;
  struct s_fd	*next;
}		t_fd;

char	*get_next_line(const int fd);
void	*free_ptr(void *ptr, t_fd *pile);

#endif /* !GET_NEXT_LINE_H_ */
