# include < omp .h >
# include < stdio .h >
# include < stdlib .h >
# include < math .h >
# include < mpi .h >
# define PI 3 . 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4 6 2 6 4 3 3 8 3 2 7 9 5 0 2 9 L
# define MTAG1 1
# define MTAG2 2
double f ( double a ) {
return ( double )4.0/(( double )1.0+( a * a ));
}

int main ( int argc , char * argv [])
{
int n , myid , numprocs , i ;
double mypi , pi , h , sum , x ;
MPI_Init (& argc ,& argv );
MPI_Comm_size ( MPI_COMM_WORLD ,& numprocs );
MPI_Comm_rank ( MPI_COMM_WORLD ,& myid );
n = 0;
for (;;) {
printf ( " Enter the number of intervals : (0 quits ) " ); scanf ( " % u " ,& n );
if ( n ==0) break ;
fx = ( double *) malloc ( n * sizeof ( double ));
h = (( double )1.0)/( double ) n ;
sum = 0.0;
#
pragma omp parallel private (i , x ) shared (h , fx , n )
{
#
pragma omp for
for ( i =1; i <= n ; i ++) {
x = h *(( double )i -( double )0.5);
fx [i -1] = f ( x );
}
}
for ( i =0; i < n ; i ++) {
sum += fx [ i ];
}
pi = h * sum ;
printf ( " pi is approx .: %.16 f Error is : %.16 f \ n " ,pi , fabs ( pi - PI ));
}
return EXIT_SUCCESS ;
}
