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

/* I/O functions for grid genotype simulator */

/* Write genotpye matrix to file
gt: genotype matrix
outfile: path to file
 */

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

int write_genotypes( int **gt, int n_rows, int n_cols, struct params *p ); 
void print_help();
void parse_args(int argc, char *argv[], struct params *p);
