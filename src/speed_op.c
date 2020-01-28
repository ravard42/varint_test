#include "varint_test.h"

/*
**	here we test the speed of our operators (time sh varint_test.sh)
**	AND overflow errors, checking the return value of our operator
**
**	V_TYPE and len = atoi(argv[3]) has no limitation here 
**	(juste the adjustement of V_MAX_LEN in varint.h to avoid overflows)
**
**		more particularly about operator overflows:
**
**		cmp_lt and cmp_eq  					<---> 	V_MAX_LEN >= len
**		add, sub, div, mod, gcd and eea 	<--->	V_MAX_LEN >= len + 1
**		mul, expmod and crt 				<--->	V_MAX_LEN >= 2 * len + 1
**		exp									<--->	V_MAX_LEN >= ? 
**													(cf 4bit long operands example in verif_op.c)
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

int			speed_op(char **argv)
{
	t_varint	 	v[5];
	t_varint		p, q;

//	ft_dprintf(2, "%sIN : SPEED_OP\n%s", KWHT, KNRM);
//	manual_init_1024_x2_prime(v, &p, &q);
//	manual_init_ovfl_tests(v);

	if (!rand_init_u64_v(NULL, v, argv)
		&& ft_dprintf(2, "%sOUT : RAND_INIT ERROR%s\n", KWHT, KNRM))
		return (-42);	

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
		v[2] = is_g_v(0, v + 2) ? g_v[1] : v[2];
		v[3] = v_expmod(v[0], v[1], v[2], true);
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
	else if (!ft_strcmp("gcd", argv[2]))
		v[3] = v_gcd(v[0], v[1]);
	else if (!ft_strcmp("eea", argv[2]))
	{
		v[0].sign = v[1].sign = 1;
		v_eea(v + 3, v[0], v[1]);
	}
	else
	{
		ft_dprintf(2, "%s'%s' : unknown operator%s\n", KRED, argv[2], KNRM);
		return (-42);
	}
	int ret = (is_g_v(3, v + 3) || is_g_v(3, v + 4)) ? -42 : 42;
	if (ret == -42)
		show_var(ret, 2, NULL, v);
//	ft_dprintf(2, "%sOUT SPEED_OP\n%s", KWHT, KNRM);
	return (ret);
}
