#include "matrix.hpp"

using idx_t = long long;
using real_t = long double;

class Partitioner;
class PartitionMetrics;

template <typename EWeightType, typename VWeightType>
class Graph {
	
	/*
	 * This class stores the graph in CRS format.
	*/

	friend class Partitioner;
	friend class PartitionMetrics;

private:

	idx_t n = 0; // count of vertices
	idx_t m = 0; // count of edges

	// sequential storage of adjacent vertices
	idx_t* adjncy = nullptr;

	size_t xadj_capacity = 0;

	// indexes of the beginning of the adjacency list of each
	// vertex (n + 1 element where xadj[n] = m)
	idx_t* xadj = nullptr;

	// vertex weights
	VWeightType* vweights = nullptr;

	// edge weights
	EWeightType* eweights = nullptr;


public:

	Graph(const spMtx<EWeightType>& matrix) {

		n = static_cast<idx_t>(matrix.m);
		m = static_cast<idx_t>(matrix.nz);

		if (m > 0) {
			adjncy = new idx_t[m];
			for (size_t i = 0; i < m; i++) {
				adjncy[i] = static_cast<idx_t>(matrix.Col[i]);
			}
		}

		if (n > 0) {
			xadj_capacity = n + 1;
			xadj = new idx_t[xadj_capacity];
			for (size_t i = 0; i < xadj_capacity; i++) {
				xadj[i] = static_cast<idx_t>(matrix.Rst[i]);
			}
		}

		if (n > 0) {
			vweights = new VWeightType[n];
			for (size_t i = 0; i < n; i++) {
				vweights[i] = 1;
			}
		}

		if (m > 0) {
			eweights = new EWeightType[m];
			if (matrix.Val != nullptr) {
				for (size_t i = 0; i < m; i++) {
					eweights[i] = matrix.Val[i];
				}
			}
			else {
				for (size_t i = 0; i < m; i++) {
					eweights[i] = 1;
				}
			}
		}
	}

	Graph(const Graph& other) {
		n = other.n;
		m = other.m;

		xadj_capacity = other.xadj_capacity;

		if (m > 0) {
			adjncy = new idx_t[m];
			for (size_t i = 0; i < m; ++i) {
				adjncy[i] = other.adjncy[i];
			}
		}

		if (xadj_capacity > 0) {
			xadj = new idx_t[xadj_capacity];
			for (size_t i = 0; i < xadj_capacity; ++i) {
				xadj[i] = other.xadj[i];
			}
		}

		if (n > 0) {
			vweights = new VWeightType[n];
			for (size_t i = 0; i < n; ++i) {
				vweights[i] = other.vweights[i];
			}
		}

		if (m > 0) {
			eweights = new EWeightType[m];
			for (size_t i = 0; i < m; ++i) {
				eweights[i] = other.eweights[i];
			}
		}
	}

	Graph(Graph&& other) noexcept {
		n = other.n;
		m = other.m;

		xadj_capacity = other.xadj_capacity;

		adjncy = other.adjncy;
		xadj = other.xadj;
		vweights = other.vweights;
		eweights = other.eweights;

		other.n = 0;
		other.m = 0;

		other.xadj_capacity = 0;

		other.adjncy = nullptr;
		other.xadj = nullptr;
		other.vweights = nullptr;
		other.eweights = nullptr;
	}

	Graph& operator=(const Graph& other) {
		if (this == &other) {
			return *this;
		}

		delete[] xadj;
		delete[] adjncy;
		delete[] vweights;
		delete[] eweights;

		n = other.n;
		m = other.m;

		xadj_capacity = other.xadj_capacity;

		if (m > 0) {
			adjncy = new idx_t[m];
			for (size_t i = 0; i < m; ++i) {
				adjncy[i] = other.adjncy[i];
			}
		}

		if (xadj_capacity > 0) {
			xadj = new idx_t[xadj_capacity];
			for (size_t i = 0; i < xadj_capacity; ++i) {
				xadj[i] = other.xadj[i];
			}
		}

		if (n > 0) {
			vweights = new VWeightType[n];
			for (size_t i = 0; i < n; ++i) {
				vweights[i] = other.vweights[i];
			}
		}

		if (m > 0) {
			eweights = new EWeightType[m];
			for (size_t i = 0; i < m; ++i) {
				eweights[i] = other.eweights[i];
			}
		}

		return *this;
	}

	Graph& operator=(Graph&& other) noexcept {
		if (this == &other) {
			return *this;
		}

		delete[] xadj;
		delete[] adjncy;
		delete[] vweights;
		delete[] eweights;

		n = other.n;
		m = other.m;

		xadj_capacity = other.xadj_capacity;

		adjncy = other.adjncy;
		xadj = other.xadj;
		vweights = other.vweights;
		eweights = other.eweights;

		other.n = 0;
		other.m = 0;

		other.xadj_capacity = 0;

		other.adjncy = nullptr;
		other.xadj = nullptr;
		other.vweights = nullptr;
		other.eweights = nullptr;

		return *this;
	}

	~Graph() {
		delete[] xadj;
		delete[] adjncy;
		delete[] vweights;
		delete[] eweights;
	}

	idx_t getVerticesCount() const noexcept {
		return n;
	}

	idx_t getEdgesCount() const noexcept {
		return m;
	}

	void print() const {
		for (idx_t u = 0; u < n; ++u) {
			for (idx_t i = xadj[u]; i < xadj[u + 1]; ++i) {
				idx_t v = adjncy[i];
				EWeightType w = eweights[i];
				std::cout << u << " " << v << " " << w << "\n";
			}
		}
	}
};