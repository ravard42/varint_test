#include "varint_test.h"

static void		show_var(int state, int res, t_u64 *u, t_varint *v)
{
	if (state == 42)
		ft_printf("%s<----SUCCES---->%s\n", KGRN, KNRM);
	else if (state == -42)
		ft_printf("%s<----FAILED---->%s\n", KRED, KNRM);
	for (int i = 0; i < 3; i++)
		u64_print(u[i], i, KMAG);	
	for (int i = 0; i < 3; i++)
		v_print(v + i, "", i, KMAG);
	if (res >= 1)
	{
		u64_print(u[3], 3, KCYN);	
		if (res == 2)
			u64_print(u[4], 4, KCYN);	
		v_print(v + 3, "", 3, KCYN);
		if (res == 2)
			v_print(v + 4, "", 4, KCYN);
	}
}

static bool	verify(char *op, t_u64 *u64, t_varint *v)
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
** about u64[5] and v[5]
**
**	index 		data
**				
**		0			1st operand
**		1			2nd operand
**	 	2			3rd operand (for modulo)
**	 	3			1st res
**	 	4			2nd res (for eea)
*/

static void		rand_init_u64_v(t_u64 *u64, t_varint *v, int fd, char **argv)
{
	uint8_t		buff;
	int			gcc_err;

	for(int i = 0; i < 5; i++)
	{
		v[i] = g_v[0];
		if (u64)
			u64[i] = g_u64_0;
	}

	for (int i = 0; i < 3; i++)
	{
		gcc_err = read(fd, &buff, 1);
		(void)gcc_err;		

		v[i].sign = (buff % 2) ? 1 : -1;
		if (u64)
			u64[i].sign = v[i].sign;
		for (int j = 0; j < atoi(argv[3]); j++)
		{
			gcc_err = read(fd, &buff, 1);
			(void)gcc_err;		
			v[i].x[j] = buff;
			if (u64)
				u64[i].x += (uint64_t)buff << 8 * j;
		}
		v_len(v + i);
	}
}


//V_TYPE = uint64_t, len = 16 (2 * 8)
static void	manual_init_v(t_varint *v, t_varint *p, t_varint *q)
{
	v[0].sign = 1;
	v[0].len = 16;
	v[0].x[0] = 0x6b6963152ba23031; 
	v[0].x[1] = 0xa0031b979d421017; 
	v[0].x[2] = 0xb9651bb108c12cc3; 
	v[0].x[3] = 0x2b4852eb5801ff86; 
	v[0].x[4] = 0x5e3d012b1a03443e; 
	v[0].x[5] = 0xe3909077ee0dd2ea; 
	v[0].x[6] = 0xc9622a10ae2d9048; 
	v[0].x[7] = 0xaf40a27a343dc068; 
	v[0].x[8] = 0x1f4d9adcf122049b; 
	v[0].x[9] = 0x14baa7522f07ebfe; 
	v[0].x[10] = 0x8a46d247de3bb6e5; 
	v[0].x[11] = 0x61aa60009b8ad92d; 
	v[0].x[12] = 0xe861470de3f1cd67; 
	v[0].x[13] = 0xdd2e2c003a6a7e03; 
	v[0].x[14] = 0x88b36375779211d0; 
	v[0].x[15] = 0x33cb19db201101d; 


	v[1].sign = 1;
	v[1].len = 16;
	v[1].x[0] = 0x1f4d9adcf122049b; 
	v[1].x[1] = 0x14baa7522f07ebfe; 
	v[1].x[2] = 0x8a46d247de3bb6e5; 
	v[1].x[3] = 0x61aa60009b8ad92d; 
	v[1].x[4] = 0xe861470de3f1cd67; 
	v[1].x[5] = 0xdd2e2c003a6a7e03; 
	v[1].x[6] = 0x88b36375779211d0; 
	v[1].x[7] = 0x33cb19db201101d; 
	v[1].x[8] = 0x6b6963152ba23031; 
	v[1].x[9] = 0xa0031b979d421017; 
	v[1].x[10] = 0xb9651bb108c12cc3; 
	v[1].x[11] = 0x2b4852eb5801ff86; 
	v[1].x[12] = 0x5e3d012b1a03443e; 
	v[1].x[13] = 0xe3909077ee0dd2ea; 
	v[1].x[14] = 0xc9622a10ae2d9048; 
	v[1].x[15] = 0xaf40a27a343dc068; 



	p->sign = 1;
	p->len = 8;
	p->x[0] = 0x6b6963152ba23031; 
	p->x[1] = 0xa0031b979d421017; 
	p->x[2] = 0xb9651bb108c12cc3; 
	p->x[3] = 0x2b4852eb5801ff86; 
	p->x[4] = 0x5e3d012b1a03443e; 
	p->x[5] = 0xe3909077ee0dd2ea; 
	p->x[6] = 0xc9622a10ae2d9048; 
	p->x[7] = 0xaf40a27a343dc068; 
	q->sign = 1;
	q->len = 8;
	q->x[0] = 0x1f4d9adcf122049b; 
	q->x[1] = 0x14baa7522f07ebfe; 
	q->x[2] = 0x8a46d247de3bb6e5; 
	q->x[3] = 0x61aa60009b8ad92d; 
	q->x[4] = 0xe861470de3f1cd67; 
	q->x[5] = 0xdd2e2c003a6a7e03; 
	q->x[6] = 0x88b36375779211d0; 
	q->x[7] = 0x33cb19db201101d; 

//	v[2] = v_mul(*p, *q);
//	v_print(v + 2, "v[2]", -2, KYEL);
	
	v[2].sign = 1;
	v[2].len = 16;
	v[2].x[0] = 0x435ab1847b75f1ab; 
	v[2].x[1] = 0x6b1840a6fdcd07cf; 
	v[2].x[2] = 0x2f65d7eb9cb12ba3; 
	v[2].x[3] = 0x66fd8f2886137290; 
	v[2].x[4] = 0x1a6790101d6307e2; 
	v[2].x[5] = 0x78e6761bf07b1fef; 
	v[2].x[6] = 0xdb288cb3f749f50e; 
	v[2].x[7] = 0x74529b3855d2ed7c; 
	v[2].x[8] = 0xfe214d8ae715c5de; 
	v[2].x[9] = 0x40bb3428b0dea941; 
	v[2].x[10] = 0x3db764f82e57d8d1; 
	v[2].x[11] = 0x360da6b046566e47; 
	v[2].x[12] = 0x513e3af1b619ef33; 
	v[2].x[13] = 0x68f58910d2c278e9; 
	v[2].x[14] = 0xebaf20bbc21ef726; 
	v[2].x[15] = 0x2374ea52816c60c;

	v[3] = v[4] = g_v[0];
}


