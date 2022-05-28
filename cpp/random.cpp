mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

uniform_int_distribution<int> distribution(0,9);
x=distribution(rng);