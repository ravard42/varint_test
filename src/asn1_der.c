#include "libft.h"

/*
** BASIC ASN1_DER-TLV INTEGER SEQUENCE encode decode TEST
**
**	usage : ./varint_test asn1_der basic out.der
**	 	1] on défini les varint à encoder directement dans le _e
**		2]	_e les encode en asn1_der dans out.der
**		3]	_d les decode en tableau de varint qu'il v_print sur stdout
*/

static int		basic_asn1_der_e(char *out_der)
{
	t_varint		v[3] = {{1, {42}, 1}, {1, {1, 1}, 2}, g_v[1]};
//	t_varint		v[3] = {g_v[0], g_v[1], g_v[2]};
	int			ret;

	ret = v_asn1_der_int_seq_e(out_der, v, 3);
	return (ret);
}

static int		basic_asn1_der_d(char *in_der)
{
	t_read 	r;
	t_varint *v;
	int		nb_v;
	int		id;

	if (ft_read(&r, in_der) < 0 
			&& ft_dprintf(2, "%sft_read error in asn1_der decoding\n%s", KRED, KNRM))
		return (-1);
	if ((v = v_asn1_der_int_seq_d(&nb_v, &r)))
	{
		id = -1;
		while (++id < nb_v)
			v_print(v + id, "id = ", id, KYEL);
		free(v);
	}
	free(r.msg);
	return (0);
}

int		basic_asn1_der_test(char *f_der)
{

	if(basic_asn1_der_e(f_der) == -1
		&& ft_dprintf(2, "%serror in basic_asn1_der_e%s\n", KRED, KNRM))
		return (-1);
	return (basic_asn1_der_d(f_der));
}

/*
** RSA ASN1_DER-TLV INTEGER SEQUENCE encode decode TEST
*/

int		rsa_asn1_der_test(char *in_der, char *out_der)
{
	t_read		r;
	t_varint		*v;
	int			nb_v;
	int			fd_out;

	if (ft_read(&r, in_der) < 0 
			&& ft_dprintf(2, "%sft_read error: rsa_asn1_der_verif\n%s", KRED, KNRM))
		return (-1);
	if ((v = v_asn1_der_int_seq_d(&nb_v, &r)))
	{
		fd_out = open(out_der, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1 && ft_dprintf(2, "error opening file\n"))
			return (-1);
		if (v_asn1_der_int_seq_e(out_der, v, nb_v) == -1)
			return (-1);
		free(v);
		free(r.msg);
		close(fd_out);
		return (0);
	}
	free(r.msg);
	return (-1);
}
