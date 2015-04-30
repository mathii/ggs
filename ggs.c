/*
  Copyright 2011 Iain Mathieson

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  
  http://www.apache.org/licenses/LICENSE-2.0
  
  Unless required by applicable law or agreed to in writing, software 
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
  See the License for the specific language governing permissions and
  limitations under the License. 
*/

/* Grid Genotype Simulator
- Coalescent simulator for genotypes from a
stepping-stone model of population structure */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "ggs_io.h"
#include "kpop.h"

const char version_number[]="1.0";

/* Function to parse command line args, returns 
parameters for simulation */
/* Go back to the start of the line and write progress */
void write_progress_to_screen(int g, struct params *p){
  printf("\rGenealogy [%d/%d]", g, p->G);
  fflush(stdout);
}

/* Simulate coalescent, generate genotypes, and return*/
void generate_genotypes( int **gt, struct params *p ){
  int i,l,g,n_nodes, n_sum, *k_val,*n, RNG_seed,*D1,*D2,*Parent;
  int *RNG_seed_ptr=&RNG_seed;
  int *n_sum_ptr=&n_sum;
  double *M, *Time, *branch_length;

  /* Allocate memory */
  n_nodes=2*p->c*p->K*p->K-1;
  D1=(int*) malloc(n_nodes*sizeof(int));
  D2=(int*) malloc(n_nodes*sizeof(int));
  Parent=(int*) malloc(n_nodes*sizeof(int));
  Time=(double*) malloc(n_nodes*sizeof(double));
  branch_length=(double*) malloc(n_nodes*sizeof(double));
  n=(int*) malloc(p->K*p->K*sizeof(int));

  M=&(p->M);
  k_val=&(p->K);
  RNG_seed=p->s;
  if( RNG_seed==0 ){
    RNG_seed=time(NULL);
  }
  n_sum=p->c*p->K*p->K;
  srand(RNG_seed);
  rand();
  for(g=0;g<p->G;g++){
    RNG_seed=rand();
    for(i=0; i<p->K*p->K; i++)
      n[i]=p->c;

    write_progress_to_screen(g+1,p);

    simulate_tree_kpop_lattice_c(k_val, n, M, RNG_seed_ptr, Time, D1, D2, branch_length, Parent);
    
    for(l=0;l<p->L;l++){
      one_mutation_from_tree(n_sum_ptr, gt[g*p->L+l], D1, D2, branch_length);
    };
  };

  /* Cleanup */
  free(D1);
  free(D2);
  free(Parent);
  free(Time);
  free(branch_length);
  free(n);
  printf("\n");
}

/* main, natch */
int main(int argc, char *argv[])
{
  struct params parameters={-1,-1,-1,-1,-1};
  struct params *p=&parameters;
  int **genotypes, i, j, n_rows, n_cols;

  printf("Grid genotype simulator, version %s\n", version_number);
  printf("(c) Iain Mathieson 2011\n\n");
  parse_args( argc, argv, p);

  /* Allocate genotype array */
  n_rows=p->L*p->G;
  n_cols=p->c*p->K*p->K;
  genotypes = (int**) malloc(n_rows*sizeof(int*));
  for( i=0; i<n_rows; i++){
    genotypes[i] = (int*) malloc(n_cols*sizeof(int));
    for(j=0; j<n_cols; j++){
      genotypes[i][j]=0;
    };
  };

  printf("Simulating...\n");
  generate_genotypes( genotypes, p);
  write_genotypes( genotypes,n_rows, n_cols, p);
  printf("Finished\n");

  /* Cleanup genotypes */
  for( i=0; i<n_rows; i++){
    free(genotypes[i]);
  }
  free(genotypes);

  return 0;
}
