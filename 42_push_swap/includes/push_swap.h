/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:34:09 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/10 09:31:04 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H

# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h> 

typedef struct s_elem
{
	int				num;
	struct s_elem	*prev;
	struct s_elem	*next;
}	t_elem;

typedef struct s_stack {
	t_elem	*first;
	int		size;
	int		smallest;
	int		biggest;
}	t_stack;

typedef struct s_data {
	char	**split_arr;
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		max_value;
}	t_data;

/*srcs printf */

size_t			ft_strlcpy(char *dest, const char *src, size_t size);
char			*ft_strdup(const char *s);
size_t			ft_strlen(const char *str);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
unsigned int	ft_intlen_base(long int n, unsigned int base);
void			ft_putnbr_base(long int nbr, char *base);
unsigned int	ft_print_address_hex(unsigned long long address);
int				ft_printf(const char *arg, ...);

/*srcs push_swap */

/* utils.c */
int				ft_isdigit(char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			*ft_calloc(size_t nmeb, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
void			ft_bzero(void *s, size_t n);
long int		ft_atoi(const char *nptr);
char			**ft_split(char const *s, char c);

/* check_input.c */
int				check_input(char **split_arr);

/* stack.c */
t_elem			*new_elem(int num);
void			split_arr_to_stack_a(t_data *data, int *index_arr);
int				calc_stack_size(char **split_arr);
int				*calc_data_index(t_data *data);

/* print.c */
void			print_stack(t_stack *stack);
void			print_arr_index(int *arr, int size);

/* swap.c */
t_data			*swap(t_data *data, char which);
t_data			*swap_both(t_data *data);

/* rotate.c */
t_data			*rotate(t_data *data, char which);
t_data			*rev_rotate(t_data *data, char which);
t_data			*rotate_both(t_data *data);
t_data			*rev_rotate_both(t_data *data);

/* apply_rotations.c */
t_data			*apply_rotations(t_data *data, int rotations, char which);
t_data			*apply_rotations_both(t_data *data, int rotations);
t_data			*apply_rev_rotations(t_data *data, int rev_rotations,
					char which);
t_data			*apply_rev_rotations_both(t_data *data, int rev_rotations);

/* push.c */
t_data			*push(t_data *data, char which);

/* init.c */
t_data			*init(int argc, char **argv);

/* process.c */
void			process_input(t_data *data, char **argv, int argc);

/* terminate.c */
void			terminate_on_success(t_data *data);
void			terminate_on_error(t_data *data);

/* sort.c */
t_data			*sorting_decision(t_data *data, int size);
t_data			*rotate_optimization(t_data *data, int rotations, char which);
int				calc_chunk_size(int size);

/* chunk_sort.c */
t_data			*chunk_sort(t_data *data);

/* chunk_sort_utils.c */
t_data			*find_in_stack_and_push(t_data *data, int find);
int				find_in_chunk_r(t_stack *stack, int chunk_min, int chunk_max);
int				find_in_chunk_rr(t_stack *stack, int chunk_min, int chunk_max);

/* sort_two_three */
t_data			*sort_two(t_data *data);
t_data			*sort_three(t_data *data);

/* sort four_five */
t_data			*sort_four_five(t_data *data);
#endif
