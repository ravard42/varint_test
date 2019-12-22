KNRM="\x1B[0m"
KRED="\x1B[31;1m"
KGRN="\x1B[32;1m"
KYEL="\x1B[33;1m"
KBLU="\x1B[34;1m"
KMAG="\x1B[35;1m"
KCYN="\x1B[36;1m"
KWHT="\x1B[37;1m"

# VARINT_TESTS

# $1 : type of the test
# "speed_op" | "verif_op" | find_prime"


if [[ $1 == "speed_op" || $1 == "verif_op" ]] && (($# == 4));then
# $2 : op to process
# $3 : numb of V_TYPE 
# $4 : numb of test


if [[ $1 == "speed_op" ]];then
COL=$KYEL
echo -e "${KBLU}SPEED_OP TEST START\n"
else
COL=$KGRN
echo -e "${KBLU}VERIF_OP TEST START\n"
fi

OK=0
i=-1

while ((++i < $4));do

./varint_test $1 $2 $3

if (($? == 42)); then
((OK += 1))
fi


echo -ne "$COL${OK}/${4}${KNRM}"
if ((i != $4 - 1));then
echo -ne "\r"
else
echo -ne "\n"
fi

done
fi

if [[ $1 == find_prime ]] && (($# == 3));then
# $2 : numb of V_TYPE
# $3 : numb of test

i=-1

echo -e "${KBLU}FIND_PRIME TEST START\n"

while ((++i < $3));do

./varint_test $1 $2

done
fi
