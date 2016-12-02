#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector rexpC(int n, float lambda) { //Rcpp Sugar
  return -log(1-runif(n))/lambda;
}

// [[Rcpp::export]]
arma::vec rexpArma(int n, float lambda){ //Armadillo
  arma::vec U(n, arma::fill::randu);
  return -log(1- U)/lambda;
}

// [[Rcpp::export]]
arma::vec rlogisC(int n, float mu, float beta){
  arma::vec U(n, arma::fill::randu);
  return mu - beta*log(U/(1-U));
}

// [[Rcpp::export]]
arma::vec rcauchyC(int n, float mu, float sigma){
  arma::vec U(n, arma::fill::randu);
  return mu + sigma*tan(3.1415*(U-.5));
}

// [[Rcpp::export]]
arma::mat normalC(int n){
  
  arma::vec U1(n, arma::fill::randu);
  arma::vec U2(n, arma::fill::randu);
  
  arma::vec X1 = arma::sqrt(-2*arma::log(U1)) % arma::cos(2*3.14*U2);
  arma::vec X2 = arma::sqrt(-2*arma::log(U1)) % arma::sin(2*3.14*U2);
  
  arma::mat out = arma::join_rows(X1,X2);
  
  return out;
}

/*** R
library(microbenchmark)

exponential = rexpC(100,2)
exponential2 = rexpArma(100,2)
logistic = rlogisC(100,5,2)
cauchy = rcauchyC(1000,0,1)

hist(cauchy, breaks=100)
hist(rcauchy(1000), breaks=100)
hist(logistic, breaks = 20)
 hist(rlogis(100,5,2), breaks=20)

microbenchmark(rexp(1000,2), rexpC(1000,2),rexpArma(1000,2))
microbenchmark(rlogisC(10000,5,2), rlogis(10000,5,2))
microbenchmark(rcauchyC(10000,0,1), rcauchy(10000,0,1))

a = normalC(10000)
dim(a)
par(mfrow=c(1,2))
hist(a[,1], freq =FALSE); hist(a[,2], freq =FALSE)


*/
