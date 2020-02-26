#include "libft.h"
#include "u64.h"

void					u64_print(t_u64 u, int numb, char *col)
{
	if (u.sign == 1)
		ft_dprintf(2, "%su64[%d] = %lx (%lu)%s\n", col, numb, u.x, u.x, KNRM);
	else
		ft_dprintf(2, "%su64[%d] = -%lx (-%lu)%s\n", col, numb, u.x, u.x, KNRM);
}

bool					u64_lt(t_u64 a, t_u64 b)
{
	int8_t	s;
	bool		ret;

	a.sign = (a.x == 0) ? 1 : a.sign;
	b.sign = (b.x == 0) ? 1 : b.sign;
	if ((s = a.sign) == b.sign)
	{
		if (s == 1)
			ret = (a.x < b.x) ? true : false;
		else
			ret = (a.x > b.x) ? true : false;
		return (ret);
	}
	if (a.sign < b.sign)
		return (true);
	return (false);
}

bool					u64_eq(t_u64 a, t_u64 b)
{
	a.sign = (a.x == 0) ? 1 : a.sign;
	b.sign = (b.x == 0) ? 1 : b.sign;
	if (a.sign == b.sign && a.x == b.x)
		return true;
	return (false);
}

t_u64					u64_add(t_u64 a, t_u64 b)
{
	t_u64		ret;

	if (a.sign == b.sign)
	{
		ret.sign = a.sign;
		ret.x = a.x + b.x;
		return (ret);
	}
	ret.sign = (a.x >= b.x) ? a.sign : b.sign;
	ret.x = (a.x >= b.x) ? a.x - b.x : b.x - a.x;
	return (ret);	
}

t_u64					u64_sub(t_u64 a, t_u64 b)
{
	b.sign *= -1;
	return (u64_add(a, b));
}

t_u64					u64_mul(t_u64 a, t_u64 b)
{
	t_u64	ret;
	
	ret.sign = a.sign * b.sign;
	ret.x = a.x * b.x;
	return (ret);
}

t_u64			u64_exp(t_u64 a, t_u64 e)
{
	t_u64		ret;
	uint64_t	i;

	if (e.x == 0)
	{
		ret.sign = 1;
		ret.x = 1;
		return (ret);
	}
	e.sign = 1;
	if (a.sign == 1)
		ret.sign = 1;
	else
		ret.sign = (e.x % 2) ? -1 : 1;
	ret.x = a.x;
	i = 1;
	while (i++ != e.x)
		ret.x *= a.x;
	return (ret);
}

t_u64			u64_div(t_u64 a, t_u64 b)
{
	t_u64		ret;

	ret.sign = a.sign * b.sign;
	ret.x = a.x / b.x;
	return (ret);
}

t_u64			u64_mod(t_u64 a, t_u64 b, bool eucl)
{
	t_u64		ret;

	ret.sign = a.sign;
	ret.x = a.x % b.x;
	if (eucl && ret.sign == -1)
	{
		ret.sign = 1;
		ret.x = b.x - ret.x; 
	}
	return (ret);
}

t_u64 	u64_expmod(t_u64 a, t_u64 e, t_u64 m, bool pos)
{
	int8_t	j;
	t_u64 	ret;

	if (e.x == 0)
	{
		ret.sign = 1;
		ret.x = 1;
		return (ret);
	}
	if (a.x == 0)
	{
		ret.sign = 1;
		ret.x = 0;
		return (ret);
	}
	e.sign = 1;
	m.sign = 1;

	j = 63;
	while ((e.x >> j & 1) == 0)
		j--;
	ret = u64_mod(a, m, pos);
	while (--j >=0)
	{
		ret = u64_mod(u64_mul(ret, ret), m, pos);
		if (e.x >> j & 1)
			ret =  u64_mod(u64_mul(ret, a), m, pos);
	}
	return (ret);
}

uint64_t		gcd(uint64_t a, uint64_t b)
{
	uint64_t		r[2];
	uint64_t		tmp;

	r[0] = (a > b) ? a : b;
	r[1] = (a > b) ? b : a;	
	while (r[1])
	{
		tmp = r[0] % r[1];
		r[0] = r[1];
		r[1] = tmp;
	}
//	ft_printf("%sGCD(%lu, %lu) = %lu%s\n", KYEL, a, b, r[0], KNRM);
	return (r[0]);
}

// cf v_sort in varint/v_tools.c
uint8_t    u64_sort(t_u64 *a, t_u64 *b, int8_t *sign) 
{
   t_u64 tmp;
	int8_t		tmp_sign;

	if (sign)
	{
		sign[0] = a->sign;
		sign[1] = b->sign;
		a->sign = 1;
		b->sign = 1;
	}	
   if (u64_lt(*a, *b))
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
		if (sign)
		{
			tmp_sign = sign[0];
			sign[0] = sign[1];
			sign[1] = tmp_sign;
		}
		return (1);
	}
	return (0);
}

void		u64_eea(t_u64 *coef_r0, t_u64 a, t_u64 b)
{
	int8_t	sign[3];
	t_u64		r[2]; // deux derniers restes
	t_u64		coef_r1[2]; // coef alpha et beta de r[1]
	t_u64		tmp[2];	
								

	sign[2] = u64_sort(&a, &b, sign);
	r[0] = a;
	coef_r0[0] = g_u64_1;
	coef_r0[1] = g_u64_0;
	r[1] = b;	
	coef_r1[0] = g_u64_0;
	coef_r1[1] = g_u64_1;

	while (r[1].x)
	{
		tmp[0] = u64_mod(r[0], r[1], true);
		tmp[1] = u64_div(u64_sub(r[0], tmp[0]), r[1]);
		r[0] = r[1];
		r[1] = tmp[0];

		tmp[0] = u64_sub(coef_r0[0], u64_mul(tmp[1], coef_r1[0]));
		tmp[1] = u64_sub(coef_r0[1], u64_mul(tmp[1], coef_r1[1]));

		coef_r0[0] = coef_r1[0];
		coef_r0[1] = coef_r1[1];
		coef_r1[0] = tmp[0];
		coef_r1[1] = tmp[1];
	}
	coef_r0[0].sign *= (sign[0] != a.sign) ? -1 : 1;
	(coef_r0[1]).sign *= (sign[1] != a.sign) ? -1 : 1;
	if (sign[2])
	{
		tmp[0] = coef_r0[0];
		coef_r0[0] = coef_r0[1];
		coef_r0[1] = tmp[0];
	}	
}
