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
