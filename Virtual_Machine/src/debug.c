#include "vm.h"

/*void    debug_player(t_player *p)
{
   	printf("char	*name = %s\n", p->name);
   	printf("char	*comment = %s\n", p->comment);
   	printf("char	content[CHAMP_MAX_SIZE + 1] = %s\n", p->content);
   	printf("int		nbr = %d \n", p->nbr);
   	printf("int		size = %d\n", p->size);
   	printf("int		live = %d \n", p->live);
   	printf("int		color = %d \n", p->color);
   	printf("int		start = %d \n", p->start);
}*/

/*void    debug_arena(t_env *env)
{
    int i;
    int players;

    i = -1;
    players = ft_parrlen((void**)env->player);
    while (++i < players)
    {
		printf(" START = %d\n",env->player[i]->start);
    }
    int hex = 0;
    i = 0;
    while (i < MEM_SIZE)
	{
		if ((i) % (32) == 0)
			printf("0x%04x  ", hex);
		printf("%02x ", 0xFF & env->a[i].hex);
		if ((i + 1) % (32) == 0)
		{
			printf("\n");
			hex += 32;
		}
		i++;
	}
}*/

void    analyse(int *tab, t_proc *proc)
{
            int i = -1;
        printf("---Byte ANALYSE---\n");
        printf("        %d\n", proc->pc);
        i = -1;
        while(tab && ++i < 16)
            printf("REG[%d] = %d   ", i + 1, proc->reg[i]);
        printf("\n\n");
}
