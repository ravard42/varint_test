BEGIN {n = 0; sum_clck = 0;}
/INSTR_AWK_FILTER/ {sum_clck += $2; n += 1; print n}
END {	print "instr_clock-time_average: ", sum_clck / n;
}
