#include "pch.h"
#include "NeuralNetwork.h"
#include "Process.h"
#include <math.h>
#include <cfloat>
#include <fstream>

void NeuralModel::InitializeModel(const int hiddenLayerCount, int* unitCounts, const int inputDimension, const int outputClassCount)
{
    this->layers = new LayerUnit[hiddenLayerCount + 1]; // hidden layers + output layer

    for (int i = 0; i < hiddenLayerCount; i++)
    {
        this->layers[i].units = new ProcessingUnit[unitCounts[i]];
        this->layers[i].unitCount = unitCounts[i];
    }

    this->layers[hiddenLayerCount].units = new ProcessingUnit[outputClassCount];
    this->layers[hiddenLayerCount].unitCount = outputClassCount;

    this->weightMatrix = new float* [hiddenLayerCount + 1];
    this->offsetValues = new float* [hiddenLayerCount + 1];

    // input -> first hidden layer
    this->weightMatrix[0] = init_array_random(inputDimension * unitCounts[0]);
    this->offsetValues[0] = init_array_random(unitCounts[0]);

    // hidden layers
    for (int i = 0; i < hiddenLayerCount - 1; i++)
    {
        this->weightMatrix[i + 1] = init_array_random(unitCounts[i] * unitCounts[i + 1]);
        this->offsetValues[i + 1] = init_array_random(unitCounts[i + 1]);
    }

    // last hidden layer -> output layer
    this->weightMatrix[hiddenLayerCount] = init_array_random(unitCounts[hiddenLayerCount - 1] * outputClassCount);
    this->offsetValues[hiddenLayerCount] = init_array_random(outputClassCount);

    this->hiddenLayerTotal = hiddenLayerCount;
    this->inputDimension = inputDimension;
    this->classCount = outputClassCount;
}

int NeuralModel::performSGDTraining(float* trainingData, float* targetData, int sampleCount)
{
    float targetVal, cumulativeError = 0, rmseError = 0;
    this->errorHistory = new double[CYCLE_MAX];

    float** layerSignals = new float* [this->hiddenLayerTotal + 1];

    for (int l = 0; l < this->hiddenLayerTotal + 1; l++)
        layerSignals[l] = new float[layers[l].unitCount];

    for (int iteration = 0; iteration < CYCLE_MAX; iteration++)
    {
        cumulativeError = 0;

        for (int s = 0; s < sampleCount; s++)
        {
            // Forward: Input Layer
            for (int j = 0; j < layers[0].unitCount; j++)
                layers[0].units[j].summedInput = 0;

            for (int j = 0; j < layers[0].unitCount; j++)
            {
                for (int i = 0; i < this->inputDimension; i++)
                {
                    layers[0].units[j].summedInput += trainingData[(s * this->inputDimension) + i] *
                        this->weightMatrix[0][(j * this->inputDimension) + i];
                }
                layers[0].units[j].summedInput += offsetValues[0][j];
                layers[0].units[j].activation = (float)tanh(layers[0].units[j].summedInput);
            }

            // Forward: Hidden + Output
            for (int l = 1; l < this->hiddenLayerTotal + 1; l++)
            {
                for (int j = 0; j < layers[l].unitCount; j++)
                    layers[l].units[j].summedInput = 0;

                for (int j = 0; j < layers[l].unitCount; j++)
                {
                    for (int i = 0; i < layers[l - 1].unitCount; i++)
                        layers[l].units[j].summedInput += layers[l - 1].units[i].activation *
                        this->weightMatrix[l][j * (layers[l - 1].unitCount) + i];

                    layers[l].units[j].summedInput += offsetValues[l][j];
                    layers[l].units[j].activation = (float)tanh(layers[l].units[j].summedInput);

                    // Output layer
                    if (l == hiddenLayerTotal)
                    {
                        if (j == (int)targetData[s])
                            targetVal = +1;
                        else
                            targetVal = -1;

                        float deriv = 1 - pow(layers[l].units[j].activation, 2);
                        layerSignals[l][j] = (targetVal - layers[l].units[j].activation) * deriv;

                        for (int i = 0; i < layers[l - 1].unitCount; i++)
                            this->weightMatrix[l][j * (layers[l - 1].unitCount) + i] +=
                            LEARNING_RATE * layerSignals[l][j] * layers[l - 1].units[i].activation;

                        this->offsetValues[l][j] += LEARNING_RATE * layerSignals[l][j];
                        cumulativeError += pow((targetVal - layers[l].units[j].activation), 2);
                    }
                }
            }

            // Backprop: Hidden Layers
            for (int l = this->hiddenLayerTotal - 1; l > 0; l--)
            {
                for (int j = 0; j < layers[l].unitCount; j++)
                {
                    float f_deriv = 1 - pow(layers[l].units[j].activation, 2);
                    float sumVal = 0;
                    for (int k = 0; k < layers[l + 1].unitCount; k++)
                        sumVal += layerSignals[l + 1][k] * this->weightMatrix[l + 1][k * layers[l].unitCount + j];

                    layerSignals[l][j] = f_deriv * sumVal;
                    for (int i = 0; i < layers[l - 1].unitCount; i++)
                        this->weightMatrix[l][j * layers[l - 1].unitCount + i] +=
                        LEARNING_RATE * layerSignals[l][j] * layers[l - 1].units[i].activation;

                    this->offsetValues[l][j] += LEARNING_RATE * layerSignals[l][j];
                }
            }

            // Backprop: Input Layer
            for (int j = 0; j < layers[0].unitCount; j++)
            {
                float f_deriv = 1 - pow(layers[0].units[j].activation, 2);
                float sumVal = 0;
                for (int k = 0; k < layers[1].unitCount; k++)
                    sumVal += layerSignals[1][k] * this->weightMatrix[1][k * layers[0].unitCount + j];

                layerSignals[0][j] = f_deriv * sumVal;
                for (int i = 0; i < this->inputDimension; i++)
                    this->weightMatrix[0][j * this->inputDimension + i] +=
                    LEARNING_RATE * layerSignals[0][j] * trainingData[(s * this->inputDimension) + i];

                offsetValues[0][j] += LEARNING_RATE * layerSignals[0][j];
            }
        }

        rmseError = sqrt(cumulativeError / (sampleCount * this->classCount));
        this->errorHistory[iteration] = (double)rmseError;
        if (rmseError < EMAX)
        {
            for (int l = 0; l < this->hiddenLayerTotal + 1; l++)
                delete[] layerSignals[l];
            delete[] layerSignals;
            return iteration;
        }
    }

    for (int l = 0; l < this->hiddenLayerTotal + 1; l++)
        delete[] layerSignals[l];
    delete[] layerSignals;
    return 0;
}


