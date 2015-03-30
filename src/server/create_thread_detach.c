/*
** create_thread_detach.c for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Tue Mar 17 19:48:53 2015 chapui_s
** Last update Tue Mar 17 19:55:59 2015 chapui_s
*/

#include "server.h"

int			create_thread_detach(t_thread_info *info,
					     t_user *user)
{
  pthread_t		thread;
  pthread_attr_t	attr;

  (void)user;
  if (pthread_attr_init(&attr) == -1)
    return (-1);
  if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) == -1)
    return (-1);
  if (pthread_create(&thread, &attr, (void *(*)(void*))run_passive,
		     info) == -1)
    return (-1);
  return (0);
}
