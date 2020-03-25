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

#>>>>> INPUT PARSER >>>>>
# available tests
test_type[0]='op'
test_type[1]='u64_cmp'
test_type[2]='nnaumenk_cmp'
test_type[3]='find_prime'
test_type[4]='asn1_der'
nb_type=5
# $1 : type of the test
for ((id = 0; id < nb_type; ++id)); do
if [[ $1 == ${test_type[$id]} ]]; then break; fi
done
if (( id == nb_type )); then
echo -ne "${KYEL}usage: sh launch.sh "
for ((i = 0; i < nb_type - 1; i++ )); do echo -n "${test_type[$i]}|"; done
echo -e "${test_type[$i]}$KRNM"
exit
fi
#<<<<< INPUT PARSER <<<<<<

#>>>>> OP TESTS >>>>>
if ((id >= 0  && id <= 2)); then
# $2 : op to process
# $3 : numb of uint8_t 
# $4 : numb of tests
if (( $# != 4 )); then
echo -e "${KYEL}usage: sh launch.sh ${test_type[$id]} op_name uint8_nb test_nb${KNRM}"
exit
fi
echo -e "${KBLU}${test_type[$id]} test start:${KNRM}\n"
i=-1
ok=0
col=$KGRN
while ((++i < $4));do
./varint_test $1 $2 $3
if (($? == 42)); then ((ok += 1)); else col=$KRED; fi
echo -ne "$col${ok}/${4}${KNRM}"
if ((i != $4 - 1));then echo -ne "\r"; else echo -ne "\n"; fi
done
#<<<<< OP TESTS <<<<<

#>>>>>FIND_PRIME TEST>>>>>
elif ((id == 3)); then
# $2 : numb of uint8_t
# $3 : numb of test
if (( $# != 3 )); then
echo -e "${KYEL}usage: sh launch.sh ${test_type[$id]} uint8_nb test_nb${KNRM}"
exit
fi
echo -e "${KBLU}${test_type[$id]} test start:${KNRM}\n"
i=-1
while ((++i < $3));do
./varint_test $1 $2
done
#<<<<<FIND_PRIME TEST<<<<<

#>>>>>ASN1_DER TEST ON RSA PRIVATE KEY>>>>>
elif ((id == 4)); then
# $3 : size of modulus in bits
# $4 : numb of test
if (( $# != 4 )); then
echo -e "${KYEL}usage: sh launch.sh ${test_type[$id]} rsa numbits test_nb${KNRM}"
exit
fi
echo -e "${KBLU}${test_type[$id]} test start:${KNRM}\n"
err512="don't use key size < 512"
i=0
ok=0
col=$KYEL
while ((i < $4));do
openssl genrsa -out rand_key.pem $3 > /dev/null 2>&1 
if (($? != 0));then echo -e "${KRED}${err512}${KNRM}"; exit; fi
openssl rsa -in rand_key.pem -outform DER -out rand_key.der > /dev/null 2>&1
./varint_test asn1_der rsa ./rand_key.der key.der
diff rand_key.der key.der
if (($? == 0));then ((ok += 1)); fi
((i += 1))
if ((i != ok));then col=$KRED; fi
echo -ne "${COL}${OK}/$4${KNRM}"
echo -ne "\r"
done
if ((i == ok));then col=$KGRN; fi
echo -e "${col}${ok}/$4${KNRM}"
rm rand_key.pem rand_key.der key.der
#<<<<<ASN1_DER TEST ON RSA PRIVATE KEY<<<<<

fi
