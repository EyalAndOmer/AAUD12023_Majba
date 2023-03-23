#include "SearchData.h"

// Metoda na naplnenie vektora
void SearchData::fill_vector(std::vector<CSVElement*>& vec, std::string file_name)
{
	ds::amt::ImplicitSequence<std::string> values;
	std::string line, element;
	bool first_row = true;
	int val_index;
	std::ifstream file(file_name);

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

			vec.push_back(new CSVElement(values));
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
	// Naplnenie udajovych struktur
	fill_vector(kraje, "documents\\uroven_1\\data\\krajeUTF8.csv");
	fill_vector(okresy, "documents\\uroven_1\\data\\okresyUTF8.csv");
	fill_vector(obce, "documents\\uroven_1\\data\\obceUTF8.csv");
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

