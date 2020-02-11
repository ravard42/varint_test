BEGIN {nna = 0; rav = 0; n = 0}
#/ms/ {print $3,$6}
#{print "yop", $1}
{print}
{print "\t\t\t", n}
/ms/ {nna += $3; rav += $6; n += 1}
END {	print "nnaumenk: ", nna / n, " ms";
		print "ravard:   ", rav / n, " ms";
}
