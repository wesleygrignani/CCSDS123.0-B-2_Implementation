// Name: Wesley Grignani
// CCSDS 123.0-B-2 compressor standard for lossless and near-lossless multispectral and hyperspectral image compression.


// CCSDS has two main block functions: the predictor block and encoder block.
// The first block to be implemented is the predictor block. This block are going to be created in the perspective to be used
// as reference to the hardware implementation.

#include "predictor.h"
#include "sample_adaptative.h"

/* Predictor block: returns a 16-bit residual mapped for the encode block
   Type of prediction: REDUCED MODE
   Local sum: COLUMN-ORIENTED
   the use of reduced mode in combination with column-oriented local sums tends to yield smaller compressed image data
   volumes for raw (uncalibrated) input images */

// local difference vector for P bands used to calculate the predicted sample value
int local_diff_vector[P] = {0x0};
int weights[P] = {0x0};
int counter[BANDS] = {0x0};
int accumulator[BANDS] = {0x0};
int bits_written = 0;
int previous_sample, init_weights = 0;

int sgn(int val) {
    return (val < 0) ? -1 : 1;
}

void init_weights_function(int init_weights, int z){
	/* weights initialization */
	if(init_weights == 1){
		/* default initialization weights */
		//pow(2, OMEGA) = 1<<OMEGA
	    weights[0] = (int) ((1<<OMEGA) * 7 / 8.0);

	    initweights_loop_1: for (int i = 1; i < P; i++) {
	        // should be ceil(), but Empordá implements floor()
	        weights[i] = floor(weights[i-1] / 8.0);
	    }

	    initweights_loop_2: for(z = 0; z < BANDS; z++){
	    	counter[z] = 1 << INI_COUNT_EXP;
	    	accumulator[z] = (counter[z] * (3 * (1 << (ACCUMULATOR_INIT + 6)) - 49)) >> 7;
	    }

	}
}

int calc_local_sum(int neighboor){
	return 4*neighboor;
}

int calc_central_diff(int sample, int local_sum){
	return (4 * sample) - local_sum;
}

int calc_predic_central(int z){
	int predict_central = 0;
	predict_central_loop: for (int i = 0; i < ((z < P) ? z : P); i++){
		predict_central += local_diff_vector[i] * weights[i];
	}

	return predict_central;
}

int calc_high_res(int predict_central, int local_sum){
	int high_res = ((int) predict_central + (POW2OMEGA*(local_sum - (4 * SMID))) + (POW2OMEGA2*SMID) + (POW2OMEGA1));
	if (high_res > (POW2OMEGA2 * SMAX) + POW2OMEGA1){
		high_res = (POW2OMEGA2 * SMAX) + POW2OMEGA1;
	}

	return high_res;
}

int calc_double_res(int t, int z, int high_res){
	int double_res = 0;
	if(t > 0){
		double_res = high_res / (POW2OMEGA1);
	}else if (t == 0){
		if(z > 0)
			double_res = 2 * previous_sample;
		else
			double_res = 2 * SMID;
	}

	return double_res;
}

int calc_quantized_index(int predicted_residual, int t){
	int quantized_index = 0;
	if(t > 0){
		quantized_index = sgn(predicted_residual) * (((abs(predicted_residual) + mz)) / (2*mz + 1));
	}else if(t == 0){
		quantized_index = predicted_residual;
	}
	return quantized_index;
}

int calc_mapped(int double_res, int quantized_index, int theta){
    int mapped;
	/* mapped quantizer index (OUTPUT FROM PREDICTOR)*/
	/* The signed quantizer index is converted to an unsigned mapped quantizer index */

    int aux1 = 0;
    if(double_res % 2 == 0){
    	aux1 = quantized_index;
    }else{
    	aux1 = -quantized_index;
    }

    //int aux1 = pow(-1, double_res) * quantized_index;

	if (abs(quantized_index) > theta){
		mapped = abs(quantized_index) + theta;
	}else if ((aux1 >= 0) &&  (aux1 <= theta)){
		mapped = 2*abs(quantized_index);
	}else{
		mapped = (2*abs(quantized_index))-1;
	}

	return mapped;
}

