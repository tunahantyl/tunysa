#pragma once
#include "Process.h"
#include <iostream>
#include <fstream>
#include <string>
#include "NeuralNetwork.h"

namespace CppCLRWinformsProjekt {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Windows::Forms::DataVisualization::Charting;
    /// <summary>
    /// Summary for Form1
    /// </summary>

    public ref class Form1 : public System::Windows::Forms::Form
    {

    public:
        Form1(void)
        {
            srand(static_cast<unsigned>(time(nullptr)));
            InitializeComponent();
            //
            //TODO: Add constructor code here
            //
            WIDTH = this->pictureBox1->Width;
            HEIGHT = this->pictureBox1->Height;
            AREASIZE = HEIGHT * WIDTH;
            MINX = WIDTH / -2;
            MAXY = HEIGHT / 2;
            testData = new float[AREASIZE * 2];				// x-y Coord              
            tag = new int[AREASIZE];					// Class tag
        }
    protected:
        ~Form1()
        {
            if (components)
            {
                delete components;
            }
            delete[] testData;
            delete[] tag;
            delete[] Samples;
            delete[] targets;
        }

    private:
        /// <summary>
        /// User Defined Variables
        int  numClass = 0, numSample = 0;
        const int inputDim = 2;
        float* Samples, * targets;
        NeuralModel* model = new NeuralModel;
        System::ComponentModel::IContainer^ components;

        // picture box area
        int WIDTH, HEIGHT;
        int AREASIZE;
        int MINX, MAXY;
        float* testData;		// x-y Coord              
        int* tag;					// Class tag

    private: System::Windows::Forms::MenuStrip^ menuStrip1;
    private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
    private: System::Windows::Forms::TextBox^ textBox1;
    private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::ComboBox^ LayerCountBox;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::TextBox^ textBox2;
    private: System::Windows::Forms::PictureBox^ pictureBox1;
    private: System::Windows::Forms::GroupBox^ groupBox1;
    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::ComboBox^ ClassCountBox;
    private: System::Windows::Forms::GroupBox^ groupBox2;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::ComboBox^ ClassNoBox;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::ComboBox^ TrainTypeBox;
    private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
    private: System::Windows::Forms::GroupBox^ groupBox3;
    private: System::Windows::Forms::Button^ button2;
    private: System::Windows::Forms::Button^ button3;
    private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ readDataToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ saveDataToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ readWeightsToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^ saveWeightsToolStripMenuItem;

#pragma region Windows Form Designer generated code
           /// <summary>
           /// Required method for Designer support.
           /// Do not modify the contents of this method with the code editor.
           /// </summary>
           void InitializeComponent(void)
           {

               System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
               System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
               System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
               this->components = gcnew System::ComponentModel::Container();
               this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
               this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
               this->label5 = (gcnew System::Windows::Forms::Label());
               this->textBox2 = (gcnew System::Windows::Forms::TextBox());
               this->label4 = (gcnew System::Windows::Forms::Label());
               this->LayerCountBox = (gcnew System::Windows::Forms::ComboBox());
               this->button1 = (gcnew System::Windows::Forms::Button());
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->ClassCountBox = (gcnew System::Windows::Forms::ComboBox());
               this->label6 = (gcnew System::Windows::Forms::Label());
               this->TrainTypeBox = (gcnew System::Windows::Forms::ComboBox());
               this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
               this->label2 = (gcnew System::Windows::Forms::Label());
               this->ClassNoBox = (gcnew System::Windows::Forms::ComboBox());
               this->label3 = (gcnew System::Windows::Forms::Label());
               this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
               this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->readDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->saveDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->readWeightsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->saveWeightsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
               this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
               this->textBox1 = (gcnew System::Windows::Forms::TextBox());
               this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
               this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
               this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
               this->button3 = (gcnew System::Windows::Forms::Button());
               this->button2 = (gcnew System::Windows::Forms::Button());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
               this->groupBox1->SuspendLayout();
               this->groupBox2->SuspendLayout();
               this->menuStrip1->SuspendLayout();
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
               this->groupBox3->SuspendLayout();
               this->SuspendLayout();
               // 
               // pictureBox1
               // 
               this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
               this->pictureBox1->Location = System::Drawing::Point(13, 35);
               this->pictureBox1->Name = L"pictureBox1";
               this->pictureBox1->Size = System::Drawing::Size(747, 578);
               this->pictureBox1->TabIndex = 0;
               this->pictureBox1->TabStop = false;
               this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox1_Paint);
               this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseClick);
               // 
               // groupBox1
               // 
               this->groupBox1->Controls->Add(this->label5);
               this->groupBox1->Controls->Add(this->textBox2);
               this->groupBox1->Controls->Add(this->label4);
               this->groupBox1->Controls->Add(this->LayerCountBox);
               this->groupBox1->Controls->Add(this->button1);
               this->groupBox1->Controls->Add(this->label1);
               this->groupBox1->Controls->Add(this->ClassCountBox);
               this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
                   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(162)));
               this->groupBox1->Location = System::Drawing::Point(766, 50);
               this->groupBox1->Name = L"groupBox1";
               this->groupBox1->Size = System::Drawing::Size(220, 171);
               this->groupBox1->TabIndex = 1;
               this->groupBox1->TabStop = false;
               this->groupBox1->Text = L"Network Architecture";
               // 
               // label5
               // 
               this->label5->AutoSize = true;
               this->label5->Location = System::Drawing::Point(109, 84);
               this->label5->Name = L"label5";
               this->label5->Size = System::Drawing::Size(86, 26);
               this->label5->TabIndex = 6;
               this->label5->Text = L"Hidden Layer \r\nNeuron Count";
               // 
               // textBox2
               // 
               this->textBox2->Location = System::Drawing::Point(10, 93);
               this->textBox2->Margin = System::Windows::Forms::Padding(2);
               this->textBox2->Name = L"textBox2";
               this->textBox2->Size = System::Drawing::Size(82, 20);
               this->textBox2->TabIndex = 5;
               this->textBox2->Text = L"4 4";
               // 
               // label4
               // 
               this->label4->AutoSize = true;
               this->label4->Location = System::Drawing::Point(108, 59);
               this->label4->Name = L"label4";
               this->label4->Size = System::Drawing::Size(119, 13);
               this->label4->TabIndex = 4;
               this->label4->Text = L"Hidden Layer Count";
               // 
               // LayerCountBox
               // 
               this->LayerCountBox->FormattingEnabled = true;
               this->LayerCountBox->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"2", L"3", L"4", L"5", L"6", L"7" });
               this->LayerCountBox->Location = System::Drawing::Point(10, 57);
               this->LayerCountBox->Name = L"LayerCountBox";
               this->LayerCountBox->Size = System::Drawing::Size(82, 21);
               this->LayerCountBox->TabIndex = 3;
               this->LayerCountBox->Text = L"2";
               // 
               // button1
               // 
               this->button1->Location = System::Drawing::Point(61, 131);
               this->button1->Name = L"button1";
               this->button1->Size = System::Drawing::Size(131, 33);
               this->button1->TabIndex = 2;
               this->button1->Text = L"Network Setting";
               this->button1->UseVisualStyleBackColor = true;
               this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
               // 
               // label1
               // 
               this->label1->AutoSize = true;
               this->label1->Location = System::Drawing::Point(108, 23);
               this->label1->Name = L"label1";
               this->label1->Size = System::Drawing::Size(74, 13);
               this->label1->TabIndex = 1;
               this->label1->Text = L"Class Count";
               this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
               // 
               // ClassCountBox
               // 
               this->ClassCountBox->FormattingEnabled = true;
               this->ClassCountBox->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"2", L"3", L"4", L"5", L"6", L"7" });
               this->ClassCountBox->Location = System::Drawing::Point(10, 20);
               this->ClassCountBox->Name = L"ClassCountBox";
               this->ClassCountBox->Size = System::Drawing::Size(82, 21);
               this->ClassCountBox->TabIndex = 0;
               this->ClassCountBox->Text = L"2";
               // 
               // label6
               // 
               this->label6->AutoSize = true;
               this->label6->Location = System::Drawing::Point(110, 19);
               this->label6->Name = L"label6";
               this->label6->Size = System::Drawing::Size(76, 13);
               this->label6->TabIndex = 8;
               this->label6->Text = L"Optimization";
               // 
               // TrainTypeBox
               // 
               this->TrainTypeBox->FormattingEnabled = true;
               this->TrainTypeBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"SGD", L"SGDwMomentum" });
               this->TrainTypeBox->Location = System::Drawing::Point(10, 19);
               this->TrainTypeBox->Name = L"TrainTypeBox";
               this->TrainTypeBox->Size = System::Drawing::Size(82, 21);
               this->TrainTypeBox->TabIndex = 7;
               this->TrainTypeBox->Text = L"SGD";
               // 
               // groupBox2
               // 
               this->groupBox2->Controls->Add(this->label2);
               this->groupBox2->Controls->Add(this->ClassNoBox);
               this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold,
                   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(162)));
               this->groupBox2->Location = System::Drawing::Point(766, 228);
               this->groupBox2->Name = L"groupBox2";
               this->groupBox2->Size = System::Drawing::Size(220, 54);
               this->groupBox2->TabIndex = 2;
               this->groupBox2->TabStop = false;
               this->groupBox2->Text = L"Data Collection";
               // 
               // label2
               // 
               this->label2->AutoSize = true;
               this->label2->Location = System::Drawing::Point(98, 23);
               this->label2->Name = L"label2";
               this->label2->Size = System::Drawing::Size(83, 13);
               this->label2->TabIndex = 1;
               this->label2->Text = L"Sample Label";
               // 
               // ClassNoBox
               // 
               this->ClassNoBox->FormattingEnabled = true;
               this->ClassNoBox->Items->AddRange(gcnew cli::array< System::Object^  >(7) { L"1", L"2", L"3", L"4", L"5", L"6", L"7" });
               this->ClassNoBox->Location = System::Drawing::Point(7, 20);
               this->ClassNoBox->Name = L"ClassNoBox";
               this->ClassNoBox->Size = System::Drawing::Size(75, 21);
               this->ClassNoBox->TabIndex = 0;
               this->ClassNoBox->Text = L"1";
               // 
               // label3
               // 
               this->label3->AutoSize = true;
               this->label3->Location = System::Drawing::Point(1170, 50);
               this->label3->Name = L"label3";
               this->label3->Size = System::Drawing::Size(0, 13);
               this->label3->TabIndex = 3;
               // 
               // menuStrip1
               // 
               this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
               this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
               this->menuStrip1->Location = System::Drawing::Point(0, 0);
               this->menuStrip1->Name = L"menuStrip1";
               this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
               this->menuStrip1->Size = System::Drawing::Size(1200, 24);
               this->menuStrip1->TabIndex = 4;
               this->menuStrip1->Text = L"menuStrip1";
               this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::menuStrip1_ItemClicked);
               // 
               // fileToolStripMenuItem
               // 
               this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
                   this->readDataToolStripMenuItem,
                       this->saveDataToolStripMenuItem, this->readWeightsToolStripMenuItem, this->saveWeightsToolStripMenuItem
               });
               this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
               this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
               this->fileToolStripMenuItem->Text = L"File";
               // 
               // readDataToolStripMenuItem
               // 
               this->readDataToolStripMenuItem->Name = L"readDataToolStripMenuItem";
               this->readDataToolStripMenuItem->Size = System::Drawing::Size(148, 22);
               this->readDataToolStripMenuItem->Text = L"Read_Data";
               this->readDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::readDataToolStripMenuItem_Click);
               // 
               // saveDataToolStripMenuItem
               // 
               this->saveDataToolStripMenuItem->Name = L"saveDataToolStripMenuItem";
               this->saveDataToolStripMenuItem->Size = System::Drawing::Size(148, 22);
               this->saveDataToolStripMenuItem->Text = L"Save_Data";
               this->saveDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveDataToolStripMenuItem_Click);
               // 
               // readWeightsToolStripMenuItem
               // 
               this->readWeightsToolStripMenuItem->Name = L"readWeightsToolStripMenuItem";
               this->readWeightsToolStripMenuItem->Size = System::Drawing::Size(148, 22);
               this->readWeightsToolStripMenuItem->Text = L"Read_Weights";
               this->readWeightsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::readWeightsToolStripMenuItem_Click);
               // 
               // saveWeightsToolStripMenuItem
               // 
               this->saveWeightsToolStripMenuItem->Name = L"saveWeightsToolStripMenuItem";
               this->saveWeightsToolStripMenuItem->Size = System::Drawing::Size(148, 22);
               this->saveWeightsToolStripMenuItem->Text = L"Save_Weights";
               this->saveWeightsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveWeightsToolStripMenuItem_Click);
               // 
               // openFileDialog1
               // 
               this->openFileDialog1->FileName = L"openFileDialog1";
               this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
               // 
               // textBox1
               // 
               this->textBox1->Location = System::Drawing::Point(992, 50);
               this->textBox1->Multiline = true;
               this->textBox1->Name = L"textBox1";
               this->textBox1->Size = System::Drawing::Size(179, 321);
               this->textBox1->TabIndex = 5;
               // 
               // chart1
               // 
               chartArea1->Name = L"ChartArea1";
               this->chart1->ChartAreas->Add(chartArea1);
               legend1->Name = L"Legend1";
               this->chart1->Legends->Add(legend1);
               this->chart1->Location = System::Drawing::Point(765, 384);
               this->chart1->Margin = System::Windows::Forms::Padding(2);
               this->chart1->Name = L"chart1";
               series1->ChartArea = L"ChartArea1";
               series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
               series1->Legend = L"Legend1";
               series1->Name = L"Error";
               this->chart1->Series->Add(series1);
               this->chart1->Size = System::Drawing::Size(405, 306);
               this->chart1->TabIndex = 6;
               this->chart1->Text = L"chart1";
               // 
               // groupBox3
               // 
               this->groupBox3->Controls->Add(this->button3);
               this->groupBox3->Controls->Add(this->button2);
               this->groupBox3->Controls->Add(this->label6);
               this->groupBox3->Controls->Add(this->TrainTypeBox);
               this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
               this->groupBox3->Location = System::Drawing::Point(765, 288);
               this->groupBox3->Margin = System::Windows::Forms::Padding(2);
               this->groupBox3->Name = L"groupBox3";
               this->groupBox3->Padding = System::Windows::Forms::Padding(2);
               this->groupBox3->Size = System::Drawing::Size(220, 83);
               this->groupBox3->TabIndex = 7;
               this->groupBox3->TabStop = false;
               this->groupBox3->Text = L"Train";
               // 
               // button3
               // 
               this->button3->Location = System::Drawing::Point(117, 46);
               this->button3->Margin = System::Windows::Forms::Padding(2);
               this->button3->Name = L"button3";
               this->button3->Size = System::Drawing::Size(99, 37);
               this->button3->TabIndex = 10;
               this->button3->Text = L"Show Samples";
               this->button3->UseVisualStyleBackColor = true;
               this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
               // 
               // button2
               // 
               this->button2->Location = System::Drawing::Point(10, 46);
               this->button2->Margin = System::Windows::Forms::Padding(2);
               this->button2->Name = L"button2";
               this->button2->Size = System::Drawing::Size(103, 37);
               this->button2->TabIndex = 9;
               this->button2->Text = L"Train";
               this->button2->UseVisualStyleBackColor = true;
               this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
               // 
               // Form1
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(1200, 731);
               this->Controls->Add(this->groupBox3);
               this->Controls->Add(this->chart1);
               this->Controls->Add(this->textBox1);
               this->Controls->Add(this->label3);
               this->Controls->Add(this->groupBox2);
               this->Controls->Add(this->groupBox1);
               this->Controls->Add(this->pictureBox1);
               this->Controls->Add(this->menuStrip1);
               this->MainMenuStrip = this->menuStrip1;
               this->Name = L"Form1";
               this->Text = L"Form1";
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
               this->groupBox1->ResumeLayout(false);
               this->groupBox1->PerformLayout();
               this->groupBox2->ResumeLayout(false);
               this->groupBox2->PerformLayout();
               this->menuStrip1->ResumeLayout(false);
               this->menuStrip1->PerformLayout();
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
               this->groupBox3->ResumeLayout(false);
               this->groupBox3->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();

           }

           void draw_sample(int temp_x, int temp_y, int label) {
               Pen^ pen;
               switch (label) {
               case 0: pen = gcnew Pen(Color::Black, 3.0f); break;
               case 1: pen = gcnew Pen(Color::Red, 3.0f); break;
               case 2: pen = gcnew Pen(Color::Blue, 3.0f); break;
               case 3: pen = gcnew Pen(Color::DeepPink, 3.0f); break;
               case 4: pen = gcnew Pen(Color::Gold, 3.0f); break;
               case 5: pen = gcnew Pen(Color::Brown, 3.0f); break;
               case 6: pen = gcnew Pen(Color::ForestGreen, 3.0f); break;
               default: pen = gcnew Pen(Color::Black, 3.0f); break;
               }//switch
               pictureBox1->CreateGraphics()->DrawLine(pen, temp_x - 5, temp_y, temp_x + 5, temp_y);
               pictureBox1->CreateGraphics()->DrawLine(pen, temp_x, temp_y - 5, temp_x, temp_y + 5);
           }//draw_sample
