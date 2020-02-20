#include "varint_test.h"

/*
**	nnaumenk time-complexity comparison
** Only for op.c
**
*/

bool			nnaumenk_show_n_free(t_bigint *b, t_varint *v, bool show, bool freee)
{
	char		name[3] = {'b', '0', 0};
	if (show)
		ft_printf("\n%sNNAUMENK%s\n", KYEL, KNRM);
	for (int i = 0; i < 5; i++)
	{
		name[1] = '0' + i;
		if (show && b[i].value)
			ft_bigint_print(name, b + i);
		if (freee && b[i].value)
			free(b[i].value);
	}
	if (show)
	{
		ft_printf("\n%sRAVARD%s\n", KYEL, KNRM);
		show_var(0, 2, NULL, v);
		ft_putchar('\n');
	}
	return (true);
}


static bool	init_nnaumenk(t_bigint *b, t_varint *v)
{
	for (int i = 0; i < 3; i++)
	{
		b[i].size = v[i].len;
		b[i].value = (unsigned char *)malloc(sizeof(unsigned char) * v[i].len);
		ft_memcpy(b[i].value, v[i].x, v[i].len);
		if (ft_memcmp(b[i].value, v[i].x, v[i].len)
			&& ft_dprintf(2, "%snnaumenk init error%s\n", KRED, KNRM)
			&& nnaumenk_show_n_free(b, v, false, true))
			return (false);
	}
	//nnaumenk_show_n_free(b, v, true, false);
	return (true);
}

static void	add_cmp(t_bigint *b, t_varint *v)
{
	clock_t	clck[2];

	t_bigint b3 = ft_bigint_dup(b);
	clck[0] = clock();
	ft_bigint_add(&b3, b + 1);
	clck[0] = clock() - clck[0];
	b[3] = b3;
		
	clck[1] = clock();
	v[3] = v_add(v[0], v[1], true);
	clck[1] = clock() - clck[1];
	printf("%snnaumenk : ( %zu , %f)\travard : ( %zu , %f) NNAUMENK_CMP_AWK_FILTER %s\n", KYEL, clck[0], (double)clck[0] / CLOCKS_PER_SEC, clck[1], (double)clck[1] / CLOCKS_PER_SEC, KNRM);
}

static void	sub_cmp(t_bigint *b, t_varint *v)
{
	clock_t	clck[2];

	t_bigint b3 = ft_bigint_dup(b);
	clck[0] = clock();
	ft_bigint_sub(&b3, b + 1);
	clck[0] = clock() - clck[0];
	b[3] = b3;
		
	clck[1] = clock();
	v[3] = v_sub(v[0], v[1], true);
	clck[1] = clock() - clck[1];
	printf("%snnaumenk : ( %zu , %f)\travard : ( %zu , %f) NNAUMENK_CMP_AWK_FILTER %s\n", KYEL, clck[0], (double)clck[0] / CLOCKS_PER_SEC, clck[1], (double)clck[1] / CLOCKS_PER_SEC, KNRM);
}

static void	mul_cmp(t_bigint *b, t_varint *v)
{
	clock_t	clck[2];

	clck[0] = clock();
	ft_bigint_mul(b + 3, b, b + 1);
	clck[0] = clock() - clck[0];
		
	clck[1] = clock();
	v[3] = v_mul(v[0], v[1], true);
	clck[1] = clock() - clck[1];
	printf("%snnaumenk : ( %zu , %f)\travard : ( %zu , %f) NNAUMENK_CMP_AWK_FILTER %s\n", KYEL, clck[0], (double)clck[0] / CLOCKS_PER_SEC, clck[1], (double)clck[1] / CLOCKS_PER_SEC, KNRM);
}

