#include "varint_test.h"

/*
** Probabilistic Primality Test
*/

static t_varint		v_rand_a(t_varint n)
{
	V_TYPE				rand_a[n.len];
	t_varint				a;

	if (n.len == 1)
		rand_a[0] = ft_range(*(V_TYPE *)ft_rand(rand_a, V_LEN), 2, n.x[0] - 1);
	else
	{
		ft_rand(rand_a, n.len * V_LEN);
		rand_a[0] = ft_range(rand_a[0], 2, V_SUP);
		rand_a[n.len - 1] = ft_range(rand_a[0], 0, n.x[n.len - 1] - 1);
	}
	a = v_init(1, rand_a, n.len);
	return (a);
}

static int	miller_witness(t_varint n, t_varint s, t_varint d)
{
	t_varint	n_min_1;
	t_varint	a;
	t_varint r;
	t_varint	i;

	n_min_1 = v_dec(n);
	a = v_rand_a(n);	
	r = v_expmod(a, d, n, true);
	if (is_g_v(1, r)
		|| v_cmp(r, "-eq", n_min_1))
		return false;
	i = g_v[1];
	while (v_cmp(i, "-lt", s))
	{
		r = v_expmod(r, g_v[2], n, true);
		if (v_cmp(r, "-eq", n_min_1))
			return (false);
		i = v_inc(i);
	}
	return (true);
}


static bool	first_prime_composite(t_varint n)
{
	t_varint	p;
	int		i;

	i = -1;
	while (++i < 2048)
	{
		p = g_v[0];
		p.x[0] = g_prime[i];
		p.x[1] = (V_SUP == 0xff) ? *((uint8_t *)(g_prime + i) + 1) : 0;
		p.len = (p.x[1]) ? 2 : 1;
		if (v_cmp(n, "-eq", p))
			return (false);
		if(is_g_v(0, v_mod(n, p, true)))
			return (true);
	}
	return (false);
}

bool			prob_prim_test(t_varint n)
{
	int8_t	nb_a;
	t_varint	n_min_1;
	t_varint s;
	t_varint d;

	if (first_prime_composite(n)
		|| v_cmp(n, "-le", g_v[2]))
		return (false);
	nb_a = 1;
	n_min_1 = v_dec(n);
	s = g_v[1];
	while (is_g_v(0, v_mod(n_min_1, v_exp(g_v[2], s), true)))
		s = v_inc(s);
	s = v_dec(s);
	d = v_div(n_min_1, v_exp(g_v[2], s));
	while (nb_a--)
		if (miller_witness(n, s, d))
			return (false);
	return (true);
}

t_varint		find_prime(V_LEN_TYPE len, bool print_prime)
{
	t_varint n;

	n = v_rand(len, false);
	n.x[0] += (n.x[0] % 2 == 0) ? 1 : 0;	
	while (!prob_prim_test(n))
	{
		n = v_rand(len, false);
		n.x[0] += (n.x[0] % 2 == 0) ? 1 : 0;	
	}
	if (print_prime)
	{
		if (V_BIT_LEN == 8)
		{
			for(int i = len - 1; i != 0; i--)
				ft_printf("%s%02x%s", KGRN, n.x[i], KNRM);
			ft_printf("%s%02x%s\n", KGRN, n.x[0], KNRM);
		}
		else if (V_BIT_LEN == 64)	
		{
			for(int i = len - 1; i != 0; i--)
				ft_printf("%s%016lx%s", KGRN, n.x[i], KNRM);
			ft_printf("%s%016lx\n%s", KGRN, n.x[0], KNRM);
		}
		else
			ft_dprintf(2, "bad V_TYPE for printing\n");
	}
	return (n);	
}
