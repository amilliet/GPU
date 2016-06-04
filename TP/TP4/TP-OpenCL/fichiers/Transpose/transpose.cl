
__kernel void transpose(__global float *in,
	  	     __global float *out)
{
	__local float tile[TILE][TILE];
		
  int x = get_global_id(0);
  int y = get_global_id(1);
  int localx = get_local_id(0);
  int localy = get_local_id(1);
  
  int groupx = get_group_id(0);
  int groupy = get_group_id(1);

  tile[localx][localy] = in[y*get_global_size(0)+x];
  barrier(CLK_LOCAL_MEM_FENCE);
  out[(get_group_id(0)*get_local_size(0) + localy) * get_global_size(0) + get_group_id(1) * get_local_size(1) + localx] = tile[localy][localx];
  
}