int NeuralModel::performSGDTrainingWithMomentum(float* trainingData, float* targetData, int sampleCount)
{
    float targetVal, cumulativeError = 0, rmseError = 0, mseError = 0;
    this->errorHistory = new double[CYCLE_MAX];

    float** layerSignals = new float* [this->hiddenLayerTotal + 1];
    float*** momentumMatrix = new float** [this->hiddenLayerTotal + 1];
    float*** momentOffset = new float** [this->hiddenLayerTotal + 1];

    for (int l = 0; l < this->hiddenLayerTotal + 1; l++)
        layerSignals[l] = new float[layers[l].unitCount];

    int inputSize = this->inputDimension * layers[0].unitCount;
    momentumMatrix[0] = new float* [inputSize];
    for (int i = 0; i < inputSize; i++)
        momentumMatrix[0][i] = init_array_zero(T_SIZE);

    for (int l = 1; l < this->hiddenLayerTotal + 1; l++)
    {
        int size = layers[l - 1].unitCount * layers[l].unitCount;
        momentumMatrix[l] = new float* [size];
        for (int i = 0; i < size; i++)
            momentumMatrix[l][i] = init_array_zero(T_SIZE);
    }

    for (int l = 0; l < this->hiddenLayerTotal + 1; l++)
    {
        int size = layers[l].unitCount;
        momentOffset[l] = new float* [size];
        for (int i = 0; i < size; i++)
            momentOffset[l][i] = init_array_zero(T_SIZE);
    }

    for (int iteration = 0; iteration < CYCLE_MAX; iteration++)
    {
        cumulativeError = 0;

        for (int s = 0; s < sampleCount; s++)
        {
            // Forward: Input Layer
            for (int j = 0; j < layers[0].unitCount; j++)
                layers[0].units[j].summedInput = 0;

            for (int j = 0; j < layers[0].unitCount; j++)
            {
                for (int i = 0; i < this->inputDimension; i++)
                {
                    layers[0].units[j].summedInput += trainingData[(s * this->inputDimension) + i] *
                        this->weightMatrix[0][(j * this->inputDimension) + i];
                }
                layers[0].units[j].summedInput += offsetValues[0][j];
                layers[0].units[j].activation = (float)tanh(layers[0].units[j].summedInput);
            }

            // Forward: Hidden + Output
            for (int l = 1; l < this->hiddenLayerTotal + 1; l++)
            {
                for (int j = 0; j < layers[l].unitCount; j++)
                    layers[l].units[j].summedInput = 0;

                for (int j = 0; j < layers[l].unitCount; j++)
                {
                    for (int i = 0; i < layers[l - 1].unitCount; i++)
                    {
                        layers[l].units[j].summedInput += layers[l - 1].units[i].activation *
                            this->weightMatrix[l][j * (layers[l - 1].unitCount) + i];
                    }
                    layers[l].units[j].summedInput += offsetValues[l][j];
                    layers[l].units[j].activation = (float)tanh(layers[l].units[j].summedInput);

                    if (l == this->hiddenLayerTotal) // output layer
                    {
                        if ((int)targetData[s] == j)
                            targetVal = +1;
                        else
                            targetVal = -1;

                        float f_deriv = 1 - pow(layers[l].units[j].activation, 2);
                        layerSignals[l][j] = (targetVal - layers[l].units[j].activation) * f_deriv;
                        for (int i = 0; i < layers[l - 1].unitCount; i++)
                        {
                            int w_index = j * (layers[l - 1].unitCount) + i;
                            float delta_w = LEARNING_RATE * layerSignals[l][j] * layers[l - 1].units[i].activation;
                            float MOMENT_SUM = 0;
                            for (int t = 0; t < T_SIZE - 1; t++)
                                MOMENT_SUM += MOMENT_RATE * momentumMatrix[l][w_index][t];

                            this->weightMatrix[l][w_index] += delta_w + MOMENT_SUM;
                            push_back(momentumMatrix, l, w_index, T_SIZE, delta_w);
                        }
                        float delta_b = LEARNING_RATE * layerSignals[l][j];
                        float MOMENT_B = 0;
                        for (int t = 0; t < T_SIZE - 1; t++)
                            MOMENT_B += MOMENT_RATE * momentOffset[l][j][t];
                        this->offsetValues[l][j] += delta_b + MOMENT_B;
                        push_back(momentOffset, l, j, T_SIZE, delta_b);

                        cumulativeError += pow((targetVal - layers[l].units[j].activation), 2);
                    }
                }
            }

            // Backprop: Hidden Layers
            for (int l = this->hiddenLayerTotal - 1; l > 0; l--)
            {
                for (int j = 0; j < layers[l].unitCount; j++)
                {
                    float f_deriv = 1 - pow(layers[l].units[j].activation, 2);
                    float sumVal = 0;
                    for (int k = 0; k < layers[l + 1].unitCount; k++)
                        sumVal += layerSignals[l + 1][k] * this->weightMatrix[l + 1][k * layers[l].unitCount + j];

                    layerSignals[l][j] = f_deriv * sumVal;

                    for (int i = 0; i < layers[l - 1].unitCount; i++)
                    {
                        float delta_w = LEARNING_RATE * layerSignals[l][j] * layers[l - 1].units[i].activation;
                        int w_index = j * layers[l - 1].unitCount + i;
                        float MOMENT_SUM = 0;
                        for (int t = 0; t < T_SIZE - 1; t++)
                            MOMENT_SUM += MOMENT_RATE * momentumMatrix[l][w_index][t];
                        this->weightMatrix[l][w_index] += delta_w + MOMENT_SUM;
                        push_back(momentumMatrix, l, w_index, T_SIZE, delta_w);
                    }
                    float delta_b = LEARNING_RATE * layerSignals[l][j];
                    float MOMENT_B = 0;
                    for (int t = 0; t < T_SIZE - 1; t++)
                        MOMENT_B += MOMENT_RATE * momentOffset[l][j][t];
                    this->offsetValues[l][j] += delta_b + MOMENT_B;
                    push_back(momentOffset, l, j, T_SIZE, delta_b);
                }
            }

            // Backprop: Input Layer
            for (int j = 0; j < layers[0].unitCount; j++)
            {
                float f_deriv = 1 - pow(layers[0].units[j].activation, 2);
                float sumVal = 0;
                for (int k = 0; k < layers[1].unitCount; k++)
                    sumVal += layerSignals[1][k] * this->weightMatrix[1][k * layers[0].unitCount + j];

                layerSignals[0][j] = f_deriv * sumVal;
                for (int i = 0; i < this->inputDimension; i++)
                {
                    float delta_w = LEARNING_RATE * layerSignals[0][j] * trainingData[(s * this->inputDimension) + i];
                    int w_index = j * this->inputDimension + i;
                    float MOMENT_SUM = 0;
                    for (int t = 0; t < T_SIZE; t++)
                        MOMENT_SUM += MOMENT_RATE * momentumMatrix[0][w_index][t];
                    this->weightMatrix[0][w_index] += delta_w + MOMENT_SUM;
                    push_back(momentumMatrix, 0, w_index, T_SIZE, delta_w);
                }
                float delta_b = LEARNING_RATE * layerSignals[0][j];
                float MOMENT_B = 0;
                for (int t = 0; t < T_SIZE - 1; t++)
                    MOMENT_B += MOMENT_RATE * momentOffset[0][j][t];
                this->offsetValues[0][j] += delta_b + MOMENT_B;
                push_back(momentOffset, 0, j, T_SIZE, delta_b);
            }
        }

        rmseError = sqrt(cumulativeError / (sampleCount * this->classCount));
        this->errorHistory[iteration] = (double)rmseError;
        if (rmseError < EMAX)
        {
            for (int l = 1; l < this->hiddenLayerTotal + 1; l++)
            {
                int size = layers[l - 1].unitCount * layers[l].unitCount;
                for (int i = 0; i < size; i++)
                    delete[] momentumMatrix[l][i];
            }
            for (int i = 0; i < inputSize; i++)
                delete[] momentumMatrix[0][i];

            for (int l = 0; l < this->hiddenLayerTotal + 1; l++) {
                int size = layers[l].unitCount;
                for (int i = 0; i < size; i++)
                    delete[] momentOffset[l][i];
                delete[] layerSignals[l];
                delete[] momentumMatrix[l];
                delete[] momentOffset[l];
            }
            delete[] momentOffset;
            delete[] momentumMatrix;
            delete[] layerSignals;
            return iteration;
        }
    }

    for (int l = 1; l < this->hiddenLayerTotal + 1; l++)
    {
        int size = layers[l - 1].unitCount * layers[l].unitCount;
        for (int i = 0; i < size; i++)
            delete[] momentumMatrix[l][i];
    }
    for (int i = 0; i < inputSize; i++)
        delete[] momentumMatrix[0][i];

    for (int l = 0; l < this->hiddenLayerTotal + 1; l++)
    {
        int size = layers[l].unitCount;
        for (int i = 0; i < size; i++)
            delete[] momentOffset[l][i];
        delete[] layerSignals[l];
        delete[] momentumMatrix[l];
        delete[] momentOffset[l];
    }

    delete[] momentOffset;
    delete[] momentumMatrix;
    delete[] layerSignals;
    return 0;
}

