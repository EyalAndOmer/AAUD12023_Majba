#include "SearchData.h"

// Pomocna metoda pre nacitanie uzemnych jednotiek z CSV suboru
void SearchData::loadCSV(const std::string& path, ImplicitList<CSVElement*>& data, std::string UC_type) {
	std::ifstream file(path);
	if (file.is_open()) {
		std::string line, element;
		bool first_row = true;

		while (std::getline(file, line)) {
			if (first_row) {
				first_row = false;
				continue;
			}

			ImplicitList<std::string> values;
			std::stringstream str(line);
			int val_index = 0;

			while (std::getline(str, element, ';')) {
				if (val_index != 0) {
					values.insertLast(element);
				}
				else {
					val_index++;
				}
			}

			// Uprava pripadov kedy vo vectore nie je 5 hodnot, specialne pripady zahranicie, umele doplnenie prazdneho stringu
			if (values.size() < 5) {
				values.insertLast("");
			}

			// Pridanie typu uzemnej jednotky
			values.insertLast(UC_type);
			data.insertLast(new CSVElement(values));
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
	ImplicitList<std::string> root_data{ "SK", "Slovenska Republika", "Slovensko", "Slovensko", "", "republika" };
	root.data_ = new CSVElement(root_data);


	// Nacitanie krajov
	ImplicitList<CSVElement*> kraje;
	loadCSV("documents\\uroven_1\\data\\krajeUTF8.csv", kraje, "kraj");

	for (auto element: kraje) {
		hierarchy->emplaceSon(*hierarchy->accessRoot(), hierarchy->degree(*hierarchy->accessRoot())).data_ = element;
	}


	// Nacitanie okresov
	ImplicitList<CSVElement*> okresy;
	loadCSV("documents\\uroven_1\\data\\okresyUTF8.csv", okresy, "okres");
	size_t son_order = 0;
	std::string current_code = "";

	ImplicitList<ds::amt::MemoryBlock<CSVElement*>*> all_okresy;
	auto current_son = hierarchy->accessSon(*hierarchy->accessRoot(), 0);

	for (auto element : okresy) {
		// Kontrola kodu daneho prvku
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

		hierarchy->emplaceSon(*current_son, hierarchy->degree(*current_son)).data_ = element;
		all_okresy.insertLast(hierarchy->accessSon(*current_son, hierarchy->degree(*current_son) - 1));
	}

	// Nacitanie obci
	ImplicitList<CSVElement*> obce;
	loadCSV("documents\\uroven_1\\data\\obceUTF8.csv", obce, "obec");
	size_t current_okres = 0;
	current_code = all_okresy.accessFirst()->data_->get_code().substr(0, 6);
	current_son = static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(all_okresy.access(current_okres));

	for (auto element : obce) {
		// Kontrola kodu daneho prvku
		if (current_code != element->get_code().substr(0, 6))
		{
			current_code = element->get_code().substr(0, 6);
			++current_okres;
			current_son = static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(all_okresy.access(current_okres));
		}
		hierarchy->emplaceSon(*current_son, hierarchy->degree(*current_son)).data_ = element;
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

	for (auto element: *hierarchy)
	{
		delete element;
	}

	delete hierarchy;

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

