#include "varint_test.h"

/*
**	Here we test our operators comparing with uint64_t operators resultats.
**	Make sure len = atoi(argv[3]) <= 8.
**
**		about verif_op test possibilities and varint.h settings:
**
**		len <= 8 for cmp_lt, cmp_eq, div, mod, gcd and eea
**			V_MAX_LEN >= len
**		len <= 7 for add and sub 
**			WARNING : V_MAX_LEN >= len + 1
**		len <= 4 for mul, expmod, crt 
**			WARNING : V_MAX_LEN >= 2 * len
**		len == 1 for exp with %16 hardcoded see line ~100
**			V_MAX_LEN >= 8
**		
**		NB : oh yeah exp resultat really need 64-bit of data for 4-bit operand
**			 need 2^20-bit of data for 16-bit operand... (cf V_EXP OVFL NOTE in v_mul_exp.c)
*/

/*
** about u64[5] and v[5]
**
**	index 		data
**				
**		0			1st operand
**		1			2nd operand
**	 	2			3rd operand: modulus (v_expmod) 
**									|| gcd (v_gcd_eea)
**	 	3			1st res
**	 	4			2nd res (for eea)
*/

int			u64_cmp(char **argv)
{

	t_u64			u64[5] = {[0 ... 4] = g_u64_0};
	t_varint	 	v[5] = {[0 ... 4 ] = g_v[0]};
	t_varint		p, q;

	
//	ft_dprintf(2, "\n%sIN : VERIF_OP\n%s", KWHT, KNRM);

	/*rand_init opt (last param): 
	**     0 		 | 2nd and 3rd operand != 0
	**     1  		 | only_pos
	**     2 		 | operand sorted (regarding sign)
	*/
	if (!rand_init_u64_v(u64, v, argv, 0)
		&& ft_dprintf(2, "%sOUT : RAND_INIT ERROR%s\n", KWHT, KNRM))
		return (-42);	
//	manual_init_u64_v(u64, v);
//	show_var(0, 0, u64, v);

//	v[0].sign = v[1].sign = v[2].sign = 1;
//	u64[0].sign = u64[1].sign = u64[2].sign = 1;
//	v[0].len = v[1].len = 5;
//	v[2].len = 1;
//	*((uint64_t *)v[0].x) = u64[0].x = 0x72c5b611479e;
//	*((uint64_t *)v[1].x) = u64[1].x = 0xd6b866cc8a00;
//	*((uint64_t *)v[2].x) = u64[2].x = 0x0;

	/*
	**	CMP TESTS
	*/

	if (!ft_strncmp("cmp", argv[2], 3))
	{
		int	ret;
		if (!ft_strcmp("_lt", argv[2] + 3))
			ret = (u64_lt(u64[0], u64[1]) == v_cmp(v, "-lt", v + 1, true)) ? 42 : -42;
		if (!ft_strcmp("_eq", argv[2] + 3))
			ret = (u64_eq(u64[0], u64[1]) == v_cmp(v, "-eq", v + 1, true)) ? 42 : -42;
		if (ret == -42)	
			show_var(ret, 1, u64, v);
		return (ret);
	}

	/*
	**	OP TESTS
	*/

	//for left and right shift,  option 1 must be ON
	if (!ft_strcmp("left_shift", argv[2]))
	{
		u64[3].x = u64[0].x << 1;
		v[3] = v_left_shift(v[0], true);
	}
	else if (!ft_strcmp("right_shift", argv[2]))
	{
		u64[3].x = u64[0].x >> 1;
		v[3] = v_right_shift(v[0], true);
	}
	else if (!ft_strcmp("add", argv[2])) {
		u64[3] = u64_add(u64[0], u64[1]);
		v[3] = v_add(v[0], v[1], true);
	}
	else if (!ft_strcmp("sub", argv[2])) {
		u64[3] = u64_sub(u64[0], u64[1]);
		v[3] = v_sub(v[0], v[1], true);
	}
	else if (!ft_strcmp("mul", argv[2])) {
		u64[3] = u64_mul(u64[0], u64[1]);
		v[3] = v_mul(v[0], v[1], true);
	}
	else if (!ft_strcmp("exp", argv[2])) {
		if (atoi(argv[3]) != 1)
			ft_dprintf(2, EXP_ERR, KRED, KYEL, KNRM);
		u64[0].x = 16;
		u64[1].x = 16;
		v[0].x[0] %= 16;		
		v[1].x[0] %= 16;		

		u64[1].sign = 1;
		u64[3] = u64_exp(u64[0], u64[1]);
		v[1].sign = 1;
		v[3] = v_exp(v[0], v[1]);
	}
	//for div|mod|expmod option 0 must be ON
	else if (!ft_strcmp("div", argv[2])) {
		u64[3] = u64_div(u64[0], u64[1]);
		v[3] = v_div(v[0], v[1], true);
	}
	else if (!ft_strcmp("mod", argv[2])) {
		u64[3] = u64_mod(u64[0], u64[1], true);
		v[3] = v_mod(v[0], v[1], true, true);
	}
	else if (!ft_strcmp("expmod", argv[2]))
	{
		u64[3] = u64_expmod(u64[0], u64[1], u64[2], true);
		v[1].sign = 1;
		v[3] = v_expmod(v[0], v[1], v[2], true);
	}
	else if (!ft_strcmp("gcd_eea", argv[2]))
	{
		u64[2].sign = 1;
		u64[2].x = gcd(u64[0].x, u64[1].x);
		v[2] = v_gcd(v[0], v[1], true);
		u64_eea(u64 + 3, u64[0], u64[1]);
		v_eea(v + 3, v[0], v[1], true);
	}
	else if (!ft_strcmp("crt", argv[2]))
	{
		p = find_prime(2, false);
//		p = g_v[2];
//		p.x[0] = 61;
		q = find_prime(2, false);
		while (v_cmp(&p, "-eq", &q, true))
			q = find_prime(1, false);
//		q = g_v[2];
//		q.x[0] = 47;

		u64[1].sign = 2;
		u64[2].sign = 2;
		u64[2].x = (((uint64_t)p.x[1] << 8) + (uint64_t)p.x[0])
			* (((uint64_t)q.x[1] << 8) + (uint64_t)q.x[0]);
		u64[3] = u64_expmod(u64[0], u64[1], u64[2], true);

	
		v[1].sign = 1;
		v[2] = v_mul(p, q, true);
		v[3] = v_crt(v[0], v[1], p, q);	
	}
	else
	{
		ft_dprintf(2, "%s'%s' : unknown operator%s\n", KRED, argv[2], KNRM);
		return (-42);
	}

	/*
	**	ERR CHECK AND VERIFICATION
	*/
	int ret;

	if ((v[3].len > 8 || v[4].len > 8)
			&& ft_dprintf(2, U64_OVFL, KRED, KNRM))
		ret = -42;
	else if (is_g_v(3, v + 3) || is_g_v(3, v + 4))
		ret = -42;
	else	
		ret = verify(argv[2], u64, v) ? 42 : -42;

	show_var(ret, 2, u64, v);

//	if (ret == -42) {
//		show_var(ret, 2, u64, v);
	//	v_print(&p, "p", -2, KYEL);		
	//	v_print(&q, "q", -2, KYEL);		
//	}
//	ft_dprintf(2, "%sOUT VERIF_OP\n%s", KWHT, KNRM);
	return (ret);
}
