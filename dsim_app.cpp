#include <stdio.h>
#include <dsim.hpp>
#include <gridpack/include/gridpack.hpp>

int gridpack_initialize(int* argcp, char ***argvp)
{
  int  ierr;
  // Initialize MPI library
  ierr = MPI_Init(argcp,argvp);

  // Initialize GA
  GA_Initialize();
  int stack = 200000, heap = 200000;
  MA_init(C_DBL, stack, heap);

  // Initialize math libraries
  gridpack::math::Initialize();

  return ierr;
}

int gridpack_finalize()
{
  int ierr;
  // Finalize Math libraries
  gridpack::math::Finalize();

  // Terminate GA
  GA_Terminate();

  // Clean up MPI libraries
  ierr = MPI_Finalize();

  return ierr;
}

  
int main(int argc, char **argv)
{
  int ierr;

  ierr = gridpack_initialize(&argc,&argv);

  DSim *dsim = new DSim();
  printf("Hello World from rank %d\n", dsim->rank());

  dsim->setconfigurationfile("input.xml");

  dsim->readnetworkdatafromconfig();

  dsim->setup();

  dsim->solve();

  delete(dsim);
  ierr = gridpack_finalize();

  return 0;
}
