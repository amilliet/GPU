__kernel void reduction(__global float *vec, int debut, int fin){
  __local float tmp[TILE];
  int index = get_global_id(0);
  int iloc = get_local_id(0);
  tmp[iloc] = vec[index + debut];

  int limit = TILE/2;

  while(iloc < limit){ //trie les threads dans la premiere partie de tableau 
    barrier(CLK_LOCAL_MEM_FENCE); // attend que les calculs soient tous faits
    tmp[iloc] += tmp[limit + iloc];
    
    limit = limit/2; // mise a jour du curseur 
  }

  if(iloc == 0){
    vec[fin + get_group_id(0)] = tmp[0];
  }

}