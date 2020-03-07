#pragma once

#include <cublas_v2.h>

#include "util/Option.h"

#ifndef NDEBUG
#define protected public
#endif

namespace SNNDPC::GPU {
template<typename T>
class Core {

public:
	Core(int k, int n, int d, int nc, const Option& option);
	virtual ~Core();

protected:
	void ComputeDistance();
	void ComputeNeighbor();
	void ComputeSharedNeighbor();
	void ComputeSimilarity();
	void ComputeRho();
	void ComputeDelta();
	void ComputeGamma();
	void ComputeCentroid();
	void AssignNonCentroidStep1();
	void AssignNonCentroidStep2();

protected:
	const int Unassigned = -1;
	const cudaDataType type;

	const int k, n, d, nc;
	const Option option;

	cublasHandle_t handle;
	T* data; // Shape [n,d]
	T* distance; // Shape [n,n]
	int* indexDistanceAsc; // Shape [n,n]
	int* indexNeighbor; // Shape [n,k]
	int* indexSharedNeighbor; // Shape [n,n,k]
	int* numSharedNeighbor; // Shape [n,n]
	T* similarity; // Shape [n,n]
	T* rho; // Shape [n]
	T* delta; // Shape [n]
	T* gamma; // Shape [n]
	int* indexAssignment; // Shape [n]
	int* indexCentroid; // Shape [nc]
};

template
class Core<float>;

template
class Core<double>;
}
#ifndef NDEBUG
#undef protected
#endif
