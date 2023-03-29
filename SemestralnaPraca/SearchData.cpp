#include "SearchData.h"

// Metoda na naplnenie hierarchie
void SearchData::fill()
{
	// Zadefinovanie korena
	auto& root = this->hierarchy->emplaceRoot();
	ds::amt::ImplicitSequence<std::string> root_data;
	root_data.insertLast().data_ = "SK";
	root_data.insertLast().data_ = "Slovenska Republika";
	root_data.insertLast().data_ = "Slovensko";
	root_data.insertLast().data_ = "Slovensko";
	root_data.insertLast().data_ = "";
	root.data_ = new CSVElement(root_data);

	// Naplnenie krajov
	ds::amt::ImplicitSequence<std::string> values;
	std::string line, element;
	bool first_row = true;
	int val_index;
	std::ifstream file("documents\\uroven_1\\data\\krajeUTF8.csv");

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (first_row)
			{
				first_row = false;
				continue;
			}
			values.clear();

			std::stringstream str(line);
			val_index = 0;

			while (std::getline(str, element, ';'))
			{
				if (val_index != 0)
				{
					values.insertLast().data_ = element;
				}
				else
				{
					val_index++;
				}
			}
			// Uprava pripadov kedy vo vectore nie je 5 hodnot, specialne pripady zahranicie, umele doplnenie prazdneho stringu
			if (values.size() < 5)
			{
				values.insertLast().data_ = "";
			}

			// Pridanie synov do stromu
			hierarchy->emplaceSon(root, hierarchy->degree(root)).data_ = new CSVElement(values);
		}
	}
	else
	{
		throw std::runtime_error("File not found");
	}
	file.close();


	// Pridanie okresov
	size_t son_order = 0;
	std::string current_code = "";
	first_row = true;
	file = std::ifstream("documents\\uroven_1\\data\\okresyUTF8.csv");
	// Vyrobenie zoznamu vsetkych vytvorenych okresov
	ds::amt::ImplicitSequence<ds::amt::ExplicitHierarchyBlock<CSVElement*>*> all_okresy;
	auto current_son = hierarchy->accessSon(root, 0);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (first_row)
			{
				first_row = false;
				continue;
			}
			values.clear();

			std::stringstream str(line);
			val_index = 0;

			while (std::getline(str, element, ';'))
			{
				if (val_index != 0)
				{
					values.insertLast().data_ = element;
				}
				else
				{
					val_index++;
				}
			}
			// Uprava pripadov kedy vo vectore nie je 5 hodnot, specialne pripady zahranicie, umele doplnenie prazdneho stringu
			if (values.size() < 5)
			{
				values.insertLast().data_ = "";
			}

			// Kontrola kodu daneho prvku
			if (current_code == "")
			{
				current_code = values.access(0)->data_.substr(0, 5);
			} else
			{
				if (current_code != values.access(0)->data_.substr(0, 5))
				{
					current_code = values.access(0)->data_.substr(0, 5);
					++son_order;
					current_son = hierarchy->accessSon(root, son_order);
				}
			}

			std::cout << current_code << " " << son_order << '\n';

			// Pridanie synov do stromu
			hierarchy->emplaceSon(*current_son, hierarchy->degree(*current_son)).data_ = new CSVElement(values);
			all_okresy.insertLast().data_ = hierarchy->accessSon(*current_son, hierarchy->degree(*current_son) - 1);
		}
	}
	else
	{
		throw std::runtime_error("File not found");
	}
	file.close();


	// Pridanie obci
	size_t current_okres = 0;
	current_code = all_okresy.accessFirst()->data_->data_->get_code().substr(0, 6);
	current_son = static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(all_okresy.access(current_okres)->data_);
	first_row = true;
	file = std::ifstream("documents\\uroven_1\\data\\obceUTF8.csv");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (first_row)
			{
				first_row = false;
				continue;
			}
			values.clear();

			std::stringstream str(line);
			val_index = 0;

			while (std::getline(str, element, ';'))
			{
				if (val_index != 0)
				{
					values.insertLast().data_ = element;
				}
				else
				{
					val_index++;
				}
			}
			// Uprava pripadov kedy vo vectore nie je 5 hodnot, specialne pripady zahranicie, umele doplnenie prazdneho stringu
			if (values.size() < 5)
			{
				values.insertLast().data_ = "";
			}

			// Kontrola kodu daneho prvku
			if (current_code != values.access(0)->data_.substr(0, 6))
			{
				current_code = values.access(0)->data_.substr(0, 6);
				++current_okres;
				current_son = static_cast<ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*>(all_okresy.access(current_okres)->data_);
			}

			// Pridanie synov do stromu
			hierarchy->emplaceSon(*current_son, hierarchy->degree(*current_son)).data_ = new CSVElement(values);
		}
	}
	else
	{
		throw std::runtime_error("File not found");
	}
	file.close();
}

SearchData::SearchData()
{
	hierarchy = new ds::amt::MultiWayExplicitHierarchy<CSVElement*>();

	fill();
}

SearchData::~SearchData()
{
	for (auto element: *hierarchy)
	{
		delete element;
	}

	delete hierarchy;

	hierarchy = nullptr;
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

