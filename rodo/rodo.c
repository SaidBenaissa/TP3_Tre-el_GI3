/*S.Benaissa (said.benaissa@ensem.ac.ma)

 * compile with command (don't forget to source the env.sh of your development folder!):
 arm-angstrom-linux-gnueabi-gcc kh4test.c -o khepera4_test -I $INCPATH -L $LIBPATH -lkhepera 
*/
#include <khepera/khepera.h>
#include <signal.h>

//#define DEBUG 1
static knet_dev_t * dsPic; // robot pic microcontroller access
int maxsp,accinc,accdiv,minspacc, minspdec; // for speed profile
static int quitReq = 0; // quit variable for loop

int main(int argc, int *argv[])
{
  int i, lpos,rpos;
  long motspeed=200;

  printf("\n Read odom \n");
  // initiate libkhepera and robot access
  if ( kh4_init(0,NULL)!=0)
  {
  	printf("\n Err d'initialisation de libkhepera!\n\n");
  	return -1;
  }
/* open robot socket and store the handle in its pointer */
  dsPic  = knet_open( "Khepera4:dsPic" , KNET_BUS_I2C , 0 , NULL );

	if ( dsPic==NULL)
  {
  	printf("\nErr: problème de communication avec Kh4 dsPic\n\n");
  	return -2;
  }	
  
 while(100)
  {
        kh4_SetMode( kh4RegSpeedProfile,dsPic );
        kh4_set_speed(motspeed,motspeed ,dsPic); 
        kh4_get_position(&lpos,&rpos,dsPic);
	printf("\n odom: left %ld | right %ld\n",lpos,rpos);
  }
  kh4_SetMode( kh4RegSpeedProfile,dsPic );
  kh4_set_speed(0,0,dsPic);

}
