#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include "Searcher.h"

void fill_vector(std::vector<CSVElement*>& vec, std::string file_name)
{
	std::vector<std::string> values;
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
					values.push_back(element);
				}
				else
				{
					val_index++;
				}
			}
			// Uprava pripadov kedy vo vectore nie je 5 hodnot, specialne pripady zahranicie, umele doplnenie prazdneho stringu
			if (values.size() < 5)
			{
				values.push_back("");
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

void main()
{
	// Nastavil som Active Page Code celeho OS windowsu na 65001, co je zevraj extended ASCII(chcp v CMD).
	// https://stackoverflow.com/a/46922476
	// Nastavil som globalny jazyk na slovencinu a zapol beta funkciu pre cely svet a funguje.
	// SetConsoleOutputCP(1250);
	// SetConsoleCP(1250);
	// setlocale(LC_ALL, "slovak");

	// Definicia udajovych struktur
	std::vector<CSVElement*> kraje;
	std::vector<CSVElement*> okresy;
	std::vector<CSVElement*> obce;

	// Naplnenie udajovych struktur
	fill_vector(kraje, "documents\\uroven_1\\data\\kraje.csv");
	fill_vector(okresy, "documents\\uroven_1\\data\\okresy.csv");
	fill_vector(obce, "documents\\uroven_1\\data\\obce.csv");

	// Definicia lambda funkcii
	auto search_from_beginning = [](std::string& element,std::string& substring) {
		// find vracia index od ktoreho sa zacina substring
		// alebo -1 ked neexistuje
		std::string lowercaseElement;
		for (char c : element) {
			lowercaseElement += std::tolower(c);
		}
		std::string lowercaseSubstring;
		for (char c : substring) {
			lowercaseSubstring += std::tolower(c);
		}
		return lowercaseElement.find(lowercaseSubstring) == 0;
	};

	auto search_substring = [](const std::string& element, const std::string& substring) {
		// std::string::npos vracia maximalnu hodnotu size_t
		std::string lowercaseElement;
		for (char c : element) {
			lowercaseElement += std::tolower(c);
		}
		std::string lowercaseSubstring;
		for (char c : substring) {
			lowercaseSubstring += std::tolower(c);
		}

		return lowercaseElement.find(lowercaseSubstring) != std::string::npos;
	};

	// Otestovanie vyhladavacieho algoritmu
	// std::string(CSVElement::*)() -> daj mi vsetky metody z triedy CSVElement, ktore nemaju ziadne parametre a vracaju std::string
	Searcher<std::vector<CSVElement*>::iterator, std::string(CSVElement::*)()> searcher(obce.begin(), obce.end());

	std::string substring = "dubnica";

	searcher.search(substring, search_substring, &CSVElement::get_official_title);
	searcher.print();

}
