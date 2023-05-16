#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cwctype>
#include <codecvt>
#include <functional>

#include "Searcher.h"
#include <libds/amt/explicit_hierarchy.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include <libds/adt/sorts.h>
#include "Filter.h"

public class SearchData
{
public:
	// Hierarcha UC
	ds::amt::MultiWayExplicitHierarchy<CSVElement*>* hierarchy;
	ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>* hierarchy_current_block;

	// Prehladavacie tabulky jednotlivych urovni UC
	ds::adt::Treap<std::string, CSVElement*> kraje_table;
	ds::adt::Treap<std::string, CSVElement*> okresy_table;
	ds::adt::Treap<std::string, CSVElement*> obce_table;
	ds::adt::Treap<std::string, ds::adt::ImplicitList<int>*> vzdelanie_table;

public:
	// nutne pre fungovanie tolower pre specialne znaky ako je ž, š, č... Bez tohoto je kod funkcny, ale std::tolower nepremeni
   // specialne znaky Ž, Č... na ž, č...
	std::locale const utf8 = std::locale("sk_SK.UTF-8");

	// Definicia lambda funkcii
	std::function<bool(const std::string&, const std::string&)> search_from_beginning = [this](const std::string& element, const std::string& substring) {
		// find vracia index od ktoreho sa zacina substring
		// alebo -1 ked neexistuje
		// Pre prekonvertovanie velkych specialnych znakov ako je Ž, Č alebo Š musime cely string prekonvertovat na wstring
		// nasledne zavolat towlower funkciu a string nasladne dat do povodneho string formatu

		std::string lowercaseSubstring = to_lower(substring);
		std::string lowercaseElement = to_lower(element);

		return lowercaseElement.find(lowercaseSubstring) == 0;
	};

	std::function<bool(const std::string&, const std::string&)> search_substring = [this](const std::string& element, const std::string& substring) {
		// std::string::npos vracia maximalnu hodnotu size_t

		std::string lowercaseSubstring = to_lower(substring);
		std::string lowercaseElement = to_lower(element);

		return lowercaseElement.find(lowercaseSubstring) != std::string::npos;
	};

	std::function<bool(const std::string&, const std::string&)> has_type = [this](const std::string& selectedUC, const std::string& elementUC) {
		return selectedUC == elementUC;
	};

	// Lambda funkcia pouzita pri filtrovani
	std::function<bool(const int&, const Filter*)> compare_numeric = [this](const int& value, const Filter* selectedFilter) {
		return selectedFilter->compare(value);
	};

	// Lambda funkcie pre sortovanie

	// Pomocna funkcia pre zistenie poctu samohlasok v slove
	int getVowelCount(std::string& str);

	std::function<bool(CSVElement*, CSVElement*)> compareAlphabetical = [this](CSVElement* l, CSVElement* r) -> bool
	{
		const std::collate<char>& coll = std::use_facet<std::collate<char>>(utf8);
		std::string& name_1 = l->get_official_title();
		std::string& name_2 = r->get_official_title();

		int result = coll.compare(name_1.data(), name_1.data() + name_1.length(),
			name_2.data(), name_2.data() + name_2.length());

		return result < 0;
	};

	std::function<bool(CSVElement*, CSVElement*)> compareVowelsCount = [&](CSVElement* l, CSVElement* r) -> bool
	{
		return getVowelCount(l->get_official_title()) > getVowelCount(r->get_official_title());
	};

public:
	SearchData();
	~SearchData();
	void fill();
	void loadCSV(const std::string& path, std::function<void(ds::adt::ImplicitList<std::string> content)> insert_function);

private:
	std::wstring to_wstring(std::string const& s);
	std::string to_string(std::wstring const& s);
	std::string to_lower(std::string const& s);
};