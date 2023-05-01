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
		main_form(void)
		{
			InitializeComponent();
			this->myData = new SearchData();
			writeDataToComboBox(cbSonsList, *myData->hierarchy_current_block->sons_);
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"kraj", "okres", "obec"});

			// Pri starte nepovol pohyb po hierarchii, kedze je zvoleny tab 1
			cbSonsList->Enabled = false;
			btLowerLevel->Enabled = false;
			btUpperLevel->Enabled = false;
		}

	protected:
		
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~main_form()
		{
			delete myData;
			if (components)
			{
				delete components;
			}
		}

	protected:


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
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ lbCurrentLevel;
	private: System::Windows::Forms::Button^ btUpperLevel;


	private: System::Windows::Forms::ComboBox^ cbSonsList;
	private: System::Windows::Forms::Button^ btLowerLevel;
	private: System::Windows::Forms::Label^ lbUCType;
	private: System::Windows::Forms::ComboBox^ cbUCType;

	private: System::Windows::Forms::Button^ btUCType;
	private: System::Windows::Forms::TabControl^ mainTabs;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::ComboBox^ cbUCType2;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ tbUCName;
	private: System::Windows::Forms::ColumnHeader^ colNoEducationYoung;
	private: System::Windows::Forms::ColumnHeader^ colBasicEducation;
	private: System::Windows::Forms::ColumnHeader^ colHighNotFinishedEducation;
	private: System::Windows::Forms::ColumnHeader^ colHighEducation;
	private: System::Windows::Forms::ColumnHeader^ colHigherEducation;
	private: System::Windows::Forms::ColumnHeader^ colUniversityEducation;
	private: System::Windows::Forms::ColumnHeader^ colNoEducation;
	private: System::Windows::Forms::CheckBox^ checkBox1;











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
			this->colNoEducationYoung = (gcnew System::Windows::Forms::ColumnHeader());
			this->colBasicEducation = (gcnew System::Windows::Forms::ColumnHeader());
			this->colHighNotFinishedEducation = (gcnew System::Windows::Forms::ColumnHeader());
			this->colHighEducation = (gcnew System::Windows::Forms::ColumnHeader());
			this->colHigherEducation = (gcnew System::Windows::Forms::ColumnHeader());
			this->colUniversityEducation = (gcnew System::Windows::Forms::ColumnHeader());
			this->colNoEducation = (gcnew System::Windows::Forms::ColumnHeader());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->cbSelectField = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->lbCurrentLevel = (gcnew System::Windows::Forms::Label());
			this->btUpperLevel = (gcnew System::Windows::Forms::Button());
			this->cbSonsList = (gcnew System::Windows::Forms::ComboBox());
			this->btLowerLevel = (gcnew System::Windows::Forms::Button());
			this->lbUCType = (gcnew System::Windows::Forms::Label());
			this->cbUCType = (gcnew System::Windows::Forms::ComboBox());
			this->btUCType = (gcnew System::Windows::Forms::Button());
			this->mainTabs = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->tbUCName = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->cbUCType2 = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->mainTabs->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// lSearchAlgorithm
			// 
			this->lSearchAlgorithm->Location = System::Drawing::Point(299, 59);
			this->lSearchAlgorithm->Name = L"lSearchAlgorithm";
			this->lSearchAlgorithm->Size = System::Drawing::Size(179, 13);
			this->lSearchAlgorithm->TabIndex = 0;
			this->lSearchAlgorithm->Text = L"Vyberte vyhladaci algoritmus";
			// 
			// cbSearchAlgorithm
			// 
			this->cbSearchAlgorithm->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbSearchAlgorithm->FormattingEnabled = true;
			this->cbSearchAlgorithm->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Zo zaciatku", L"V celom slove" });
			this->cbSearchAlgorithm->Location = System::Drawing::Point(299, 74);
			this->cbSearchAlgorithm->Name = L"cbSearchAlgorithm";
			this->cbSearchAlgorithm->Size = System::Drawing::Size(179, 21);
			this->cbSearchAlgorithm->TabIndex = 2;
			// 
			// lSearchBox
			// 
			this->lSearchBox->AutoSize = true;
			this->lSearchBox->Location = System::Drawing::Point(524, 8);
			this->lSearchBox->Name = L"lSearchBox";
			this->lSearchBox->Size = System::Drawing::Size(157, 13);
			this->lSearchBox->TabIndex = 3;
			this->lSearchBox->Text = L"Zadajte string pre porovnavanie";
			// 
			// tbSearch
			// 
			this->tbSearch->Location = System::Drawing::Point(527, 25);
			this->tbSearch->Name = L"tbSearch";
			this->tbSearch->Size = System::Drawing::Size(183, 20);
			this->tbSearch->TabIndex = 4;
			// 
			// buttonSearch
			// 
			this->buttonSearch->Location = System::Drawing::Point(560, 100);
			this->buttonSearch->Name = L"buttonSearch";
			this->buttonSearch->Size = System::Drawing::Size(170, 30);
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
			this->lvSearchOutput->AutoArrange = false;
			this->lvSearchOutput->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(12) {
				this->colLongName,
					this->colShorterName, this->colShortestName, this->colCode, this->ColNote, this->colNoEducationYoung, this->colBasicEducation,
					this->colHighNotFinishedEducation, this->colHighEducation, this->colHigherEducation, this->colUniversityEducation, this->colNoEducation
			});
			this->lvSearchOutput->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->lvSearchOutput->HideSelection = false;
			this->lvSearchOutput->Location = System::Drawing::Point(16, 215);
			this->lvSearchOutput->Name = L"lvSearchOutput";
			this->lvSearchOutput->Size = System::Drawing::Size(1015, 215);
			this->lvSearchOutput->TabIndex = 6;
			this->lvSearchOutput->UseCompatibleStateImageBehavior = false;
			this->lvSearchOutput->View = System::Windows::Forms::View::Details;
			// 
			// colLongName
			// 
			this->colLongName->Text = L"Cely nazov";
			this->colLongName->Width = 143;
			// 
			// colShorterName
			// 
			this->colShorterName->Text = L"Skrateny nazov";
			this->colShorterName->Width = 170;
			// 
			// colShortestName
			// 
			this->colShortestName->Text = L"Kratky nazov";
			this->colShortestName->Width = 148;
			// 
			// colCode
			// 
			this->colCode->Text = L"Kod";
			this->colCode->Width = 119;
			// 
			// ColNote
			// 
			this->ColNote->Text = L"Poznamka";
			// 
			// colNoEducationYoung
			// 
			this->colNoEducationYoung->Text = L"bez ukončeného vzdelania – osoby vo veku 0-14 rokov";
			// 
			// colBasicEducation
			// 
			this->colBasicEducation->Text = L"základné vzdelanie";
			// 
			// colHighNotFinishedEducation
			// 
			this->colHighNotFinishedEducation->Text = L"stredné odborné (učňovské) vzdelanie (bez maturity)";
			// 
			// colHighEducation
			// 
			this->colHighEducation->Text = L"úplné stredné vzdelanie";
			// 
			// colHigherEducation
			// 
			this->colHigherEducation->Text = L"vyššie odborné vzdelanie";
			// 
			// colUniversityEducation
			// 
			this->colUniversityEducation->Text = L"vysokoškolské vzdelanie";
			// 
			// colNoEducation
			// 
			this->colNoEducation->Text = L"bez školského vzdelania – osoby vo veku 15 rokov a viac";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(296, 9);
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
			this->cbSelectField->Location = System::Drawing::Point(299, 24);
			this->cbSelectField->Name = L"cbSelectField";
			this->cbSelectField->Size = System::Drawing::Size(181, 21);
			this->cbSelectField->TabIndex = 8;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(12, 23);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(146, 24);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Aktualna uroven";
			// 
			// lbCurrentLevel
			// 
			this->lbCurrentLevel->AutoSize = true;
			this->lbCurrentLevel->Location = System::Drawing::Point(13, 47);
			this->lbCurrentLevel->Name = L"lbCurrentLevel";
			this->lbCurrentLevel->Size = System::Drawing::Size(108, 13);
			this->lbCurrentLevel->TabIndex = 10;
			this->lbCurrentLevel->Text = L"Slovenska Republika";
			// 
			// btUpperLevel
			// 
			this->btUpperLevel->Location = System::Drawing::Point(148, 67);
			this->btUpperLevel->Name = L"btUpperLevel";
			this->btUpperLevel->Size = System::Drawing::Size(118, 23);
			this->btUpperLevel->TabIndex = 11;
			this->btUpperLevel->Text = L"uroven vyssie";
			this->btUpperLevel->UseVisualStyleBackColor = true;
			this->btUpperLevel->Click += gcnew System::EventHandler(this, &main_form::btUpperLevel_Click);
			// 
			// cbSonsList
			// 
			this->cbSonsList->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbSonsList->FormattingEnabled = true;
			this->cbSonsList->Location = System::Drawing::Point(15, 98);
			this->cbSonsList->Name = L"cbSonsList";
			this->cbSonsList->Size = System::Drawing::Size(134, 21);
			this->cbSonsList->TabIndex = 12;
			// 
			// btLowerLevel
			// 
			this->btLowerLevel->Location = System::Drawing::Point(148, 96);
			this->btLowerLevel->Name = L"btLowerLevel";
			this->btLowerLevel->Size = System::Drawing::Size(118, 23);
			this->btLowerLevel->TabIndex = 13;
			this->btLowerLevel->Text = L"Uroven nizsie";
			this->btLowerLevel->UseVisualStyleBackColor = true;
			this->btLowerLevel->Click += gcnew System::EventHandler(this, &main_form::btLowerLevel_Click);
			// 
			// lbUCType
			// 
			this->lbUCType->AutoSize = true;
			this->lbUCType->Location = System::Drawing::Point(18, 8);
			this->lbUCType->Name = L"lbUCType";
			this->lbUCType->Size = System::Drawing::Size(145, 13);
			this->lbUCType->TabIndex = 15;
			this->lbUCType->Text = L"Vyberte typ uzemnej jednotky";
			// 
			// cbUCType
			// 
			this->cbUCType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbUCType->FormattingEnabled = true;
			this->cbUCType->Location = System::Drawing::Point(21, 24);
			this->cbUCType->Name = L"cbUCType";
			this->cbUCType->Size = System::Drawing::Size(179, 21);
			this->cbUCType->TabIndex = 14;
			// 
			// btUCType
			// 
			this->btUCType->Location = System::Drawing::Point(560, 100);
			this->btUCType->Name = L"btUCType";
			this->btUCType->Size = System::Drawing::Size(170, 30);
			this->btUCType->TabIndex = 17;
			this->btUCType->Text = L"Zobrazit";
			this->btUCType->UseVisualStyleBackColor = true;
			this->btUCType->Click += gcnew System::EventHandler(this, &main_form::btUCType_Click);
			// 
			// mainTabs
			// 
			this->mainTabs->Controls->Add(this->tabPage1);
			this->mainTabs->Controls->Add(this->tabPage2);
			this->mainTabs->Controls->Add(this->tabPage3);
			this->mainTabs->Location = System::Drawing::Point(274, 23);
			this->mainTabs->Name = L"mainTabs";
			this->mainTabs->SelectedIndex = 0;
			this->mainTabs->Size = System::Drawing::Size(762, 167);
			this->mainTabs->TabIndex = 18;
			this->mainTabs->SelectedIndexChanged += gcnew System::EventHandler(this, &main_form::mainTabs_SelectedIndexChanged);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->tbUCName);
			this->tabPage1->Controls->Add(this->cbUCType);
			this->tabPage1->Controls->Add(this->btUCType);
			this->tabPage1->Controls->Add(this->lbUCType);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(754, 141);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Konkretne vyhladavanie";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(224, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(160, 13);
			this->label4->TabIndex = 19;
			this->label4->Text = L"Zadajte nazov uzemnej jednotky";
			// 
			// tbUCName
			// 
			this->tbUCName->Location = System::Drawing::Point(225, 25);
			this->tbUCName->Name = L"tbUCName";
			this->tbUCName->Size = System::Drawing::Size(181, 20);
			this->tbUCName->TabIndex = 18;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->checkBox1);
			this->tabPage2->Controls->Add(this->cbUCType2);
			this->tabPage2->Controls->Add(this->label3);
			this->tabPage2->Controls->Add(this->cbSelectField);
			this->tabPage2->Controls->Add(this->lSearchAlgorithm);
			this->tabPage2->Controls->Add(this->cbSearchAlgorithm);
			this->tabPage2->Controls->Add(this->lSearchBox);
			this->tabPage2->Controls->Add(this->tbSearch);
			this->tabPage2->Controls->Add(this->buttonSearch);
			this->tabPage2->Controls->Add(this->label1);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(754, 141);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Bodove vyhladavanie";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(21, 51);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(90, 17);
			this->checkBox1->TabIndex = 18;
			this->checkBox1->Text = L"Vybrat vsetky";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// cbUCType2
			// 
			this->cbUCType2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbUCType2->FormattingEnabled = true;
			this->cbUCType2->Location = System::Drawing::Point(21, 24);
			this->cbUCType2->Name = L"cbUCType2";
			this->cbUCType2->Size = System::Drawing::Size(179, 21);
			this->cbUCType2->TabIndex = 16;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(18, 8);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(145, 13);
			this->label3->TabIndex = 17;
			this->label3->Text = L"Vyberte typ uzemnej jednotky";
			// 
			// tabPage3
			// 
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(806, 141);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Filtrovanie";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// main_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1047, 436);
			this->Controls->Add(this->mainTabs);
			this->Controls->Add(this->btLowerLevel);
			this->Controls->Add(this->cbSonsList);
			this->Controls->Add(this->btUpperLevel);
			this->Controls->Add(this->lbCurrentLevel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->lvSearchOutput);
			this->Name = L"main_form";
			this->Text = L"AAUD1 Semestralna Praca, made by Maros Majba 2023";
			this->mainTabs->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void buttonSearch_Click(System::Object^ sender, System::EventArgs^ e) {
	// Definicia indexov pre comboboxy, potrebne pre kontrolu ci je nieco zvolene
	int cbSearchAlgorithmIndex = cbSearchAlgorithm->SelectedIndex;
	int cbFieldSelectIndex = cbSelectField->SelectedIndex;
	int cbUCTypeIndex = cbUCType2->SelectedIndex;
	String^ tbSearchValue = tbSearch->Text;
	bool passed = false;

	if (cbFieldSelectIndex == -1)
	{
		MessageBox::Show("Vyberte pole nad ktorym chcete porovnavat.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else if (String::IsNullOrEmpty(tbSearchValue))
	{
		MessageBox::Show("Zadajte text na porovnanie.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else if (cbSearchAlgorithmIndex == -1)
	{
		MessageBox::Show("Zvolte algoritmus pomocou ktoreho chcete vyhladavat.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else if (cbUCTypeIndex == -1)
	{
		MessageBox::Show("Zvolte typ uzemnej jednotky ktoru chcete vyhladavat.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else
	{
		passed = true;
	}

	if (passed)
	{
		lvSearchOutput->Items->Clear();
		this->myData->searcher.clear();

		// Ziskanie zadanych hodnot
		std::string selectedAlgorithm = msclr::interop::marshal_as<std::string>(cbSearchAlgorithm->SelectedItem->ToString());
		std::string selectedField = msclr::interop::marshal_as<std::string>(cbSelectField->SelectedItem->ToString());
		std::string selectedUC = msclr::interop::marshal_as<std::string>(cbUCType2->SelectedItem->ToString());
		std::string substring = msclr::interop::marshal_as<std::string>(tbSearchValue);

		auto selectedAlgorithmLambda = selectedAlgorithm == "Zo zaciatku" ? myData->search_from_beginning : myData->search_substring;
		ds::amt::ImplicitSequence<CSVElement*>* selectedFileData;


		// Postupne ziskavanie a testovanie zapisanych hodnot
		std::string(CSVElement::* selectedFieldMethod)();


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
		myData->searcher.search(selectedUC, myData->has_type, &CSVElement::get_UC_type,
			ds::amt::MultiWayExplicitHierarchy<CSVElement*>::PreOrderHierarchyIterator(myData->hierarchy, myData->hierarchy_current_block),
			ds::amt::MultiWayExplicitHierarchy<CSVElement*>::PreOrderHierarchyIterator(myData->hierarchy, nullptr));


		Searcher<ds::adt::ImplicitList<CSVElement*>::IteratorType, std::string(CSVElement::*)()> output_searcher;
		output_searcher.search(substring, selectedAlgorithmLambda, selectedFieldMethod,
			myData->searcher.getOutput().begin(), myData->searcher.getOutput().end());

		this->writeDataToTable(&output_searcher.getOutput());
	}
}
void writeDataToTable(ds::adt::ImplicitList<CSVElement*>* outputElements)
{
	lvSearchOutput->Items->Clear();
	for (auto item : *outputElements)
	{
		writeDataToTable(*item);
	}
}

void writeDataToTable(CSVElement& element)
{
	std::cout << element.get_has_education() << '\n';

	lvSearchOutput->Items->Clear();
	ListViewItem^ listViewItem = gcnew ListViewItem(gcnew String(element.get_official_title().c_str()));
	listViewItem->SubItems->Add(gcnew String(element.get_medium_title().c_str()));
	listViewItem->SubItems->Add(gcnew String(element.get_short_title().c_str()));
	listViewItem->SubItems->Add(gcnew String(element.get_code().c_str()));
	listViewItem->SubItems->Add(gcnew String(element.get_note().c_str()));

	if (element.get_has_education())
	{
		listViewItem->SubItems->Add(gcnew String(std::to_string(element.get_no_education_young()).c_str()));
		listViewItem->SubItems->Add(gcnew String(std::to_string(element.get_basic_education()).c_str()));
		listViewItem->SubItems->Add(gcnew String(std::to_string(element.get_high_lower_education()).c_str()));
		listViewItem->SubItems->Add(gcnew String(std::to_string(element.get_high_higher_education()).c_str()));
		listViewItem->SubItems->Add(gcnew String(std::to_string(element.get_higher_education()).c_str()));
		listViewItem->SubItems->Add(gcnew String(std::to_string(element.get_university_education()).c_str()));
		listViewItem->SubItems->Add(gcnew String(std::to_string(element.get_no_education_old()).c_str()));
		listViewItem->SubItems->Add(gcnew String(std::to_string(element.get_not_clarified()).c_str()));
	}
	lvSearchOutput->Items->Add(listViewItem);
}

void writeDataToTable(ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>* outputElements)
{
	lvSearchOutput->Items->Clear();
	for (auto item : *outputElements)
	{
		writeDataToTable(*item->data_);
	}
}

void writeDataToComboBox(ComboBox^ comboBox, ds::adt::ImplicitList<std::string>& elements)
{
	for (auto item : elements)
	{
		comboBox->Items->Add(gcnew String(item.c_str()));
	}
}

void writeDataToComboBox(ComboBox^ comboBox, ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>& elements)
{
	for (auto item : elements)
	{
		comboBox->Items->Add(gcnew String(item->data_->get_official_title().c_str()));
	}
}
private: System::Void btUpperLevel_Click(System::Object^ sender, System::EventArgs^ e) {
	if (myData->hierarchy->isRoot(*myData->hierarchy_current_block))
	{
		MessageBox::Show("Zvoleny vrchol je korenom.\n Nemozno ist o uroven vyssie.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else
	{
		myData->hierarchy_current_block = myData->hierarchy->accessParent(*myData->hierarchy_current_block);
		cbSonsList->Items->Clear();
		cbUCType->Items->Clear();
		writeDataToComboBox(cbSonsList, *myData->hierarchy_current_block->sons_);
		lbCurrentLevel->Text = gcnew String(myData->hierarchy_current_block->data_->get_official_title().c_str());

		// Zmena obsahu cb uzemneho celku
		if (myData->hierarchy_current_block->data_->get_UC_type() == "republika")
		{
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"kraj", "okres", "obec"});
		}
		else if (myData->hierarchy_current_block->data_->get_UC_type() == "kraj")
		{
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"okres", "obec"});
		}
		else
		{
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"obec"});
		}
	}
}
private: System::Void btLowerLevel_Click(System::Object^ sender, System::EventArgs^ e) {
	if (cbSonsList->SelectedIndex == -1)
	{
		MessageBox::Show("Zvolte prvok na ktory sa chcete posunut", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else
	{
		if (myData->hierarchy->degree(*myData->hierarchy->accessSon(*myData->hierarchy_current_block, cbSonsList->SelectedIndex)) == 0)
		{
			MessageBox::Show("Zvoleny vrchol je list.\n Nemozno ist o uroven nizsie.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
		else
		{
			myData->hierarchy_current_block = myData->hierarchy->accessSon(*myData->hierarchy_current_block, cbSonsList->SelectedIndex);
			cbSonsList->Items->Clear();
			cbUCType->Items->Clear();
			writeDataToComboBox(cbSonsList, *myData->hierarchy_current_block->sons_);
			lbCurrentLevel->Text = gcnew String(myData->hierarchy_current_block->data_->get_official_title().c_str());

			// Zmena obsahu cb uzemneho celku
			if (myData->hierarchy_current_block->data_->get_UC_type() == "kraj")
			{
				writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"okres", "obec"});
			} else if (myData->hierarchy_current_block->data_->get_UC_type() == "okres")
			{
				writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"obec"});
			} else
			{
				writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{""});
			}
		}
	}
}
private: System::Void btUCType_Click(System::Object^ sender, System::EventArgs^ e) {
	std::string nameUC = msclr::interop::marshal_as<std::string>(tbUCName->Text);
	if (cbUCType->SelectedIndex == -1)
	{
		MessageBox::Show("Vyberte uzemnu jednotku, ktoru chcete zobrazit", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else if (nameUC == "") {
		MessageBox::Show("Zadajte nazov uzemnej jednotky", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	} else
	{
		std::string selectedUC = msclr::interop::marshal_as<std::string>(cbUCType->SelectedItem->ToString());
		CSVElement** foundElement = nullptr;
		ds::adt::ImplicitList<CSVElement*>* foundElements = nullptr;
		if (selectedUC == "kraj")
		{
			this->myData->kraje_table.tryFindWithDuplicities(nameUC, foundElement, foundElements);
		} else if (selectedUC == "okres")
		{
			this->myData->okresy_table.tryFindWithDuplicities(nameUC, foundElement, foundElements);
		} else
		{
			this->myData->obce_table.tryFindWithDuplicities(nameUC, foundElement, foundElements);
		}

		if (foundElement == nullptr)
		{
			MessageBox::Show("UC so zadanym menom neexistuje", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		} else
		{
			if (foundElements == nullptr)
			{
				this->writeDataToTable(**foundElement);
			} else
			{
				foundElements->insertLast(*foundElement);
				this->writeDataToTable(foundElements);
			}
		}
	}

}
private: System::Void mainTabs_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	switch(mainTabs->SelectedIndex)
	{
	case 0:
		cbUCType->Items->Clear();
		if (myData->hierarchy_current_block->data_->get_UC_type() == "republika")
		{
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"kraj", "okres", "obec"});
		} else if (myData->hierarchy_current_block->data_->get_UC_type() == "kraj")
		{
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"okres", "obec"});
		}
		else if (myData->hierarchy_current_block->data_->get_UC_type() == "okres")
		{
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"obec"});
		}
		else
		{
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{""});
		}

		cbSonsList->Enabled = false;
		btLowerLevel->Enabled = false;
		btUpperLevel->Enabled = false;
		break;
	case 1:
		cbUCType2->Items->Clear();
		if (myData->hierarchy_current_block->data_->get_UC_type() == "republika")
		{
			writeDataToComboBox(cbUCType2, ds::adt::ImplicitList<std::string>{"kraj", "okres", "obec"});
		} else if (myData->hierarchy_current_block->data_->get_UC_type() == "kraj")
		{
			writeDataToComboBox(cbUCType2, ds::adt::ImplicitList<std::string>{"okres", "obec"});
		}
		else if (myData->hierarchy_current_block->data_->get_UC_type() == "okres")
		{
			writeDataToComboBox(cbUCType2, ds::adt::ImplicitList<std::string>{"obec"});
		}
		else
		{
			writeDataToComboBox(cbUCType2, ds::adt::ImplicitList<std::string>{""});
		}

		cbSonsList->Enabled = true;
		btLowerLevel->Enabled = true;
		btUpperLevel->Enabled = true;
		break;
	case 2:
		cbSonsList->Enabled = false;
		btLowerLevel->Enabled = false;
		btUpperLevel->Enabled = false;
		break;
	}
}
};
}
