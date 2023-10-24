# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 12:53:31 by zwong             #+#    #+#              #
#    Updated: 2023/10/24 12:51:10 by zwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = 	main.cpp RPN.cpp

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(SRCS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

clean : 
	rm $(OBJS)

fclean : clean 
	rm -rf $(NAME)

re : fclean all