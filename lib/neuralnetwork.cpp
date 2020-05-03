#include "neuralnetwork.hpp"
#include "utils.hpp"
#include "rng.hpp"

namespace cynapse {
	NeuralNetwork::NeuralNetwork(std::vector<uintmax_t> layers) {
		for (uintmax_t layer = 0; layer < layers.size(); layer++) {
			// Initialize neurons
			std::vector<Neuron> layerNeurons;
			for (uintmax_t neuronIndex = 0; neuronIndex < layers[layer]; neuronIndex++)
				layerNeurons.push_back(Neuron());
			this->neurons.push_back(layerNeurons);

			// Initialize weights
			if (layer < layers.size() - 1) {
				this->weights.push_back(std::vector<std::vector<double>>());
				for (uintmax_t pre = 0; pre < layers[layer]; pre++) {
					this->weights[layer].push_back(std::vector<double>());
					for (uintmax_t post = 0; post  < layers[layer + 1]; post++) {
						this->weights[layer][pre].push_back(rng.genRange(-1.0, 1.0));
					}
				}
			}
		}
	}

	std::vector<std::vector<Neuron>> NeuralNetwork::getNeurons() {
		return this->neurons;
	}

	void NeuralNetwork::setNeurons(std::vector<std::vector<Neuron>> newNeurons) {
		this->neurons = newNeurons;
	}

	std::vector<std::vector<double>> NeuralNetwork::getNeuronBiases() {
		std::vector<std::vector<double>> neuronBiases;

		for (uintmax_t layer = 0; layer < this->neurons.size(); layer++) {
			neuronBiases.push_back(std::vector<double>());

			for (uintmax_t neuron = 0; neuron < this->neurons[layer].size(); neuron++)
				neuronBiases[layer].push_back(this->neurons[layer][neuron].getBias());
		}

		return neuronBiases;
	}

	void NeuralNetwork::setNeuronBiases(std::vector<std::vector<double>> newNeuronBiases) {
		if (this->neurons.size() != newNeuronBiases.size())
			return;

		for (uintmax_t layer = 0; layer < this->neurons.size(); layer++) {
			if (this->neurons[layer].size() != newNeuronBiases[layer].size())
				return;

			for (uintmax_t neuron = 0; neuron < this->neurons[layer].size(); neuron++)
				this->neurons[layer][neuron].setBias(newNeuronBiases[layer][neuron]);
		}
	}

	std::vector<std::vector<std::vector<double>>> NeuralNetwork::getWeights() {
		return this->weights;
	}

	void NeuralNetwork::setWeights(std::vector<std::vector<std::vector<double>>> newWeights) {
		this->weights = newWeights;
	}

	std::vector<std::vector<double>> NeuralNetwork::feedForward(std::vector<double> inputs) {
		std::vector<std::vector<double>> artifacts;
		artifacts.push_back(inputs);

		for (uintmax_t i = 0; i < this->neurons.size() - 1; i++) {
			std::vector<double> layerArtifacts;

			for (uintmax_t j = 0; j < this->neurons[i + 1].size(); j++) {
				std::vector<double> currentWeights;
				for (uintmax_t k = 0; k < this->neurons[i].size(); k++)
					currentWeights.push_back(this->weights[i][k][j]);

				layerArtifacts.push_back(this->neurons[i + 1][j].run(artifacts[i], currentWeights));
			}

			artifacts.push_back(layerArtifacts);
		}

		return artifacts;
	}

	std::vector<double> NeuralNetwork::guess(std::vector<double> inputs) {
		std::vector<std::vector<double>> artifacts = this->feedForward(inputs);
		return artifacts[artifacts.size() - 1];
	}

	void NeuralNetwork::train(std::vector<double> inputs, std::vector<double> outputs, double learningRate) {
		std::vector<std::vector<double>> artifacts = this->feedForward(inputs);

		// Errors are in reverse order
		std::vector<std::vector<double>> errors;
		errors.push_back(std::vector<double>());
		for (uintmax_t i = 0; i < outputs.size(); i++)
			errors[0].push_back(outputs[i] - artifacts[artifacts.size() - 1][i]);

		for (uintmax_t currentLayer = this->neurons.size() - 1; currentLayer >= 1; currentLayer--) {
			std::vector<double> gradients = artifacts[currentLayer];
			std::vector<std::vector<double>> weightDeltas;

			for (uintmax_t currentNeuron = 0; currentNeuron < this->neurons[currentLayer].size(); currentNeuron++) {
				gradients[currentNeuron] = dsigmoid(gradients[currentNeuron]) * errors[errors.size() - 1][currentNeuron]  * learningRate;
				this->neurons[currentLayer][currentNeuron].setBias(this->neurons[currentLayer][currentNeuron].getBias() + gradients[currentNeuron]);
			}

			errors.push_back(std::vector<double>(this->neurons[currentLayer - 1].size(), 0.0));
			for (uintmax_t previousNeuron = 0; previousNeuron < this->neurons[currentLayer - 1].size(); previousNeuron++) {
				weightDeltas.push_back(std::vector<double>());
				for (uintmax_t currentNeuron = 0; currentNeuron < this->neurons[currentLayer].size(); currentNeuron++)
					weightDeltas[previousNeuron].push_back(gradients[currentNeuron] * artifacts[currentLayer - 1][previousNeuron]);

				for (uintmax_t previousWeight = 0; previousWeight < this->weights[currentLayer - 1][previousNeuron].size(); previousWeight++) {
					this->weights[currentLayer - 1][previousNeuron][previousWeight] += weightDeltas[previousNeuron][previousWeight];
					const double newError = errors[errors.size() - 2][previousWeight] * this->weights[currentLayer - 1][previousNeuron][previousWeight];
					const uintmax_t currentErrorLayer = errors.size() - 1;
					errors[currentErrorLayer][previousNeuron] += newError;
				}
			}
		}
	}
}
