
__kernel void addmat(__global float *A,
		     __global float *B,
		     __global float *C)
{
	int row = get_global_id(1);
	int col = get_global_id(0);
	C[get_global_size(0) * row + col] = A[get_global_size(0) * row + col] + B[get_global_size(0) * row + col];
	
}
