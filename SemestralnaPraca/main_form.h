#pragma once
#include <libds/amt/implicit_sequence.h>
#include <msclr/marshal_cppstd.h>
#include "SearchData.h";
#include "filtrovanie_window.h"
#include "Filter.h"
#include <libds/adt/list.h>
#include <libds/adt/sorts.h>

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
		SearchData* myData; // objekt so zadefinovanymi lambda funkciami a pomocnymi atributmi
		filtrovanie_window^ filtrovanieWindow; // instancia druheho formularu
		ds::adt::ImplicitList<CSVElement*>* outputList; // list ulozenych hodnot
		ds::adt::ImplicitList<Filter*>* selectedFilters; // list ulozenych filtrov

	private: System::Windows::Forms::ListBox^ lbSelectedFilters;

	private: System::Windows::Forms::Button^ btnClearListView;
	private: System::Windows::Forms::ComboBox^ cbSortAlgorithm;




	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ btnSortListView;
	private: System::Windows::Forms::Button^ btnFilter;
	public:
		main_form(void)
		{
			InitializeComponent();

			this->myData = new SearchData();
			selectedFilters = new ds::adt::ImplicitList<Filter*>();
			filtrovanieWindow = gcnew filtrovanie_window();
			outputList = new ds::adt::ImplicitList<CSVElement*>();

			writeDataToComboBox(cbSonsList, *myData->hierarchy_current_block->sons_);
			writeDataToComboBox(cbUCType, ds::adt::ImplicitList<std::string>{"kraj", "okres", "obec"});

			// Pri starte nepovol pohyb po hierarchii, kedze je zvoleny tab 1
			cbSonsList->Enabled = false;
			btLowerLevel->Enabled = false;
			btUpperLevel->Enabled = false;

			// Pri starte taktiez nepovolit zoradovanie, kedze tabulka bude mat vzdy UC s rovnakym nazvom
			cbSortAlgorithm->Enabled = false;
			btnSortListView->Enabled = false;
		}

	protected:
		
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~main_form()
		{
			delete myData;

			delete outputList;

			for (auto element : *selectedFilters)
			{
				delete element;
			}

			delete selectedFilters;

			delete filtrovanieWindow;

			for (int i = 0; i < lbSelectedFilters->Items->Count; i++)
			{
				delete lbSelectedFilters->Items[i];
			}
			lbSelectedFilters->Items->Clear();

			delete lbSelectedFilters;

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
	private: System::Windows::Forms::CheckBox^ checkSelectAllUC;
private: System::Windows::Forms::Button^ btnRemoveAllFilters;

private: System::Windows::Forms::Button^ btnRemoveFilter;

private: System::Windows::Forms::Button^ btnAddFilter;

	private: System::Windows::Forms::Label^ label5;

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
			this->checkSelectAllUC = (gcnew System::Windows::Forms::CheckBox());
			this->cbUCType2 = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->btnFilter = (gcnew System::Windows::Forms::Button());
			this->lbSelectedFilters = (gcnew System::Windows::Forms::ListBox());
			this->btnRemoveAllFilters = (gcnew System::Windows::Forms::Button());
			this->btnRemoveFilter = (gcnew System::Windows::Forms::Button());
			this->btnAddFilter = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->btnClearListView = (gcnew System::Windows::Forms::Button());
			this->cbSortAlgorithm = (gcnew System::Windows::Forms::ComboBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->btnSortListView = (gcnew System::Windows::Forms::Button());
			this->mainTabs->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			// 
			// lSearchAlgorithm
			// 
			this->lSearchAlgorithm->Location = System::Drawing::Point(299, 59);
			this->lSearchAlgorithm->Name = L"lSearchAlgorithm";
			this->lSearchAlgorithm->Size = System::Drawing::Size(179, 13);
			this->lSearchAlgorithm->TabIndex = 0;
			this->lSearchAlgorithm->Text = L"Vyberte vyhladávací algoritmus";
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
			this->lSearchBox->Size = System::Drawing::Size(168, 13);
			this->lSearchBox->TabIndex = 3;
			this->lSearchBox->Text = L"Zadajte reťazec pre porovnavanie";
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
			this->lvSearchOutput->Location = System::Drawing::Point(21, 232);
			this->lvSearchOutput->Name = L"lvSearchOutput";
			this->lvSearchOutput->Size = System::Drawing::Size(1015, 198);
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
			this->label1->Size = System::Drawing::Size(186, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Vyberte stĺpec nad ktorým vyhladávať";
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
			this->label2->Size = System::Drawing::Size(137, 24);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Aktuálny vrchol";
			// 
			// lbCurrentLevel
			// 
			this->lbCurrentLevel->AutoSize = true;
			this->lbCurrentLevel->Location = System::Drawing::Point(13, 47);
			this->lbCurrentLevel->Name = L"lbCurrentLevel";
			this->lbCurrentLevel->Size = System::Drawing::Size(108, 13);
			this->lbCurrentLevel->TabIndex = 10;
			this->lbCurrentLevel->Text = L"Slovenská Republika";
			// 
			// btUpperLevel
			// 
			this->btUpperLevel->Location = System::Drawing::Point(148, 67);
			this->btUpperLevel->Name = L"btUpperLevel";
			this->btUpperLevel->Size = System::Drawing::Size(118, 23);
			this->btUpperLevel->TabIndex = 11;
			this->btUpperLevel->Text = L"Úroveň vyššie";
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
			this->btLowerLevel->Text = L"Úroveň nižšie";
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
			this->lbUCType->Text = L"Vyberte typ územnej jednotky";
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
			this->btUCType->Text = L"Zobraziť";
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
			this->tabPage1->Text = L"Bodové vyhladávanie";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(224, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(160, 13);
			this->label4->TabIndex = 19;
			this->label4->Text = L"Zadajte názov územnej jednotky";
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
			this->tabPage2->Controls->Add(this->checkSelectAllUC);
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
			this->tabPage2->Text = L"Hĺbkové vyhládávanie";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// checkSelectAllUC
			// 
			this->checkSelectAllUC->AutoSize = true;
			this->checkSelectAllUC->Location = System::Drawing::Point(21, 51);
			this->checkSelectAllUC->Name = L"checkSelectAllUC";
			this->checkSelectAllUC->Size = System::Drawing::Size(91, 17);
			this->checkSelectAllUC->TabIndex = 18;
			this->checkSelectAllUC->Text = L"Vybrať všetky";
			this->checkSelectAllUC->UseVisualStyleBackColor = true;
			this->checkSelectAllUC->CheckedChanged += gcnew System::EventHandler(this, &main_form::checkSelectAllUC_CheckedChanged);
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
			this->label3->Text = L"Vyberte typ územnej jednotky";
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->btnFilter);
			this->tabPage3->Controls->Add(this->lbSelectedFilters);
			this->tabPage3->Controls->Add(this->btnRemoveAllFilters);
			this->tabPage3->Controls->Add(this->btnRemoveFilter);
			this->tabPage3->Controls->Add(this->btnAddFilter);
			this->tabPage3->Controls->Add(this->label5);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(754, 141);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Filtrovanie";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// btnFilter
			// 
			this->btnFilter->Location = System::Drawing::Point(589, 99);
			this->btnFilter->Name = L"btnFilter";
			this->btnFilter->Size = System::Drawing::Size(146, 33);
			this->btnFilter->TabIndex = 8;
			this->btnFilter->Text = L"Filtrovať";
			this->btnFilter->UseVisualStyleBackColor = true;
			this->btnFilter->Click += gcnew System::EventHandler(this, &main_form::btnFilter_Click);
			// 
			// lbSelectedFilters
			// 
			this->lbSelectedFilters->FormattingEnabled = true;
			this->lbSelectedFilters->Location = System::Drawing::Point(211, 24);
			this->lbSelectedFilters->Name = L"lbSelectedFilters";
			this->lbSelectedFilters->Size = System::Drawing::Size(524, 69);
			this->lbSelectedFilters->TabIndex = 7;
			// 
			// btnRemoveAllFilters
			// 
			this->btnRemoveAllFilters->Location = System::Drawing::Point(12, 80);
			this->btnRemoveAllFilters->Name = L"btnRemoveAllFilters";
			this->btnRemoveAllFilters->Size = System::Drawing::Size(174, 23);
			this->btnRemoveAllFilters->TabIndex = 4;
			this->btnRemoveAllFilters->Text = L"Odstránit vsetky";
			this->btnRemoveAllFilters->UseVisualStyleBackColor = true;
			this->btnRemoveAllFilters->Click += gcnew System::EventHandler(this, &main_form::btnRemoveAllFilters_Click);
			// 
			// btnRemoveFilter
			// 
			this->btnRemoveFilter->Location = System::Drawing::Point(12, 51);
			this->btnRemoveFilter->Name = L"btnRemoveFilter";
			this->btnRemoveFilter->Size = System::Drawing::Size(174, 23);
			this->btnRemoveFilter->TabIndex = 3;
			this->btnRemoveFilter->Text = L"Odstrániť filter";
			this->btnRemoveFilter->UseVisualStyleBackColor = true;
			this->btnRemoveFilter->Click += gcnew System::EventHandler(this, &main_form::btnRemoveFilter_Click);
			// 
			// btnAddFilter
			// 
			this->btnAddFilter->Location = System::Drawing::Point(12, 22);
			this->btnAddFilter->Name = L"btnAddFilter";
			this->btnAddFilter->Size = System::Drawing::Size(174, 23);
			this->btnAddFilter->TabIndex = 2;
			this->btnAddFilter->Text = L"Pridať filter";
			this->btnAddFilter->UseVisualStyleBackColor = true;
			this->btnAddFilter->Click += gcnew System::EventHandler(this, &main_form::btnAddFilter_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(208, 4);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(65, 13);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Pridané filtre";
			// 
			// btnClearListView
			// 
			this->btnClearListView->Location = System::Drawing::Point(903, 203);
			this->btnClearListView->Name = L"btnClearListView";
			this->btnClearListView->Size = System::Drawing::Size(129, 23);
			this->btnClearListView->TabIndex = 19;
			this->btnClearListView->Text = L"Vyčistiť";
			this->btnClearListView->UseVisualStyleBackColor = true;
			this->btnClearListView->Click += gcnew System::EventHandler(this, &main_form::btnClearListView_Click);
			// 
			// cbSortAlgorithm
			// 
			this->cbSortAlgorithm->FormattingEnabled = true;
			this->cbSortAlgorithm->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Názvu", L"Počtu samohlások" });
			this->cbSortAlgorithm->Location = System::Drawing::Point(576, 203);
			this->cbSortAlgorithm->Name = L"cbSortAlgorithm";
			this->cbSortAlgorithm->Size = System::Drawing::Size(174, 21);
			this->cbSortAlgorithm->TabIndex = 20;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(573, 189);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(72, 13);
			this->label7->TabIndex = 21;
			this->label7->Text = L"Zoradiť podľa";
			// 
			// btnSortListView
			// 
			this->btnSortListView->Location = System::Drawing::Point(756, 203);
			this->btnSortListView->Name = L"btnSortListView";
			this->btnSortListView->Size = System::Drawing::Size(129, 23);
			this->btnSortListView->TabIndex = 22;
			this->btnSortListView->Text = L"Zoradiť";
			this->btnSortListView->UseVisualStyleBackColor = true;
			this->btnSortListView->Click += gcnew System::EventHandler(this, &main_form::btnSortListView_Click);
			// 
			// main_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1047, 436);
			this->Controls->Add(this->btnSortListView);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->cbSortAlgorithm);
			this->Controls->Add(this->btnClearListView);
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
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//***********************************
		//Metody na vypis udajov do list view
		//***********************************

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

		//*************************************
		//Metody na vypis udajov do combo boxov
		//*************************************

		void writeDataToComboBox(ComboBox^ comboBox, ds::adt::ImplicitList<std::string>& elements)
		{
			for (auto item : elements)
			{
				comboBox->Items->Add(gcnew String(item.c_str()));
			}
		}


		// Metoda je nutna, pretoze hierarchia nevracia adt, ale amt sekvenciu
		void writeDataToComboBox(ComboBox^ comboBox, 
			ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>& elements)
		{
			for (auto item : elements)
			{
				comboBox->Items->Add(gcnew String(item->data_->get_official_title().c_str()));
			}
		}

		void writeFilter(Filter* filter)
		{
			lbSelectedFilters->Items->Add(gcnew String(filter->toString().c_str()));

			selectedFilters->insertLast(filter);
		}

		// Pomocna metoda pre vypis moznych UC na zaklade pozicie bloku hierarchie
		void writePossibleUC(ComboBox^ comboBox)
		{
			comboBox->Items->Clear();
			if (myData->hierarchy_current_block->data_->get_UC_type() == "republika")
			{
				writeDataToComboBox(comboBox, ds::adt::ImplicitList<std::string>{"kraj", "okres", "obec"});
			}
			else if (myData->hierarchy_current_block->data_->get_UC_type() == "kraj")
			{
				writeDataToComboBox(comboBox, ds::adt::ImplicitList<std::string>{"okres", "obec"});
			}
			else if (myData->hierarchy_current_block->data_->get_UC_type() == "okres")
			{
				writeDataToComboBox(comboBox, ds::adt::ImplicitList<std::string>{"obec"});
			}
			else
			{
				writeDataToComboBox(comboBox, ds::adt::ImplicitList<std::string>{""});
			}
		}


		//*********************
		//Metody pre zmenu tabu
		//*********************

		private: System::Void mainTabs_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
			// 
			switch (mainTabs->SelectedIndex)
			{
			case 0:
				// Nastavenie zapnutia a vypnutia prechadzaca po hierarchii na zaklade tabu
				cbSonsList->Enabled = false;
				btLowerLevel->Enabled = false;
				btUpperLevel->Enabled = false;

				cbSortAlgorithm->Enabled = false;
				btnSortListView->Enabled = false;
				break;
			case 1:
				writePossibleUC(cbUCType2);

				cbSonsList->Enabled = true;
				btLowerLevel->Enabled = true;
				btUpperLevel->Enabled = true;

				cbSortAlgorithm->Enabled = true;
				btnSortListView->Enabled = true;
				break;
			case 2:
				cbSonsList->Enabled = false;
				btLowerLevel->Enabled = false;
				btUpperLevel->Enabled = false;

				cbSortAlgorithm->Enabled = true;
				btnSortListView->Enabled = true;
				break;
			}
		}

		//****************
	    //Metody pre tab 1
	    //****************

		private: System::Void btUCType_Click(System::Object^ sender, System::EventArgs^ e) {
			std::string nameUC = msclr::interop::marshal_as<std::string>(tbUCName->Text);
			if (cbUCType->SelectedIndex == -1)
			{
				MessageBox::Show("Vyberte územnú jednotku, ktorú chcete zobraziť", "Chyba", 
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			else if (nameUC == "") {
				MessageBox::Show("Zadajte názov územnej jednotky", "Chyba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			else
			{
				std::string selectedUC = msclr::interop::marshal_as<std::string>(cbUCType->SelectedItem->ToString());

				CSVElement** foundElement = nullptr;
				ds::adt::ImplicitList<CSVElement*>* foundElements = nullptr;
				if (selectedUC == "kraj")
				{
					this->myData->kraje_table.tryFindWithDuplicities(nameUC, foundElement, foundElements);
				}
				else if (selectedUC == "okres")
				{
					this->myData->okresy_table.tryFindWithDuplicities(nameUC, foundElement, foundElements);
				}
				else
				{
					this->myData->obce_table.tryFindWithDuplicities(nameUC, foundElement, foundElements);
				}

				if (foundElement == nullptr)
				{
					MessageBox::Show("UC so zadaným menom neexistuje", "Chyba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
				else
				{
					outputList->clear();

					if (foundElements->isEmpty())
					{
						outputList->insertLast(*foundElement);
					}
					else
					{
						outputList->insertLast(*foundElement);

						for (auto el: *foundElements)
						{
							outputList->insertLast(el);
						}
					}
					this->writeDataToTable(outputList);
				}
			}
		}
		
		//****************
	    //Metody pre tab 2
	    //****************

		// Posunutie sa o uroven vyssie
		private: System::Void btUpperLevel_Click(System::Object^ sender, System::EventArgs^ e) {
			if (myData->hierarchy->isRoot(*myData->hierarchy_current_block))
			{
				MessageBox::Show("Zvolený vrchol je koreň.\n Nemožno ísť o úroveň vyššie.", 
					"Chyba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			else
			{
				myData->hierarchy_current_block = myData->hierarchy->accessParent(*myData->hierarchy_current_block);
				cbSonsList->Items->Clear();
				writeDataToComboBox(cbSonsList, *myData->hierarchy_current_block->sons_);
				lbCurrentLevel->Text = gcnew String(myData->hierarchy_current_block->data_->get_official_title().c_str());

				// Zmena obsahu cb uzemneho celku
				writePossibleUC(cbUCType2);
			}
		}

		// Posunutie sa o uroven nizsie
		private: System::Void btLowerLevel_Click(System::Object^ sender, System::EventArgs^ e) {
			if (cbSonsList->SelectedIndex == -1)
			{
				MessageBox::Show("Zvolte prvok, na ktorý sa chcete posunúť", "Chyba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			else
			{
				if (myData->hierarchy->isLeaf(*myData->hierarchy_current_block))
				{
					MessageBox::Show("Zvolený vrchol je list.\n Nemožno ísť o úroveň nižšie.", 
						"Chyba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
				else
				{
					myData->hierarchy_current_block = myData->hierarchy->accessSon(*myData->hierarchy_current_block, 
						cbSonsList->SelectedIndex);
					cbSonsList->Items->Clear();
					writeDataToComboBox(cbSonsList, *myData->hierarchy_current_block->sons_);
					lbCurrentLevel->Text = gcnew String(myData->hierarchy_current_block->data_->get_official_title().c_str());

					// Zmena obsahu cb uzemneho celku
					writePossibleUC(cbUCType2);
				}
			}
		}

		// Vyhladanie z daneho vrchola
		private: System::Void buttonSearch_Click(System::Object^ sender, System::EventArgs^ e) {
			// Definicia indexov pre comboboxy, potrebne pre kontrolu ci je nieco zvolene
			int cbSearchAlgorithmIndex = cbSearchAlgorithm->SelectedIndex;
			int cbFieldSelectIndex = cbSelectField->SelectedIndex;
			int cbUCTypeIndex = cbUCType2->SelectedIndex;
			String^ tbSearchValue = tbSearch->Text;
			bool passed = false;
			bool search_all = false;

			if (cbFieldSelectIndex == -1 && cbSelectField->Enabled)
			{
				MessageBox::Show("Vyberte pole, nad ktorým chcete porovnávať.", "Chyba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			} else if (String::IsNullOrEmpty(tbSearchValue) && tbSearch->Enabled)
			{
				MessageBox::Show("Zadajte text na porovnanie.", "Chyba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			} else if (cbSearchAlgorithmIndex == -1 && cbSearchAlgorithm->Enabled)
			{
				MessageBox::Show("Zvolte algoritmus, pomocou ktorého chcete vyhladávať.", "Chyba", 
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
			} else if (cbUCTypeIndex == -1)
			{
				MessageBox::Show("Zvolte typ územnej jednotky, ktorú chcete vyhladať.", "Chyba", 
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
			} else
			{
				passed = true;
			}

			if (cbSelectField->Enabled)
			{
				search_all = false;
			} else
			{
				search_all = true;
			}

			if (passed)
			{
				lvSearchOutput->Items->Clear();

				std::string selectedAlgorithm;
				std::string selectedField;
				std::string substring;
				std::string(CSVElement:: * selectedFieldMethod)();
				std::function<bool(const std::string&, const std::string&)> selectedAlgorithmLambda;

				std::string selectedUC = msclr::interop::marshal_as<std::string>(cbUCType2->SelectedItem->ToString());
				if (!search_all)
				{
					// Ziskanie zadanych hodnot
					selectedAlgorithm = msclr::interop::marshal_as<std::string>(cbSearchAlgorithm->SelectedItem->ToString());
					selectedField = msclr::interop::marshal_as<std::string>(cbSelectField->SelectedItem->ToString());
					substring = msclr::interop::marshal_as<std::string>(tbSearchValue);

					selectedAlgorithmLambda = selectedAlgorithm == "Zo zaciatku" ? 
						myData->search_from_beginning : myData->search_substring;


					if (selectedField == "Cele meno")
					{
						selectedFieldMethod = &CSVElement::get_official_title;
					}
					else if (selectedField == "Skratene meno")
					{
						selectedFieldMethod = &CSVElement::get_medium_title;
					}
					else if (selectedField == "Kratke meno")
					{
						selectedFieldMethod = &CSVElement::get_short_title;
					}
					else if (selectedField == "Kod")
					{
						selectedFieldMethod = &CSVElement::get_code;
					}
					else {
						selectedFieldMethod = &CSVElement::get_note;
					}
				}

				Searcher<ds::amt::MultiWayExplicitHierarchy<CSVElement*>::PreOrderHierarchyIterator, std::string(CSVElement::*)()> searcher;

				// Zavolanie samotnej search metody
				searcher.search<std::string, std::string>(selectedUC, myData->has_type, &CSVElement::get_UC_type,
					ds::amt::MultiWayExplicitHierarchy<CSVElement*>::PreOrderHierarchyIterator(myData->hierarchy, 
						myData->hierarchy_current_block),
					ds::amt::MultiWayExplicitHierarchy<CSVElement*>::PreOrderHierarchyIterator(myData->hierarchy, nullptr));

				outputList->assign(searcher.getOutput());

				// Aplikovanie filtra na vyhladane UC, pokial je zadany
				if (!search_all)
				{
					Searcher<ds::adt::ImplicitList<CSVElement*>::IteratorType, std::string(CSVElement::*)()> output_searcher;

					output_searcher.search<std::string, std::string>(substring, selectedAlgorithmLambda, selectedFieldMethod,
						searcher.getOutput().begin(), searcher.getOutput().end());

					outputList->assign(output_searcher.getOutput());
				}

				this->writeDataToTable(outputList);
			}
		}

		// Pomocna metoda pre umoznenie vypisu vsetkych UC daneho typu z daneho vrcholu
		private: System::Void checkSelectAllUC_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			if (checkSelectAllUC->Checked)
			{
				cbSelectField->Enabled = false;
				cbSearchAlgorithm->Enabled = false;
				tbSearch->Enabled = false;
			} else
			{
				cbSelectField->Enabled = true;
				cbSearchAlgorithm->Enabled = true;
				tbSearch->Enabled = true;
			}
		}

		//****************
	    //Metody pre tab 3
	    //****************

		// Pridanie filtra
		private: System::Void btnAddFilter_Click(System::Object^ sender, System::EventArgs^ e) {
			filtrovanie_window^ filtrovanieWindow = gcnew filtrovanie_window();
			filtrovanieWindow->ShowDialog();
			if (filtrovanieWindow->DialogResult == System::Windows::Forms::DialogResult::OK)
			{
				Filter* given_filter = filtrovanieWindow->getFilter();
				this->writeFilter(given_filter);
			}
		}

		// Odstranenie filtra
		private: System::Void btnRemoveFilter_Click(System::Object^ sender, System::EventArgs^ e) {
			if (lbSelectedFilters->SelectedIndex != -1)
			{
				delete selectedFilters->access(lbSelectedFilters->SelectedIndex);
				selectedFilters->remove(lbSelectedFilters->SelectedIndex);
				lbSelectedFilters->Items->RemoveAt(lbSelectedFilters->SelectedIndex);
			}
		}

		// Odstranenie vsetkych filtrov
		private: System::Void btnRemoveAllFilters_Click(System::Object^ sender, System::EventArgs^ e) {
			lbSelectedFilters->Items->Clear();

			for (auto element : *selectedFilters)
			{
				delete element;
			}

			selectedFilters->clear();
		}

		// Spustenie filtrovania
		private: System::Void btnFilter_Click(System::Object^ sender, System::EventArgs^ e) {
			if (this->selectedFilters->isEmpty())
			{
				MessageBox::Show("Zadajte aspoň jeden filter", "Chyba", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			else
			{
				Searcher<ds::adt::ImplicitList<CSVElement*>::IteratorType, int(CSVElement::*)()> output_searcher;

				for (Filter* filter : *selectedFilters)
				{
					output_searcher.search<int, Filter*>(filter, myData->compare_numeric, filter->getSelectedMethod(),
						outputList->begin(), outputList->end());
					outputList->assign(output_searcher.getOutput());
					output_searcher.clear();
				}

				this->selectedFilters->clear();
				lbSelectedFilters->Items->Clear();
				

				writeDataToTable(outputList);
			}
		}

		//*********************
	    //Metody pre sortovanie
	    //*********************

		// Vycistenie listview a listu so zvolenymi polozkami
		private: System::Void btnClearListView_Click(System::Object^ sender, System::EventArgs^ e) {
			outputList->clear();
			lvSearchOutput->Items->Clear();
		}

		// Zoradenie hodnot v liste hodnot
		private: System::Void btnSortListView_Click(System::Object^ sender, System::EventArgs^ e) {
			std::function<bool(CSVElement*, CSVElement*)> selected_method;

			if (cbSortAlgorithm->SelectedIndex == -1)
			{
				MessageBox::Show("Vyberte triediaci algoritmus", "Chyba",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
			} else
			{
				selected_method = cbSortAlgorithm->SelectedIndex == 0 ? myData->compareAlphabetical : myData->compareVowelsCount;

				ds::adt::QuickSort<CSVElement*> sorter;

				// Nutna konvencia na implicitsequence, kedze sorty nemaju listy...
				ds::amt::ImplicitSequence<CSVElement*> list;

				for (auto el : *outputList)
				{
					list.insertLast().data_ = el;
				}

				sorter.sort(list, selected_method);

				outputList->clear();

				for (auto el : list)
				{
					outputList->insertLast(el);
				}

				writeDataToTable(outputList);

			}
		}
};
}
