#!/bin/bash

KNRM="\x1B[0m"
KRED="\x1B[31;1m"
KGRN="\x1B[32;1m"
KYEL="\x1B[33;1m"
KBLU="\x1B[34;1m"
KMAG="\x1B[35;1m"
KCYN="\x1B[36;1m"
KWHT="\x1B[37;1m"

# $1 : type of the test
# "op" | "u64_cmp" | "nnaumenk_cmp" | "find_prime" | "asn1_der"

#-----OP TESTS-----

if [[ $1 == "op" || $1 == "u64_cmp" || $1 == "nnaumenk_cmp" ]] && (($# == 4));then
# $2 : op to process
# $3 : numb of uint8_t 
# $4 : numb of tests


if [[ $1 == "op" ]];then
COL=$KYEL
echo -e "${KBLU}OP TEST START${KNRM}\n"
elif [[ $1 == "u64_cmp" ]];then
COL=$KGRN
echo -e "${KBLU}U64_CMP TEST START${KNRM}\n"
else
COL=$KGRN
echo -e "${KBLU}NNAUMENK_CMP TEST START\n\nAverage compute-time by op on $4 random $2 ${KNRM}\n"
fi

OK=0
i=-1

while ((++i < $4));do

./varint_test $1 $2 $3

if (($? == 42)); then
((OK += 1))
else
COL=$KRED
fi


echo -ne "$COL${OK}/${4}${KNRM}"
if ((i != $4 - 1));then
echo -ne "\r"
else
echo -ne "\n"
fi

done
fi

#-----FIND_PRIME TEST-----

if [[ $1 == find_prime ]] && (($# == 3));then
# $2 : numb of uint8_t
# $3 : numb of test

i=-1

echo -e "${KBLU}FIND_PRIME TEST START${KNRM}\n"

while ((++i < $3));do

./varint_test $1 $2

done
fi

#-----ASN1_DER TEST-----

#BASIC

if [[ $1 == asn1_der && $2 == basic ]];then
./varint_test asn1_der basic out.der
hexdump -ve '1/1 "%.2x"' out.der
rm out.der
fi

#RSA PRIVATE KEY

if [[ $1 == asn1_der && $2 == rsa ]] && (($# == 4));then
# $3 : size of modulus in bits
# $4 : numb of test

i=0
OK=0
COL=$KYEL

while ((i < $4));do
openssl genrsa -out rand_key.pem $3 > /dev/null 2>&1 
openssl rsa -in rand_key.pem -outform DER -out rand_key.der > /dev/null 2>&1
./varint_test asn1_der rsa ./rand_key.der key.der
diff rand_key.der key.der

if (($? == 0));then
((OK += 1))
fi
((i += 1))

if ((i != OK));then
COL=$KRED
fi
echo -ne "${COL}${OK}/$4${KNRM}"
echo -ne "\r"
done

if ((i == OK));then
COL=$KGRN
fi
echo -e "${COL}${OK}/$4${KNRM}"
rm rand_key.pem rand_key.der key.der

fi
