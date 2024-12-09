#pragma once
#define BIAS 1.0
#define LEARNING_RATE 0.1
#define EMAX 0.01
#define CYCLE_MAX 30000
#define MOMENT_RATE 0.99
#define T_SIZE 2

struct ProcessingUnit
{
    float summedInput;
    float activation;
    ProcessingUnit() { summedInput = 0; activation = 0; };
};

struct LayerUnit
{
    ProcessingUnit* units;
    int unitCount;
    ~LayerUnit() {
        delete[] units;
    }
};

class NeuralModel
{
public:
    NeuralModel();
    ~NeuralModel();
    void InitializeModel(const int hiddenLayerCount, int* unitCounts, const int inputDimension, const int outputClassCount);
    int performSGDTraining(float* trainingData, float* targetData, int sampleCount);
    int performSGDTrainingWithMomentum(float* trainingData, float* targetData, int sampleCount);
    void ExecuteTest(float* testData, int* predictedLabels, int dataCount);
    void ExportWeights();
    void InitializeFromWeightsFile();
    double* errorHistory;
private:
    LayerUnit* layers;
    float** weightMatrix;
    float** offsetValues;
    int hiddenLayerTotal; // HIDDEN LAYER COUNT
    int inputDimension;   // INPUT DIMENSION
    int classCount;       // CLASS COUNT
};
