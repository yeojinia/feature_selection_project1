#include "utils.h"
LinearRegressionModel* LinearRegressionModel::instance = 0;

LinearRegressionModel* LinearRegressionModel::getInstance(const Dataset &data_train)
{
	if (instance == 0)
		instance = new LinearRegressionModel(data_train);
	return instance;
}

LinearRegressionModel::LinearRegressionModel(const Dataset &data_train)
{
	// Copy to the data of linear regression
	data.copy(data_train); 
	// Initialize random weights
	init_weights(data_train.num_features); 
	bestMSE = 100000.;
}

LinearRegressionModel::~LinearRegressionModel()
{
}

void LinearRegressionModel::print_best_model()
{
	std::cout << "The Best linear model: ";
	print_linear_model(best_weights);
	std::cout << "The MSE : " << bestMSE << std::endl;
}

void LinearRegressionModel::select_features()
{
	std::cout << "Selected Features by L1 Regularization: ";
	for (int i = 1; i < best_weights.size(); i++) {
		if (best_weights[i] < 1.0) {
			continue;
		}
		else {
			std::cout << "x" << (i-1);
		}
		if (i != (best_weights.size() - 1))
			std::cout << ", ";
	}
	std::cout << std::endl;
}

void LinearRegressionModel::print_linear_model(std::vector<float> &weights)
{
	char* linear_function = new char[1000];
	strcpy(linear_function, "y = ");
	for (int i = 0; i < number_weights; i++) {
		char *temp = new char[number_weights +1];
		if(i == 0 )
			sprintf(temp, "%.4f ", weights[i]);
		else
			sprintf(temp, "%.4f*x%d ", weights[i], i-1);
		strcat(linear_function, temp);
		if (i == number_weights - 1) {
			strcat(linear_function, "\n");
		}
		else {
			strcat(linear_function, "+");
		}
		delete[] temp;
	}
	std::cout << linear_function;
	delete[] linear_function;
}

void LinearRegressionModel::train(int max_iteration, float learning_rate)
{
	std::vector<float> Y_pred;
	
	Y_pred.assign(data.num_examples, 0);
	float lambda = 0.;
	for(int i =0; i< max_iteration; i++){
		fit(Y_pred);
		//lambda += 0.001;
		lambda = 0.1;
		float mse = l1_reg_update_weights(data, Y_pred, learning_rate, lambda);
		if (i % 1000 == 0) {
			std::cout << "Iteration: " << i << ", MSE = " << mse << std::endl;
			print_linear_model(value);
		}
	}
}


void LinearRegressionModel::fit(std::vector<float> & Y_pred)
{
	for (int i = 0; i < data.num_examples; i++) {
		float prediction = 0;
		for (int j = 0; j < number_weights; j++) {
			prediction = prediction + value[j] * (data.X[i][j]); 
		}
		Y_pred[i] = prediction;
	}
}


float LinearRegressionModel::mean_squared_error(std::vector<float> &Y_pred, std::vector<float> &y, int num_examples) {

	float total = 0;
	for (int i = 0; i < num_examples; i++) {
		total += ((y[i] - Y_pred[i])*(y[i] - Y_pred[i]));
	}
	return (total /(float)num_examples);
}

float LinearRegressionModel::l1_reg_update_weights(Dataset data, std::vector<float> & y_pred, float learning_rate, float hyper_param)
{
	// gradient descent with L1 regularization
	float multiplier = learning_rate / data.num_examples; 
	for (int i = 0; i < number_weights; i++) {
		float total = 0.;
		float residual;
		for (int j = 0; j < data.num_examples; j++) {
			residual = (y_pred[j] - data.Y[j]);
			total += (residual * data.X[j][i]);
		}
		if(value[i] > 0 )
			value[i] = value[i] - (multiplier * total) - (learning_rate * hyper_param);
		else
			value[i] = value[i] - (multiplier * total) + (learning_rate * hyper_param);
	}

	float mse = mean_squared_error(y_pred, data.Y, data.num_examples);

	if (mse < bestMSE) {
		bestMSE = mse;
		if (best_weights.size() != 0) {
			best_weights.clear();
		}
		for(int i=0; i<number_weights; i++){
			best_weights.push_back(value[i]);
		}
	}

	return mse;
}

void LinearRegressionModel::init_weights(int num_features)
{
	number_weights = num_features;
	// random initalization for weights
	for (int i = 0; i < number_weights; i++) {
		value.push_back((float)(rand() % 100));
	}
}

