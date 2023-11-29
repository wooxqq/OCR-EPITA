#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>


#define nbInputs 2
#define nbHiddenNodes 2
#define nbOutput 1
#define nbTrainingSets 4


double initweight(){
	return ((double)rand())/((double)RAND_MAX);
}

double sigmoid(double x){
	return 1/(1+exp(-x));
}

double dSigmoid(double x){
	return x*(1-x);
}

void swap(int a, int b)
{
	int s=b;
	b=a;
	a=s;
}

void shuffle(int *array,size_t n)
{
	if (n>1)
	{
		for (size_t i=0; i<n-1;i++)
		{
			size_t j= i+rand() /(RAND_MAX / (n-i) +1);
			swap(array[j],array[i]);
		}
	}
}

int main()
{
	srand(time(NULL));
	//float finaloutput;
	const double learningrate=0.1f;

	double hiddenLayer[nbHiddenNodes];
	double outputLayer[nbOutput];

	double hiddenLayerBias[nbHiddenNodes];
	double outputLayerBias[nbOutput];

	double hiddenWeights[nbInputs][nbHiddenNodes]; 
	double outputsWeights[nbHiddenNodes][nbOutput];

	double training_inputs[nbTrainingSets][nbInputs] =	 {{0.0f,0.0f},
								{1.0f,0.0f},
								{0.0f,1.0f},
								{1.0f,1.0f}};

	double training_outputs[nbTrainingSets][nbOutput] =	{{0.0f},
								{1.0f},
								{1.0f},
								{0.0f}};

	for (int i=0;i<nbInputs;i++)
	{
		for (int j=0;j<nbHiddenNodes;j++)
		{
			hiddenWeights[i][j]=initweight();
		}
	}

	for (int i=0; i<nbHiddenNodes; i++)
	{
		for (int j=0; j<nbOutput; j++)
		{
			outputsWeights[i][j]=initweight();
		}
	}

	for (int i=0; i<nbOutput; i++)
	{
		outputLayerBias[i]=initweight();
	}

	int trainingSetOrder[]={0,1,2,3};

	int numberOfLoop=100000;
	// Train the neural network for numberOfLoop
	
	for (int loop=0; loop<numberOfLoop; loop++)
	{
		shuffle(trainingSetOrder,nbTrainingSets);

		for (int x=0; x<nbTrainingSets; x++)
		{
			int i=trainingSetOrder[x];

			//Forward pass

			// Compute hidden layer activation
			
			for (int j=0; j<nbHiddenNodes; j++)
			{
				double activation=hiddenLayerBias[j];
				for(int k=0; k<nbInputs; k++)
				{
					activation+=training_inputs[i][k]*hiddenWeights[k][j];
				}
				hiddenLayer[j]=sigmoid(activation);
			}

			// Compute outputs layer activation
			
			for (int j=0; j<nbOutput;j++)
			{
				double activation=outputLayerBias[j];
				for(int k=0; k<nbHiddenNodes;k++)
				{
					activation+=hiddenLayer[k]*outputsWeights[k][j];
				}
				outputLayer[j]=sigmoid(activation);
			}

			printf("Input: %g %g Output: %g Predicted Ouput: %g \n",training_inputs[i][0],training_inputs[i][1],outputLayer[0],training_outputs[i][0]);

			//if (atoi(argv[0])==training_inputs[i][0] && atoi(argv[1])==training_inputs[i][1])
			//{
			//	finaloutput=outputLayer[0];
			//}

			//Backprop
			//
			//Compute change in output Weights

			double deltaOutput[nbOutput];

			for( int j=0;j<nbOutput; j++)
			{
				double error= (training_outputs[i][j]-outputLayer[j]);
				deltaOutput[j]=error*dSigmoid(outputLayer[j]);
			}

			//Compute change in hidden Weights
			double deltaHidden[nbHiddenNodes];
			for(int j=0;j<nbHiddenNodes; j++)
			{
				double error=0.0f;
				for (int k=0; k<nbOutput;k++)
				{
					error+=deltaOutput[k]*outputsWeights[j][k];
				}
				deltaHidden[j]=error*dSigmoid(hiddenLayer[j]);
			}

			//Apply change in output Weights
			for (int j=0; j<nbOutput; j++)
			{
				outputLayerBias[j]+= deltaOutput[j] * learningrate;
				for (int k=0; k<nbHiddenNodes; k++)
				{
					outputsWeights[k][j]+= hiddenLayer[k] * deltaOutput[j] *learningrate;
				}
			}
			
			//Apply change in hidden weights
			for (int j=0; j<nbHiddenNodes; j++)
			{
				hiddenLayerBias[j]+= deltaHidden[j] *learningrate;
				for (int k=0; k<nbInputs; k++)
				{
					hiddenWeights[k][j]+=training_inputs[i][k] * deltaHidden[j] *learningrate;
				}
			}
		}
	}
}
