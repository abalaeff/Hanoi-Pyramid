#
# Usage:
#  gawk -v Ndisks=6 -f Hanoi_ave.awk Hanoi_6_256_steps_10M_sample_31415_Distribution.dat
#
# Input format: the distribution of unscaled COM positions:
#           $1              $2                  $3 
# COM_position(unscaled)   N_of_instances    Probability=N_of_instances/N_sampling
#

BEGIN {
  a = 0; a2 = 0; Npoints = 0;
  Cscale = 2./(Ndisks*(Ndisks+1.));
}

{
 a += $1*$2;
 a2 += $1*$1*$2;
 Npoints += $2;
}

END {
 a /= Npoints;
 a2 /= Npoints;
 sigma = sqrt( a2 - a*a );
 printf("%lf +/- %lf \n", a*Cscale, sigma*Cscale);

}
