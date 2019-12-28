#include <iostream>
#include <aquila/global.h>
#include <aquila/source/generator/SineGenerator.h>
#include "Dsp.h"
using namespace std;
using namespace Dp;
int main()
{
    cout << "Hello world!" << endl;
    std::vector<float> data1 = {3, 6 , 4};
    std::vector<float> data2 = {7, 12, -9};
    Dsp *dsp = new Dsp();

    /*std::cout << "Variance :\n" << dsp->var(data1) << std::endl;

    float cov = dsp->cov1D(data1, data2);
    std::cout << "covariance " << cov << endl;

    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>  A = dsp->cov(data1, data2);
    std::cout << "Covariance matrix A:\n" << A << std::endl;

    float stdv = dsp->std1D(data1);
    std::cout << "standard deviation data1:\n" << stdv << std::endl;

    float in[] = {3, 4, 5, 0, 0};
    float kernel[] = {2, 1};
    float out[5];
    int a = dsp->convolve1D(in, out, 5, kernel, 2);
    for(unsigned int i = 0; i < 5; i++){
         std::cout << "Convolution output:\n" << out[i] << std::endl;
    }*/
    int dataSize = 1000;
    int length = 100;
    std::vector<float> dataA;
    std::vector<float> dataB;
    float* output;
    output = (float *)malloc(sizeof(float) * length);
    for(int i = 0; i < dataSize; i++){
        dataA.push_back((rand() % 100) + 1);
        dataB.push_back(dataA[i] + (rand() % 100));
    }
    dsp->xcorr(dataA, dataB, length, output);
    for(int i = 0; i < length; i++){
         std::cout << output[i] << std::endl;
    }
    return 0;
}
