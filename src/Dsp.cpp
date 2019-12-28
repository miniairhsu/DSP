#include "Dsp.h"

namespace Dp{
    Dsp::Dsp()
    {
        //ctor
    }

    float Dsp::mean1D(std::vector<float> &data){
        float result = 0;
        for(unsigned int i = 0; i < data.size(); i ++){
            result += data[i];
        }
        return result / data.size();
    }

    float Dsp::std1D(std::vector<float> &data){
        float result = 0;
        float mean = mean1D(data);
        for(unsigned int i = 0; i < data.size(); i++){
            result += pow(data[i] - mean, 2);
        }
        return sqrt(result/(data.size()-1));
    }

    int Dsp::convolve1D(float* in, float* out, int dataSize, float* kernel, int kernelSize){
        int i, j, k;
        // check validity of params
        if(!in || !out || !kernel) return -1;
        if(dataSize <=0 || kernelSize <= 0) return -1;
        // start convolution from out[kernelSize-1] to out[dataSize-1] (last)
        for(i = kernelSize-1; i < dataSize; ++i)
        {
            out[i] = 0;                             // init to 0 before accumulate
            for(j = i, k = 0; k < kernelSize; --j, ++k)
                out[i] += in[j] * kernel[k];
        }
        // convolution from out[0] to out[kernelSize-2]
        for(i = 0; i < kernelSize - 1; ++i)
        {
            out[i] = 0;                             // init to 0 before sum
            for(j = i, k = 0; j >= 0; --j, ++k)
                out[i] += in[j] * kernel[k];
        }
        return 0;
    }

    float Dsp::var(std::vector<float> &data1){
        float mean = this->mean1D(data1);
        float result = 0;
        for(unsigned int i = 0; i < data1.size(); i++){
            result += (data1[i] - mean) * (data1[i] - mean);
        }
        return result/ (data1.size()-1);
    }

    float Dsp::cov1D(std::vector<float> &data1, std::vector<float> &data2){
        float result = 0;
        if( data1.size() != data2.size()) return 0;
        float mean1 = this->mean1D(data1);
        float mean2 = this->mean1D(data2);
        for(unsigned int i = 0; i < data1.size(); i++){
            result = result + (data1[i] - mean1) * (data2[i] - mean2);
        }
        return result / (static_cast<float>(data1.size() - 1));
    }

    Eigen::MatrixXf Dsp::cov(std::vector<float> &data1, std::vector<float> &data2){
        float var1 = var(data1);
        float var2 = var(data2);
        float cov1 = cov1D(data1, data2);
        float cov2 = cov1;
        Eigen::MatrixXf result(2,2);
        result(0,0) = var1;
        result(0,1) = cov1;
        result(1,0) = cov2;
        result(1,1) = var2;
        return result;
    }

    float Dsp::divation(std::vector<float> &data, float mean){
        float result = 0;
        for(unsigned int i = 0; i < data.size(); i++){
            result += pow(data[i] - mean, 2);
        }
        return result;
    }

    void Dsp::xcorr(std::vector<float> &data1, std::vector<float> &data2, int length, float* out){
        float mean1 = this->mean1D(data1);
        float mean2 = this->mean1D(data2);
        float div1 = this->divation(data1, mean1);
        float div2 = this->divation(data2, mean2);
        float denom = sqrt(div1 * div2);
        float sxy;
        for (int delay = 0; delay < length; delay++ ) {
            sxy = 0;
            for( int i = 0; i < length; i++ ) {
                int j = i + delay - length / 2;
                while ( j < 0 )
                    j += length;
                j %= length;
                sxy += (data1[i] - mean1) * (data2[j] - mean2);
            }
            out[delay]  = sxy / denom;
        }
    }

    Dsp::~Dsp()
    {
        //dtor
    }
}
