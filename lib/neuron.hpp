#include <vector>

class Neuron {
	private:
		double bias;

	public:
		Neuron();

		double getBias();
		void setBias(double newBias);

		double run(std::vector<double> inputs, std::vector<double> weights);
};
