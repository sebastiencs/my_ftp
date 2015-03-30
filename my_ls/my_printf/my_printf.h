/*
** my_printf.h for my_printf in /home/chapui_s/travaux/my_printf
**
** Made by chapui_s
** Login   <chapui_s@epitech.net>
**
** Started on  Wed Nov 13 18:30:52 2013 chapui_s
** Last update Tue Mar 17 03:32:00 2015 chapui_s
*/

#ifndef MY_PRINTF_H_
# define MY_PRINTF_H_

# include <stdarg.h>

# define	HH	(1)
# define	H	(2)
# define	LL	(3)
# define	L	(4)
# define	J	(5)
# define	Z	(6)
# define	T	(7)

typedef struct	s_params
{
  int		is_other_param;
  int		less;
  int		plus;
  int		space;
  int		diez;
  int		zero;
  int		width;
  int		is_width_in_arg;
  int		is_precision;
  int		precision;
  int		is_precision_in_arg;
  int		length;
}		t_params;

typedef struct	s_struct_arg
{
  va_list	arg;
  va_list	arg_tmp;
}		t_struct_arg;

typedef struct		s_tmp_arg
{
  unsigned long long	uint;
  long long		t_int;
  char			*t_char;
  void			*ptr;
  unsigned int		*chars_to_save;
}			t_tmp_arg;

unsigned int		calc_int(long long nb);
unsigned int		calc_uint(unsigned long long nb);
unsigned int		calc_octal(unsigned long long nb);
unsigned int		calc_hexa(unsigned long long nb);
unsigned int		calc_binary(unsigned long long nb);
unsigned int		calc_binary(unsigned long long nb);
int			is_parameter_number(const char *str);
void			my_putstr(char *str);
void			my_putchar(char c);
void			add_space(unsigned int size_to_add);
void			add_zero(unsigned int size_to_add);
unsigned int		my_strlen(char *str);
int			my_atoi(const char *str);
unsigned long long	convert_hexa_length(unsigned long long nb,
					    t_params *params);
unsigned int		print_int(t_tmp_arg *tmp, t_params *params,
				  unsigned int s_to_add,
				  unsigned int s_to_print);
unsigned int		print_uint(t_tmp_arg *tmp, t_params *params,
				   unsigned int s_to_add,
				   unsigned int s_to_print);
unsigned int		print_char(t_tmp_arg *tmp, t_params *params,
				   unsigned int s_to_add,
				   unsigned int s_to_print);
unsigned int		print_large_hexa(t_tmp_arg *tmp, t_params *params,
					 unsigned int s_to_add,
					 unsigned int s_to_print);
unsigned int		print_little_hexa(t_tmp_arg *tmp, t_params *params,
					  unsigned int s_to_add,
					  unsigned int s_to_print);
unsigned int		print_octal(t_tmp_arg *tmp, t_params *params,
				    unsigned int s_to_add,
				    unsigned int s_to_print);
unsigned int		print_ptr(t_tmp_arg *tmp, t_params *params,
				  unsigned int s_to_add,
				  unsigned int s_to_print);
unsigned int		print_str(t_tmp_arg *tmp, t_params *params,
				  unsigned int s_to_add,
				  unsigned int s_to_print);
unsigned int		print_all_str(t_tmp_arg *tmp, t_params *params,
				      unsigned int s_to_add,
				      unsigned int s_to_print);
unsigned int		print_binary(t_tmp_arg *tmp, t_params *params,
				      unsigned int s_to_add,
				      unsigned int s_to_print);
void			my_putnbr(long long nb, int precision,
				  int size_nb, int is_plus);
void			my_put_unsigned_nb(unsigned long long nb,
					   int precision, char *base);
unsigned int		calc_size_to_print(t_tmp_arg *tmp, char c);
unsigned long long	convert_uint_length(unsigned long long nb,
					    t_params *params);
void			init_params_to_zero(t_params *params);
int			init_flags_width_prec(t_params *params,
					      const char *str,
					      unsigned int i);
int			init_length(t_params *params, const char *str,
				    unsigned int i);
void			stock_arg(va_list *arg, t_tmp_arg *tmp, char c);
unsigned int		is_to_convert(const char *str);
unsigned int		save_chars(t_tmp_arg *tmp, unsigned int chars_to_save);
unsigned int		print_percent(void);

#endif /* !MY_PRINTF_H_ */
