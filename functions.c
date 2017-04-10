#include "functions.h"
#include <stdio.h>

/* I will use a macro to define bias */
#define BIAS 0

/*************/
/* GET INPUT */
/*************/

/* gets a input for the perceptron from a data file */
float getInput(FILE * ftp)
{
  float input;

  /* scan the input from the training data */
  fscanf(ftp, "%f ", &input);

  /* Return the input */
  return input;
}


/******************/
/* GET THRESHOLD  */
/******************/
/* Ask the user for a threshold */
/* Note: for now I won't use this function.
 * Instead of asking the user for the threshold,
 * I'll just define it as a macro. 
 */
float getThreshold(void)
{
  float threshold;

  printf("Threshold: ");
  scanf("%f", &threshold);

  return threshold;
}

/**********************/
/* SUM WEIGHTED INPUT */
/**********************/
/* A function for the dot product (summation) of weighted
 * inputs (i.e., (input1 * weight1) + (input2 * weight2) ... */
float sumWeightedInputs(float input1, float input2, float weight1, float weight2)
{
  /* sum means dot product here */
  float sum = 0;

  /* figure out the dot product here */
  sum = (input1 * weight1) + (input2 * weight2);
	sum = sum + BIAS; // add bias

  /* return sum */
  return sum;
}

/******************/
/* UPDATE WEIGHTS */
/******************/

/* This is the function that updates the weights 
 * if the neuron misclassified input. */
/* I am using this formual to update weights: 
 * new weight = old weight + (learning rate * current input * (error)
 * where error = expected output - actual output */
float updateWeights(float weight, float learning_rate, float input, float error)
{
	float new_weight = 0;

	/* use the formula here */
	new_weight = weight + (learning_rate * input * error);
		
	return new_weight;
}

/***********************/
/* ACTIVATION FUNCTION */
/***********************/

/* Activation Function -- sees if the weights is greater 
 * than a certain number, called threshold, and returns 1
 * and 0 therwise. */
int activationFunction(float dot_product, float threshold)
{
  if (dot_product >= threshold) return 1;
  /* object actual_outputified to class 1 */

  else return 2;
  /* object actual_outputified to class 2 */
}

/*****************/
/* CHECK OUTPUT  */
/*****************/

/* Function checks the actual output of the perceptron's ouput against the expected output. */
float checkOutput(FILE * ftp, float actual_output)
{
  float expected_output = 0;

  /* error = expected_ouput - actual_output */
  float error = 0;
  /* the value of error is needed in the update
   * weight formula */

  /* get expected output from data file */
  fscanf(ftp, "%f ", &expected_output);
  printf("\n"); // new line

  printf("Expected Output: %.2f\n", expected_output);
  printf("Actual Output: %.2f\n", actual_output);

  /* calculate error */
  error = expected_output - actual_output;
  return error;
}



