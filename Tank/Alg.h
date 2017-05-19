#pragma once
using namespace std;


namespace alg{

template <typename T>
inline T max(T a, T b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}


template <typename T>
inline T min(T a, T b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

}