#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <unordered_map>
#include <immintrin.h>

int main(int argc, char* argv[])
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<int> leftInput;
	std::vector<int> rightInput;
	int left, right;
	while (std::cin >> left >> right)
	{
		leftInput.push_back(left);
		rightInput.push_back(right);
	}

	sort(leftInput.begin(), leftInput.end());
	sort(rightInput.begin(), rightInput.end());
	assert(leftInput.size() == rightInput.size());

    std::unordered_map<int, int> rightCount;
    for (const int& num : rightInput)
		++rightCount[num];

	int sum{0};
	int similarity{0};

	__m256i sumVec = _mm256_setzero_si256();
	for (int i = 0; i < leftInput.size(); i += 8)
	{
		__m256i leftVec = _mm256_loadu_si256((__m256i*)&leftInput[i]);
		__m256i rightVec = _mm256_loadu_si256((__m256i*)&rightInput[i]);
		__m256i diffVec = _mm256_abs_epi32(_mm256_sub_epi32(leftVec, rightVec));
		sumVec = _mm256_add_epi64(sumVec, diffVec);
	}

	int sumArray[8];
	_mm256_storeu_si256((__m256i*)sumArray, sumVec);
	for (int i = 0; i < 8; ++i)
		sum += sumArray[i];

	for (int j = 0; j < leftInput.size(); ++j)
		similarity += leftInput[j] * rightCount[leftInput[j]];

    auto end = std::chrono::high_resolution_clock::now();
	auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Execution Time (Milliseconds):\t" << durationMs.count() << '\n';
    std::cout << "Execution Time (Nanoseconds):\t" << durationNs.count() << "\n\n";
	std::cout << "Result:\t\t\t\t" << sum << '\n';
	std::cout << "Similarity Score:\t\t" << similarity << '\n';

	return 0;
}
