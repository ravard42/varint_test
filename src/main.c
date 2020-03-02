#include "libft.h"
#include "varint_test.h"

static void			type_usage( void )
{
	static char		*type[] = {"op", "u64_cmp", "nnaumenk_cmp", "find_prime", "asn1_der"};

	for (int i = 0; i < 4; i++)
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
	return (-1);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (usage());
	else if (!ft_strcmp("op", argv[1]) && argc == 4)
		return (op(argv));
	else if (!ft_strcmp("u64_cmp", argv[1]) && argc == 4)
		return (u64_cmp(argv));
//	else if (!ft_strcmp("nnaumenk_cmp", argv[1]) && argc == 4)
//		return (nnaumenk_cmp(argv));
	else if (!ft_strcmp("find_prime", argv[1]) && argc == 3)
		find_prime(atoi(argv[2]), true);
	else if (!ft_strcmp("asn1_der", argv[1]) && argc > 2)
		if (!ft_strcmp("rsa", argv[2]) && argc == 5)
			return (rsa_asn1_der_test(argv[3], argv[4]));
	return (0);
}
