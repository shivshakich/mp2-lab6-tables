#pragma once

#include <msclr/marshal_cppstd.h>
#include <string>
#include <fstream>

#include "../../include/tscantable.h"	// неупорядоченная таблица
#include "../../include/tsorttable.h"	// упорядоченная таблица
#include "../../include/tarrayhash.h"	// хэш-таблица (массив)
#include "../../include/tlisthash.h"	// хэш-таблица (список)
#include "../../include/ttreetable.h"	// дерево поиска
#include "../../include/tavltree.h"		// АВЛ-дерево

namespace CppWinForm1 {

	const std::string fileName = "text_file.txt";
	const std::string tmpFileName = "tmp_file.txt";

	const std::string ABC = "0123456789"; //abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMOPQRSTUVWXYZ";
	const int LEN_ABC = ABC.length();

	std::string GetRandKey(int _len = 10) {
		std::string res = "";

		for (int i = 0; i < _len; ++i) {
			res += ABC[rand() % LEN_ABC];
		}

		return res;
	}

	TPolynom GetRandVal(int _len = 3) {
		TPolynom pol;

		const int MIN = pol.GetMINDEGREE();
		const int MAX = pol.GetMAXDEGREE();

		for (int i = 0; i < _len; ++i) {
			double c = (rand() % 21) - 10;	// -10...+10
			int x = (rand() % (MAX - MIN)) - MIN;
			int y = (rand() % (MAX - MIN)) - MIN;
			int z = (rand() % (MAX - MIN)) - MIN;

			pol += TMonom{ c, x, y, z };
		}
			

		return pol;
	}

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			tab = new TScanTable;

			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (tab) {
				TTable* pDel = tab;
				tab = nullptr;
				delete pDel;
			}

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;



	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::RadioButton^ radioButton6;

	private: System::Windows::Forms::RadioButton^ radioButton4;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Label^ label7;








	protected:


	private: System::Windows::Forms::RadioButton^ radioButton5;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ textBox6;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		
		TTable* tab;
	private: System::Windows::Forms::DataGridViewButtonColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::Button^ button6;



		   int count;

		void RefreshDataGridView() {
			dataGridView1->Rows->Clear();

			int i = 0;
			for (tab->Reset(); !tab->IsEnd(); tab->GoNext()) {
				dataGridView1->Rows->Add();
				String^ s_key = gcnew String(tab->GetKey().c_str());
				String^ s_val = gcnew String(tab->GetValue().ToString().c_str());
				dataGridView1->Rows[i]->Cells[1]->Value = s_key;
				dataGridView1->Rows[i]->Cells[2]->Value = s_val;

				++i;
			}
		}

		void RefreshEff() {
			String^ s_eff = gcnew String(std::to_string(tab->GetEff()).c_str());
			textBox1->Text = s_eff;
		}

