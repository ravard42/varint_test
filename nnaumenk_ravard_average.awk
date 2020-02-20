BEGIN {nna = 0; rav = 0; n = 0}
{print}
/NNAUMENK_CMP_AWK_FILTER/ {nna += $4; rav += $10; n += 1; print "\t\t\t", n}
END {	print "nnaumenk: ", nna / n, " clocks";
		print "ravard:   ", rav / n, " clocks";
		ratio = nna / rav;
		if (ratio > 1) {
			print "ratio:    ", nna / rav;
		}
		else {
			print "ratio:     1 /", 1 / ratio;
		}
}
