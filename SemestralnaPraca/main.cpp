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
			// Uprava pripadov kedy vo vectore nie je 5 hodnot, umele doplnenie prazdneho stringu
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
	//SetConsoleOutputCP(1250);
	//SetConsoleCP(1250);


	// Definicia path nefunguje, SPYTAT SA!!!
	//auto path = std::filesystem::current_path();
	//path.append("documents\\uroven1\\data\\kraje.csv");
	//std::cout << path << '\n';

	// Definicia udajovych struktur
	std::vector<CSVElement*> kraje;
	std::vector<CSVElement*> okresy;
	std::vector<CSVElement*> obce;

	// Naplnenie udajovych struktur
	fill_vector(kraje, "kraje.csv");
	fill_vector(okresy, "okresy.csv");
	fill_vector(obce, "obce.csv");

	// Definicia lambda funkcii
	auto seach_from_beginning = [](const std::string& element, const std::string& substring) {
		// find vracia index od ktoreho sa zacina substring
		// alebo -1 ked neexistuje
		return element.find(substring) == 0;
	};

	auto search_substring = [](const std::string& element, const std::string& substring) {
		// std::string::npos vracia maximalnu hodnotu size_t
		return element.find(substring) != std::string::npos;
	};

	// Otestovanie vyhladavacieho algoritmu
	Searcher<std::vector<CSVElement*>::iterator, std::string(CSVElement::*)()> searcher(obce.begin(), obce.end());

	std::string substring = "Tren";

	searcher.search(substring, seach_from_beginning, &CSVElement::get_official_title);
	searcher.print();

}