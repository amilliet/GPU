__kernel void addmat(__global int y,
		     __global int x,
		     __global float *ocean,
		     __global int nb_lines,
		     __global int **tmp)
{
    if(deep < DEPTH){
        if (y > num_thread*nb_lines-DEPTH && y>=DEBUT && x > DEBUT && y+1 < FIN &&  y+1 < (num_thread+1)*nb_lines+DEPTH && x+1 < FIN){
            test_tas(y, x-1, deep, ocean,num_thread,nb_lines,tmp);
            //test_tas(y, x+1, deep, ocean);
            test_tas(y-1, x, deep, ocean,num_thread,nb_lines,tmp);
            //test_tas(y+1, x, deep, ocean);
        }
    }
}