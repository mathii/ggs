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

/* I/o functions for grid genotype simulator */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Parameters for simulation */
struct params
{
  int K; 			/* Grid size - KxK demes*/
  int c;			/* Number of individuals in each deme */
  double M;			/* Migration rate, M */
  int L;			/* Number of loci at each genealogy */
  int G;			/* Number of genealogies */
  int s;                        /* Random seed, default zero sets by clock */
  char *out;			/* output path */
}; 

/* Write genotpye matrix to file
gt: genotype matrix
outfile: path to file
 */
int write_genotypes( int **gt, int n_rows, int n_cols, struct params *p )
{
  int l,g,i,j,k;
  FILE *outfile;

  if(p->out != NULL){
    outfile=fopen(p->out,"w");
    printf("Writing to %s\n", p->out);
  }
  else{
    outfile=stdout;
    printf("Writing to screen\n");
  }

  fprintf(outfile, "\t");
  for(i=0;i<p->K;i++)
    for(j=0;j<p->K;j++)
      for(k=0;k<p->c;k++)
	fprintf(outfile, "%d/%d/%d\t",i,j,k);
     
  fprintf(outfile, "\b\n");

  for(g=0;g<p->G;g++){
    for(l=0;l<p->L;l++){
      fprintf(outfile, "%d,%d\t", g, l);
      for( j=0; j<n_cols-1; j++){
	fprintf( outfile, "%d\t", gt[g*p->L+l][j]);
      };
      fprintf( outfile, "%d\n", gt[g*p->L+l][n_cols-1]);
    };
  };

  fclose(outfile);

  return 0;
}; 

/* Print help to screen */

void print_help()
{
  printf("\nArguments:\n");
  printf("-K: Grid size. There will be K*K demes (required)\n");
  printf("-c: Number of individuals sampled from each deme (required)\n");
  printf("-M: Migration rate (required)\n");
  printf("-G: Number of genealogies (independent trees) to simulate (required)\n");
  printf("-L: Number of loci to simulate at each genotype (required)\n");
  printf("-o: Output file (leave blank to print to screen)\n");
};

/* Parse arguments */

void parse_args(int argc, char *argv[], struct params *p)
{
  int  arg;
  p->s=0;
    while ((arg = getopt (argc, argv, "K:c:M:L:G:ho:s:")) != -1)
      {     
	switch(arg)
	  {
	  case 'K':
	    p->K=atoi(optarg);
	    break;
	  case 'c':
	    p->c=atoi(optarg);
	    break;
	  case 'M':
	    p->M=atof(optarg);
	    break;
	  case 'G':
	    p->G=atoi(optarg);
	    break;
	  case 'L':
	    p->L=atoi(optarg);
	    break;
	  case 'h':
	    print_help();
	    exit(0);
	    break;
	  case 'o':
	    p->out=optarg;
	    break;
	  case 's':
	    p->s=atoi(optarg);
	  };
      };
    
    if( p->K<0 || p->c<0 || p->M<0 || p->G<0 || p->L<0){  
      printf("Please specify all required arguments: K,c,M,G and L\n");
      print_help();
      exit(0);
    }
    else{
      printf("Running with the following arguments\n");
      printf("K=%d\n", p->K);
      printf("c=%d\n", p->c);
      printf("M=%f\n", p->M);
      printf("L=%d\n", p->L);
      printf("G=%d\n", p->G);
      if(p->out != NULL){
	printf("out=%s\n", p->out);
      };
    }

};
