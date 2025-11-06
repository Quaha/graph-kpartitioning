#pragma once

#include <iostream>
#include <algorithm>

#include "utils.hpp"
#include "config.hpp"

struct ProgramStatistics {
	
	inline static Vector<real_t> average;
	inline static Vector<real_t> maximum;
	inline static Vector<real_t> median;

	inline static Vector<real_t> max_maximum;
	inline static Vector<real_t> max_median;

	inline static Vector<real_t> denominator;

	static void InitMatchingStatistics() {

		ProgramConfig::collect_mathing_statistics = true;

		average.resize(ProgramConfig::coarsening_itarations_limit + 1_i, 0.0_r);
		maximum.resize(ProgramConfig::coarsening_itarations_limit + 1_i, 0.0_r);
		median.resize(ProgramConfig::coarsening_itarations_limit + 1_i, 0.0_r);

		max_maximum.resize(ProgramConfig::coarsening_itarations_limit + 1_i, 0.0_r);
		max_median.resize(ProgramConfig::coarsening_itarations_limit + 1_i, 0.0_r);

		denominator.resize(ProgramConfig::coarsening_itarations_limit + 1_i, 0.0_r);
	}

	template <typename vw_t>
	static void UpdateMatchingStatistics(Vector<vw_t> weights, int_t level) {

		const int_t n = weights.size();
		const real_t total_w = static_cast<real_t>(std::accumulate(weights.begin(), weights.end(), c<vw_t>(0)));

		std::sort(weights.begin(), weights.end());

		median[level] += static_cast<real_t>(weights[n / 2_i]) / total_w;
		maximum[level] += static_cast<real_t>(weights[n - 1_i] / total_w);
		average[level] += static_cast<real_t>(std::accumulate(weights.begin(), weights.end(), c<vw_t>(0))) / static_cast<real_t>(n) / total_w;

		max_maximum[level] = std::max(max_maximum[level], static_cast<real_t>(weights[n - 1_i] / total_w));
		max_median[level] = std::max(max_median[level], static_cast<real_t>(weights[n / 2_i]) / total_w);

		denominator[level] += 1.0_r;
	}

	static void PrintMatchingStatistics() {
		if (!ProgramConfig::collect_mathing_statistics) {
			return;
		}

		std::cout << "\n" << "# Level | Average | Average Max | Max of Max | Average Median | Max of Median\n";

		for (int_t i = 1_i; i < average.size(); ++i) {
			average[i] *= 100.0_r;
			maximum[i] *= 100.0_r;
			median[i] *= 100.0_r;

			max_maximum[i] *= 100.0_r;
			max_median[i] *= 100.0_r;

			average[i] /= denominator[i];
			maximum[i] /= denominator[i];
			median[i] /= denominator[i];

			std::cout << i << " " << average[i] << " " << maximum[i] << " " << max_maximum[i] << " "  << median[i] << " " << max_median[i] << "\n";
		}
	}

};