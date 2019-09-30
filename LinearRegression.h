#pragma once

class LinearRegressionModel {
	Dataset data;

public:
	LinearRegressionModel(const Dataset &data_train);
	~LinearRegressionModel();
	static LinearRegressionModel* getInstance(const Dataset &data_train);

	void print_linear_model(std::vector<float> &weights);
	void print_best_model();
	void train(int max_iteration, float learning_rate);
	float mean_squared_error(std::vector<float> &y_pred1, std::vector<float> &y_true, int num_examples);
	float l1_reg_update_weights(Dataset data, std::vector<float> & y_pred1, float learning_rate, float hyper_param);
	void init_weights(int num_features);
	void select_features();

private:
	void fit(std::vector<float> & y_pred1);
	static LinearRegressionModel* instance; 
	float *values;
	std::vector<float> value;
	int number_weights;
	float bestMSE;
	std::vector<float> best_weights;
};

