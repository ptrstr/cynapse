namespace cynapse {
	class RNG {
		private:
			unsigned seed;

		public:
			RNG(unsigned seed = 0);
			unsigned getSeed();
			void setSeed(unsigned newSeed);
			double genRange(double min, double max);
	};

#ifndef RNG_H
#define RNG_H
	extern RNG rng;
#endif
}
