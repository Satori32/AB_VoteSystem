#include <iostream>
#include <vector>
#include <cstdint>
#include <tuple>
#include <random>
#include <algorithm>

typedef std::vector<std::uintmax_t> DType;

std::tuple<std::uintmax_t, std::uintmax_t> DoMajorityVote(std::uintmax_t V,unsigned int S=0) {//TaSuUKeThu
	std::uintmax_t B = 0;
	std::uintmax_t R = 0;

	std::minstd_rand mr(S);


	for (std::uintmax_t i = 0; i < V; i++) {
		if (mr()%2) {
			B++;
		}
		else {
			R++;
		}
	}

	return{ B,R };
}

DType MakeVector(std::uintmax_t BL, std::uintmax_t RL, unsigned int S = 0, bool IsShuffle = true) {

	DType R;

	for (std::uintmax_t i = 0; i < BL; i++) {
		R.push_back(1);
	}
	for (std::uintmax_t i = 0; i < RL; i++) {
		R.push_back(2);
	}

	if (IsShuffle) {
		std::mt19937 mt(S);
		std::shuffle(R.begin(), R.end(), mt);
	}

	return R;
}

std::tuple<std::uintmax_t, std::uintmax_t, std::uintmax_t> Lottery(DType D, unsigned int S = 0) {

	if (D.size() <= 2) {
		return { 0,1,1 };
	}

	DType R;

	std::minstd_rand mr(S);

	for (std::uintmax_t i = 0; i < 3; i++) {
		std::uniform_int_distribution<> ui(0, D.size()-1);
		std::uintmax_t V = ui(mr);
		R.push_back(D[V]);
		D.erase(D.begin() + V);
	}

	return { R[0],R[1],R[2] };
	
}

std::uintmax_t Janken(unsigned int BS = 0, unsigned int RS = 10) {

	std::mt19937 BR(BS);
	std::mt19937 RR(RS);

	std::uniform_int_distribution<> ui(0, 100);

	std::uintmax_t BD = ui(BR);
	std::uintmax_t RD = ui(RR);

	BR.discard(RD);
	RR.discard(BD);

	std::uintmax_t BH = 0;
	std::uintmax_t RH = 0;
	do {

		BH = ui(BR);
		RH = ui(RR);
	} while (BH==RH);

	return  BH > RH ? 1 : 0;
}

std::tuple<std::uintmax_t,std::uintmax_t,std::uintmax_t> DoHoge() {
	std::uintmax_t BV = 0;
	std::uintmax_t RV = 0;

	std::uintmax_t L = 1000000;
	std::uintmax_t Scale = 100;

	std::random_device rd;
	unsigned int BS = 0;
	unsigned int RS = 0;
	unsigned int SS = rd();
	
	do {
		BS = rd();
		RS = rd();
	} while (BS == RS);

	std::tie(BV, RV) = DoMajorityVote(L,SS);

	DType D = MakeVector((BV / (double)L) * Scale + 0.4, (RV / (double)L) * Scale + 0.4,SS);

	std::uintmax_t One=0;
	std::uintmax_t Tow=0;
	std::uintmax_t Three=0;
	std::tie(One, Tow, Three) = Lottery(D,SS);

	std::uintmax_t J = -1;

	if (One != Tow )  {
		J=Janken(BS,RS);
	}
	else if (One != Three) {
		J=Janken(BS,RS);
	}
	else if (Tow != Three) {
		J=Janken(BS,RS);
	}
	else {
		J = One;
	}

	return {J,BV,RV};
}

int main() {

	std::size_t L = 7;

	for (std::size_t i = 0; i < L; i++) {
		std::uintmax_t A, B, R;

		std::tie(A, B, R) = DoHoge();

		std::cout << "Winner Is " << (A == 1 ? "First" : "Second") << "!" << std::endl;
		std::cout << B << " Vs. " << R << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
