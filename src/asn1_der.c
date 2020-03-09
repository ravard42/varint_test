#include "libft.h"

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
	if ((v = v_asn1_int_seq_der_d(&nb_v, &r)))
	{
		free(r.msg);
		if (v_asn1_int_seq_der_e(&r, v, nb_v) == -1)
			return (-1);
		fd_out = open(out_der, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1 && ft_dprintf(2, "error opening file\n"))
			return (-1);
		write(fd_out, r.msg, r.len);
		free(r.msg);
		free(v);
		close(fd_out);
		return (0);
	}
	free(r.msg);
	return (-1);
}