void NeuralModel::ExecuteTest(float* testData, int* predictedLabels, int dataCount)
{
    int maxIndex = 0;
    for (int sample = 0; sample < dataCount; sample++)
    {
        for (int j = 0; j < layers[0].unitCount; j++)
            layers[0].units[j].summedInput = 0;

        for (int j = 0; j < layers[0].unitCount; j++)
        {
            for (int i = 0; i < this->inputDimension; i++)
            {
                layers[0].units[j].summedInput += testData[(sample * this->inputDimension) + i] *
                    this->weightMatrix[0][(j * this->inputDimension) + i];
            }
            layers[0].units[j].summedInput += offsetValues[0][j];
            layers[0].units[j].activation = (float)tanh(layers[0].units[j].summedInput);
        }

        for (int l = 1; l < this->hiddenLayerTotal + 1; l++)
        {
            for (int j = 0; j < layers[l].unitCount; j++)
                layers[l].units[j].summedInput = 0;

            for (int j = 0; j < layers[l].unitCount; j++)
            {
                for (int i = 0; i < layers[l - 1].unitCount; i++)
                    layers[l].units[j].summedInput += layers[l - 1].units[i].activation *
                    this->weightMatrix[l][j * (layers[l - 1].unitCount) + i];

                layers[l].units[j].summedInput += offsetValues[l][j];
                layers[l].units[j].activation = (float)tanh(layers[l].units[j].summedInput);
            }
        }

        float tempMax = -FLT_MAX;
        int outLayerIndex = this->hiddenLayerTotal;
        for (int j = 0; j < this->classCount; j++)
        {
            if (layers[outLayerIndex].units[j].activation > tempMax)
            {
                tempMax = layers[outLayerIndex].units[j].activation;
                maxIndex = j;
            }
        }
        predictedLabels[sample] = maxIndex;
    }
}

