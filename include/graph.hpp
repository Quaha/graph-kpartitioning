#include "matrix.hpp"

using int_t = long long;
using real_t = long double;

using VertexType = int_t;

template <typename EWeightType, typename VWeightType>
class Graph {
	
	/*
	 * This class stores the graph in CRS format.
	*/

private:

	size_t n = 0; // count of vertices
	size_t m = 0; // count of edges

	// sequential storage of adjacent vertices
	VertexType* adjncy = nullptr;

	size_t xadj_capacity = 0;

	// indexes of the beginning of the adjacency list of each
	// vertex (n + 1 element where xadj[n] = m)
	VertexType* xadj = nullptr;

	// vertex weights (all weights are equal to 1 at nullptr)
	VWeightType* vweights = nullptr;

	// edge weights (all weights are equal to 1 at nullptr)
	EWeightType* eweights = nullptr;


public:

	Graph(const spMtx<EWeightType>& matrix) {

		n = matrix.m;
		m = matrix.nz;

		if (n > 0) {
			xadj_capacity = n + 1;
			xadj = new VertexType[xadj_capacity];
			for (size_t i = 0; i < xadj_capacity; i++) {
				xadj[i] = static_cast<VertexType>(matrix.Rst[i]);
			}
		}

		if (m > 0) {
			adjncy = new VertexType[m];
			for (size_t i = 0; i < m; i++) {
				adjncy[i] = static_cast<VertexType>(matrix.Col[i]);
			}
		}

		if (matrix.Val && m > 0) {
			eweights = new EWeightType[m];
			for (size_t i = 0; i < m; i++) {
				eweights[i] = matrix.Val[i];
			}
		}
	}

	Graph(const Graph& other) {
		n = other.n;
		m = other.m;

		xadj_capacity = other.xadj_capacity;

		if (m > 0) {
			adjncy = new VertexType[m];
			for (size_t i = 0; i < m; ++i) {
				adjncy[i] = other.adjncy[i];
			}
		}

		if (xadj_capacity > 0) {
			xadj = new VertexType[xadj_capacity];
			for (size_t i = 0; i < xadj_capacity; ++i) {
				xadj[i] = other.xadj[i];
			}
		}

		if (other.vweights != nullptr && n > 0) {
			vweights = new VWeightType[n];
			for (size_t i = 0; i < n; ++i) {
				vweights[i] = other.vweights[i];
			}
		}

		if (other.eweights != nullptr && m > 0) {
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
			adjncy = new VertexType[m];
			for (size_t i = 0; i < m; ++i) {
				adjncy[i] = other.adjncy[i];
			}
		}

		if (xadj_capacity > 0) {
			xadj = new VertexType[xadj_capacity];
			for (size_t i = 0; i < xadj_capacity; ++i) {
				xadj[i] = other.xadj[i];
			}
		}

		if (other.vweights != nullptr && n > 0) {
			vweights = new VWeightType[n];
			for (size_t i = 0; i < n; ++i) {
				vweights[i] = other.vweights[i];
			}
		}

		if (other.eweights != nullptr && m > 0) {
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

	size_t getVerticesCount() const noexcept {
		return n;
	}

	size_t getEdgesCount() const noexcept {
		return m;
	}
};