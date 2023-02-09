//
// Created by Wesley Grignani
//

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

// Bands of predictions shall be an integer in the range 0 <= P <= 15
#define P 3

// Dynamic size of sample
#define D 16

// OMEGA constant
#define OMEGA 8

#define POW2OMEGA (1<<OMEGA) //pow(2, OMEGA)
#define POW2OMEGA1 (1<<OMEGA+1)//pow(2, OMEGA+1)
#define POW2OMEGA2 (1<<OMEGA+2)//pow(2, OMEGA+2)

// Size of sample
#define SAMPLE_SIZE 16

// Quantizer fidelity control - Utilized for near-lossless compression (error control)
#define mz 0

#define V_MIN 5
#define V_MAX 9
#define T_INC 6

// Number of bands, rows and columns of the image and its used for prediction
#define NBANDS 5
#define BANDS 5
#define NROWS 5
#define NCOLS 5

// Maximum and medium value of a sample size used
#define SMAX (1<<SAMPLE_SIZE)-1 //pow(2, SAMPLE_SIZE) - 1
#define SMID (1<<SAMPLE_SIZE-1) //pow(2, SAMPLE_SIZE -1)

//
#define W_MAX pow(2, OMEGA + 2) - 1
#define W_MIN -pow(2, OMEGA + 2)


int sgn(int val);

// function to init weights memory
void init_weights_function(int init_weights, int z);
int calc_local_sum(int neighboor);
int calc_central_diff(int sample, int local_sum);
int calc_predic_central(int z);
int calc_high_res(int predict_central, int local_sum);
int calc_double_res(int t, int z, int high_res);
int calc_quantized_index(int predicted_residual, int t);
int calc_mapped(int double_res, int quantized_index, int theta);
void calc_weight_update(int clipped, int double_res, int t);

// Function to predict sample
int predictor(int sample, int neighboor, int t, int z);


#endif //PREDICTOR_H

