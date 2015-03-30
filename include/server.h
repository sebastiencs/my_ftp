/*
** server.h for epitech in /home/chapuis_s/rendu/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Mar 16 06:33:50 2015 chapui_s
** Last update Sun Mar 22 16:00:18 2015 chapui_s
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "common.h"

/*----------Enums----------*/

enum		e_mode_thread
{
  READ,
  WRITE
};

typedef enum	e_status
{
  NOT_LOGGED_IN = 0,
  LOGGED_IN = 1
}		t_status;

typedef enum	e_mode
{
  NONE = 0,
  ACTIVE = 1,
  PASSIVE = 2
}		t_mode;

/*-------Structures--------*/

typedef struct	s_help
{
  char		*name;
  char		*msg;
}		t_help;

typedef struct	s_server
{
  int		port;
  int		fd;
  int		fd_client;
  char		*local_ip;
}		t_server;

typedef struct	s_user_list
{
  char		*name;
  char		*password;
  char		*directory;
}		t_user_list;

typedef struct	s_reply
{
  int		num;
  char		*msg;
  int		complete_msg;
}		t_reply;

typedef struct	s_thread_info
{
  int		read_or_write;
  int		fd;
  void		*data;
  size_t	size_data;
}		t_thread_info;

typedef struct		s_user
{
  int			fd;
  int			run;
  char			*buffer;
  t_status		status;
  t_user_list		user;
  char			*local_ip;
  t_mode		mode;
  t_thread_info		*thread_info;
  char			*dir_current;
}			t_user;

typedef struct	s_cmd
{
  char		*name;
  int		(*func)(t_user *user, char *param);
  int		need_logged_in;
}		t_cmd;

/*----------Defines----------*/

# define CLIENTS_MAX		(255)
# define SIZE_MAX_BUFFER	(1024)
# define ADDR_LOCAL_IP		("8.8.8.8")
# define PORT_LOCAL_IP		(53)
# define PORT_PASSIVE_MIN	(5000)
# define PORT_PASSIVE_MAX	(6000)
# define TMP_LIST_DIR		("/tmp/tmp_listing")

/*---------Globales----------*/

/* int		passive_mode_on; */
sem_t		g_lock;
sem_t		g_lock_finish;
int		g_transfer_completed;

/*--------Prototypes---------*/

int		get_port(t_server *server, char *port);
int		usage(void);
int		create_server(t_server *server);
int		accept_client(t_server *server);
int		set_user(t_user *user, char *param);
int		send_reply(int fd, int num, char *opt_msg);
int		send_syst(t_user *user, char *param);
int		password(t_user *user, char *param);
int		enter_passive_mode(t_user *user, char *param);
void		*run_passive(t_thread_info *info);
int		list_directory(t_user *user, char *param);
int		check_directory(t_user *user, char *param, char *buffer);
char		*convert_telnet(char *home);
void		free_list_users(t_user_list *list, int nb);
t_user_list	*get_list_users(int *nb_users);
t_user_list	*get_users(int fd, t_user_list *list, int *nb);
void		get_new_user(int fd, t_user_list *tmp);
int		change_dir(t_user *user, char *param);
int		change_dir_up(t_user *user, char *param);
int		quit(t_user *user, char *param);
int		get_dir(t_user *user, char *param);
int		delete(t_user *user, char *param);
int		check_directory(t_user *user, char *param, char *buffer);
char		*manage_from_root(t_user *user, char *buffer, char *param);
int		help(t_user *user, char *param);
int		noop(t_user *user, char *param);
size_t		get_size_file(char *file);
int		send_file(t_user *user, char *param);
int		get_type(t_user *user, char *param);
int		receive_file(t_user *user, char *param);
int		create_thread_detach(t_thread_info *info, t_user *user);
int		receive_clients(t_server *server);
int		get_command(t_user *user);
int		exec_command(t_user *user);
int		get_command(t_user *user);

#endif /* !SERVER_H_ */
