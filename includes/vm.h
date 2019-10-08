#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct		s_champs
{
	char			*name;
	char			*comment;
	void			*executable_code;
	size_t			size_name;
	size_t			size_comment;
	size_t			size_executable;
}					t_champs;

typedef struct		s_all
{
	int				*fd;
	t_champs		*champ;
	size_t			nb_champ;
    unsigned int	flag;
}					t_all;