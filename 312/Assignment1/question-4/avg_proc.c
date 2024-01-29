#include <rpc/rpc.h>
#include "avg.h"
#include <stdio.h>

/* run locally on 'server' called by a remote client. */
static double sum;
static double sum_squared;
static double variance; 
static double stddev; 

/* 
 * routine notice the _1 the version number 
 * notice the client handle, not sued here but needs to be 
 * a parameter 
 */
double * average_1(input_data *input, CLIENT *client) {
  /* input is paramters were marshalled by genrated routine */
  /*  a pointer to a double, is set to begining of data array  */
  double *dp = input->input_data.input_data_val;

  u_int i;
  sum, sum_squared = 0;

  /* iterate until end of number of times (data_len) */
  for( i = 1; i <= input->input_data.input_data_len; i++ )
    {
      sum += *dp;
      sum_squared += (*dp) * (*dp);
      dp++; 
    }

  variance = (sum_squared / input->input_data.input_data_len) - pow((sum / input->input_data.input_data_len), 2);

  stddev = sqrt(variance); 

  return( &stddev );
}

/* 
 * server stub 'average_1_svc function handle called in avg_svc that was
 * generated by rpcgen 
 * FYI:
 *   result = (*local)((char *)&argument, rqstp);
 *   where local is (char *(*)(char *, struct svc_req *)) average_1_svc;
 */
double * average_1_svc(input_data *input, struct svc_req *svc) {
  CLIENT *client;
  return(average_1(input, client));
}