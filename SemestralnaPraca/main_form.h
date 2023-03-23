#pragma once
// Docasne riesenie
#include <libds/amt/implicit_sequence.h>
#include <msclr/marshal_cppstd.h>
#include "SearchData.h";

namespace Gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for main_form
	/// </summary>
	public ref class main_form : public System::Windows::Forms::Form
	{
	private:
		SearchData* myData;
	public:
		main_form(SearchData* data)
		{
			InitializeComponent();
			this->myData = data;
		}

	protected:
		
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~main_form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lFileSelect;
	protected:

	private: System::Windows::Forms::ComboBox^ cbFileSelect;
	private: System::Windows::Forms::Label^ lSearchAlgorithm;
	private: System::Windows::Forms::ComboBox^ cbSearchAlgorithm;
	private: System::Windows::Forms::Label^ lSearchBox;
	private: System::Windows::Forms::TextBox^ tbSearch;

	private: System::Windows::Forms::Button^ buttonSearch;
	private: System::Windows::Forms::ListView^ lvSearchOutput;
	private: System::Windows::Forms::ColumnHeader^ colLongName;
	private: System::Windows::Forms::ColumnHeader^ colShorterName;
	private: System::Windows::Forms::ColumnHeader^ colShortestName;
	private: System::Windows::Forms::ColumnHeader^ colCode;
	private: System::Windows::Forms::ColumnHeader^ ColNote;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ cbSelectField;

	protected:


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
			this->lFileSelect = (gcnew System::Windows::Forms::Label());
			this->cbFileSelect = (gcnew System::Windows::Forms::ComboBox());
			this->lSearchAlgorithm = (gcnew System::Windows::Forms::Label());
			this->cbSearchAlgorithm = (gcnew System::Windows::Forms::ComboBox());
			this->lSearchBox = (gcnew System::Windows::Forms::Label());
			this->tbSearch = (gcnew System::Windows::Forms::TextBox());
			this->buttonSearch = (gcnew System::Windows::Forms::Button());
			this->lvSearchOutput = (gcnew System::Windows::Forms::ListView());
			this->colLongName = (gcnew System::Windows::Forms::ColumnHeader());
			this->colShorterName = (gcnew System::Windows::Forms::ColumnHeader());
			this->colShortestName = (gcnew System::Windows::Forms::ColumnHeader());
			this->colCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->ColNote = (gcnew System::Windows::Forms::ColumnHeader());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->cbSelectField = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// lFileSelect
			// 
			this->lFileSelect->AutoSize = true;
			this->lFileSelect->Location = System::Drawing::Point(22, 23);
			this->lFileSelect->Name = L"lFileSelect";
			this->lFileSelect->Size = System::Drawing::Size(182, 13);
			this->lFileSelect->TabIndex = 0;
			this->lFileSelect->Text = L"Vyberte subor nad ktorym vyhladavat";
			// 
			// cbFileSelect
			// 
			this->cbFileSelect->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbFileSelect->FormattingEnabled = true;
			this->cbFileSelect->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Kraje", L"Okresy", L"Obce" });
			this->cbFileSelect->Location = System::Drawing::Point(25, 40);
			this->cbFileSelect->Name = L"cbFileSelect";
			this->cbFileSelect->Size = System::Drawing::Size(179, 21);
			this->cbFileSelect->TabIndex = 1;
			// 
			// lSearchAlgorithm
			// 
			this->lSearchAlgorithm->Location = System::Drawing::Point(270, 24);
			this->lSearchAlgorithm->Name = L"lSearchAlgorithm";
			this->lSearchAlgorithm->Size = System::Drawing::Size(179, 13);
			this->lSearchAlgorithm->TabIndex = 0;
			this->lSearchAlgorithm->Text = L"Vyberte vyhladaci algoritmus";
			this->lSearchAlgorithm->Click += gcnew System::EventHandler(this, &main_form::label2_Click);
			// 
			// cbSearchAlgorithm
			// 
			this->cbSearchAlgorithm->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbSearchAlgorithm->FormattingEnabled = true;
			this->cbSearchAlgorithm->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Zo zaciatku", L"V celom slove" });
			this->cbSearchAlgorithm->Location = System::Drawing::Point(270, 40);
			this->cbSearchAlgorithm->Name = L"cbSearchAlgorithm";
			this->cbSearchAlgorithm->Size = System::Drawing::Size(179, 21);
			this->cbSearchAlgorithm->TabIndex = 2;
			this->cbSearchAlgorithm->SelectedIndexChanged += gcnew System::EventHandler(this, &main_form::cbSearchAlgorithm_SelectedIndexChanged);
			// 
			// lSearchBox
			// 
			this->lSearchBox->AutoSize = true;
			this->lSearchBox->Location = System::Drawing::Point(22, 76);
			this->lSearchBox->Name = L"lSearchBox";
			this->lSearchBox->Size = System::Drawing::Size(157, 13);
			this->lSearchBox->TabIndex = 3;
			this->lSearchBox->Text = L"Zadajte string pre porovnavanie";
			// 
			// tbSearch
			// 
			this->tbSearch->Location = System::Drawing::Point(25, 93);
			this->tbSearch->Name = L"tbSearch";
			this->tbSearch->Size = System::Drawing::Size(183, 20);
			this->tbSearch->TabIndex = 4;
			// 
			// buttonSearch
			// 
			this->buttonSearch->Location = System::Drawing::Point(201, 93);
			this->buttonSearch->Name = L"buttonSearch";
			this->buttonSearch->Size = System::Drawing::Size(75, 20);
			this->buttonSearch->TabIndex = 5;
			this->buttonSearch->Text = L"Vyhladat";
			this->buttonSearch->UseVisualStyleBackColor = true;
			this->buttonSearch->Click += gcnew System::EventHandler(this, &main_form::buttonSearch_Click);
			// 
			// lvSearchOutput
			// 
			this->lvSearchOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lvSearchOutput->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->colLongName,
					this->colShorterName, this->colShortestName, this->colCode, this->ColNote
			});
			this->lvSearchOutput->HideSelection = false;
			this->lvSearchOutput->Location = System::Drawing::Point(25, 119);
			this->lvSearchOutput->Name = L"lvSearchOutput";
			this->lvSearchOutput->Size = System::Drawing::Size(739, 130);
			this->lvSearchOutput->TabIndex = 6;
			this->lvSearchOutput->UseCompatibleStateImageBehavior = false;
			this->lvSearchOutput->View = System::Windows::Forms::View::Details;
			// 
			// colLongName
			// 
			this->colLongName->Text = L"Cely nazov";
			this->colLongName->Width = 200;
			// 
			// colShorterName
			// 
			this->colShorterName->Text = L"Skrateny nazov";
			this->colShorterName->Width = 200;
			// 
			// colShortestName
			// 
			this->colShortestName->Text = L"Kratky nazov";
			this->colShortestName->Width = 119;
			// 
			// colCode
			// 
			this->colCode->Text = L"Kod";
			this->colCode->Width = 120;
			// 
			// ColNote
			// 
			this->ColNote->Text = L"Poznamka";
			this->ColNote->Width = 80;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(496, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(184, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Vyberte stlpec nad ktorym vyhladavat";
			// 
			// cbSelectField
			// 
			this->cbSelectField->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(5) {
				L"Cele meno", L"Skratene meno",
					L"Kratke meno", L"Kod", L"Poznamka"
			});
			this->cbSelectField->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbSelectField->FormattingEnabled = true;
			this->cbSelectField->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Cele meno", L"Skratene meno", L"Kratke meno",
					L"Kod", L"Poznamka"
			});
			this->cbSelectField->Location = System::Drawing::Point(499, 39);
			this->cbSelectField->Name = L"cbSelectField";
			this->cbSelectField->Size = System::Drawing::Size(181, 21);
			this->cbSelectField->TabIndex = 8;
			// 
			// main_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(776, 261);
			this->Controls->Add(this->cbSelectField);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->lvSearchOutput);
			this->Controls->Add(this->buttonSearch);
			this->Controls->Add(this->tbSearch);
			this->Controls->Add(this->lSearchBox);
			this->Controls->Add(this->cbSearchAlgorithm);
			this->Controls->Add(this->lSearchAlgorithm);
			this->Controls->Add(this->cbFileSelect);
			this->Controls->Add(this->lFileSelect);
			this->Name = L"main_form";
			this->Text = L"AAUD1 Semestralna Praca, made by Maros Majba 2023";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void cbSearchAlgorithm_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void buttonSearch_Click(System::Object^ sender, System::EventArgs^ e) {

	// Definicia indexov pre comboboxy, potrebne pre kontrolu ci je nieco zvolene

	int cbFileSelectIndex = cbFileSelect->SelectedIndex;
	int cbSearchAlgorithmIndex = cbSearchAlgorithm->SelectedIndex;
	int cbFieldSelectIndex = cbFileSelect->SelectedIndex;

	bool cbFileSelected = false;
	bool cbSearchAlgorithmSelected = false;
	bool tbSearchFilled = false;
	bool cbFieldSelected = false;

	String^ tbSearchValue = tbSearch->Text;

	if (cbFieldSelectIndex == -1)
	{
		MessageBox::Show("Vyberte pole nad ktorym chcete porovnavat.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		cbFieldSelected = false;
	} else
	{
		cbFieldSelected = true;
	}

	if (String::IsNullOrEmpty(tbSearchValue))
	{
		MessageBox::Show("Zadajte text na porovnanie.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		tbSearchFilled = false;
	} else
	{
		tbSearchFilled = true;
	}

	if (cbFileSelectIndex == -1)
	{
		MessageBox::Show("Zvolte subor nad ktorym chcete vyhladavat.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		cbFileSelected = false;
	} else
	{
		cbFileSelected = true;
	}

	if (cbSearchAlgorithmIndex == -1)
	{
		MessageBox::Show("Zvolte algoritmus pomocou ktoreho chcete vyhladavat.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		cbSearchAlgorithmSelected = false;
	} else
	{
		cbSearchAlgorithmSelected = true;
	}

	if (cbFileSelected && cbSearchAlgorithmSelected && cbFieldSelected && tbSearchFilled)
	{
		// Zmazanie list view itemov
		lvSearchOutput->Items->Clear();

		// Ziskanie zadanych hodnot
		std::string selectedFile = msclr::interop::marshal_as<std::string>(cbFileSelect->SelectedItem->ToString());
		std::string selectedAlgorithm = msclr::interop::marshal_as<std::string>(cbSearchAlgorithm->SelectedItem->ToString());
		std::string selectedField = msclr::interop::marshal_as<std::string>(cbSelectField->SelectedItem->ToString());
		std::string substring = msclr::interop::marshal_as<std::string>(tbSearchValue);

		auto selectedAlgorithmLambda = selectedAlgorithm == "Zo zaciatku" ? myData->search_from_beginning : myData->search_substring;
		std::vector<CSVElement*> selectedFileData;


		// Postupne ziskavanie a testovanie zapisanych hodnot
		if (selectedFile == "Obce")
		{
			selectedFileData = myData->obce;
		} else if (selectedFile == "Okresy")
		{
			selectedFileData = myData->okresy;
		} else {
			selectedFileData = myData->kraje;
		}

		std::string(CSVElement:: * selectedFieldMethod)();


		if (selectedField == "Cele meno")
		{
			selectedFieldMethod = &CSVElement::get_official_title;
		} else if (selectedField == "Skratene meno")
		{
			selectedFieldMethod = &CSVElement::get_medium_title;
		} else if (selectedField == "Kratke meno")
		{
			selectedFieldMethod = &CSVElement::get_short_title;
		} else if (selectedField == "Kod")
		{
			selectedFieldMethod = &CSVElement::get_code;
		} else {
			selectedFieldMethod = &CSVElement::get_note;
		}

		// Zavolanie samotnej search metody
		myData->searcher.search(substring, selectedAlgorithmLambda, selectedFieldMethod, selectedFileData.begin(), selectedFileData.end());

		// Vypis ziskanych elementov do listview
		std::vector<CSVElement*> outputElements = myData->searcher.getOutput();
		for (auto item: outputElements)
		{
			ListViewItem^ listViewItem = gcnew ListViewItem(gcnew String(item->get_official_title().c_str()));
			listViewItem->SubItems->Add(gcnew String(item->get_medium_title().c_str()));
			listViewItem->SubItems->Add(gcnew String(item->get_short_title().c_str()));
			listViewItem->SubItems->Add(gcnew String(item->get_code().c_str()));
			listViewItem->SubItems->Add(gcnew String(item->get_note().c_str()));
			lvSearchOutput->Items->Add(listViewItem);
		}
	}
}
};
}
