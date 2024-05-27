
#include "params.h"
#include "model_params.h"
#include "data.h"
#define RAND_GEN 10
template <int N>
void print_vec(vec_t<T, N> &v);


template<int I, int J>
void get_layer(mat_s_t<T, I, J> &w_hw, vec_s_t<T, I> &b_hw, mat_t<T, I, J> &w_sw, vec_t<T,I> &b_sw, const float w_f[I][J], const float b_f[I]){
	for(int i = 0; i<I; i++){
		b_sw[i] = b_f[i];
		for(int j=0; j<J; j++){
			w_sw[i][j] = w_f[i][j];
		}
	}
	b_hw.write(b_sw);
	w_hw.write(w_sw);
}

template <int B, int N>
void get_inputs(vec_s_t<T, N> &in_hw, mat_t<T, B, N> &in_sw, const float in[B][N]){

	for(int b=0; b<B; b++){
		for(int i = 0; i < N; i++){in_sw[b][i] = in[b][i];}
		in_hw.write(in_sw[b]);
	}
}

template <int N>
void print_vec(vec_t<T, N> &v){
	cout << "{";
	for(int i = 0; i < N; i++){cout << v[i]<< " ";}
	cout << "}" << endl;
}
template <int N>
void print_arr(const float arr[N]){
	cout << "{";
	for(int i = 0; i < N; i++){cout << arr[i] << " ";}
	cout << "{" << endl;
}

template<int N>
int out_cmp(const float pred_sw[N], vec_t<T, N> pred_hw){
	int ret = 0;
	T temp;
	for(int i = 0; i<N; i++){
		temp = pred_sw[i];
//		error when positive predicted software values differ from predicted hardware values
		ret += ((pred_sw[i] > 0) && (hls::abs((temp - pred_hw[i])) > 1));
		//ret += (pred_sw[i] > 0) && (pred_sw[i] != pred_hw[i]);
	}
	return ret;
}

int main(int argc, char **argv){

	mat_s_t<T,L1, IN_DIM> w1("w1");
	vec_s_t<T,L1> b1("b1");
	mat_s_t<T,L2, L1> w2("w2");
	vec_s_t<T,L2> b2("b2");
	mat_s_t<T,OUT_DIM, L2> w3("w3");
	vec_s_t<T,OUT_DIM> b3("b3");
	vec_s_t<T,IN_DIM> in("in");
	vec_s_t<T,OUT_DIM> out("out");

	mat_t <T, L1, IN_DIM> w1_sw;
	vec_t<T,L1> b1_sw;
	mat_t <T, L2, L1> w2_sw;
	vec_t<T,L2> b2_sw;
	mat_t <T, OUT_DIM, L2> w3_sw;
	vec_t<T,OUT_DIM> b3_sw;
	mat_t<T, BATCH_SIZE, IN_DIM> in_sw;
	vec_t<T,OUT_DIM> out_sw;

	int err = 0;
	int err_temp;

// Generate random inputs
	//get_inputs<IN_DIM>(in, in_sw);


	//TODO: add batchsize to the data.h file
	//TODO: fix data.h syntax error
	//TODO: format output to proper prediction
	get_inputs<BATCH_SIZE, IN_DIM>(in, in_sw, in_batch);
	get_layer<L1, IN_DIM>(w1, b1, w1_sw, b1_sw, weights_1, bias_1);
	get_layer<L2, L1>(w2, b2, w2_sw, b2_sw, weights_2, bias_2);
	get_layer<OUT_DIM, L2>(w3, b3, w3_sw, b3_sw, weights_3, bias_3);
	for(int i = 0; i<BATCH_SIZE; i++){
		Forward_net(&w1_sw, &b1_sw, &w2_sw, &b2_sw, &w3_sw, &b3_sw, in, out);
	}
	for(int i = 0; i<100; i++){
		out_sw = out.read();
		err_temp = out_cmp<OUT_DIM>(pred_batch[i], out_sw);
		err += err_temp;
		if(err_temp != 0){
			cout << err_temp << endl;
			cout << "Error! Instead of:\t\t\t";
			print_arr<OUT_DIM>(pred_batch[i]);
			cout << "Returned erroneous values:\t";
		}
		print_vec<OUT_DIM>(out_sw);
	}

	return err;
}
