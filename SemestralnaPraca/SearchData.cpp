#include "SearchData.h"

// Pomocna metoda pre nacitanie uzemnych jednotiek z CSV suboru
void SearchData::loadCSV(const std::string& path, std::function<void(ds::adt::ImplicitList<std::string> content)> insert_function) {
	std::ifstream file(path);

	if (file.is_open()) {
		std::string line, element;
		bool first_row = true;

		while (std::getline(file, line)) {
			if (first_row) {
				first_row = false;
				continue;
			}

			ds::adt::ImplicitList<std::string> values;
			std::stringstream str(line);

			while (std::getline(str, element, ';')) {
				values.insertLast(element);
			}

			// Uprava pripadov kedy vo vectore nie je 5 hodnot, specialne pripady zahranicie, umele doplnenie prazdneho stringu
			if (values.size() < 6) {
				values.insertLast("");
			}

			// Pridanie typu uzemnej jednotky
			insert_function(values);
		}
	} else {
		throw std::runtime_error("File not found");
	}
	file.close();
}

// Metoda na naplnenie vsetkych udajovych struktur
void SearchData::fill()
{
	// Zadefinovanie korena
	auto& root = hierarchy->emplaceRoot();
	ds::adt::ImplicitList<std::string> root_data{ "SK", "Slovenska Republika", "Slovensko", "Slovensko", "", "republika" };
	root.data_ = new CSVElement(root_data);

	// Pomocna lambda funkcia, ktora sluzi na upravenie udajov a nasledne zavedenie vyvoreneho objektu CSVElement do udajovych struktur
	std::function<void(ds::adt::ImplicitList<std::string>)> insert_kraj = [&](ds::adt::ImplicitList<std::string> content) {
		// Nastavenie typu UC
		content.insertLast("kraj");
		// Zmazanie ID prvku
		content.removeFirst();

		auto element = new CSVElement(content);

		// Pridanie do stromu a tabulky
		auto* inserted_hierarchy_block = hierarchy->emplaceSon(*hierarchy->accessRoot(), 
			hierarchy->degree(*hierarchy->accessRoot())).data_ = element;
		this->kraje_table.insertWithDuplicities(inserted_hierarchy_block->get_official_title(), inserted_hierarchy_block);
	};

	loadCSV("documents\\uroven_1\\data\\krajeUTF8.csv", insert_kraj);

	// Nacitanie okresov
	int kraj_order = 0; // premenna na uchovanie indexu aktualne spracovaneho kraja
	std::string current_code = ""; // premenna na uchovanie kodu aktualneho kraja
	ds::adt::ImplicitList<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*> all_okresy; // list smernikov na vsetky vytvorene okresy v hierarchii
	auto current_son = hierarchy->accessSon(*hierarchy->accessRoot(), 0); // premenna na uchovanie aktualne spracovaneho kraja

	std::function<void(ds::adt::ImplicitList<std::string>)> insert_okres = [&](ds::adt::ImplicitList<std::string> content) {
		content.insertLast("okres");
		content.removeFirst();
		auto element = new CSVElement(content);

		if (current_code == "")
		{
			current_code = element->get_code().substr(0, 5);
		}
		else
		{
			if (current_code != element->get_code().substr(0, 5))
			{
				current_code = element->get_code().substr(0, 5);
				++kraj_order;
				current_son = hierarchy->accessSon(*hierarchy->accessRoot(), kraj_order);
			}
		}

		auto* inserted_hierarchy_block = hierarchy->emplaceSon(*current_son, hierarchy->degree(*current_son)).data_ = element;
		this->okresy_table.insertWithDuplicities(inserted_hierarchy_block->get_official_title(), inserted_hierarchy_block);
		all_okresy.insertLast(hierarchy->accessSon(*current_son, hierarchy->degree(*current_son) - 1));
	};

	loadCSV("documents\\uroven_1\\data\\okresyUTF8.csv", insert_okres);

	// Nacitanie obci
	int current_okres = 0;
	current_code = all_okresy.accessFirst()->data_->get_code().substr(0, 6);
	current_son = all_okresy.access(current_okres);

	std::function<void(ds::adt::ImplicitList<std::string>)> insert_obec = [&](ds::adt::ImplicitList<std::string> content)
	{
		content.insertLast("obec");
		content.removeFirst();
		auto element = new CSVElement(content);
		if (current_code != element->get_code().substr(0, 6))
		{
			current_code = element->get_code().substr(0, 6);
			++current_okres;
			current_son = all_okresy.access(current_okres);
		}
		auto* inserted_hierarchy_block = hierarchy->emplaceSon(*current_son, hierarchy->degree(*current_son)).data_ = element;
		this->obce_table.insertWithDuplicities(inserted_hierarchy_block->get_official_title(), inserted_hierarchy_block);
	};

	loadCSV("documents\\uroven_1\\data\\obceUTF8.csv", insert_obec);

	// Nacitanie udajov o vzdelani pre jednotlive obce
	std::function<void(ds::adt::ImplicitList<std::string>)> insert_vzdelanie = [&](ds::adt::ImplicitList<std::string> content)
	{
		content.remove(1);
		ds::adt::ImplicitList<int>* table_data = new ds::adt::ImplicitList<int>();
		table_data->insertLast(std::stoi(content[1]));
		table_data->insertLast(std::stoi(content[2]));
		table_data->insertLast(std::stoi(content[3]));
		table_data->insertLast(std::stoi(content[4]));
		table_data->insertLast(std::stoi(content[5]));
		table_data->insertLast(std::stoi(content[6]));
		table_data->insertLast(std::stoi(content[7]));
		table_data->insertLast(std::stoi(content[8]));
		vzdelanie_table.insert(content.access(0), table_data);
	};
	loadCSV("documents\\uroven_1\\data\\vzdelanieUTF8.csv", insert_vzdelanie);

	for (auto obec : obce_table)
	{
		// Pridanie vzdelania pre obec vo for each
		ds::adt::ImplicitList<int>** found_data;
		if (vzdelanie_table.tryFind(obec.data_->get_code(), found_data))
		{
			obec.data_->set_education(*found_data);
		}

		// Pridanie vzdelania do obci s rovnakym nazvom ako je nazov obce vo for each
		if (!obec.elements_->isEmpty())
		{
			for (auto duplicite_obec = obec.elements_->begin(); duplicite_obec != obec.elements_->end(); ++duplicite_obec)
			{
				if (vzdelanie_table.tryFind((*duplicite_obec)->get_code(), found_data))
				{
					(*duplicite_obec)->set_education(*found_data);
				}
			}
		}
	}

	// Nacitanie udajov o vzdelani pre jednotlive okresy
	for (auto okres : all_okresy)
	{
		ds::adt::ImplicitList<int> okres_vzdelavanie {0, 0, 0, 0, 0, 0, 0, 0};
		bool change = false;

		for (auto it = okres->sons_->begin(); it != okres->sons_->end(); ++it)
		{
			if ((*it)->data_->get_has_education())
			{
				change = true;
				okres_vzdelavanie[0] += (*it)->data_->get_no_education_young();
				okres_vzdelavanie[1] += (*it)->data_->get_basic_education();
				okres_vzdelavanie[2] += (*it)->data_->get_high_lower_education();
				okres_vzdelavanie[3] += (*it)->data_->get_high_higher_education();
				okres_vzdelavanie[4] += (*it)->data_->get_higher_education();
				okres_vzdelavanie[5] += (*it)->data_->get_university_education();
				okres_vzdelavanie[6] += (*it)->data_->get_no_education_old();
				okres_vzdelavanie[7] += (*it)->data_->get_not_clarified();
			}
		}

		// Udaje o vzdelani nastav iba ak aspon jeden vrchol syna obsahuje udaje o vzdelavani
		if (change)
		{
			okres->data_->set_education(&okres_vzdelavanie);
		}
	}


	// Nacitanie udajov o vzdelani pre jednotlive kraje
	for (auto it = root.sons_->begin(); it != root.sons_->end(); ++it)
	{
		ds::adt::ImplicitList<int> kraj_vzdelavanie{ 0, 0, 0, 0, 0, 0, 0, 0 };
		bool change = false;

		for (auto it_okres = (*it)->sons_->begin(); it_okres != (*it)->sons_->end(); ++it_okres)
		{
			if ((*it_okres)->data_->get_has_education())
			{
				change = true;
				kraj_vzdelavanie[0] += (*it_okres)->data_->get_no_education_young();
				kraj_vzdelavanie[1] += (*it_okres)->data_->get_basic_education();
				kraj_vzdelavanie[2] += (*it_okres)->data_->get_high_lower_education();
				kraj_vzdelavanie[3] += (*it_okres)->data_->get_high_higher_education();
				kraj_vzdelavanie[4] += (*it_okres)->data_->get_higher_education();
				kraj_vzdelavanie[5] += (*it_okres)->data_->get_university_education();
				kraj_vzdelavanie[6] += (*it_okres)->data_->get_no_education_old();
				kraj_vzdelavanie[7] += (*it_okres)->data_->get_not_clarified();
			}
		}

		if (change)
		{
			(*it)->data_->set_education(&kraj_vzdelavanie);
		}
	}

}

