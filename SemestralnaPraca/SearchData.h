#include <libds/amt/implicit_sequence.h>
#include "Searcher.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cwctype>
#include <codecvt>
#include <functional>  // Import pre lambdu

// Enum nazvov suborov

public class SearchData
{
public:
	SearchData();
public:
	// Definicia udajovych struktur
	std::vector<CSVElement*> kraje;
	std::vector<CSVElement*> okresy;
	std::vector<CSVElement*> obce;
	void fill_vector(std::vector<CSVElement*>& vec, std::string file_name);
	Searcher<std::vector<CSVElement*>::iterator, std::string(CSVElement::*)()> searcher;
	std::wstring to_wstring(std::string const& s);
	std::string to_string(std::wstring const& s);
	std::string to_lower(std::string const& s);

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
};