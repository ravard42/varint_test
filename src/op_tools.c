#include "varint_test.h"

/* 
**	for all functions in there set u to NULL if in op tests
*/
 
/*
** 	res param: 	0 -> only print  3 operand var 
**				1 -> print operand var and first result
**				2 -> print all var
*/

void			show_var(int state, int res, t_u64 *u, t_varint *v)
{
	char	name[5] = {'v', '[', '0', ']', 0};

	ft_printf("\n%s<--------------SHOW_VAR IN--------------->%s\n", KYEL, KNRM);
	if (state == 42)
		ft_printf("\n%sSUCCES%s\n", KGRN, KNRM);
	else if (state == -42)
		ft_printf("\n%sFAILED%s\n", KRED, KNRM);
	if (u)
		for (int i = 0; i < 3; i++)
			u64_print(u[i], i, KMAG);	
	for (int i = 0; i < 3; i++)
	{
		name[2] = '0' + i;
		v_print(name, v + i);
	}
	if (res >= 1)
	{
		if (u)
		{
			u64_print(u[3], 3, KCYN);	
			if (res == 2)
				u64_print(u[4], 4, KCYN);
		}
		v_print("v[3]", v + 3);
		if (res == 2)
			v_print("v[4]", v + 4);
	}
	ft_printf("\n%s<--------------SHOW_VAR OUT-------------->%s\n", KYEL, KNRM);
}

bool			rand_init_u64_v(t_u64 *u64, t_varint *v, char **argv)
{
	for (int i = 0; i < 3; i++)
	{
		v[i] = v_rand(atoi(argv[3]), true);
		if (is_g_v(3, v + i))
			return (false);
		if (u64)
		{
			u64[i].sign = v[i].sign;
			for (int j = 0; j < atoi(argv[3]); j++)
				u64[i].x += (uint64_t)v[i].x[j] << 8 * j;
		}
	}
	return true;
}

/*
** argv[3] useless here
*/

bool				manual_init_u64_v(t_u64 *u64, t_varint *v)
{
	(void)u64;
	(void)v;
	// init manually here
	return true;
}

// beware that dst got enough memorie space to store nb_v varint

t_varint			*asn1_der_init(t_varint *dest, char *der_file)
{
	t_read	r;
	int		nb_v;
	t_varint	*ptr;
	
	// LOAD p
	if (ft_read(&r, der_file) < 0
		&& ft_dprintf(2, "%serror reading p.der%s\n", KRED, KNRM))
		return NULL;

	ptr = v_asn1_der_int_seq_d(&nb_v, &r);
	//v_print("ret", ret);
	ft_memcpy(dest, ptr, sizeof(t_varint) * nb_v);
	free(r.msg);
	free(ptr);
	return (dest);
}

/*
** Only for verif_op.c
*/
bool			verify(char *op, t_u64 *u64, t_varint *v)
{
	uint64_t		verif[2] = {0};
	bool			ret;

	for (int i = 0; i < (v + 3)->len; i++)
		verif[0] += (uint64_t)(v + 3)->x[i] << (8 * i);
	ret = ((u64 + 3)->sign == (v + 3)->sign
			&& (u64 + 3)->x == verif[0]) ? true : false;
	if (!ft_strcmp(op, "eea"))
	{
		for (int i = 0; i < (v + 4)->len; i++)
			verif[1] += (uint64_t)(v + 4)->x[i] << (8 * i);
		ret = ((u64 + 4)->sign == (v + 4)->sign
			&& (u64 + 4)->x == verif[1]) ? true : false;
	}
	return (ret);
}


/*
**	nnaumenk time-complexity comparison
** Only for op.c
**
*/


static bool	init_nnaumenk(t_bigint *b, t_varint *v)
{
	if (is_g_v(0, v + 1))
		v[1] = g_v[1];

	for (int i = 0; i < 3; i++)
	{
	// ONLY POS NUMBER
		v[i].sign = 1;
	//
		b[i].size = v[i].len;
		b[i].value = (unsigned char *)malloc(sizeof(unsigned char) * v[i].len);
		ft_memcpy(b[i].value, v[i].x, v[i].len);
		if (ft_memcmp(b[i].value, v[i].x, v[i].len)
			&& ft_dprintf(2, "%snnaumenk init error%s\n", KRED, KNRM)
			&& nnaumenk_show_n_free(b, v, false, true))
			return (false);
	}
	return (true);
}

#define NB_TEST 420
static void	add_x1000(t_bigint *b, t_varint *v)
{
	clock_t	start;
	double t[2] = {0};

	b[3] = ft_bigint_dup(b);

	for (int i = 0; i < NB_TEST; i++)
	{
		start = clock();
		ft_bigint_add(b, b + 1);
		t[0] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
		if (i != NB_TEST - 1)
		{
			free(b[0].value);
			b[0] = ft_bigint_dup(b + 3);
		}
		start = clock();
		v[3] = v_add(v[0], v[1], true);
		t[1] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
	}
	printf("add_x1000 nnaumenk compute time : %fms\n", t[0] / NB_TEST);		
	printf("add_x1000 ravard compute time : %fms\n", t[1] / NB_TEST);		
}

bool	verif_nnaumenk_ravard(t_bigint *b, t_varint *v)
{
	int	ret;

	if (is_g_v(0, v + 4))
		ret = ft_memcmp(b[3].value, v[3].x, v[3].len) ? -42 : 42;
	else
		ret = (ft_memcmp(b[4].value, v[4].x, v[4].len)
			|| ft_memcmp(b[3].value, v[3].x, v[3].len)) ? -42 : 42;
	//PRINT
	nnaumenk_show_n_free(b,v, false, true);
	ft_printf("signs = (%d, %d)\n\n", v[0].sign, v[1].sign);
	return (ret);
}

int	nnaumenk_speed_cmp(t_varint *v)
{
	t_bigint b[5] = {[0 ... 4] = {NULL, 0}};

	if (!init_nnaumenk(b, v))
		return (-42);


	add_x1000(b, v);

//	ft_bigint_mul(b + 3, b, b + 1);
//	v[3] = v_mul(v[0], v[1], true);
//	ft_bigint_div(b + 4, b + 3, b, b + 1);		
//	v[4] = v_div(v[0], v[1], true);
//	v[3] = v_mod(v[0], v[1], true, true);

	return (verif_nnaumenk_ravard(b, v));
}

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
