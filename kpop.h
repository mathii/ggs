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

/* Sampling functions - anaalgous to the R functions */
int sample(int n, double *probs);
int sample_populations(int *pop_list, int pop, int n_sum);

/* Actually simulate the tree */
void simulate_tree_kpop_lattice_c(int *k_val, int *n, double *M, int *RNG_seed, double *Time, int *D1, int *D2, double* Branch_Length, int* Parent);

/* Throw down a mutation on the tree and return the genotypes if the individuals*/
void one_mutation_from_tree(int *n_sum, int *gt,int *D1, int *D2, double* Branch_Length);

/* Fill in all the descendants of node with genotype 1 */
void fill_in_genotypes(int n_sum, int *gt, int *D1, int*D2, int node);