int			speed_op(int fd, char **argv)
{
	t_varint	 	v[5];
	t_varint		p, q;

	manual_init_v(v, &p, &q);
//	rand_init_u64_v(NULL, v, fd, argv);	

	if (!ft_strcmp("cmp_lt", argv[2]))
		v_cmp(v[0], "-lt", v[1]);
	if (!ft_strcmp("cmp_eq", argv[2]))
		v_cmp(v[0], "-eq", v[1]);
	else if (!ft_strcmp("add", argv[2]))
		v[3] = v_add(v[0], v[1]);
	else if (!ft_strcmp("sub", argv[2]))
		v[3] = v_sub(v[0], v[1]);
	else if (!ft_strcmp("mul", argv[2]))
		v[3] = v_mul(v[0], v[1]);
	else if (!ft_strcmp("exp", argv[2])) {
		v[1].sign = 1;
		v[3] = v_exp(v[0], v[1]);
	}
	else if (!ft_strcmp("div", argv[2])) {
		v[1] = is_g_v(0, v[1]) ? g_v[1] : v[1];
		v[3] = v_div(v[0], v[1]);
	}
	else if (!ft_strcmp("mod", argv[2])) {
		v[1] = is_g_v(0, v[1]) ? g_v[1] : v[1];
		v[3] = v_mod(v[0], v[1], true);
	}
	else if (!ft_strcmp("expmod", argv[2]))
	{
		//manual
		v[3] = v_expmod(v[0], v[1], v_mul(p, q), true);
		v_print(v + 3, "v[3]", -2, KYEL);


//		random
//		v[1].sign = 1;
//		v[2] = is_g_v(0, v[2]) ? g_v[1] : v[2];
//		v[3] = v_expmod(v[0], v[1], v[2], true);
	}
	else if (!ft_strcmp("crt", argv[2]))
	{
		//manual
		v[3] = v_crt(v[0], v[1], p, q);	
		v_print(v + 3, "v[3]", -2, KYEL);
		
//		random
//		p = find_prime(fd, atoi(argv[3]) / 2, false);
//		q = find_prime(fd, atoi(argv[3]) / 2, false);
//		v[1].sign = 1;
//		v[3] = v_crt(v[0], v[1], p, q);	
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
	if (is_g_v(3, v[3]) || is_g_v(3, v[4]))
		return (-42);	
	return (42);
}

int			verif_op(int fd, char **argv)
{

	t_u64			u64[5]; 
	t_varint	 	v[5];
	t_varint		p, q;

	rand_init_u64_v(u64, v, fd, argv);	
	//show_var(0, 2, u64, v);	

	/*
	**	CMP TESTS
	*/

	if (!ft_strncmp("cmp", argv[2], 3))
	{
		int	ret;
		if (v[1].len > 8
			&& ft_dprintf(2, U64_OVFL, KYEL, KNRM))
			return (-42);	
		if (!ft_strcmp("_lt", argv[2] + 3))
		{

			if (u64_lt(u64[0], u64[1]))
				ret = v_cmp(v[0], "-lt", v[1]) ? 42 : -42;
			else 
				ret = v_cmp(v[0], "-ge", v[1]) ? 42 : -42;

			if (ret == -42)	
				show_var(ret, 1, u64, v);
			return ret;
		}
		if (!ft_strcmp("_eq", argv[2] + 3))
		{
			if (u64_eq(u64[0], u64[1]))
				ret = v_cmp(v[0], "-eq", v[1]) ? 42 : -42;
			else 
				ret = v_cmp(v[0], "-ne", v[1]) ? 42 : -42;

			if (ret == -42)	
				show_var(ret, 1, u64, v);
			return ret;
		}
	}

	/*
	**	OP TESTS
	*/

	if (!ft_strcmp("add", argv[2])) {
		u64[3] = u64_add(u64[0], u64[1]);
		v[3] = v_add(v[0], v[1]);
	}
	else if (!ft_strcmp("sub", argv[2])) {
		u64[3] = u64_sub(u64[0], u64[1]);
		v[3] = v_sub(v[0], v[1]);
	}
	else if (!ft_strcmp("mul", argv[2])) {
		u64[3] = u64_mul(u64[0], u64[1]);
		v[3] = v_mul(v[0], v[1]);
	}
	else if (!ft_strcmp("exp", argv[2])) {
		if (atoi(argv[3]) != 1)
			ft_dprintf(2, EXP_ERR, KRED, KYEL, KNRM);
		u64[0].x %= 16;
		u64[0].sign = (u64[0].x == 0) ? 1 : u64[0].sign;
		u64[1].x %= 16;
		v[0].x[0] %= 16;		
		v[1].x[0] %= 16;		

		u64[1].sign = 1;
		u64[3] = u64_exp(u64[0], u64[1]);
		v[1].sign = 1;
		v[3] = v_exp(v[0], v[1]);
	}
	else if (!ft_strcmp("div", argv[2])) {
		u64[3] = u64_div(u64[0], u64[1]);
		v[1] = is_g_v(0, v[1]) ? g_v[1] : v[1];
		v[3] = v_div(v[0], v[1]);
	}
	else if (!ft_strcmp("mod", argv[2])) {
		u64[3] = u64_mod(u64[0], u64[1], true);
		v[1] = is_g_v(0, v[1]) ? g_v[1] : v[1];
		v[3] = v_mod(v[0], v[1], true);
	}
	else if (!ft_strcmp("expmod", argv[2]))
	{
	//	u64[3] = u64_expmod(u64[0], u64[1], u64[2], true);

		p = find_prime(fd, 2, false);
		q = find_prime(fd, 2, false);
	
		u64[1].sign = 1;
		u64[2].sign = 1;
		u64[2].x = (((uint64_t)p.x[1] << 8) + (uint64_t)p.x[0])
			* (((uint64_t)q.x[1] << 8) + (uint64_t)q.x[0]);
		u64[3] = u64_expmod(u64[0], u64[1], u64[2], true);

	//	v[1].sign = 1;
	//	v[2] = is_g_v(0, v[2]) ? g_v[1] : v[2];
	//	v[3] = v_expmod(v[0], v[1], v[2], true);

		v[1].sign = 1;
		v[3] = v_expmod(v[0], v[1], v_mul(p, q), true);

	}
	else if (!ft_strcmp("crt", argv[2]))
	{
		p = find_prime(fd, 2, false);
		q = find_prime(fd, 2, false);
		
		u64[1].sign = 1;
		u64[2].sign = 1;
		u64[2].x = (((uint64_t)p.x[1] << 8) + (uint64_t)p.x[0])
			* (((uint64_t)q.x[1] << 8) + (uint64_t)q.x[0]);
		u64[3] = u64_expmod(u64[0], u64[1], u64[2], true);

	
		v[1].sign = 1;
		v[2] = v_mul(p, q);
		v[3] = v_crt(v[0], v[1], p, q);	
	}
	else if (!ft_strcmp("gcd", argv[2]))
	{
		u64[3].sign = 1;
		u64[3].x = gcd(u64[0].x, u64[1].x);
		v[3] = v_gcd(v[0], v[1]);
	}
	else if (!ft_strcmp("eea", argv[2]))
	{
		u64[0].sign = u64[1].sign = 1;
		u64_eea(u64 + 3, u64[0], u64[1]);
		v[0].sign = v[1].sign = 1;
		v_eea(v + 3, v[0], v[1]);
	}
	else
	{
		ft_dprintf(2, "%s'%s' : unknown operator%s\n", KRED, argv[2], KNRM);
		return (-42);
	}

	/*
	**	¿ERR?
	*/

	if (v[3].len > 8 || v[4].len > 8)
		ft_dprintf(2, U64_OVFL, KYEL, KNRM);
	else if (is_g_v(3, v[3]) || is_g_v(3, v[4]))
		return (-42);	

	/*
	**	VERIFICATION
	**
	** ret == 42 for SUCCES printing and -42 for FAILURE
	** 2nd param: 	0 -> only print operand var 
	**					1 -> print operand var and first result
	**					2 -> print all var
	*/

	int ret = verify(argv[2], u64, v) ? 42 : -42;
	if (ret == -42) {
		show_var(ret, 1, u64, v);
//		v_print(&p, "p", -2, KYEL);		
//		v_print(&q, "q", -2, KYEL);		
	}
	return (ret);
}
