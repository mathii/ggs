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

#ifndef _GGS_CORE
#define _GGS_CORE

void write_progress_to_screen(int g, struct params *p);
void generate_genotypes( int **gt, struct params *p );
int main(int argc, char *argv[]);
#endif
