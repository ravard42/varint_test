#include "varint_test.h"

/*
**	Here we run varint operators on randomely choose varint variables,
**	then we can test the rapidity of our operators (time sh varint_test.sh op [...])
**	or test overflow errors, checking the return value of our operator.
**	We can test operators on manual input settings too with manual_init_u64_v func
**	or compare the v_expmod and v_crt with manual_init_1024_x2_prime.
**
**	uint8_t and len = atoi(argv[3]) has no limitation here 
**	(juste the adjustement of V_MAX_LEN in varint.h to avoid overflows)
**
**		more particularly about operator overflows:
**
**		cmp_lt, cmp_eq, div, mod, gcd and eea	<---> 	V_MAX_LEN >= len
**		add, sub								<--->	V_MAX_LEN >= len + 1
**		mul, expmod, crt			 			<--->	V_MAX_LEN >= 2 * len
**		exp										<--->	len <= 2 cf v_check.c
*/

/*
** about u64[5] and v[5]
**
**	index 		data
**				
**		0			1st operand
**		1			2nd operand
**	 	2			3rd operand (for modulus only)
**	 	3			1st res
**	 	4			2nd res (for eea)
*/


static bool	show_n_free(t_bigint *b, t_varint *v, bool show)
{
		char		name[3] = {'b', '0', 0};

		ft_printf("\n%sNNAUMENK%s\n", KYEL, KNRM);
		for (int i = 0; i < 5; i++)
		{
			name[1] = '0' + i;
			if (show && (b + i)->value)
				ft_bigint_print(name, b + i);
			if (b[i].value)
				free(b[i].value);
		}
		ft_printf("\n%sRAVARD%s\n", KYEL, KNRM);
		if (show && v)
			show_var(0, 2, NULL, v);
		ft_putchar('\n');
		return (true);
}

int			op(char **argv)
{
	t_varint	 	v[5];
	t_varint		p, q;

//	ft_dprintf(2, "%sIN : SPEED_OP\n%s", KWHT, KNRM);
	
	if (!rand_init_u64_v(NULL, v, argv)
		&& ft_dprintf(2, "%sOUT : RAND_INIT ERROR%s\n", KWHT, KNRM))
		return (-42);

	if (!ft_strcmp("nnaumenk", argv[2]))
	{
		t_bigint b[5];

		if (is_g_v(0, v + 1))
			v[1] = g_v[1];
		for (int i = 0; i < 5; i++)
			b[i].value = NULL;
	
		for (int i = 0; i < 3; i++)
		{
			v[i].sign = 1;
			b[i].size = v[i].len;
			b[i].value = (unsigned char *)malloc(sizeof(unsigned char) * v[i].len);
			ft_memcpy(b[i].value, v[i].x, v[i].len);
			if (ft_memcmp(b[i].value, v[i].x, v[i].len)
				&& ft_dprintf(2, "%sinit error%s\n", KRED, KNRM)
				&& show_n_free(b, v, false))
				return (-42);
		}
	
		ft_bigint_mul(b + 3, b, b + 1);		
		v[3] = v_mul(v[0], v[1], true);
//		ft_bigint_div(b + 4, b + 3, b, b + 1);		
//		v[4] = v_div(v[0], v[1], true);
//		v[3] = v_mod(v[0], v[1], true, true);
//		v[3] = v_mod(v[0], v[1], true, true);
		
	
//		if (!is_g_v(0, v + 4) && 
//			(ft_memcmp(b[4].value, v[4].x, v[4].len)
//			|| ft_memcmp(b[4].value, v[4].x, v[4].len)))
		if (ft_memcmp(b[3].value, v[3].x, v[3].len))
		{
			show_n_free(b,v, true);
			ft_printf("FAILED\n");
			return (-42);
		}

		show_n_free(b, v, true);
		ft_printf("SUCCES\n");
		
		return (42);
	}

//	manual_init_u64_v(NULL, v);
//	manual_init_1024_x2_prime(v, &p, &q);

	if (!ft_strcmp("cmp_lt", argv[2]))
		v_cmp(v, "-lt", v + 1, true);
	if (!ft_strcmp("cmp_eq", argv[2]))
		v_cmp(v, "-eq", v + 1, true);
	else if (!ft_strcmp("add", argv[2]))
		v[3] = v_add(v[0], v[1], true);
	else if (!ft_strcmp("sub", argv[2]))
		v[3] = v_sub(v[0], v[1], true);
	else if (!ft_strcmp("mul", argv[2]))
		v[3] = v_mul(v[0], v[1], true);
	else if (!ft_strcmp("exp", argv[2])) {
		v[1].sign = 1;
//		v[0].x[0] %= 17;	
//		v[1].x[0] %= 17;
		v[3] = v_exp(v[0], v[1]);
	}
	else if (!ft_strcmp("div", argv[2])) {
		v[1] = is_g_v(0, v + 1) ? g_v[1] : v[1];
		v[3] = v_div(v[0], v[1], true);
	}
	else if (!ft_strcmp("mod", argv[2])) {
		v[1] = is_g_v(0, v + 1) ? g_v[1] : v[1];
		v[3] = v_mod(v[0], v[1], true, true);
	}
	else if (!ft_strcmp("expmod", argv[2]))
	{
		//manual
//		v[3] = v_expmod(v[0], v[1], v_mul(p, q), true);
//		v_print(v + 3, "v[3]", -2, KYEL);


//		random
		v[1].sign = 1;

//		v[0].sign = v[2].sign = 1;

		v[2] = is_g_v(0, v + 2) ? g_v[1] : v[2];
//		ft_printf("IN expmod\n");
		v[3] = v_expmod(v[0], v[1], v[2], true);
//		ft_printf("OUT expmod\n");
//		show_var(42, 1, NULL, v);
	}
	else if (!ft_strcmp("gcd", argv[2]))
		v[3] = v_gcd(v[0], v[1]);
	else if (!ft_strcmp("eea", argv[2]))
	{
		v[0].sign = v[1].sign = 1;
		v_eea(v + 3, v[0], v[1]);
	}
	else if (!ft_strcmp("crt", argv[2]))
	{
		//manual
//		v[3] = v_crt(v[0], v[1], p, q);	
//		v_print(v + 3, "v[3]", -2, KYEL);
		
//		random
		p = find_prime(atoi(argv[3]) / 2, false);
		q = find_prime(atoi(argv[3]) / 2, false);
		v[1].sign = 1;
		v[3] = v_crt(v[0], v[1], p, q);	
	}
	else
	{
		ft_dprintf(2, "%s'%s' : unknown operator%s\n", KRED, argv[2], KNRM);
		return (-42);
	}
	int ret = (is_g_v(3, v + 3) || is_g_v(3, v + 4)) ? -42 : 42;
//	if (ret == -42)
//		show_var(ret, 2, NULL, v);
//	ft_dprintf(2, "%sOUT SPEED_OP\n%s", KWHT, KNRM);
	return (ret);
}