static void	div_cmp(t_bigint *b, t_varint *v)
{
	clock_t	clck[2];

	clck[0] = clock();
	ft_bigint_div(b + 3, b + 4, b, b + 1);
	clck[0] = clock() - clck[0];
		
	clck[1] = clock();
	v[3] = v_div(v[0], v[1], true);
	clck[1] = clock() - clck[1];
	printf("%snnaumenk : ( %zu , %f)\travard : ( %zu , %f) NNAUMENK_CMP_AWK_FILTER %s\n", KYEL, clck[0], (double)clck[0] / CLOCKS_PER_SEC, clck[1], (double)clck[1] / CLOCKS_PER_SEC, KNRM);
}

static void	mod_cmp(t_bigint *b, t_varint *v)
{
	clock_t	clck[2];

	clck[0] = clock();
	ft_bigint_div(b + 4, b + 3, b, b + 1);
	clck[0] = clock() - clck[0];
		
	clck[1] = clock();
	v[3] = v_mod(v[0], v[1], true, true);
	clck[1] = clock() - clck[1];
	printf("%snnaumenk : ( %zu , %f)\travard : ( %zu , %f) NNAUMENK_CMP_AWK_FILTER %s\n", KYEL, clck[0], (double)clck[0] / CLOCKS_PER_SEC, clck[1], (double)clck[1] / CLOCKS_PER_SEC, KNRM);
}

static void	expmod_cmp(t_bigint *b, t_varint *v)
{
	clock_t	clck[2];

	clck[0] = clock();
	ft_pow_mod(b + 3, b, b + 1, b + 2);
	clck[0] = clock() - clck[0];
		
	clck[1] = clock();
	v[3] = v_expmod(v[0], v[1], v[2], true);
	clck[1] = clock() - clck[1];
	printf("%snnaumenk : ( %zu , %f)\travard : ( %zu , %f) NNAUMENK_CMP_AWK_FILTER %s\n", KYEL, clck[0], (double)clck[0] / CLOCKS_PER_SEC, clck[1], (double)clck[1] / CLOCKS_PER_SEC, KNRM);
}

static int	verif_nnaumenk_ravard(t_bigint *b, t_varint *v)
{
	int	ret;

//	for (int i = 0; i < v[3].len; i++)
//		 ft_printf("(i, cmp) = (%d, %d)\n", i, ft_memcmp(b[3].value + i , &v[3].x[i], 1));

	if (b[3].size != (size_t)v[3].len)
		ret = -42;
	else
		ret = ft_memcmp(b[3].value, v[3].x, v[3].len) ? -42 : 42;
	//PRINT
	bool show = (ret == -42) ? true : false;	
	nnaumenk_show_n_free(b,v, show, true);
//	ft_printf("signs = (%d, %d)\n\n", v[0].sign, v[1].sign);
	return (ret);
}

int	nnaumenk_cmp(char **argv)
{
	t_varint	 	v[5] = { [0 ... 4]  = g_v[0]};
	t_bigint 	b[5] = {[0 ... 4] = {NULL, 0}};

//	ft_dprintf(2, "%sIN : NNAUMENK_CMP\n%s", KWHT, KNRM);

	if (!rand_init_u64_v(NULL, v, argv, 6)
		&& ft_dprintf(2, "%sOUT : RAND_INIT ERROR%s\n", KWHT, KNRM))
		return (-42);

//	asn1_der_init(v, "der_files/mul_debug.der");
//	asn1_der_init(v, "der_files/ret.der");
//	asn1_der_init(v + 1, "der_files/p_mul.der");

	if (!init_nnaumenk(b, v))
		return (-42);

//	v_asn1_der_int_seq_e("mul_debug.der", v, 2);

	if (!ft_strcmp("add", argv[2]))
		add_cmp(b, v);
	else if (!ft_strcmp("sub", argv[2]))
		sub_cmp(b, v);
	else if (!ft_strcmp("mul", argv[2]))
	  	mul_cmp(b, v);
	else if (!ft_strcmp("div", argv[2]))
	  	div_cmp(b, v);
	else if (!ft_strcmp("mod", argv[2]))
	  	mod_cmp(b, v);
	else if (!ft_strcmp("expmod", argv[2]))
	  	expmod_cmp(b, v);

	return (verif_nnaumenk_ravard(b, v));
}

