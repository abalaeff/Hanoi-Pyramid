//
//  Usage:
//      simulate_Hanoi [Game Length] [Sampling Size] [RNG Seed] > MyHanoiTrajectory_M_N_T_Nsample.dat
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstring>

int init_disks();
int next_step();
int print_disks_pegs();

// The pyramid parameters
#define Ndisks 3
#define Mpegs  3
int Disks[Ndisks]; // The disk positions
int Pegs[Mpegs];  // The number of the top disk at each peg; -1 if empty 
int CoM = 0; // Center of mass (unscaled); initially all disks sit at point zero

main(int argc , char *argv[] )
{
  // The pyramid parameters
  
  double CoM_scale = 2./(Ndisks*(Ndisks+1)); // Center of mass scaling

  // Simulation parameters
  int T_sim_steps = 10; // 10 steps by default, unless provided as the first call argument
  int N_sample = 1000;   // 1000 trajectories by default, unless provided as the second call argument

  // Miscellaneous variables  
  int i, j, ii;

  // Read the number of steps and the sampling size
  if ( argc > 1 ) { T_sim_steps = atoi(argv[1]); }
  if ( argc > 2 ) { N_sample    = atoi(argv[2]); }

  // Initialize the random number generator
  if ( argc > 3 ) {
   srand(atof(argv[3])); 
  } else {
   srand(time(NULL)); 
  }

  // Run the simulation N_sample times, print the results to the stdout
  for( i = 0; i< N_sample; i++ ) {

  // Initialize the disk positions
    init_disks();

  // Run the simulation
    for( j = 0; j< T_sim_steps; j++ ) {
      next_step();
    }

  // Print the simulation result to the stdout
  //  printf("%d %lf\n", i, CoM*CoM_scale);
  // For precision issues, will pring the unscaled result;
  //  will apply scaling during the data processing.
    printf("%d %d\n", i, CoM);
  }

  exit(0);
}

//---------------------------
// Subroutine:
// Perform next step of the simulation from a given board position
// Returns: the change in the center of mass position (unscaled).

int next_step( ) {

  int i, j; // counters
  int idisk_mov; // The disk to be moved
  int jmov, jpeg_from, jpeg_to; // The pegs between which the disk is moved
  int CoM_change; // CoM change after the move (unscaled)
  int Moves[2*Mpegs-2], N_moves=0; // The array and the number of possible moves
                                 // Move coding:
                                 //  Moves[i] == j: the top disk of the j'th peg to be moved to the right 
                                 //  Moves[i] == -j: the top disk of the j'th peg to be moved to the left 

// Calculate the possible moves
  for( j=0; j<Mpegs; j++ ) {
    // Reminder:
    //  Pegs[j] is the number of the *top* disk sitting on the j'th peg, or -1 if the peg is empty

    if( Pegs[j] == -1 ) continue;
 
    // Is move left possible?
    if( j > 0 ) {
     if( Pegs[j-1] > Pegs[j] || Pegs[j-1] == -1 ) {
      Moves[N_moves] = -j; 
      N_moves++;
    }}

    // Is move right possible?
    if( j < Mpegs-1 ) {
      if( Pegs[j+1] > Pegs[j] || Pegs[j+1] == -1 ) {
        Moves[N_moves] = j;
        N_moves++;
    }}
  }

// Choose a move at random

  jmov = Moves[rand() % N_moves];
  if( jmov >= 0 ) { jpeg_from =  jmov; jpeg_to = jpeg_from + 1; }
  else {            jpeg_from = -jmov; jpeg_to = jpeg_from - 1; }
  idisk_mov = Pegs[jpeg_from];

// Move the disk, update the arrays
  Pegs[jpeg_to] = idisk_mov;  // The "to" peg gets a shiny new disk
  Disks[idisk_mov] = jpeg_to; // The shiny new disk gets assigned to the "to" peg

  Pegs[jpeg_from] = -1; // The "from" peg is empty unless other disks are found on it
  for( i=idisk_mov+1; i<Ndisks; i++ ) {
    if( Disks[i] == jpeg_from ) {
      Pegs[jpeg_from] = i;
      break;
    }
  }

// Update the center of mass position
  CoM_change = (idisk_mov+1) * ( jpeg_to - jpeg_from );
  CoM += CoM_change;
 
  return CoM_change;
}

//-------------------------------------------
// Subroutine: initialize the disk positions

int init_disks( ) {

  int i;

  for( i=0; i<Ndisks; i++ ) { Disks[i] = 0; }
  CoM = 0;
 
  Pegs[0] = 0; 
  for( i=1; i<Mpegs; i++ ) { Pegs[i] = -1; }

}

//---------------------------------------------------------
// Subroutine: print the board state. Useful for debugging.

int print_disks_pegs() {

  int ii;

  printf("Disks: ");
  for( ii = 0; ii< Ndisks; ii++ ) { printf("%d ", Disks[ii]); }
  printf("\n");
  printf("Pegs: ");
  for( ii = 0; ii< Mpegs; ii++ ) { printf("%d ", Pegs[ii]); }
  printf("\n");

}

//---------------------------------------------------------

