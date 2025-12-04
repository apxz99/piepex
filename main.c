#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include "./libft.h"

char *find_envpath(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if(ft_strncmp(envp[i],"PATH=",5) == 0)
			return envp[i] + 5;
		i++;
	}
	return NULL;
}
int	main(int argc, char **argv, char **envp)
{
	char *envpath;
	char **path;

	envpath = find_envpath(envp);
	printf("%s\n",envpath);

	path = ft_split(envpath, ':');
	char *temp[10];
	for (int i = 0; path[i] ; i++)
	{
		temp[i] = ft_strjoin(path[i], "/ls");
		if(access(temp[i], X_OK))
		{
			printf("X_OK : %s\n",temp[i]);
			return(0);
		}
		printf("%s",temp[i]);
	}

	//for(int i = 0; envp[i]; i++)
	//{
	//	printf("%s\n",envp[i]);
	//}
	return(0);
}