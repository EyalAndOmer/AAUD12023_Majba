#pragma once

namespace Gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for filtrovanie_window
	/// </summary>
	public ref class filtrovanie_window : public System::Windows::Forms::Form
	{
	public:
		filtrovanie_window(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~filtrovanie_window()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:


	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ comboBox3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(97, 19);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(224, 18);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(25, 24);
			this->label3->TabIndex = 4;
			this->label3->Text = L"je";
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"najviac", L"najmenej", L"menej", L"viac", L"medzi" });
			this->comboBox3->Location = System::Drawing::Point(255, 21);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(121, 21);
			this->comboBox3->TabIndex = 5;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(394, 23);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 6;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(607, 65);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 33);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Pridat filter";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(526, 66);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 33);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Zrusit";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &filtrovanie_window::button2_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(11, 17);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 24);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Hodnota";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(500, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(20, 24);
			this->label1->TabIndex = 9;
			this->label1->Text = L"a";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(526, 23);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 10;
			// 
			// filtrovanie_window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(688, 110);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->label2);
			this->Name = L"filtrovanie_window";
			this->Text = L"Vytvorenie filtra";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Hide();
}
};
}
