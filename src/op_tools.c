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
	{
		for (int i = 0; i < 3; i++)
			u64_print(u[i], i, KMAG);	
		if (res >= 1) {
			u64_print(u[3], 3, KCYN);	
			if (res == 2)
				u64_print(u[4], 4, KCYN);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		name[2] = '0' + i;
		v_print(1, name, v + i);
	}
	if (res >= 1)
	{
		v_print(1, "v[3]", v + 3);
		if (res == 2)
			v_print(1, "v[4]", v + 4);
	}
	ft_printf("\n%s<--------------SHOW_VAR OUT-------------->%s\n\n", KYEL, KNRM);
}

/*
**	options on one_byte:
** 	bit index | option
**	----------------------------------------
**     0 		 | 2nd and 3rd operand != 0
**     1  		 | only_pos
**     2 		 | operand sorted (regarding sign)
**
** example: only_pos and sorted --> opt = 6 (00000110)
*/

bool			rand_init_u64_v(t_u64 *u64, t_varint *v, char **argv, uint8_t opt)
{
// VARINT RANDOM INITIALISATION
	uint16_t	tmp;
	for (int i = 0; i < 3; i++)
	{
		v[i] = v_rand(ft_range(*((uint16_t *)ft_rand(&tmp, 2)), 1, atoi(argv[3]) + 1), true);
		if (is_g_v(3, v + i))
			return (false);
	}
// HANDLE OPT
	// avoid divison by 0
	if ((opt & 1) && is_g_v(0, v + 1))
		v[1] = g_v[1];
	if ((opt & 1) && is_g_v(0, v + 2))
		v[2] = g_v[1];
	// ONLY POS NUMBER
	if (opt & 2) {
		for (int i = 0; i < 3; i++)
			v[i].sign = 1;
	}
	// SORT IT
	if (opt & 4)
		v_sort(v, v + 1, NULL);
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

	uint64_t buff = 0xf304c5;
	v[0] = v_init(1, (uint8_t *)&buff, 3);
	buff = 0x010bf4e565;
	v[1] = v_init(1, (uint8_t *)&buff, 5);


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

	ptr = v_asn1_int_seq_der_d(&nb_v, &r);
	//v_print(1, "ret", ret);
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
	uint64_t		verif = 0;
	bool			ret;

	for (int i = 0; i < (v + 3)->len; i++)
		verif += (uint64_t)(v + 3)->x[i] << (8 * i);
	ret = ((u64 + 3)->sign == (v + 3)->sign
			&& (u64 + 3)->x == verif) ? true : false;
	if (!ft_strcmp(op, "gcd_eea") && ret == true)
	{
		verif = 0;
		for (int i = 0; i < (v + 2)->len; i++)
			verif += (uint64_t)(v + 2)->x[i] << (8 * i);
		if (verif != (u64 + 2)->x
			&& ft_dprintf(2, "%sGCDs doesn't match%s\n", KRED, KNRM))
			return (false);
		verif = 0;
		for (int i = 0; i < (v + 4)->len; i++)
			verif += (uint64_t)(v + 4)->x[i] << (8 * i);
		ret = ((u64 + 4)->sign == (v + 4)->sign
			&& (u64 + 4)->x == verif) ? true : false;
		if (ret)
			ft_printf("%sGCD_EEA OK : u64[3] * u64[0] + u64[4] * u64[1] = %lu (u64[2] <-> GCD)\n%s", KGRN, u64[3].sign * u64[3].x * u64[0].sign * u64[0].x + u64[4].sign * u64[4].x * u64[1].sign * u64[1].x, KNRM);
	}
	return (ret);
}
