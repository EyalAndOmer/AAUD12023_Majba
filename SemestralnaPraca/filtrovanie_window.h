#pragma once
#include "CSVElement.h"
#include "Filter.h"

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
	private:
		Filter* selectedFilter = nullptr; // Vybrany filter
	public:
		filtrovanie_window(void)
		{
			InitializeComponent();

			lbTwoSideFilter->Hide();
			tbConditionValue2->Hide();
		}

		Filter* getFilter()
		{
			return selectedFilter;
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
			
			delete selectedFilter;
		}
	private: System::Windows::Forms::ComboBox^ cbFilterSelectValue;
	protected:

	protected:



	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ComboBox^ cbFilterSelectCondition;
	private: System::Windows::Forms::TextBox^ tbConditionValue1;



	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ lbTwoSideFilter;

	private: System::Windows::Forms::TextBox^ tbConditionValue2;



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
			this->cbFilterSelectValue = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->cbFilterSelectCondition = (gcnew System::Windows::Forms::ComboBox());
			this->tbConditionValue1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->lbTwoSideFilter = (gcnew System::Windows::Forms::Label());
			this->tbConditionValue2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// cbFilterSelectValue
			// 
			this->cbFilterSelectValue->FormattingEnabled = true;
			this->cbFilterSelectValue->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Ziadne vzdelanie mlady", L"Zakladne vzdelanie",
					L"Stredne vzdelanie bez maturity", L"Stredne vzdelanie s maturitou", L"Vyssie vzdelanie", L"Vysokoskolske vzdelanie", L"Ziadne vzdelanie stary"
			});
			this->cbFilterSelectValue->Location = System::Drawing::Point(97, 19);
			this->cbFilterSelectValue->Name = L"cbFilterSelectValue";
			this->cbFilterSelectValue->Size = System::Drawing::Size(121, 21);
			this->cbFilterSelectValue->TabIndex = 3;
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
			// cbFilterSelectCondition
			// 
			this->cbFilterSelectCondition->FormattingEnabled = true;
			this->cbFilterSelectCondition->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"viac", L"menej", L"najviac", L"najmenej",
					L"medzi"
			});
			this->cbFilterSelectCondition->Location = System::Drawing::Point(255, 21);
			this->cbFilterSelectCondition->Name = L"cbFilterSelectCondition";
			this->cbFilterSelectCondition->Size = System::Drawing::Size(121, 21);
			this->cbFilterSelectCondition->TabIndex = 5;
			this->cbFilterSelectCondition->SelectedIndexChanged += gcnew System::EventHandler(this, &filtrovanie_window::cbFilterSelectCondition_SelectedIndexChanged);
			// 
			// tbConditionValue1
			// 
			this->tbConditionValue1->Location = System::Drawing::Point(394, 23);
			this->tbConditionValue1->Name = L"tbConditionValue1";
			this->tbConditionValue1->Size = System::Drawing::Size(100, 20);
			this->tbConditionValue1->TabIndex = 6;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(607, 65);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 33);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Pridat filter";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &filtrovanie_window::button1_Click);
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
			// lbTwoSideFilter
			// 
			this->lbTwoSideFilter->AutoSize = true;
			this->lbTwoSideFilter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lbTwoSideFilter->Location = System::Drawing::Point(500, 19);
			this->lbTwoSideFilter->Name = L"lbTwoSideFilter";
			this->lbTwoSideFilter->Size = System::Drawing::Size(20, 24);
			this->lbTwoSideFilter->TabIndex = 9;
			this->lbTwoSideFilter->Text = L"a";
			// 
			// tbConditionValue2
			// 
			this->tbConditionValue2->Location = System::Drawing::Point(526, 23);
			this->tbConditionValue2->Name = L"tbConditionValue2";
			this->tbConditionValue2->Size = System::Drawing::Size(100, 20);
			this->tbConditionValue2->TabIndex = 10;
			// 
			// filtrovanie_window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(688, 110);
			this->Controls->Add(this->tbConditionValue2);
			this->Controls->Add(this->lbTwoSideFilter);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->tbConditionValue1);
			this->Controls->Add(this->cbFilterSelectCondition);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->cbFilterSelectValue);
			this->Controls->Add(this->label2);
			this->Name = L"filtrovanie_window";
			this->Text = L"Vytvorenie filtra";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	int (CSVElement:: * selectedMethod)(); // zvolena metoda
	int upperBound;
	int lowerBound;
	std::string attribute_name;


	if (cbFilterSelectValue->SelectedIndex == -1) {
		MessageBox::Show("Vyberte metodu filtra.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else if(cbFilterSelectCondition->SelectedIndex == -1) {
		MessageBox::Show("Vyberte condition filtra.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else if (String::IsNullOrEmpty(tbConditionValue1->Text)) {
		MessageBox::Show("Zadajte hodnotu dolnej hranice.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else if (String::IsNullOrEmpty(tbConditionValue2->Text) && tbConditionValue2->Visible) {
		MessageBox::Show("Zadajte hodnotu hornej hranice.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else {
		// Vyber zvolenej metody

		switch(cbFilterSelectValue->SelectedIndex)
		{
		case 0:
			selectedMethod = &CSVElement::get_no_education_young;
			attribute_name = "Ziadne vzdelanie mlady";
			break;
		case 1:
			selectedMethod = &CSVElement::get_basic_education;
			attribute_name = "Zakladne vzdelanie";
			break;
		case 2:
			selectedMethod = &CSVElement::get_high_lower_education;
			attribute_name = "Stredne vzdelanie bez maturity";
			break;
		case 3:
			selectedMethod = &CSVElement::get_high_higher_education;
			attribute_name = "Stredne vzdelanie s maturitou";
			break;
		case 4:
			selectedMethod = &CSVElement::get_higher_education;
			attribute_name = "Vyssie vzdelanie";
			break;
		case 5:
			selectedMethod = &CSVElement::get_university_education;
			attribute_name = "Vysokoskolske vzdelanie";
			break;
		case 6:
			selectedMethod = &CSVElement::get_no_education_old;
			attribute_name = "Ziadne vzdelanie stary";
			break;
		case 7:
			selectedMethod = &CSVElement::get_not_clarified;
			attribute_name = "Neuvedene";
			break;
		}

		lowerBound = System::Convert::ToInt32(tbConditionValue1->Text);

		if (!String::IsNullOrEmpty(tbConditionValue2->Text))
		{
			upperBound = System::Convert::ToInt32(tbConditionValue2->Text);
		}


		switch(cbFilterSelectCondition->SelectedIndex)
		{
		case 0:
			this->selectedFilter = new FilterMoreThan(lowerBound, selectedMethod, attribute_name);
			break;
		case 1:
			this->selectedFilter = new FilterLessThan(lowerBound, selectedMethod, attribute_name);
			break;
		case 2:
			this->selectedFilter = new FilterMax(lowerBound, selectedMethod, attribute_name);
			break;
		case 3:
			this->selectedFilter = new FilterMin(lowerBound, selectedMethod, attribute_name);
			break;
		case 4:
			this->selectedFilter = new FilterBetween(lowerBound, upperBound, selectedMethod, attribute_name);
			break;
		}

		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
}
private: System::Void cbFilterSelectCondition_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	switch (cbFilterSelectCondition->SelectedIndex)
	{
	case 0:
		lbTwoSideFilter->Hide();
		tbConditionValue2->Hide();
		break;
	case 1:
		lbTwoSideFilter->Hide();
		tbConditionValue2->Hide();
		break;
	case 2:
		lbTwoSideFilter->Hide();
		tbConditionValue2->Hide();
		break;
	case 3:
		lbTwoSideFilter->Hide();
		tbConditionValue2->Hide();
		break;
	case 4:
		lbTwoSideFilter->Show();
		tbConditionValue2->Show();
		break;
	}
}
};
}
