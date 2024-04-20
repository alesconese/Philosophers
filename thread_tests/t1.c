#include "../philo.h"

void	*routine()
{
	printf("Test fromm threads\n");
	sleep(3);
	printf("Ending thread\n");
}

int	main(int argc, char **argv)
{
	pthread_t	t1, t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0 || pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_join(t1, NULL) != 0 || pthread_join(t2, NULL) != 0)
		return 2;
	return 0;
}
