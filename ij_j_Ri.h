#include "params.h"
template<int OUT, int IN>
void ij_j_Ri(mat_t<T, OUT, IN> *w, vec_t<T, OUT> *b,
			 vec_s_t<T, IN> &in, vec_s_t<T, OUT> &out){

	// w : matrix of weights
	// b : matrix of biases
	// in : input vector
	// out : output vector

	vec_t<T,IN> in_temp = in.read();
	vec_t<T,OUT> out_temp;



	Row: for(int i = 0; i<OUT; i++){
		vec_t<T,IN> product;

		vec_prod<OUT, IN>(&((*w)[i]), in_temp, product);
		rsum<IN>((*b)[i], product, out_temp[i]);
	}
	out << out_temp;
}
template<int OUT, int IN>
void ij_j_i(mat_t<T, OUT, IN> *w, vec_s_t<T, IN> &in, vec_s_t<T, OUT> &out){

	vec_t<T, IN> in_temp = in.read;

	vec_t<T,OUT> out_temp;

	Row: for(int i = 0; i<OUT; i++){
			vec_t<T,IN> product;

			vec_prod<OUT, IN>(&((*w)[i]), in_temp, product);
			rsum<IN>((*b)[i], product, out_temp[i]);
		}
		out << out_temp;

}

template<int OUT, int IN>
void vec_prod(vec_t<T, IN> *w, vec_t<T, IN> &in, vec_t<T, IN> &out){
	Prod: for(int j = 0; j<IN; j++){
				out[j] = (*w)[j] * in[j];
			}
}
template<int N>
void rsum(T b, vec_t<T,N> &in, T &out){
	T out_temp = 0.0;
	const T zero = 0.0;
	Sum: for(int j =0; j<N; j++){
				out_temp+=in[j];
			}
	out_temp += b;

	out = out_temp > zero ? out_temp : zero;

}


template<int OUT, int IN>
void ij_j_i(mat_t<T, OUT, IN> *w, vec_s_t<T, IN> &in, vec_s_t<T, OUT> &out){

	vec_t<T, IN> in_temp = in.read;

	vec_t<T,OUT> out_temp;

	Row: for(int i = 0; i<OUT; i++){
			vec_t<T,IN> product;

			vec_prod<OUT, IN>(&((*w)[i]), in_temp, product);
			rsum<IN>((*b)[i], product, out_temp[i]);
		}
		out << out_temp;

}
