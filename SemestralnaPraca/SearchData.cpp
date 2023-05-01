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
	}
	else {
		throw std::runtime_error("File not found");
	}
	file.close();
}

// Metoda na naplnenie hierarchie
void SearchData::fill()
{
	// Zadefinovanie korena
	auto& root = hierarchy->emplaceRoot();
	ds::adt::ImplicitList<std::string> root_data{ "SK", "Slovenska Republika", "Slovensko", "Slovensko", "", "republika" };
	root.data_ = new CSVElement(root_data);


	// Nacitanie krajov
	std::function<void(ds::adt::ImplicitList<std::string>)> insert_kraj = [&](ds::adt::ImplicitList<std::string> content) {
		content.insertLast("kraj");
		// Zmazanie ID prvku
		content.removeFirst();
		auto element = new CSVElement(content);

		auto* inserted_hierarchy_block = hierarchy->emplaceSon(*hierarchy->accessRoot(), hierarchy->degree(*hierarchy->accessRoot())).data_ = element;
		this->kraje_table.insertWithDuplicities(inserted_hierarchy_block->get_official_title(), inserted_hierarchy_block);
	};

	ds::adt::ImplicitList<CSVElement*> kraje;
	loadCSV("documents\\uroven_1\\data\\krajeUTF8.csv", insert_kraj);



	// Nacitanie okresov
	size_t son_order = 0;
	std::string current_code = "";
	ds::adt::ImplicitList<ds::amt::MemoryBlock<CSVElement*>*> all_okresy;
	auto current_son = hierarchy->accessSon(*hierarchy->accessRoot(), 0);

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
				++son_order;
				current_son = hierarchy->accessSon(*hierarchy->accessRoot(), son_order);
			}
		}

		auto* inserted_hierarchy_block = hierarchy->emplaceSon(*current_son, hierarchy->degree(*current_son)).data_ = element;
		this->okresy_table.insertWithDuplicities(inserted_hierarchy_block->get_official_title(), inserted_hierarchy_block);

		all_okresy.insertLast(hierarchy->accessSon(*current_son, hierarchy->degree(*current_son) - 1));
	};

	loadCSV("documents\\uroven_1\\data\\okresyUTF8.csv", insert_okres);

	// Nacitanie obci
	size_t current_okres = 0;
	current_code = all_okresy.accessFirst()->data_->get_code().substr(0, 6);
	current_son = static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(all_okresy.access(current_okres));

	std::function<void(ds::adt::ImplicitList<std::string>)> insert_obec = [&](ds::adt::ImplicitList<std::string> content)
	{
		content.insertLast("obec");
		content.removeFirst();
		auto element = new CSVElement(content);
		if (current_code != element->get_code().substr(0, 6))
		{
			current_code = element->get_code().substr(0, 6);
			++current_okres;
			current_son = static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(all_okresy.access(current_okres));
		}
		auto* inserted_hierarchy_block = hierarchy->emplaceSon(*current_son, hierarchy->degree(*current_son)).data_ = element;
		this->obce_table.insertWithDuplicities(inserted_hierarchy_block->get_official_title(), inserted_hierarchy_block);
	};

	loadCSV("documents\\uroven_1\\data\\obceUTF8.csv", insert_obec);

	// Nacitanie udajov o vzdelani
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
		ds::adt::ImplicitList<int>** found_data;
		if (vzdelanie_table.tryFind(obec.data_->get_code(), found_data))
		{
			obec.data_->set_education(*found_data);
		}
	}

	for (auto okres : all_okresy)
	{
		ds::adt::ImplicitList<int> okres_vzdelavanie {0, 0, 0, 0, 0, 0, 0, 0};
		for (auto it = static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(okres)->sons_->begin(); it != static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(okres)->sons_->end(); ++it)
		{
			if ((*it)->data_->get_has_education())
			{
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
		okres->data_->set_education(&okres_vzdelavanie);
	}

	for (auto it = root.sons_->begin(); it != root.sons_->end(); ++it)
	{
		ds::adt::ImplicitList<int> kraj_vzdelavanie{ 0, 0, 0, 0, 0, 0, 0, 0 };
		for (auto it_kraj = (*it)->sons_->begin(); it_kraj != (*it)->sons_->end(); ++it_kraj)
		{
			kraj_vzdelavanie[0] += (*it_kraj)->data_->get_no_education_young();
			kraj_vzdelavanie[1] += (*it_kraj)->data_->get_basic_education();
			kraj_vzdelavanie[2] += (*it_kraj)->data_->get_high_lower_education();
			kraj_vzdelavanie[3] += (*it_kraj)->data_->get_high_higher_education();
			kraj_vzdelavanie[4] += (*it_kraj)->data_->get_higher_education();
			kraj_vzdelavanie[5] += (*it_kraj)->data_->get_university_education();
			kraj_vzdelavanie[6] += (*it_kraj)->data_->get_no_education_old();
			kraj_vzdelavanie[7] += (*it_kraj)->data_->get_not_clarified();
		}
		(*it)->data_->set_education(&kraj_vzdelavanie);
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

	for (auto element : vzdelanie_table)
	{
		delete element.data_;
	}

	hierarchy = nullptr;
	hierarchy_current_block = nullptr;
}

// nutne pre fungovanie tolower pre specialne znaky ako je ž, š, č... Bez tohoto je kod funkcny, ale std::tolower nepremeni
// specialne znaky Ž, Č... na ž, č...
std::locale const utf8("en_US.UTF-8");


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