		void PrintResult(const std::string& _str) {
			String^ s_res = gcnew String(_str.c_str());
			textBox2->Text = s_res;
		}

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Column1,
					this->Column2, this->Column3
			});
			this->dataGridView1->Location = System::Drawing::Point(13, 14);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(900, 400);
			this->dataGridView1->TabIndex = 0;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView1_CellContentClick);
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"[DELETE]";
			this->Column1->MinimumWidth = 6;
			this->Column1->Name = L"Column1";
			this->Column1->Width = 75;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"KEY";
			this->Column2->MinimumWidth = 6;
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Width = 125;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"VALUE";
			this->Column3->MinimumWidth = 6;
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			this->Column3->Width = 600;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(133, 417);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 420);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(114, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Эффективность";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(240, 420);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(77, 16);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Результат";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(323, 417);
			this->textBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(440, 22);
			this->textBox2->TabIndex = 4;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::White;
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->radioButton6);
			this->panel1->Controls->Add(this->radioButton5);
			this->panel1->Controls->Add(this->radioButton4);
			this->panel1->Controls->Add(this->radioButton3);
			this->panel1->Controls->Add(this->radioButton2);
			this->panel1->Controls->Add(this->radioButton1);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Location = System::Drawing::Point(16, 446);
			this->panel1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(301, 295);
			this->panel1->TabIndex = 5;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(4, 281);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(102, 16);
			this->label4->TabIndex = 7;
			this->label4->Text = L"КЧ-дерева нет";
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Location = System::Drawing::Point(7, 159);
			this->radioButton6->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(107, 20);
			this->radioButton6->TabIndex = 6;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"АВЛ-дерево";
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(7, 132);
			this->radioButton5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(126, 20);
			this->radioButton5->TabIndex = 5;
			this->radioButton5->TabStop = true;
			this->radioButton5->Text = L"Дерево поиска";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(7, 105);
			this->radioButton4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(168, 20);
			this->radioButton4->TabIndex = 4;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"Хэш-таблица (список)";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(7, 78);
			this->radioButton3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(170, 20);
			this->radioButton3->TabIndex = 3;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Хэш-таблица (массив)";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(7, 50);
			this->radioButton2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(189, 20);
			this->radioButton2->TabIndex = 2;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Упорядоченная таблица";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(7, 25);
			this->radioButton1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(206, 20);
			this->radioButton1->TabIndex = 1;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Неупорядоченная таблица";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(4, 4);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 16);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Тип таблицы";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(323, 446);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(440, 23);
			this->button1->TabIndex = 6;
			this->button1->Text = L"Создать таблицу с заданным количеством записей";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(324, 475);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"В файл";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(405, 475);
			this->button3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(85, 23);
			this->button3->TabIndex = 8;
			this->button3->Text = L"Из файла";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(469, 505);
			this->textBox3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(187, 22);
			this->textBox3->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(325, 505);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(130, 16);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Полное имя файла";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(661, 689);
			this->button4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(101, 23);
			this->button4->TabIndex = 11;
			this->button4->Text = L"Поиск";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(325, 694);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(41, 16);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Ключ";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(469, 690);
			this->textBox4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(187, 22);
			this->textBox4->TabIndex = 13;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(469, 719);
			this->textBox5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(187, 22);
			this->textBox5->TabIndex = 14;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(661, 718);
			this->button5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(101, 23);
			this->button5->TabIndex = 15;
			this->button5->Text = L"Добавить\r\n";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(325, 724);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(66, 16);
			this->label7->TabIndex = 16;
			this->label7->Text = L"Полином";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(325, 532);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(105, 16);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Число записей";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(469, 532);
			this->textBox6->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(187, 22);
			this->textBox6->TabIndex = 18;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(919, 14);
			this->textBox7->Multiline = true;
			this->textBox7->Name = L"textBox7";
			this->textBox7->ReadOnly = true;
			this->textBox7->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox7->Size = System::Drawing::Size(381, 727);
			this->textBox7->TabIndex = 19;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(769, 446);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(144, 23);
			this->button6->TabIndex = 20;
			this->button6->Text = L"Печать";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::PaleGoldenrod;
			this->ClientSize = System::Drawing::Size(1312, 753);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->dataGridView1);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	// [Создать таблицу с заданным количеством записей]

	std::string err = "";

	std::string _key_ = "~";

	try {
		std::string strCount = msclr::interop::marshal_as<std::string>(textBox6->Text);

		err = "Не удалось прочитать число записей";
		std::string tabType = "";

		size_t len = 0;
		int count = std::stoi(strCount, &len);

		if (len != strCount.length()) throw "";

		err = "Введённое число выходит за границу допустимых значений";
		if (count > tab->GetTabMaxSize()) throw "";

		delete tab;

		err = "Не был выбран radio button";
		if (radioButton1->Checked)
			tab = new TScanTable(count), tabType = "TScanTable";
		else if (radioButton2->Checked)
			tab = new TSortTable, tabType = "TSortTable";
		else if (radioButton3->Checked)
			tab = new TArrayHash, tabType = "TArrayHash";
		else if (radioButton4->Checked)
			tab = new TListHash, tabType = "TListHash";
		else if (radioButton5->Checked)
			tab = new TTreeTable, tabType = "TTreeTable";
		else if (radioButton6->Checked)
			tab = new TAVLTree, tabType = "TAVLTree";
		else throw "";

		err = "не удалось вставить запись";

		for (int i = 0; i < count; ++i) {
			err += " " + std::to_string(i);
			tab->InsRecord(GetRandKey(), GetRandVal());
		}

		//String^ s_datacount = gcnew String(std::to_string(tab->GetDataCount()).c_str());
		//textBox6->Text = s_datacount;

		RefreshDataGridView();
		RefreshEff();
		PrintResult("Создана новая таблица типа " + tabType + " из " + std::to_string(tab->GetDataCount()) + " записей");
	}
	catch (...) {
		String^ s = gcnew String(err.c_str());
		System::Windows::Forms::MessageBox::Show(s);
		PrintResult("ОШИБКА: не удалось создать таблицу");
	}
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	// [поиск]

	std::string err = "Ошибка при поиске по ключу";

	try {
		std::string strKey = msclr::interop::marshal_as<std::string>(textBox4->Text);

		tab->ClearEff();
		bool res = tab->FindRecord(strKey);
		
		std::string strRes = res ? "Ключ найден" : "Ключ не найден";
		RefreshEff();
		PrintResult(strRes);
	}
	catch (...) {
		String^ s_err = gcnew String(err.c_str());
		System::Windows::Forms::MessageBox::Show(s_err);
	}
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	// [добавить]

	std::string err = "Ошибка при добавлении новой записи";

	try {
		std::string strKey = msclr::interop::marshal_as<std::string>(textBox4->Text);
		std::string strVal = msclr::interop::marshal_as<std::string>(textBox5->Text);


		tab->ClearEff();
		err = "Программа не смогла вставить запись в таблицу";
		tab->InsRecord(strKey, TPolynom(strVal));

		std::string strRes = "Программа смогла вставить запись в таблицу";
		RefreshDataGridView();
		RefreshEff();
		PrintResult(strRes);
	}
	catch (...) {
		String^ s_err = gcnew String(err.c_str());
		System::Windows::Forms::MessageBox::Show(s_err);
	}
}
private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	// [удалить]

	std::string strRes = "Вызов Delete не произошёл";

	int _row = dataGridView1->CurrentCell->RowIndex;

	if (_row < tab->GetDataCount()) {

		//int _column = dataGridView1->CurrentCell->ColumnIndex;
		//PrintResult(std::to_string(_row) + ' ' + std::to_string(_column));

		String^ s_key = dataGridView1->Rows[_row]->Cells[1]->Value->ToString();
		std::string _key = msclr::interop::marshal_as<std::string>(s_key);

		int oldDataCount = tab->GetDataCount();

		tab->ClearEff();
		tab->DelRecord(_key);

		int newDataCount = tab->GetDataCount();

		RefreshDataGridView();
		RefreshEff();

		strRes = oldDataCount == newDataCount ? "Число записей в таблице не изменилось" :
			"Запись была удалена";
	}

	PrintResult(strRes);
}
private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	//[В файл]

	std::ofstream out;
	out.open(fileName);

	if (out.is_open())
		out << *tab;

	out.close();

	PrintResult("Таблица была сохранена в файл");
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	//[Из файла]
	std::string err = "";
	std::string tabType = "";

	try {
		if (tab) {
			TTable* pDel = tab;
			tab = nullptr;
			delete pDel;
		}

		err = "Не был выбран radio button";

		if (radioButton1->Checked)
			tab = new TScanTable(), tabType = "TScanTable";
		else if (radioButton2->Checked)
			tab = new TSortTable(), tabType = "TSortTable";
		else if (radioButton3->Checked)
			tab = new TArrayHash(), tabType = "TArrayHash";
		else if (radioButton4->Checked)
			tab = new TListHash(), tabType = "TListHash";
		else if (radioButton5->Checked)
			tab = new TTreeTable(), tabType = "TTreeTable";
		else if (radioButton6->Checked)
			tab = new TAVLTree(), tabType = "TAVLTree";
		else throw "";
		tab->ClearEff();

		std::string line;
		err = "не удалось прочитать строку";

		std::ifstream in(fileName);

		int i = 0;
		if (in.is_open())
			while (std::getline(in, line)) {
				err += " " + std::to_string(i);

				int pos = 0;
				while (pos < line.size() && line[pos] != ' ') ++pos;
				// от 0 до pos-1 читаем имя 

				if (pos <= 0) throw "";

				std::string name = line.substr(0, pos);
				TPolynom pol(line.substr(pos));

				tab->InsRecord(name, TPolynom(pol));

				++i;
			}

		in.close();
		
		RefreshDataGridView();
		RefreshEff();
		PrintResult("Таблица была прочитана из файла");
	}
	catch (...) {
		String^ s_err = gcnew String(err.c_str());
		System::Windows::Forms::MessageBox::Show(s_err);
	}
}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	// [Печать] : button6, textBox7

	// запись в файл

	std::ofstream out;
	out.open(tmpFileName);

	if (out.is_open())
		tab->Print(out);

	out.close();

	// чтение из файла в textBox

	textBox7->Text = "";

	std::string line;

	std::ifstream in(tmpFileName);

	if (in.is_open())
		while (std::getline(in, line)) {
			String^ s = gcnew String(line.c_str());
			textBox7->AppendText(s);
			textBox7->Text += "\r\n";
		}

	in.close();
}
};
}