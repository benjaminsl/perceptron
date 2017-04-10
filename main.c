/*************************************************************/
/* This is a program that implements the preceptron learning */
/* algorithm -- single layer. It gets the training set from  */
/* the file training_data.txt (change the macro to use a     */
/* different file). Right now it only works with two inputs. */
/*************************************************************/

/**********************************/
/* How the data file works:       */
/* ^Each line is a new set        */
/* ^the first number is input1    */ 
/* ^the second number is input2   */
/* ^the third number is the class */
/*     means the end of data      */
/**********************************/ 

/***********************************************/
/* Here is a very good tutorial on perceptron: */
/* http://tinyurl.com/lul2yw4                  */
/***********************************************/

#include <stdio.h>
#include <stdlib.h>
/* for rand() */
#include <time.h>
#include <unistd.h>
/* for sleep */
#include <stdbool.h>
/* for type bool */

#include "functions.h"
/* function for updating weights */

/* _______________ */
/*                 */
/*     MACROS      */
/* _______________ */
#define THRESHOLD .5
#define DATA_FILE "training_data.txt"
#define LEARNING_RATE -.2 
// NOTE: bias defined in functions.c

int main(void)
{
	/* ___________________ */
	/*                     */
  /*     FILE I/O        */
  /* ___________________ */

	/* open training_data.txt for reading */
	FILE * file_pointer = fopen(DATA_FILE, "r");
	
	/* make sure the file can be opened */
	if (file_pointer == NULL)
	{
		fprintf(stderr, "Cannot open training data file.\n");
		fprintf(stderr, "Check permissions for data file.\n");
		exit(1);
	}

	/* ___________________ */
	/*                     */
  /*     VARIABLES       */
  /* ___________________ */

	float input1 = 0, input2 = 0;	
	/* the inputs for the artifical neural network */

	float weight1 = 0, weight2 = 0;
	/* the weights for the artifical neural network */

	float threshold = 0;
	/* used in Activation Function */
	/* if summation of weighted inputs >= threshold,
   * Activation Function returns true. Otherwise,
   * Activation Function returns false. */


	/* get learning rate from macro */
	float learning_rate = LEARNING_RATE;

	float dot_product = 0;
	/* dot product = (a1 * b1) + (a2 * b2) + ... + (an * bn) */
  /* This will be the summation of all the weighted inputs.
   * This value will be given to the activation function. */

	/* What actual_output is the object being classified in? */
	int actual_output = 0;

  /* error = expected output - actual ouput */
	/* error is used in the update weight formula */
	float error = 0;

	/* I will keep track of if there are any incorrect
   * classifications left by using a boolean value.
   * true means there are still incorrect classifications
   * flase means all classifications are correct. */
	bool incorrectClassifications = true;

	printf("PERCEPTRON TRAINING ALGORITHM IMPLEMENTATION\n");

	/* ___________________ */
	/*                     */
  /*        INPUT        */
  /* ___________________ */

	/* We need to seed the random number generator. 
 	 * Otherwise, it will produce the same number every time
 	 * the program is run. */
	srand(time(NULL));
	/* I am using the current time to seed rand(). */

	/* get threshold from the user */
	//threshold = getThreshold();

	/* get threshold from macro */
	threshold = THRESHOLD;

	/* The weights will start off as random numbers in 
	 * the range [0, 1]. */
	weight1 = ((float)rand()/(float)(RAND_MAX/1.0)); 
	weight2 = ((float)rand()/(float)(RAND_MAX/1.0)); 

	while (incorrectClassifications == true)
	{
		incorrectClassifications = false;

		/* Let's loop through all the data sets. */
		int i = 1;

		/* loop will break if input = 999 */
		while (1)
		{

			/* get input from the data set file */	
			input1 = getInput(file_pointer);
			if (input1 == 999) break;
			input2 = getInput(file_pointer);

			/* ___________________ */
			/*                     */
			/*     CALCULATION     */
			/* ___________________ */

			/* sum the weighted inputs */
			dot_product = sumWeightedInputs(input1, input2, weight1, weight2);

			/* apply activation function to sum of weighted inputs */
			actual_output = activationFunction(dot_product, threshold);	

			/* ___________________ */
			/*                     */
			/*       OUPUT         */
			/* ___________________ */

			/* print which data set we are on */
			printf("Data Set %d\n", i);

			/* print the inputs */
			printf("\n"); // new line
			printf("Input 1 = %.2f\n", input1);
			printf("Input 2 = %.2f\n", input2);

			/* print the weights */
			printf("\n"); // new line
			printf("Weight 1 = %.2f\n", weight1);
			printf("Weight 2 = %.2f\n", weight2);

			/* print the summation of weighted inputs */
			printf("\n"); // new line
			printf("Summation = %.2f\n", dot_product);

			/* print the actual_output */
			printf("Object classified to class %d.\n", actual_output);

			/* check the output */
			error = checkOutput(file_pointer, actual_output);

			/* print the result */
			if (error == 0) printf("Ouput correct.\n");
			else 
			{
				/* set incorrectClassifications to true 
         * to loop through the data set once more */
				incorrectClassifications = true;
	
				printf("Output incorrect.\n");
				printf("Error = %.0f\n", error);

				/* we need to update the weights if *
				 * there is an error */
				weight1 = updateWeights(weight1, learning_rate, input1, error);
				weight2 = updateWeights(weight2, learning_rate, input2, error);

				/* print the new weights */
				printf("\n"); // new line;
				printf("NEW WEIGHTS: \n");
				printf("*** New weight 1: %.2f\n", weight1);
				printf("*** New weight 2: %.2f\n", weight2);
			} // ends else

				printf("\n");
				printf("-----------------------------------------------\n");
				printf("-----------------------------------------------\n\n");

				i++; //increment i
			
				sleep(1);

		} // ends while (1)

	/* set the file pointer back to beginning of file */
	rewind(file_pointer);

	} // ends while(incorrectClassifications == true)

	/* Print the final weights */
	printf("\n");
	printf("Final Weights: \n");
	printf("Weight 1: %.2f\n", weight1);	
	printf("Weight 2: %.2f\n", weight2);

	/* close the input file */ 
	fclose(file_pointer);

	return 0;

} // ends main()
