NAME = libftprintf.a

CC = gcc -Wall -Wextra -Werror -g

INC_LIB 	= -I ./inc/
PATH_PRINTF = ./printf_src/
PATH_LIB 	= ./libft_src/
PATH_OBJ 	= ./obj/

SRC_PRINTF = 	ft_printf.c parsing.c type_s.c type_d_i.c type_p.c\
				type_o_big_o.c type_u.c type_x.c type_big_x.c type_c_big_d.c\
				type_big_c.c type_big_s.c type_b.c unicode_tools.c parsing_tools.c

SRC_LIB = 	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c\
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c\
			ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c\
			ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c\
			ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c\
			ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c\
			ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c\
			ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c\
			ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_putchar.c ft_putstr.c\
			ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c\
			ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c\
			ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_isupper.c\
			ft_islower.c ft_lstaddend.c ft_d_lstaddfront.c ft_d_lstaddend.c\
			ft_d_lstdel.c ft_d_lstdelone.c ft_switchchar.c ft_itoa.c\
			ft_count_n.c ft_pow.c ft_itoa_base.c ft_wchar_len.c ft_wstr_len.c\
			ft_is_digit_str.c ft_atoil.c ft_is_int_size.c ft_get_next_line.c\
			ft_free_split.c ft_count_char.c

LIBOBJ 	  = $(addprefix $(PATH_OBJ), $(SRC_LIB:.c=.o))
PRINTFOBJ = $(addprefix $(PATH_OBJ), $(SRC_PRINTF:.c=.o))

all : $(NAME)

$(NAME) : $(LIBOBJ) $(PRINTFOBJ)
	@echo "\033[1;32m◊ +++++ created $(NAME) : √\033[0m"
	@ar rc $(NAME) $(PRINTFOBJ) $(LIBOBJ)
	@ranlib $(NAME)

$(PATH_OBJ)%.o: $(PATH_LIB)%.c
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@$(CC) -o $@ -c $(INC_LIB) $<

$(PATH_OBJ)%.o: $(PATH_PRINTF)%.c
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@$(CC) -o $@ -c $(INC_LIB) $<

.PHONY : fclean clean re

fclean : clean
	@echo "\033[1;31m◊ ----- DELETING $(NAME)	: √\033[0m"
	@rm -rf $(NAME)

clean :
	@echo "\033[1;31m◊ ----- DELETING OBJECTS 	: √\033[0m"
	@rm -rf	$(PRINTFOBJ) $(LIBOBJ)

re : fclean all
