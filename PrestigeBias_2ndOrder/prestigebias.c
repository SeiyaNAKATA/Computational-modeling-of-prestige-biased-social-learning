#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"mt19937ar.h"
#include"prestigebias.h"



/* Parameters */
int TIME;
int TRANSIENT;
int SEED;


/* Statistical values */
int NumberOfTrait[NUMOFTRAIT];
double FreqOfTrait[NUMOFTRAIT];

//double Prestige_Sum;
double Biased_Prestige[INDIVIDUALS];
double BiasedPrestige_Sum;
double CumulativeChoiceProb[INDIVIDUALS];

double ChoiceProb[INDIVIDUALS];

double mutation_prob;
int mutation_interval;


/* File pointer */
FILE *Frequency;
FILE *Choice;
FILE *Demonstrator;
FILE *DynamicPrestige;


/* Decision making by roulette selection with Boltzman distributuion */
void DecisionMaking(Individual *indiv, int t){

  /* variables */
  int i,j;


  /* Initialization */
  for(i = 0; i < NUMOFTRAIT; i++){
    NumberOfTrait[i] = 0;
  }

  for(i = 0; i < INDIVIDUALS; i++){
    Biased_Prestige[i] = 0.0;
    ChoiceProb[i] = 0.0;
    CumulativeChoiceProb[i] = 0.0;
  }

  BiasedPrestige_Sum = 0.0;


  /*** Biased transmission ***/
  for(i = 0; i < INDIVIDUALS; i++){
    /* Prestige bias */
    Biased_Prestige[i] = pow(indiv[i].d_prestige, indiv[i].p_bias);
    BiasedPrestige_Sum += Biased_Prestige[i];
  }

  for(i = 0; i < INDIVIDUALS; i++){
    ChoiceProb[i] = Biased_Prestige[i]/BiasedPrestige_Sum;
  }


  /* Calculating cumulative prestige */
  for(i = 0; i < INDIVIDUALS; i++){
    if(i == 0){
      /* Prestige bias */
      CumulativeChoiceProb[i] = ChoiceProb[i];

    }else if(i > 0){
      /* Prestige bias */
      CumulativeChoiceProb[i] = CumulativeChoiceProb[i-1] + ChoiceProb[i];
    }
  }


  /* Choosing demonstrator */
  int n = 0; /* counter */
  double sample = 0.0;

  for(i = 0; i < INDIVIDUALS; i++){
    sample = genrand_real3();
    for(j = 0; j < INDIVIDUALS; j++){
      if(sample <= CumulativeChoiceProb[j]){
        indiv[i].demonstrator = j;
        n++;
        break;
      }
    }
  }


  /* Calculating dynamic prestige */
  /* initialization */  
  for(i = 0; i < INDIVIDUALS; i++){
	indiv[i].d_prestige = 0;
  }

  for(i = 0; i < INDIVIDUALS; i++){
	indiv[indiv[i].demonstrator].d_prestige ++;
  }
  

  /* Copying demonstrator's last choice */
  for(i = 0; i < INDIVIDUALS; i++){
	indiv[i].choice = indiv[indiv[i].demonstrator].choice_last;
  }


  /* Mutation */
  if((t >= mutation_interval) && ((t % mutation_interval) == 0)){

    int counter = 0;
    double random_num = 0.0;

    for(i = 0; i < INDIVIDUALS; i++){

     random_num = genrand_real3();

	 /* If the Number of traits is two */
     for(j = 0; j < INDIVIDUALS; j++){
       if(random_num <= mutation_prob){
         if(indiv[i].choice == 0){ /* flipping the traits */
           indiv[i].choice = 1;
         }else if(indiv[i].choice == 1){ /* flipping the traits */
           indiv[i].choice = 0;
         }
         counter++;
         break;
       }
     }
    }

  }


 return;

}


/* File open */
void FileOpen(){

  //char str[256];

  if((Frequency = fopen("./Frequency.dat","w")) == NULL){
    printf("error Frequency\n");
    exit(1);  
  }

  if((Choice = fopen("./Choice.dat","w")) == NULL){
    printf("error Choice\n");
    exit(1);  
  }

  if((Demonstrator = fopen("./Demonstrator.dat","w")) == NULL){
    printf("error Demonstrator\n");
    exit(1);  
  }

  if((DynamicPrestige = fopen("./DynamicPrestige.dat","w")) == NULL){
    printf("error DynamicPrestige\n");
    exit(1);  
  }

}


/* File close */
void FileClose(){

  fclose(Frequency);

}


