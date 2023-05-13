#include "Searcher.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cwctype>
#include <codecvt>
#include <functional>
#include <libds/amt/explicit_hierarchy.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include <libds/adt/sorts.h>

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


private:
	// nutne pre fungovanie tolower pre specialne znaky ako je ž, š, č... Bez tohoto je kod funkcny, ale std::tolower nepremeni
   // specialne znaky Ž, Č... na ž, č...
	std::locale const utf8 = std::locale("en_US.UTF-8");

public:
	SearchData();
	~SearchData();
	void fill();
	void loadCSV(const std::string& path, std::function<void(ds::adt::ImplicitList<std::string> content)> insert_function);
	Searcher<ds::amt::MultiWayExplicitHierarchy<CSVElement*>::PreOrderHierarchyIterator, std::string(CSVElement::*)()> searcher;

private:
	std::wstring to_wstring(std::string const& s);
	std::string to_string(std::wstring const& s);
	std::string to_lower(std::string const& s);
};