void NeuralModel::ExportWeights()
{
    char** c = new char* [1];
    c[0] = "../Data/weights.txt";
    std::ofstream file(c[0]);
    if (!file.bad()) {
        file << this->hiddenLayerTotal << " " << this->inputDimension << " " << this->classCount;
        for (int i = 0; i < this->hiddenLayerTotal; i++)
            file << " " << layers[i].unitCount;
        file << std::endl;

        int size = this->inputDimension * this->layers[0].unitCount;
        for (int k = 0; k < size; k++)
            file << weightMatrix[0][k] << " ";
        file << std::endl;

        for (int k = 0; k < this->layers[0].unitCount; k++)
            file << offsetValues[0][k] << " ";
        file << std::endl;

        for (int l = 0; l < this->hiddenLayerTotal; l++) {
            int size = this->layers[l].unitCount * this->layers[l + 1].unitCount;
            for (int k = 0; k < size; k++)
                file << weightMatrix[l + 1][k] << " ";
            file << std::endl;
            for (int k = 0; k < this->layers[l + 1].unitCount; k++)
                file << offsetValues[l + 1][k] << " ";
            file << std::endl;
        }
        file.close();
    }
    else System::Windows::Forms::MessageBox::Show("Dosya açılamadı");
    delete[] c;
}

