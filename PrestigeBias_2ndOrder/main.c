#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"mt19937ar.h"
#include"prestigebias.h"




FILE *Frequency;
FILE *Choice;
FILE *Demonstrator;
FILE *DynamicPrestige;


int main(int argc, char *argv[]){

  /* variables */
  int i; /* Index */
  int t; /* Time step */
  int init_choice;
  double init_choice_double;


  /* Declaration of struct */
  Individual indiv[INDIVIDUALS];


  /* parameters */
  /* Homogeneous condition*/
  for(i = 0; i < INDIVIDUALS; i++){
    indiv[i].p_bias = atof(argv[1]);
    //printf("%f\n", indiv[i].p_bias);
  }



  /* parameters **/
  mutation_prob = atof(argv[2]);
  mutation_interval = atoi(argv[3]);
  TIME = atoi(argv[4]);
  TRANSIENT = atoi(argv[5]);
  SEED = atoi(argv[6]);  


  /* Dynamic prestige */
  for(i = 0; i < INDIVIDUALS; i++){
    indiv[i].d_prestige = 1;
  }


 
  /* Initialization */  
  for(i = 0; i < INDIVIDUALS; i++){
    indiv[i].demonstrator = (int)(genrand_real3() * INDIVIDUALS);
  }



  /* Initialization: MT */
  init_genrand(SEED);

 
  /* File open */
  FileOpen();


  /* Dynamics */
  for(t = 0; t < TIME; t++){
   
    /** Decision making **/
    /* Initial choice */
    if(t == 0){
      for(i = 0; i < INDIVIDUALS; i++){
        /* Initial choice of cultural trait */
        if(i <= 19){
          init_choice_double = genrand_real3() * NUMOFTRAIT;
          init_choice = (int)init_choice_double;
          indiv[i].choice = init_choice;
        }else if(i > 19){
          init_choice_double = genrand_real3() * NUMOFTRAIT;
          init_choice = (int)init_choice_double;
          indiv[i].choice = init_choice;
        }
      }


    }else if(t >= 1){
      /* Choosing demonstrator, copying his/her trait */
      DecisionMaking(indiv,t);
    }


    /* Copying the present choice to the last choice */
    for(i = 0; i < INDIVIDUALS; i++){
      indiv[i].choice_last = indiv[i].choice;
    }


    /* Calculatiing number of each trait chosen at time t */
    for(i = 0; i < INDIVIDUALS; i++){
      NumberOfTrait[indiv[i].choice] += 1;
    }


    /*** Non-biased transmission ***/
    /* Calculatiing frequencies of each trait */
    for(i = 0; i < NUMOFTRAIT; i++){
      FreqOfTrait[i] = (double)NumberOfTrait[i]/(double)INDIVIDUALS;
    }
  

    fprintf(Frequency, "%d\t", t);
    for(i = 0; i < NUMOFTRAIT; i++){
      fprintf(Frequency, "%f\t", FreqOfTrait[i]);
    }
    fprintf(Frequency, "\n");



    fprintf(Choice, "%d\t", t);
    for(i = 0; i < INDIVIDUALS; i++){
      fprintf(Choice, "%d\t", indiv[i].choice);
    }
    fprintf(Choice, "\n");


    fprintf(Demonstrator, "%d\t", t);
    for(i = 0; i < INDIVIDUALS; i++){
      fprintf(Demonstrator, "%d\t", indiv[i].demonstrator);
    }
    fprintf(Demonstrator, "\n");


    fprintf(DynamicPrestige, "%d\t", t);
    for(i = 0; i < INDIVIDUALS; i++){
      fprintf(DynamicPrestige, "%d\t", indiv[i].d_prestige);
    }
    fprintf(DynamicPrestige, "\n");


    /* Initialization */
    for(i = 0; i < NUMOFTRAIT; i++){
      NumberOfTrait[i] = 0;
    }

  }/* end of dynamics */


  /* file close */
  FileClose();

  
  return 0;

}




