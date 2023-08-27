#ifndef PRESTIGEBIAS_H
#define PRESTIGEBIAS_H


#define NUMOFTRAIT 2 /* Number of cultural trait */
#define INDIVIDUALS 100 /* Number of players */

#define PI 4.0*atan(1.0)


/* Player */
typedef struct Individual{
	int choice; /* Move at time t */
	int choice_last; /* Move at time t-1 */
	int demonstrator; /* Demonstrator at time t */
	double s_prestige; /* Prestige as given attribute (static prestige) */
	int d_prestige; /* Prestige as number of reference (dynamic prestige) */
    double p_bias; /* Prestige bias */
} Individual;



/* Parameters */
extern int TIME;
extern int TRANSIENT;
extern int SEED;


/* Statistical values */
extern int NumberOfTrait[NUMOFTRAIT];
extern double FreqOfTrait[NUMOFTRAIT];
extern double Biased_Prestige[INDIVIDUALS];
extern double BiasedPrestige_Sum;
extern double ChoiceProb[INDIVIDUALS];
extern double CumulativeChoiceProb[INDIVIDUALS];

extern double mutation_prob;
extern int mutation_interval;



/*** Prototype function ***/
/* Decision making */
void DecisionMaking(Individual *indiv, int t);


/* File open */
void FileOpen();

/* File close */
void FileClose();



#endif


