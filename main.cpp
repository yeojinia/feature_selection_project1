#include "utils.h"

int main()
{

	const char* filename = "lpga2009.txt";
	Dataset data = read_data(filename);

	int max_iteration = 10000;
	float learning_rate = 0.001;

	LinearRegressionModel* linear_reg = LinearRegressionModel::getInstance(data);
	std::cout << "Training Started." << std::endl ;
	linear_reg->train(max_iteration, learning_rate);
	linear_reg->print_best_model();
	linear_reg->select_features();

	Sleep(50000);

	return 0;
}