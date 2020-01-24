The code was written in July 2017 for the semifinal task 1
of Data Incubator fellowship competition.

The code simulates a random game of Hanoi Pyramid with 
desired parameters, and repeats the simulation a desired 
number of times. The goal is to determine the average center
mass position of the disks on the board after N moves.

The CPP code runs the simulation, the Awk scripts/commands 
process the results and prepare the data file for plotting
by xmgrace.

The two JPEG files show results of two simulations for a
3-peg and a 6-peg Hanoi Pyramid games.

---------------------------------------------------

Execution sequence

gcc -o simulate_Hanoi_6 simulate_Hanoi.cpp
./simulate_Hanoi_6 256 10000000 31415 > Hanoi_6_256_steps_10M_sample_31415.dat &

gawk '{a[$2]++}END{for(i in a){ print i, a[i], a[i]/NR}}' Hanoi_6_256_steps_10M_sample_31415.dat | sort -g -k1,1 > Hanoi_6_256_steps_10M_sample_31415_Distribution.dat

gawk -v Ndisks=6 -f Hanoi_ave.awk Hanoi_6_256_steps_10M_sample_31415_Distribution.dat

xmgrace -nxy Hanoi_3_100K_distribution.dat

