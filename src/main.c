#include "libft.h"
#include "varint_test.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (ft_printf("%sfor usage run: sh varint_test.sh%s\n", KYEL, KNRM));
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
