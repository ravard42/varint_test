#ifndef VARINT_TEST_H
# define VARINT_TEST_H

#include "libft.h"
#include "u64.h"
#include "first_primes.h"


# define VERIF_U8_ERR	"%sverif_op test need V_TYPE set to uint8_t%s\n"
# define EXP_ERR			"%stest difficulty must be 1 for exp test\n%sreduction mod16 to not overflow uint64_t is automated\n%s"
# define U64_OVFL			"%suint64_t C type ovfl -> varint op can't be verified%s\n"

void		show_var(int state, int res, t_u64 *u, t_varint *v);
bool		rand_init_u64_v(t_u64 *u64, t_varint *v, char **argv);
void		manual_init_1024_x2_prime(t_varint *v, t_varint *p, t_varint *q);
bool		verify(char *op, t_u64 *u64, t_varint *v);

int			speed_op(char **argv);
int			verif_op(char **argv);
t_varint	find_prime(V_LEN_TYPE len, bool print_prime);
int			basic_asn1_der_test(char *f_der);
int			rsa_asn1_der_test(char *in_der, char *out_der);



#endif
