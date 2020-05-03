namespace cynapse {
#define ACTIVATION(X) sigmoid(X)
#define DACTIVATION(X) dsigmoid(X)

	double sigmoid(double value);
	double dsigmoid(double value);
}