void calc_weight_update(int clipped, int double_res, int t){
	/* double resolution prediction error */

	int double_res_pred_error = (2*clipped) - double_res;

	int p = V_MIN + (int)((t-5) / (1<<T_INC));

	if (p > V_MAX) p = V_MAX;
    else if (p < V_MIN) p = V_MIN;

    p = p + D - OMEGA;

    if(double_res_pred_error < 0){
    	double_res_pred_error = -1;
    }else{
    	double_res_pred_error = 1;
    }

    weight_update_loop:for (int j = 0; j < P; j++) {

    	weights[j] = weights[j] + (int)((double_res_pred_error * (1/(1<<p)) * local_diff_vector[j] + 1) / 2);

        if (weights[j] > W_MAX) weights[j] = W_MAX;
        else if (weights[j] < W_MIN) weights[j] = W_MIN;
        //printf("weight:%d\n", weights[j]);
    }
}

int predictor(int sample,
		       int neighboor,
			   int t,
			   int z){

	/* weights initialization */
	if(init_weights == 0){
		init_weights_function(init_weights, z);
		init_weights++;
	}

	/* local sum: implemented using the column-oriented method as seen in the standard */
	int local_sum = calc_local_sum(neighboor);
	//printf("Local sum: %d\n", local_sum);

	/* The local sums are used to calculate local difference values
	 * central local difference: In each spectral band, the central local difference, is equal to
	 * the difference between the local sum σz,y,x and four times the sample representative value*/
	int central_local_diff = calc_central_diff(sample, local_sum);
	//printf("central_diff: %d\n",central_local_diff );

	/* PREDICTION CALCULATION */

	/* predict sample local difference */
	int predict_central = calc_predic_central(z);
	//printf("predicted central: %d\n",predict_central);

	/* high resolution predicted sample value, is calculated as */
	int high_res = calc_high_res(predict_central, local_sum);
	//printf("High res: %d\n", high_res);


	/* double resolution predicted sample is calculated as */
	int double_res = calc_double_res(t, z, high_res);
	//printf("Double res: %d\n", double_res);

	/* predicted sample value is calculated as */
	int predicted_sample = double_res/2;
	//printf("Predicted sample: %d\n", predicted_sample);
	previous_sample = sample;


	/* ------------------------------------- QUANTIZATION STEP --------------------------------- */
	/* The prediction residual, is the difference between the predicted and actual sample values */
	int predicted_residual = sample - predicted_sample;
	//printf("Predicted residual: %d\n", predicted_residual);

	/* The prediction residual shall be quantized using a uniform quantizer, producing as output
	 * the signed integer quantizer index defined as: */

	int quantized_index = calc_quantized_index(predicted_residual, t);
	//printf("Quantized index: %d\n", quantized_index);

	// theta calculation
	int theta = (predicted_sample < SMAX-predicted_sample) ? predicted_sample : SMAX-predicted_sample;
	//printf("theta: %d\n", theta);
    int mapped = calc_mapped(double_res, quantized_index, theta);
    //printf("%d ",mapped);


	/*--------------------------------------- WEIGHTS UPDATE ------------------------------------ */
	/* s' clipped version of the quantizer bin center */
	/* If lossless is used, then s'z(t) = sz(t) */
	int clipped = sample;

	if(t > 0){
		calc_weight_update(clipped, double_res, t);
	}

    // Rotate local differences vector
    rotate_loop: for (int k = P-1; k > 0; k--) {
    	local_diff_vector[k] = local_diff_vector[k-1];
    }
    local_diff_vector[0] = central_local_diff;

    encode_sample(counter, accumulator, t, z, mapped, &bits_written);

    return mapped;
}