SearchData::SearchData()
{
	hierarchy = new ds::amt::MultiWayExplicitHierarchy<CSVElement*>();
	fill();
	hierarchy_current_block = static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(hierarchy->accessRoot());
}

SearchData::~SearchData()
{
	searcher.getOutput().clear();

	for (auto element : *hierarchy)
	{
		delete element;
	}

	delete hierarchy;

	for (auto element : kraje_table)
	{
		delete element.elements_;
	}

	for (auto element : okresy_table)
	{
		delete element.elements_;
	}

	for (auto element : obce_table)
	{
		delete element.elements_;
	}

	for (auto element : vzdelanie_table)
	{
		delete element.data_;
	}

	hierarchy = nullptr;
	hierarchy_current_block = nullptr;
}


// Nasledujuci kod bol zobrany z nasledujuceho zdroja
// https://www.appsloveworld.com/cplus/100/39/c-c-utf-8-upper-lower-case-conversions

// Convert UTF-8 byte string to wstring
std::wstring SearchData::to_wstring(std::string const& s) {
	std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	return conv.from_bytes(s);
}

// Convert wstring to UTF-8 byte string
std::string SearchData::to_string(std::wstring const& s) {
	std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	return conv.to_bytes(s);
}

// Converts a UTF-8 encoded string to upper case
std::string SearchData::to_lower(std::string const& s) {
	auto ss = to_wstring(s);
	for (auto& c : ss) {
		c = std::tolower(c, utf8);
	}
	return to_string(ss);
}

