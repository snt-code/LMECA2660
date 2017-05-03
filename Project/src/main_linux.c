/*
 *  CFD - Linux Version of the Main
 *  by Son Tran
 */

#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include "cfd.h"


void print_problem_data(struct _problem* Problem){
  char buff_omega_name[50];
  char buff_psi_name[50];
  char buff_u_name[50];
  char buff_v_name[50];
  sprintf(buff_omega_name ,"data/CFD_omega_%d.txt",(int) ( (*Problem).t * 100 ));
  sprintf(buff_psi_name   ,"data/CFD_psi_%d.txt"  ,(int) ( (*Problem).t * 100 ));
  sprintf(buff_u_name     ,"data/CFD_u_%d.txt"    ,(int) ( (*Problem).t * 100 ));
  sprintf(buff_v_name     ,"data/CFD_v_%d.txt"    ,(int) ( (*Problem).t * 100 ));
  FILE* file_omega = fopen(buff_omega_name,"w");
  FILE* file_psi   = fopen(buff_psi_name  ,"w");
  FILE* file_u     = fopen(buff_u_name    ,"w");
  FILE* file_v     = fopen(buff_v_name    ,"w");

  if(file_omega == NULL || file_psi == NULL || file_u == NULL || file_v == NULL){ fprintf(stderr,"File error\n"); exit(1);}
    for(int j = 0 ; j < (*Problem).Ny ; j++){
      for(int i = 0; i < (*Problem).Nx ; i++){
        fprintf(file_omega,"%f "   ,(*Problem).omega[i][j]);
        fprintf(file_psi  ,"%f "   ,(*Problem).psi  [i][j]);
        fprintf(file_u    ,"%f "   ,(*Problem).u    [i][j]);
        fprintf(file_v    ,"%f "   ,(*Problem).v    [i][j]);
    }
    fprintf(file_omega ,"\n");
    fprintf(file_psi   ,"\n");
    fprintf(file_u     ,"\n");
    fprintf(file_v     ,"\n");
  }
  /* Pour printer à la verticale - Quel utilité ? Bonne question
  for(int i = 0; i < (*Problem).Nx ; i++){
    for(int j = 0 ; j < (*Problem).Ny ; j++){
        fprintf(file_omega,"%f "   ,(*Problem).omega[i][j]);
        fprintf(file_psi  ,"%f "   ,(*Problem).psi  [i][j]);
        fprintf(file_u    ,"%f "   ,(*Problem).u    [i][j]);
        fprintf(file_v    ,"%f "   ,(*Problem).v    [i][j]);
    }
    fprintf(file_omega ,"\n");
    fprintf(file_psi   ,"\n");
    fprintf(file_u     ,"\n");
    fprintf(file_v     ,"\n");
  }
  */
  fclose(file_omega);
  fclose(file_psi);
  fclose(file_u);
  fclose(file_v);
}

int main(int argv,char* argc[]){
  fprintf(stderr, "Starting Computing\n");
  double CFL   =   1.0 ;
  double L     =   2.0 ;
  double H     =   1.0 ;
  double h     =   0.001;
  double dt    =   0.1 ;
  double Ls    = L/4.0 ;
  double Hs    = H/2.0 ;
  double tmax  =   5.0 ;
  double phi   =   1.98;
  double Q0    =   1;
  double tol   =   0.01;
  double nu    =   1e-3;

  struct _problem* Problem = init_problem();
  init_problem_physical(Problem,CFL,L,H,Ls,Hs,h,dt,tmax,Q0,tol,nu);
  init_problem_numerical(Problem,phi);
  init_problem_map(Problem);
  init_problem_vector_domain(Problem);
  // ---Code Benchmarking-------
  struct timespec start, finish;
  double elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);
  // ---------------------------
  //poisson_inner_psi_iterator(Problem);
  //first_time_integration(Problem);
  integration_omega(Problem);
  // ---Code Benchmarking-------
  clock_gettime(CLOCK_MONOTONIC, &finish);
  elapsed = (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  // ---------------------------
  //test_omega_domainFill (Problem);

  //test_psi_boundaryFill(Problem,test_Qfunc_const);
  print_problem_data(Problem);
  printf("Done \n");


  printf("Time Elapsed: %f s\n",elapsed);
  free_problem_vector_domain(Problem);
}
