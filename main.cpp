#include <iostream>
#include <armadillo>
#include <fstream>

//problema: nao consigo multiplicar matrizes...

using namespace std;
using namespace arma;

float media(vec x);  //funcao para media
vec cumsumK(vec x); // soma acumulada
vec rexpArma(int n, float lambda); // geracao de variavel exponencial
vec rlogisC(int n, float mu, float beta); // geracao de variavel logistica
arma::vec rcauchyC(int n, float mu, float sigma); // geracao de variavel Cauchy
arma::mat normalC(int n); //geracao de duas N(0,1) iid

int main()
{
    int A[5][5];
    mat B = randu<mat>(5,10);
    mat C = randu<mat>(10,5);
    const int m=5, n=5;

    vec vetor(100, fill::zeros);
    vetor = rexpArma(100,2);
    vetor = rlogisC(10000,5,2);
    vetor = rcauchyC(1000,0,1);

    mat res = zeros<mat>(10,2);
    res = normalC(10);

    cout << res << endl;

    return 0;
}

float media(vec x){

    float soma;
    soma = sum(x);
    int n = x.n_elem;

    soma /= n;

    return soma;

}

vec cumsumK(vec x){
    int n = x.n_elem;
    vec out(n);

    for(int i=0; i<n; i++){
        out(i) = sum(x.rows(0,i));
    }

    return out;
}

vec rexpArma(int n, float lambda){
  vec U(n, fill::randu);
  return -log(1- U)/lambda;
}

vec rlogisC(int n, float mu, float beta){
  vec U(n, fill::randu);
  return mu - beta*log(U/(1-U));
}

arma::vec rcauchyC(int n, float mu, float sigma){
  arma::vec U(n, arma::fill::randu);
  return mu + sigma*tan(3.14159265*(U-.5));
}

arma::mat normalC(int n){

  arma::vec U1(n, arma::fill::randu);
  arma::vec U2(n, arma::fill::randu);

  arma::vec X1 = arma::sqrt(-2*arma::log(U1)) % arma::cos(2*3.14*U2);
  arma::vec X2 = arma::sqrt(-2*arma::log(U1)) % arma::sin(2*3.14*U2);

  arma::mat out = arma::join_rows(X1,X2);

  return out;
}
