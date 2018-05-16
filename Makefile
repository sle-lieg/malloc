CC		= gcc
FLAGS	= -Wall -Wextra -Werror -g
RM		= rm -rf

SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = libft/
INC_DIR = inc/

SRC_F	=	malloc.c allocator.c treeChecker.c treeGetters.c treeInserter.c\
			treeRemover.c treeRotations.c treeTools.c free.c realloc.c calloc.c\
			debug.c
SRC = $(addprefix $(SRC_DIR), $(SRC_F))
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC		= -I $(INC_DIR)
INC_LIB = -I $(LIB_DIR)$(INC_DIR)
LIB		= -L$(LIB_DIR) -lftprintf
LIBFT	= $(LIB_DIR)libftprintf.a

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

EXEC	= libft_malloc_$(HOSTTYPE).so
SLINK	= libft_malloc.so

all: createDir $(LIBFT) $(EXEC)

createDir:
	@test -d $(SRC_DIR) || mkdir $(SRC_DIR)
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)

$(LIBFT):
	@echo "Creating $@..."
	@make -C $(LIB_DIR)

$(EXEC): $(OBJ)
	$(CC) -shared -o $@ $^ $(LIBFT)
	@ln -s $(EXEC) $(SLINK)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c -o $@ $< $(INC) $(INC_LIB)

clean:
	@$(RM) $(OBJ)
	make clean -C $(LIB_DIR)

fclean: clean
	@$(RM) $(EXEC)
	@$(RM) $(SLINK)	
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: clean fclean re