void NeuralModel::InitializeFromWeightsFile()
{
    char** c = new char* [1];
    std::ifstream file;
    int LayerNum, Dim, numclass;
    int* neuronCount;
    c[0] = "../Data/weights.txt";
    file.open(c[0]);
    if (file.is_open()) {
        file >> LayerNum >> Dim >> numclass;
        neuronCount = new int[LayerNum];
        for (int i = 0; i < LayerNum; i++)
            file >> neuronCount[i];
        this->InitializeModel(LayerNum, neuronCount, Dim, numclass);
        int size = this->inputDimension * this->layers[0].unitCount;
        for (int k = 0; k < size; k++)
            file >> weightMatrix[0][k];
        for (int k = 0; k < this->layers[0].unitCount; k++)
            file >> offsetValues[0][k];

        for (int l = 0; l < this->hiddenLayerTotal; l++) {
            int size = this->layers[l].unitCount * this->layers[l + 1].unitCount;
            for (int k = 0; k < size; k++)
                file >> weightMatrix[l + 1][k];
            for (int k = 0; k < this->layers[l + 1].unitCount; k++)
                file >> offsetValues[l + 1][k];
        }
        file.close();
        System::String^ StringArray;
        for (int i = 0; i < LayerNum; i++)
            StringArray += System::Convert::ToString(neuronCount[i]) + " ";
        System::Windows::Forms::MessageBox::Show("Dosya başarı ile okundu" + "\r\n"
            + "Dimension:  " + System::Convert::ToString(Dim) + "\r\n"
            + "Hidden Layer:  " + System::Convert::ToString(LayerNum) + "\r\n"
            + "Neurons:  " + StringArray + "\r\n"
            + "numClass:  " + System::Convert::ToString(numclass) + "\r\n"
        );
    }
    else System::Windows::Forms::MessageBox::Show("Ağırlık dosyası açılamadı");
}

NeuralModel::NeuralModel()
{
}

NeuralModel::~NeuralModel()
{
    for (int i = 0; i < hiddenLayerTotal + 1; i++)
    {
        delete[] weightMatrix[i];
        delete[] offsetValues[i];
    }
    delete[] weightMatrix;
    delete[] offsetValues;
    delete[] layers;
    delete[] errorHistory;
}
