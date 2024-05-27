#include "params.h"
#include "ij_j_Ri.h"
#include "model_params.h"
void Forward_net(mat_t<T, L1, IN_DIM> *w1, vec_t<T, L1> *b1,
		mat_t<T, L2, L1> *w2,  vec_t<T, L2> *b2,
		mat_t<T, OUT_DIM, L2> *w3,  vec_t<T, OUT_DIM> *b3,
		vec_s_t<T, IN_DIM> &in,  vec_s_t<T, OUT_DIM> &out){

	#pragma HLS INTERFACE mode=m_axi port = w1 depth=50
	#pragma HLS INTERFACE mode=m_axi port = w2 depth = 50
	#pragma HLS INTERFACE mode=m_axi port = w3 depth = 50
	#pragma HLS INTERFACE mode=m_axi port = b1 depth = 50
	#pragma HLS INTERFACE mode=m_axi port = b2 depth = 50
	#pragma HLS INTERFACE mode=m_axi port = b3 depth = 50


#pragma HLS dataflow


	vec_s_t<T, L1> s1("s1");
	vec_s_t<T,L2> s2("s2");

	ij_j_Ri<L1, IN_DIM>(w1, b1, in, s1);
	ij_j_Ri<L2, L1> (w2, b2, s1, s2);
	ij_j_Ri<OUT_DIM, L2>(w3, b3, s2, out);

}
