/**
 *  \file mandelbrot_susie.cc
 *  \brief HW 2: Mandelbrot set Susie code
 */


#include <iostream>
#include <cstdlib>
#include <mpi.h>

#include "render.hh"

using namespace std;

#define WIDTH 1000
#define HEIGHT 1000

int
mandelbrot(double x, double y) {
  int maxit = 511;
  double cx = x;
  double cy = y;
  double newx, newy;

  int it = 0;
  for (it = 0; it < maxit && (x*x + y*y) < 4; ++it) {
    newx = x*x - y*y + cx;
    newy = 2*x*y + cy;
    x = newx;
    y = newy;
  }
  return it;
}

int
main(int argc, char* argv[]) {
  //Initilize MPI environment
  int world_rank, world_size;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size); // # of processes 

  double minX = -2.1;
  double maxX = 0.7;
  double minY = -1.25;
  double maxY = 1.25;
  
  int height, width;
  if (argc == 3) {
    height = atoi (argv[1]);
    width = atoi (argv[2]);
    assert (height > 0 && width > 0);
  } else {
    fprintf (stderr, "usage: %s <height> <width>\n", argv[0]);
    fprintf (stderr, "where <height> and <width> are the dimensions of the image.\n");
    return -1;
  }

  int chunk_size = height / world_size;
  double send[chunk_size];

  double it = (maxY - minY)/height;
  double jt = (maxX - minX)/width;
  double x, y;


  gil::rgb8_image_t img(height, width);
  auto img_view = gil::view(img);

  if (world_rank == 0) 
  {
    // Master code
    MPI_Gather( send, width*height, MPI_INT, NULL, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
  } else {
    // Slave code
      y = minY;
      for (int i = 0; i < height; ++i) {
        x = minX;
        for (int j = 0; j < width; ++j) {
          img_view(j, world_rank*i) = render(mandelbrot(x, y)/512.0);
          x += jt;
        }
        y += it;
      }

  } 



  gil::png_write_view("mandelbrot_susie.png", const_view(img));
}

/* eof */
