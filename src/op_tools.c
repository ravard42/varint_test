#include "varint_test.h"

/* 
**	Can be Used by both speed_op.c and verif_op.c
**
** 	2nd param: 	0 -> only print  3 operand var 
**				1 -> print operand var and first result
**				2 -> print all var
*/

void			show_var(int state, int res, t_u64 *u, t_varint *v)
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

/*
**	Used by both speed_op.c and verif_op.c
**	NB : in speed_op u64 = NULL
*/

bool			rand_init_u64_v(t_u64 *u64, t_varint *v, char **argv)
{
	for(int i = 0; i < 5; i++)
	{
		v[i] = g_v[0];
		if (u64)
			u64[i] = g_u64_0;
	}

	for (int i = 0; i < 3; i++)
	{
		if (is_g_v(3, v[i] = v_rand(atoi(argv[3]), true)))
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
** Only for speed_op.c
**
** initialisation for crt vs expmod speed test
** V_TYPE = uint64_t, V_MAX_LEN = 65 (2 * 32 + 1)
**
** NB: need to be in manual in speed_op.c
*/
void			manual_init_1024_x2_prime(t_varint *v, t_varint *p, t_varint *q)
{
	for (int i = 0; i < 5; i++)
		v[i] = g_v[0];
	*p = g_v[0];
	*q = g_v[0];


	v[0].len = 32;
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
	v[0].x[16] = 0x4e762326f6dd0021; 
	v[0].x[17] = 0xd21c82d1c6cc8851; 
	v[0].x[18] = 0x4b7d6bc79a951918; 
	v[0].x[19] = 0xb28d190ae13113fd; 
	v[0].x[20] = 0xa60ff5b0744892a4; 
	v[0].x[21] = 0xbe2b00f0969e606b; 
	v[0].x[22] = 0x84d8e7bce6fa33; 
	v[0].x[23] = 0x8f85014de6390d3e; 
	v[0].x[24] = 0x31617a4a6e112879; 
	v[0].x[25] = 0xff199de6cd9435fe; 
	v[0].x[26] = 0xe876d083498a911a; 
	v[0].x[27] = 0x82f588470c1725f7; 
	v[0].x[28] = 0x263394d21d1b8f67; 
	v[0].x[29] = 0x4876fd330b8c9bb0; 
	v[0].x[30] = 0x80cd8d4896f370e; 
	v[0].x[31] = 0x456a15a595b51b28; 

	v[1].len = 32;
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
	v[1].x[16] = 0x3a097a178d083151; 
	v[1].x[17] = 0x3c3b62c30f6d1f3b; 
	v[1].x[18] = 0x664f6fa3fa13ede0; 
	v[1].x[19] = 0x56a380d50fb1dae7; 
	v[1].x[20] = 0xba657efbb9be8d51; 
	v[1].x[21] = 0x8645c4150ddd4fad; 
	v[1].x[22] = 0xafaa02f875e70e4b; 
	v[1].x[23] = 0xf45fb30229ef60b2; 
	v[1].x[24] = 0x8b33fd00530590c2;  
	v[1].x[25] = 0xbd05a698b962da6; 
	v[1].x[26] = 0xe79a05c8b35414d2; 
	v[1].x[27] = 0xd2fce9303d773095; 
	v[1].x[28] = 0xbdde878c92a493ad; 
	v[1].x[29] = 0x996a9766de837d0c; 
	v[1].x[30] = 0xa27fcb1e39308aa8; 
	v[1].x[31] = 0x146caa1b7f67d37a; 

	p->len = 16;
	p->x[0] = 0x3a097a178d083151; 
	p->x[1] = 0x3c3b62c30f6d1f3b; 
	p->x[2] = 0x664f6fa3fa13ede0; 
	p->x[3] = 0x56a380d50fb1dae7; 
	p->x[4] = 0xba657efbb9be8d51; 
	p->x[5] = 0x8645c4150ddd4fad; 
	p->x[6] = 0xafaa02f875e70e4b; 
	p->x[7] = 0xf45fb30229ef60b2; 
	p->x[8] = 0x8b33fd00530590c2;  
	p->x[9] = 0xbd05a698b962da6; 
	p->x[10] = 0xe79a05c8b35414d2; 
	p->x[11] = 0xd2fce9303d773095; 
	p->x[12] = 0xbdde878c92a493ad; 
	p->x[13] = 0x996a9766de837d0c; 
	p->x[14] = 0xa27fcb1e39308aa8; 
	p->x[15] = 0x146caa1b7f67d37a; 
	
	q->len = 16;
	q->x[0] = 0x4e762326f6dd0021; 
	q->x[1] = 0xd21c82d1c6cc8851; 
	q->x[2] = 0x4b7d6bc79a951918; 
	q->x[3] = 0xb28d190ae13113fd; 
	q->x[4] = 0xa60ff5b0744892a4; 
	q->x[5] = 0xbe2b00f0969e606b; 
	q->x[6] = 0x84d8e7bce6fa33; 
	q->x[7] = 0x8f85014de6390d3e; 
	q->x[8] = 0x31617a4a6e112879; 
	q->x[9] = 0xff199de6cd9435fe; 
	q->x[10] = 0xe876d083498a911a; 
	q->x[11] = 0x82f588470c1725f7; 
	q->x[12] = 0x263394d21d1b8f67; 
	q->x[13] = 0x4876fd330b8c9bb0; 
	q->x[14] = 0x80cd8d4896f370e; 
	q->x[15] = 0x456a15a595b51b28; 

	//v[2] = v_mul(*p, *q);
	//v_print(v + 2, "v[2]", -2, KYEL);
	
	v[2].len = 32;
	v[2].x[0] = 0xfa5ec18596fb5b71; 
	v[2].x[1] = 0x289e89d4263ab758; 
	v[2].x[2] = 0x97d97754f2e3a74c; 
	v[2].x[3] = 0x2d3f94b1ca8d5e1b; 
	v[2].x[4] = 0xf95caf5299a9cb03; 
	v[2].x[5] = 0x3c1b8316a414f682; 
	v[2].x[6] = 0x8550ae2fdf9412a; 
	v[2].x[7] = 0x7bae35762ca380d0; 
	v[2].x[8] = 0xf122a43a19232d6a; 
	v[2].x[9] = 0x2ec423bc30ac0753; 
	v[2].x[10] = 0x6c22757cd7514798; 
	v[2].x[11] = 0x8dc8a5aeccc08afd; 
	v[2].x[12] = 0xb78b72b08186fa71; 
	v[2].x[13] = 0xe1977a2f81588610; 
	v[2].x[14] = 0x2af507feccb84026; 
	v[2].x[15] = 0xfb1a971c511d5e2; 
	v[2].x[16] = 0x58322fee8d1b2778; 
	v[2].x[17] = 0x75898ff40e2d559; 
	v[2].x[18] = 0xc18df5b218f0b43e; 
	v[2].x[19] = 0x6d99bb0d9da42cad; 
	v[2].x[20] = 0x3ca43e4e4ac9e4c5; 
	v[2].x[21] = 0xa66886d7a356372e; 
	v[2].x[22] = 0x981bfab571e56c42; 
	v[2].x[23] = 0x44fcce6ae755b55; 
	v[2].x[24] = 0xeea4841702a6c071;  
	v[2].x[25] = 0x149edfe040fd681b; 
	v[2].x[26] = 0x89ce0b51acd2954a; 
	v[2].x[27] = 0x52b492d17f2b05d6; 
	v[2].x[28] = 0x3cb9bb7b09d9caf1; 
	v[2].x[29] = 0x957c5a2d54401937; 
	v[2].x[30] = 0x2f0080f8b385b8ce; 
	v[2].x[31] = 0x589c091f8a9542b; 
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
