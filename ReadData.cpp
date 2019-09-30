#include "utils.h"

Dataset read_data(const char* filename)
{

	int index = 0;
	int num_examples = 0;
	int num_features = 0;

	std::ifstream datafile(filename);
	/* check the number of examples */
	std::string line;
	while (std::getline(datafile, line)) {
		num_examples++;
		if (num_examples == 1){
			int cnt = 0;
			while (line[cnt] != NULL) {
				if (line[cnt] == ',') {
					num_features++;
				}
				cnt++;
			}
		}
	}
	datafile.close();

	/* Assign memory for the dataset with independent variables and dependent variable */
	std::vector<std::vector <float>> X;
	for(int i =0; i< num_examples; i++){
		std::vector <float> example;
		example.assign(num_features, 0.);
		X.push_back(example);
	}
	std::vector<float> Y;
	Y.assign(num_examples, 0.);

	/* Re-load the data file, and save the data */
	std::ifstream reloadfile(filename);
	int total_cnt = 0;
	int example_cnt = 0;

	while (std::getline(reloadfile, line, ',')) {
		std::stringstream line_stream(line);
		float number;
			
		line_stream >> number;
		if( (total_cnt) == ((num_features) *example_cnt  + (num_features - 1) ) ) {
			Y[example_cnt] = number;
			example_cnt++;
		}
		else{
			X[example_cnt][total_cnt % (num_features)] = number;
		}
		total_cnt++;
	}
	reloadfile.close();

	/* Normalize the features  Z = (X-mean)/delta  */
	std::vector<float> mean;
	for (int i = 0; i < num_features; i++) {
		float sum = 0.;
		for (int j = 0; j < num_examples; j++)
			sum += X[j][i];
		mean.push_back(sum / (float)num_examples);
	}

	std::vector<float> deviation;
	for (int i = 0; i < num_features; i++) {
		float diff_sum = 0.;
		for (int j = 0; j < num_examples; j++) {
			diff_sum += ((X[j][i] - mean[i])*(X[j][i] - mean[i]));
		}
		deviation.push_back(diff_sum / (float)num_examples);
	}

	for (int i = 0; i < num_features; i++) {
		for (int j = 0; j < num_examples; j++){
			if(deviation[i] > 0.00001)
				// normalization
				X[j][i] = ((X[j][i] - mean[i]) / deviation[i]); 
		}
	}

	/* generate a Dataset instance */
	Dataset data = Dataset(X, Y, num_examples, num_features);
	return data;
}

