#include "varint_test.h"

/*
**	Here we run varint operators on randomely choose varint variables,
**	then we can test the rapidity of our operators (time sh varint_test.sh op [...])
**	or test overflow errors, checking the return value of our operator.
**	We can test operators on manual input settings too with manual_init_u64_v func or load asn1 der integer sequence previously encoded. (v_asn1_int_seq_der_e|d)
**
**	len = atoi(argv[3]) has no limitation here 
**	(juste the adjustement of V_MAX_LEN in varint.h to avoid overflows)
**
**		more particularly about operator overflows:
**
**		cmp_lt, cmp_eq, div, mod, gcd and eea	<---> 	V_MAX_LEN >= len
**		add, sub								<--->	V_MAX_LEN >= len + 1
**		mul, expmod, crt			 			<--->	V_MAX_LEN >= 2 * len
**		exp										<--->	len <= 2 (cf V_EXP OVFL NOTE in v_mul_exp.c)
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

int			op(char **argv)
{
	t_varint	 	v[5] = { [0 ... 4]  = g_v[0]};

//	ft_dprintf(2, "%sIN : SPEED_OP\n%s", KWHT, KNRM);

	/*rand_init opt (last param): 
	**     0 		 | 2nd and 3rd operand != 0
	**     1  		 | only_pos
	**     2 		 | operand sorted (regarding sign)
	*/
	if (!rand_init_u64_v(NULL, v, argv, 0)
		&& ft_dprintf(2, "%sOUT : RAND_INIT ERROR%s\n", KWHT, KNRM))
		return (-42);

	ft_dprintf(2, "(v[0].len, v[1].len) = (%d, %d)\n", v[0].len, v[1].len);
//	v[0] = g_v[0];
//	v[0].len = 8;
//	v[0].x[0] = 5;
//	v[0].x[1] = 5;
//	v[0].x[2] = 5;
//	v[0].x[3] = 5;
//	v[0].x[4] = 5;
//	v[0].x[5] = 5;
//	v[0].x[6] = 5;
//	v[0].x[7] = 5;

	
//	manual_init_u64_v(NULL, v);

	if (!ft_strcmp("cmp_lt", argv[2]))
		v_cmp(v, "-lt", v + 1, true);
	else if (!ft_strcmp("cmp_eq", argv[2]))
		v_cmp(v, "-eq", v + 1, true);
	else if (!ft_strcmp("add", argv[2]))
		v[3] = v_add(v[0], v[1], true);
	else if (!ft_strcmp("sub", argv[2]))
		v[3] = v_sub(v[0], v[1], true);
	else if (!ft_strcmp("mul", argv[2]))
		v[3] = v_mul(v[0], v[1], true);
	else if (!ft_strcmp("exp", argv[2])) {
		v[1].sign = 1;
//		v[0].x[0] %= 16;	
//		v[1].x[0] %= 16;
		v[3] = v_exp(v[0], v[1]);
	}
	//for div|mod|expmod option 0 must be ON
	else if (!ft_strcmp("div", argv[2]))
		v[3] = v_div(v[0], v[1], true);
	else if (!ft_strcmp("mod", argv[2]))
		v[3] = v_mod(v[0], v[1], true, true);
	else if (!ft_strcmp("expmod", argv[2]))
	{

		//ASN1_DER_INIT
//		t_varint		p, q;
//		asn1_der_init(v, "der_files/v0_v1_v2.der"); // v[2] = p * q
//		asn1_der_init(&p, "der_files/p.der");
//		asn1_der_init(&q, "der_files/q.der");
//		v[3] = v_expmod(v[0], v[1], v_mul(p, q, true), true);
//		show_var(0, 2, NULL, v);

		//RANDOM_INIT
		v[1].sign = 1;
		v[3] = v_expmod(v[0], v[1], v[2], true);
//		show_var(42, 1, NULL, v);
	}
//	else if (!ft_strcmp("crt", argv[2]))
//	{
//		
//		//ASN1_DER_INIT
//		t_varint		p, q;
//		asn1_der_init(v, "der_files/v0_v1_v2.der"); // v[2] = p * q
//		asn1_der_init(&p, "der_files/p.der");
//		asn1_der_init(&q, "der_files/q.der");
//		v[3] = v_crt(v[0], v[1], p, q);
//		show_var(0, 2, NULL, v);
//		
//		//RANDOM_INIT
////		p = find_prime(atoi(argv[3]) / 2, false);
////		q = find_prime(atoi(argv[3]) / 2, false);
////		v[1].sign = 1;
////		v[3] = v_crt(v[0], v[1], *p, *q);
//	}
	else if (!ft_strcmp("gcd_eea", argv[2]))
	{
		v[2] = v_gcd(v[0], v[1], true);
		if (!v_eea(v + 3, v[0], v[1], true))
			v[3] = g_v[3];
	}
	else
	{
		ft_dprintf(2, "%s'%s' : unknown operator%s\n", KRED, argv[2], KNRM);
		return (-42);
	}
	int ret = (is_g_v(3, v + 3) || is_g_v(3, v + 4)) ? -42 : 42;
	
//	show_var(ret, 2, NULL, v);

//	ft_dprintf(2, "%sOUT SPEED_OP\n%s", KWHT, KNRM);
	return (ret);
}
