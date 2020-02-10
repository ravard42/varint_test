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

/*
**	options on one_byte:
** 	bit | option
**     0  | 2nd operand not 0
**     1  | only_pos
**     2  | operand sorted (regarding sign)
**
** example: only_pos and sorted --> opt = 5 (00000110)
*/

bool			rand_init_u64_v(t_u64 *u64, t_varint *v, char **argv, uint8_t opt)
{
// VARINT RANDOM INITIALISATION
	for (int i = 0; i < 3; i++)
	{
		v[i] = v_rand(atoi(argv[3]), true);
		if (is_g_v(3, v + i))
			return (false);
	}
// HANDLE OPT
	// avoid divison by 0
	if ((opt & 1) && is_g_v(0, v + 1))
		v[1] = g_v[1];
	// ONLY POS NUMBER
	if (opt & 2) {
		for (int i = 0; i < 3; i++)
			v[i].sign = 1;
	}
	// SORT IT
	if (opt & 4)
		v_sort(v, v + 1, NULL, false);
// INIT U64
	if (u64) {
		for (int i = 0; i < 3; i++) {
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
	// init manually here

	v[0].sign = 1;
	v[1].sign = 1;
	v[0].len = v[1].len = 8;
	uint64_t buff = 0x491ab7c04c953991;
	ft_memcpy((char *)v[0].x, (char *)&buff, 8);
	buff = 0x1d5fbbe7c2934e36;
	ft_memcpy((char *)v[1].x, (char *)&buff, 8);



	if (u64) {
		for (int i = 0; i < 3; i++) {
			u64[i].sign = v[i].sign;
			for (int j = 0; j < 8; j++)
				u64[i].x += (uint64_t)v[i].x[j] << 8 * j;
		}
	}
	return true;
}

// beware that dest got enough memorie space to store nb_v varint

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

#define NB_TEST 100
static void	NB_TEST_add(t_bigint *b, t_varint *v)
{
	clock_t	start;
	double 	t[2] = {0};
	t_bigint	b0_save;


	for (int i = 0; i < NB_TEST; i++)
	{
		b0_save = ft_bigint_dup(b);
		start = clock();
		ft_bigint_add(&b0_save, b + 1);
		t[0] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
		if (i != NB_TEST - 1)
			free(b0_save.value);
		else
			b[3] = b0_save;
		
		start = clock();
		v[3] = v_add(v[0], v[1], true);
		t[1] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%d_add nnaumenk --> average compute time by op : %fms\n", NB_TEST, t[0] / NB_TEST);		
	printf("%d_add ravard --> average compute time by op : %fms\n", NB_TEST, t[1] / NB_TEST);		
}

static void	NB_TEST_sub(t_bigint *b, t_varint *v)
{
	clock_t	start;
	double 	t[2] = {0};
	t_bigint	b0_save;

	for (int i = 0; i < NB_TEST; i++)
	{
		b0_save = ft_bigint_dup(b);
		start = clock();
		ft_bigint_sub(&b0_save, b + 1);
		t[0] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
		if (i != NB_TEST - 1)
			free(b0_save.value);
		else
			b[3] = b0_save;
		
		start = clock();
		v[3] = v_sub(v[0], v[1], true);
		t[1] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%d_sub nnaumenk --> average compute time by op : %fms\n", NB_TEST, t[0] / NB_TEST);		
	printf("%d_sub ravard --> average compute time by op : %fms\n", NB_TEST, t[1] / NB_TEST);		
}

static void	NB_TEST_mul(t_bigint *b, t_varint *v)
{
	clock_t	start;
	double 	t[2] = {0};


	for (int i = 0; i < NB_TEST; i++)
	{
		start = clock();
		ft_bigint_mul(b + 3, b, b + 1);
		t[0] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
		if (i != NB_TEST - 1)
			free(b[3].value);
		
		start = clock();
		v[3] = v_mul(v[0], v[1], true);
		t[1] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%d_mul nnaumenk --> average compute time by op : %fms\n", NB_TEST, t[0] / NB_TEST);		
	printf("%d_mul ravard --> average compute time by op : %fms\n", NB_TEST, t[1] / NB_TEST);		
}

static void	NB_TEST_div(t_bigint *b, t_varint *v)
{
	clock_t	start;
	double 	t[2] = {0};


	for (int i = 0; i < NB_TEST; i++)
	{
		start = clock();
		ft_bigint_div(b + 3, b + 4, b, b + 1);		
		t[0] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
		if (i != NB_TEST - 1) {
			free(b[3].value);
			free(b[4].value);
		}
		
		start = clock();
		v[3] = v_div(v[0], v[1], true);
		t[1] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%d_div nnaumenk --> average compute time by op : %fms\n", NB_TEST, t[0] / NB_TEST);		
	printf("%d_div ravard --> average compute time by op : %fms\n", NB_TEST, t[1] / NB_TEST);		
}

static void	NB_TEST_mod(t_bigint *b, t_varint *v)
{
	clock_t	start;
	double 	t[2] = {0};


	for (int i = 0; i < NB_TEST; i++)
	{
		start = clock();
		ft_bigint_div(b + 4, b + 3, b, b + 1);		
		t[0] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
		if (i != NB_TEST - 1) {
			free(b[3].value);
			free(b[4].value);
		}
		start = clock();
		v[3] = v_mod(v[0], v[1], true, true);
		t[1] += 1000 * (double)(clock() - start) / CLOCKS_PER_SEC;
	}
	printf("%d_mod nnaumenk --> average compute time by op : %fms\n", NB_TEST, t[0] / NB_TEST);		
	printf("%d_mod ravard --> average compute time by op : %fms\n", NB_TEST, t[1] / NB_TEST);		
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
	nnaumenk_show_n_free(b,v, false, true);
//	ft_printf("signs = (%d, %d)\n\n", v[0].sign, v[1].sign);
	return (ret);
}

int	nnaumenk_speed_cmp(t_varint *v, char *op)
{
	t_bigint b[5] = {[0 ... 4] = {NULL, 0}};

	if (!init_nnaumenk(b, v))
		return (-42);

//	v_asn1_der_int_seq_e("mul_debug.der", v, 2);

	if (!ft_strcmp("add", op))
		NB_TEST_add(b, v);
	else if (!ft_strcmp("sub", op))
		NB_TEST_sub(b, v);
	else if (!ft_strcmp("mul", op))
	  	NB_TEST_mul(b, v);
	else if (!ft_strcmp("div", op))
	  	NB_TEST_div(b, v);
	else if (!ft_strcmp("mod", op))
	  	NB_TEST_mod(b, v);

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
