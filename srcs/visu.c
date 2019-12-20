#include "vm_corewar.h"

void		simple_hexdump(t_all *all)
{
	int	octet;

	octet = 0;
	printf("0x%04x : ", octet);
	while (octet < MEM_SIZE)
	{ 
		printf("%.2hhx ", all->map.character[octet]);
		if (octet && !((octet + 1) % 64) && octet + 1 < MEM_SIZE)
		{
			printf("\n");
			printf("0x%04x : ", octet + 1);
		}
		octet++;
	}
	printf("\n");
}

void		hexdump_map_square(t_all *all)
{
    int			proc;
	int			i;
	char		*last_color;

	if (!(all->flag & FLAG_VISU))
		return ;
	i = -1;
	last_color = NULL;
	moveTo(0, 0);
	while (++i < MEM_SIZE)
	{
		proc = is_a_process(all, i);
		if (proc)
		{
			if (last_color != background_color[proc])
				printf("%s", (last_color = background_color[proc]));
		}
		else if (last_color != all->map.color_in_map[i])
			printf("%s", (last_color = all->map.color_in_map[i]));
		if (!((i + 1) % 64))
			printf("%.2hhx\n", all->map.character[i]);
		else
			printf("%.2hhx\033[0;39m %s", all->map.character[i], last_color);
	}
	read(0, &i, 4);
}
