#include "neuron.hpp"
#include "utils.hpp"
#include "rng.hpp"
#include <cstdint>

namespace cynapse {
	Neuron::Neuron() {
		this->bias = rng.genRange(-1.0, 1.0);
	}

	double Neuron::getBias() {
		return this->bias;
	}

	void Neuron::setBias(double newBias) {
		this->bias = newBias;
	}

	double Neuron::run(std::vector<double> inputs, std::vector<double> weights) {
		if (inputs.size() != weights.size())
			return 0.0;

		double sum = this->bias;
		for (uintmax_t i = 0; i < inputs.size(); i++)
			sum += inputs[i] * weights[i];

		return ACTIVATION(sum);
	}
}