#pragma endregion
    private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
        if (numClass == 0)
            MessageBox::Show("The Network Architecture should be first set up");
        else {
            float* x;
            x = new float[inputDim];
            int temp_x = (System::Convert::ToInt32(e->X));
            int temp_y = (System::Convert::ToInt32(e->Y));

            x[0] = float(temp_x - (pictureBox1->Width / 2));
            x[1] = float(pictureBox1->Height / 2 - temp_y);
            int label;
            int numLabel = Convert::ToInt32(ClassNoBox->Text);
            if (numLabel > numClass)
                MessageBox::Show("The class label cannot be greater than the maximum number of classes.");
            else {
                label = numLabel - 1; //Values start from 0
                if (numSample == 0) {
                    numSample = 1;
                    Samples = new float[numSample * inputDim];
                    targets = new float[numSample];
                    for (int i = 0; i < inputDim; i++)
                        Samples[i] = x[i];
                    targets[0] = float(label);
                }
                else {
                    numSample++;
                    Samples = Add_Data(Samples, numSample, x, inputDim);
                    targets = Add_Labels(targets, numSample, label);
                }

                draw_sample(temp_x, temp_y, label);
                label3->Text = "Samples Count: " + System::Convert::ToString(numSample);
            }
        }
    }
    private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        Pen^ pen = gcnew Pen(Color::Black, 3.0f);
        int center_width, center_height;
        center_width = (int)(pictureBox1->Width / 2);
        center_height = (int)(pictureBox1->Height / 2);
        e->Graphics->DrawLine(pen, center_width, 0, center_width, pictureBox1->Height);
        e->Graphics->DrawLine(pen, 0, center_height, pictureBox1->Width, center_height);
    }
    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

        //Input convertion
        numClass = Convert::ToInt32(ClassCountBox->Text);
        const int LAYER_COUNT = Convert::ToInt32(LayerCountBox->Text);
        int* NEURON_COUNT = new int[LAYER_COUNT];

        array<String^>^ StringArray = textBox2->Text->Split(' ');

        for (int i = 0; i < LAYER_COUNT; i++)
            NEURON_COUNT[i] = Convert::ToInt32(StringArray[i]);

        // Ağı sinir yapısı oluşturma
        model->InitializeModel(LAYER_COUNT, NEURON_COUNT, inputDim, numClass); // Init yerine InitializeModel

        button1->Text = " Network is Ready : ";
    }
    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
        // Batch Normalization
        float mean[2];
        float variance[2];
        float* normalizedSamples = Batch_Norm(Samples, numSample, inputDim, mean, variance);

        // Training
        int cycle = 0;
        if (TrainTypeBox->Text == "SGD")
            cycle = model->performSGDTraining(normalizedSamples, targets, numSample); // TrainSGD -> performSGDTraining
        else if (TrainTypeBox->Text == "SGDwMomentum")
            cycle = model->performSGDTrainingWithMomentum(normalizedSamples, targets, numSample); // TrainSGDwMoment -> performSGDTrainingWithMomentum
        else
            MessageBox::Show("Wrong Train Type");

        if (cycle == 0) {
            MessageBox::Show("Egitim yapilamadi");
            cycle = CYCLE_MAX;
        }
        label3->Text += "   Cycle:" + System::Convert::ToString(cycle);

        // Plotting chart
        for (int c = 0; c < cycle; c++)
            if (c % 10 == 0)
                chart1->Series["Error"]->Points->AddXY((int)c, model->errorHistory[c]);

        chart1->Refresh();

        // Area Normalization
        int counter = 0;
        for (int row = 0; row < HEIGHT; row++)				// Y-AXIS
            for (int col = 0; col < WIDTH; col++)			// X-AXIS
            {
                testData[counter * 2] = ((col + MINX) - mean[0]) / sqrt(variance[0]);		// X COORD
                testData[counter * 2 + 1] = ((MAXY - row) - mean[1]) / sqrt(variance[1]);   // Y COORD
                counter++;
            }

        // Testing
        model->ExecuteTest(testData, tag, AREASIZE); // Test -> ExecuteTest
        //Show Area
        Bitmap^ surface = gcnew Bitmap(WIDTH, HEIGHT);
        pictureBox1->Image = surface;

        for (int row = 0; row < HEIGHT; row++)
            for (int col = 0; col < WIDTH; col++)
            {
                System::Drawing::Color color;
                switch (tag[row * WIDTH + col]) {
                case 0: color = Color::FromArgb(192, 192, 192); break;
                case 1: color = Color::FromArgb(255, 130, 130); break;
                case 2: color = Color::FromArgb(130, 130, 255); break;
                case 3: color = Color::FromArgb(255, 130, 255); break;
                case 4: color = Color::FromArgb(255, 255, 130); break;
                case 5: color = Color::FromArgb(198, 159, 89); break;
                case 6: color = Color::LawnGreen; break;
                default: color = Color::Black; break;

                }//switch
                surface->SetPixel(col, row, color);
            }
        delete[] normalizedSamples;
    }

    private: System::Void readDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
        char** c = new char* [1];
        c[0] = "../Data/Samples.txt";
        std::ifstream file;
        int num, w, h, Dim;
        file.open(c[0]);
        if (file.is_open()) {
            file >> Dim >> w >> h >> num;
            textBox1->Text += "Dimension: " + Convert::ToString(Dim) + " w: " + Convert::ToString(w) +
                " h:" + Convert::ToString(h) + " numClass: " + Convert::ToString(num) + "\r\n";
            int inputDim = Dim;
            numClass = num;

            numSample = 0;
            float* x = new float[inputDim];

            while (!file.eof()) {
                if (numSample == 0) {
                    numSample = 1;
                    Samples = new float[numSample * inputDim];
                    targets = new float[numSample];

                    for (int i = 0; i < inputDim; i++) {
                        if (!(file >> Samples[i])) {
                            break;
                        }
                    }
                    if (!(file >> targets[0])) {
                        break;
                    }
                }
                else {
                    for (int i = 0; i < inputDim; i++) {
                        if (!(file >> x[i])) {
                            break;
                        }
                    }
                    int label;
                    if (!(file >> label)) {
                        break;
                    }

                    numSample++;
                    Samples = Add_Data(Samples, numSample, x, inputDim);
                    targets = Add_Labels(targets, numSample, label);
                }
            }

            delete[] x;
            file.close();

            for (int i = 0; i < numSample; i++) {
                int drawX = static_cast<int>(Samples[i * inputDim] + w);
                int drawY = static_cast<int>(h - Samples[i * inputDim + 1]);
                draw_sample(drawX, drawY, static_cast<int>(targets[i]));

                for (int j = 0; j < inputDim; j++)
                    textBox1->Text += Convert::ToString(Samples[i * inputDim + j]) + " ";
                textBox1->Text += Convert::ToString(targets[i]) + "\r\n";
            }

            label3->Text = "Samples Count: " + System::Convert::ToString(numSample);
            MessageBox::Show("Dosya basari ile okundu");
        }
        else {
            MessageBox::Show("Dosya acilamadi");
        }

        delete[]c;
    }
    private: System::Void saveDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
        if (numSample != 0) {
            char** c = new char* [1];
            c[0] = "../Data/Samples.txt";
            std::ofstream ofs(c[0]);
            if (!ofs.bad()) {
                ofs << inputDim << " " << pictureBox1->Width / 2 << " " << pictureBox1->Height / 2 << " " << numClass << std::endl;
                for (int i = 0; i < numSample; i++) {
                    for (int d = 0; d < inputDim; d++)
                        ofs << Samples[i * inputDim + d] << " ";
                    ofs << targets[i] << std::endl;
                }
                ofs.close();
            }
            else MessageBox::Show("Samples icin dosya acilamadi");
            delete[]c;
        }
        else MessageBox::Show("At least one sample should be given");
    }
    private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
        if (numSample != 0)
            for (int i = 0; i < numSample; i++) {
                Pen^ pen;
                switch ((int)targets[i]) {
                case 0: pen = gcnew Pen(Color::Black, 3.0f); break;
                case 1: pen = gcnew Pen(Color::Red, 3.0f); break;
                case 2: pen = gcnew Pen(Color::Blue, 3.0f); break;
                case 3: pen = gcnew Pen(Color::DeepPink, 3.0f); break;
                case 4: pen = gcnew Pen(Color::Gold, 3.0f); break;
                case 5: pen = gcnew Pen(Color::Brown, 3.0f); break;
                case 6: pen = gcnew Pen(Color::ForestGreen, 3.0f); break;
                default: pen = gcnew Pen(Color::Black, 3.0f); break;
                }
                int temp_x = static_cast<int>(Samples[i * 2] + (pictureBox1->Width / 2.0f));
                int temp_y = static_cast<int>((pictureBox1->Height / 2.0f) - Samples[i * 2 + 1]);
                pictureBox1->CreateGraphics()->DrawLine(pen, temp_x - 5, temp_y, temp_x + 5, temp_y);
                pictureBox1->CreateGraphics()->DrawLine(pen, temp_x, temp_y - 5, temp_x, temp_y + 5);
            }
    }
    private: System::Void readWeightsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
        model->InitializeFromWeightsFile(); // InitFromFile -> InitializeFromWeightsFile
    }
    private: System::Void saveWeightsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
        model->ExportWeights(); // SaveWeights -> ExportWeights
    }

    private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
    }
    private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e) {
    }
    };
}
