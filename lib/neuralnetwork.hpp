#include "neuron.hpp"
#include <vector>
#include <cstdint>

class NeuralNetwork {
	private:
		std::vector<std::vector<Neuron>> neurons;
		std::vector<std::vector<std::vector<double>>> weights;
	public:
		NeuralNetwork(std::vector<uintmax_t> layers);

		std::vector<std::vector<Neuron>> getNeurons();
		void setNeurons(std::vector<std::vector<Neuron>> newNeurons);

		std::vector<std::vector<double>> getNeuronBiases();
		void setNeuronBiases(std::vector<std::vector<double>> newNeuronBiases);

		std::vector<std::vector<std::vector<double>>> getWeights();
		void setWeights(std::vector<std::vector<std::vector<double>>> newWeights);

		std::vector<std::vector<double>> feedForward(std::vector<double> inputs);
		std::vector<double> guess(std::vector<double> inputs);
		void train(std::vector<double> inputs, std::vector<double> outputs, double learningRate);
};
