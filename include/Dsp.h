#ifndef DSP_H
#define DSP_H
#include <vector>
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
namespace Dp{
    class Dsp
    {
        public:
            Dsp();
            float mean1D(std::vector<float> &data);
            float std1D(std::vector<float> &data);
            float cov1D(std::vector<float> &data1, std::vector<float> &data2);
            int convolve1D(float* in, float* out, int dataSize, float* kernel, int kernelSize);
            float var(std::vector<float> &data1);
            Eigen::MatrixXf cov(std::vector<float> &data1, std::vector<float> &data2);
            virtual ~Dsp();

        protected:

        private:
    };
}

#endif // DSP_H
