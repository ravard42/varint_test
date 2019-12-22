#ifndef U64_H
#define U64_H

typedef struct			s_u64
{
	int8_t				sign;
	uint64_t				x;
}							t_u64;

static const t_u64   g_u64_0 = {1, 0x00};
static const t_u64   g_u64_1 = {1, 0x01};

void			u64_print(t_u64 u, int numb, char *col);
bool			u64_lt(t_u64 a, t_u64 b);
bool			u64_eq(t_u64 a, t_u64 b);
t_u64			u64_add(t_u64 a, t_u64 b);
t_u64			u64_sub(t_u64 a, t_u64 b);
t_u64			u64_mul(t_u64 a, t_u64 b);
t_u64			u64_exp(t_u64 a, t_u64 b);
t_u64			u64_div(t_u64 a, t_u64 e);
t_u64			u64_mod(t_u64 a, t_u64 e, bool pos);
t_u64 		u64_expmod(t_u64 a, t_u64 e, t_u64 m, bool pos);
uint64_t		gcd(uint64_t a, uint64_t b);
void			u64_eea(t_u64 *coef_r0, t_u64 a, t_u64 b);

#endif
