#include "libft.h"
#include "varint_test.h"

static void			type_usage( void )
{
	static char		*type[] = {"verif_op", "speed_op", "find_prime", "asn1_der_int_seq"};

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

# define TOTO 2

typedef struct  s_test
{
	int			i[TOTO];
}				t_test;

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (usage());
	if (!ft_strcmp("speed_op", argv[1]) && argc == 4)
		return (speed_op(argv));
	if (!ft_strcmp("verif_op", argv[1]) && argc == 4)
	{
		if (sizeof(V_TYPE) != 1
			&& ft_dprintf(2, VERIF_U8_ERR, KRED, KNRM))
			return (-1);
		return (verif_op(argv));
	}
	if (!ft_strcmp("find_prime", argv[1]) && argc == 3)
		find_prime(atoi(argv[2]), true);
	if (!ft_strcmp("asn1_der", argv[1])) {
		if (!ft_strcmp("basic", argv[2]) && argc == 4)
			return(basic_asn1_der_test(argv[3]));
		if (!ft_strcmp("rsa", argv[2]) && argc == 5)
			return (rsa_asn1_der_test(argv[3], argv[4]));
	}
	return (0);
}
