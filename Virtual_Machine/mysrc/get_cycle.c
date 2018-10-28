#include "vm.h"

int		check_operation(int a)
{
	if (a > 0 && a < 17)
		return (1);
	else
		return (0);
}

void	get_cycle(t_env *env, t_proc *proc)
{
    int a;

	a = env->a[proc->pc].hex & 0xFF;
	if (check_operation(a))
	{
		proc->cycle += env->op_tab[a].nbr_cycles - 2;
		proc->running = 1;
	}
}
