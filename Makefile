# Meta

NAME := fdf

SRCDIR := ./src
OBJDIR := ./obj

SRC :=\
main.c \
app.c \
camera.c \
scene.c \
ft_math.c \
int2.c \
float3.c \
float3_transform.c \
float4x4.c \
float4x4_transform.c \
window.c \
input.c \
draw.c \
rasterizer.c \
mesh.c \
mesh_util.c \

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=%.d)

ARCH := $(shell uname)

# MiniLibX

ifeq ($(ARCH), Linux)
MLX_DIR := ./third-party/minilibx-linux
MLX_AR := $(MLX_DIR)/libmlx.a
MLX_LD := -lXext -lX11 -L$(MLX_DIR) -lmlx 
else
MLX_DIR := /usr/local/include
MLX_AR := /usr/local/lib/libmlx.a
MLX_LD := -lmlx -framework OpenGL -framework AppKit
endif

# Libft

FT_DIR := ./third-party/libft
FT_AR := $(FT_DIR)/libft.a
FT_LD := -L ./third-party/libft -lft

# Compilation and linking

CC := cc
INCLUDE := -I$(MLX_DIR) -I$(FT_DIR) -I$(SRCDIR)
CFLAGS := -march=native -Ofast -Wall -Werror -Wextra $(INCLUDE)
LDFLAGS := -lm $(MLX_LD) $(FT_LD) 

# Rules

all: $(NAME)

$(NAME): $(MLX_AR) $(FT_AR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

$(MLX_AR):
	$(MAKE) -C $(MLX_DIR)

$(FT_AR):
	$(MAKE) -C $(FT_DIR)

# Include dependency info
-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c  
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(CFLAGS) -MMD -c $< -o $@ 

clean:
	/bin/rm -rf $(OBJDIR)
ifeq ($ARCH, Linux)
	make clean -C $(MLX_DIR)
endif

fclean: clean
	make fclean -C $(FT_DIR)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all so clean fclean re
