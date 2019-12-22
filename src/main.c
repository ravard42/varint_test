#include "libft.h"
#include "varint_test.h"

static void			type_usage( void )
{
	static char		*type[] = {"verif_op", "speed_op", "find_primes"};

	for (int i = 0; i < 3; i++)
		ft_printf("\n%s%s%s:\n", KBLU, type[i], KNRM);
			
}

//static void			opts_usage( void )
//{
//	static char		*opts[] = {"end0",
//									P, Q, R, S, "end1",
//									E, D, I, O,
//									DES_ONLY, A, K, V, SALT, PW, "end2"};
//	int				i;
//
//	i = -1;
//	ft_printf("\n%sStandard opts%s:\n", KYEL, KNRM);
//	while (ft_strcmp("end0", opts[++i]))
//		ft_printf(" %s\n", opts[i]);
//	ft_printf("\n%sMessage Digest opts%s:\n", KYEL, KNRM);
//	while (ft_strcmp("end1", opts[++i]))
//		ft_printf(" %s\n", opts[i]);
//	ft_printf("\n%sCipher opts%s:\n", KYEL, KNRM);
//	while (ft_strcmp("end2", opts[++i]))
//		ft_printf(" %s\n", opts[i]);

# define U "%susage%s: ./varint_test %stype %s[opts]%s [args]\n"

int			usage(void)
{
	ft_printf(U, KGRN, KWHT, KBLU, KYEL, KWHT);
	type_usage();
//	opts_usage();
	return (0);
}

int	main(int argc, char **argv)
{
	int			fd;

	if (argc == 1)
		return (usage());
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
		return (0);
	if (!ft_strcmp("speed_op", argv[1]) && argc == 4)
		return (speed_op(fd, argv));
	if (!ft_strcmp("verif_op", argv[1]) && argc == 4)
	{
		if (sizeof(V_TYPE) != 1
			&& ft_dprintf(2, VERIF_U8_ERR, KRED, KNRM))
			return (0);
		return (verif_op(fd, argv));
	}
	if (!ft_strcmp("find_prime", argv[1]) && argc == 3)
		find_prime(fd, atoi(argv[2]), true);
	close(fd);
	return (0);
}
