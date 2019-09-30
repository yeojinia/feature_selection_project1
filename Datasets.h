#pragma once

class Dataset {
public:
	std::vector<std::vector <float>> X;
	std::vector<float> Y;
	
	int num_features;
	int num_examples;

	Dataset();
	Dataset(std::vector<std::vector<float>> &X1, std::vector<float> &Y, int num_examples, int num_features);
	~Dataset();

	void copy(const Dataset &data);

};