#include "utils.hpp"
#include <cmath>

namespace cynapse {
	double sigmoid(double value) {
		return 1.0 / (1.0 + exp(-1.0 * value));
	}

	double dsigmoid(double value) {
		return sigmoid(value) * (1.0 - sigmoid(value));
	}
}
