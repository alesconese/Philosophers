# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/20 18:45:25 by ade-tole          #+#    #+#              #
#    Updated: 2024/04/20 18:45:28 by ade-tole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	gcc

SRCS	=	src/main.c src/time.c src/monitor.c src/init.c src/philo_loop.c

INCS	=	inc/philo.h

FLAGS	=	-Wall -Wextra -Werror -MMD -pthread -g -fsanitize=thread

OBJS	=	$(SRCS:.c=.o)

DEPS	=	$(SRCS:.c=.d)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o:%.c Makefile $(INCS)
				$(CC) $(FLAGS) -c $< -o $@

clean	:
				rm -rf $(OBJS) $(DEPS)
			
fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

-include $(DEPS)

.PHONY	:	all clean fclean re
