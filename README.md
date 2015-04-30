Copyright 2011 Iain Mathieson

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
  
http://www.apache.org/licenses/LICENSE-2.0
  
Unless required by applicable law or agreed to in writing, software 
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
See the License for the specific language governing permissions and
limitations under the License. 

***********************************************************************
Grid Genotype Simulator
- Coalescent simulator for genotypes from a
stepping-stone model of population structure

***********************************************************************

COMPILING

gcc -Wall ggs.c kpop.c ggs_io.c -o ggs

EXAMPLE

`./ggs -K 10 -c 2 -M 0.01 -G 10 -L 100 -o genotypes.txt -s 12345`

ARGUMENTS

-K: Grid size. There will be K*K demes.
-c: Number of individuals sampled from each deme
-M: Migration rate
-G: Number of genealogies (independent trees) to simulate
-L: Number of loci to simulate at each genotype
-o: Output file (leave blank to print to screen)
-s: Random seed (defaults to 0, and sets according to the clock)

OUTPUT

The output has individuals in columns and variants in rows. Columns
are labeled as xpos,ypos,individual, where xpos and ypos are the grid
positions and individual is the label of that individual in that grid
square. so 0<=xpos,ypos<K and 0<=individual<c. Rows are labeled as 
genealogy,locus where 0<genealogy<=G and 0<=locus<L. For each variant 0 
represents an ancestral allele and 1 represents a derived allele. 

DETAILS
Details can be found in "Differential confounding of rare and common 
variants in spatially structured populations; Mathieson I, McVean G;
Nature Genetics 2012". Please cite this paper if you use this software.
