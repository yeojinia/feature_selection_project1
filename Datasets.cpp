#include "utils.h"

Dataset::Dataset()
{
}

Dataset::~Dataset()
{
}

Dataset::Dataset(std::vector<std::vector<float>> &X1, std::vector<float> &Y1, int num_examples, int num_features)
{

	for (int i = 0; i < num_examples; i++) {
		this->X.push_back(X1[i]);
	}
	this->Y = Y1;
	this->num_examples = num_examples;
	this->num_features = num_features;

}

/* Being called by Linear Regression */
void Dataset::copy(const Dataset &data) 
{
	
	for (int i = 0; i < data.num_examples; i++) {
		X.push_back(data.X[i]);
	}
	Y = data.Y;
	num_examples = data.num_examples;
	num_features = data.num_features;

}
