#ifndef VARINT_TEST_H
# define VARINT_TEST_H

#include <time.h>
#include <stdio.h>
#include "libft.h"
#include "u64.h"
#include "first_primes.h"

# define EXP_ERR			"%stest difficulty must be 1 for exp test\n%sreduction mod16 to not overflow uint64_t is automated\n%s"
# define U64_OVFL			"%suint64_t C type ovfl -> varint op can't be verified%s\n"

void			show_var(int state, int res, t_u64 *u, t_varint *v);
bool			rand_init_u64_v(t_u64 *u64, t_varint *v, char **argv);
bool			manual_init_u64_v(t_u64 *u64, t_varint *v);
t_varint		*asn1_der_init(t_varint *dest, char *der_file);
bool			verify(char *op, t_u64 *u64, t_varint *v);

int			op(char **argv);
int			nnaumenk_speed_cmp(t_varint *v);
bool			nnaumenk_show_n_free(t_bigint *b, t_varint *v, bool show, bool free);
int			verif_op(char **argv);
t_varint	find_prime(int16_t len, bool print_prime);
int			basic_asn1_der_test(char *f_der);
int			rsa_asn1_der_test(char *in_der, char *out_der);



#endif
