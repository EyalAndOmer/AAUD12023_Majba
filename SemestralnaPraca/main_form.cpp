#include "main_form.h"
#include <Windows.h>
#include <locale>

using namespace System;
using namespace System::Windows::Forms;

void main()
{
	// Nastavil som Active Page Code celeho OS windowsu na 65001, co je zevraj extended ASCII(chcp v CMD).
	// https://stackoverflow.com/a/46922476
	// Nastavil som globalny jazyk na slovencinu a zapol beta funkciu pre cely svet a funguje.
	//   SetConsoleOutputCP(1250);
	//   SetConsoleCP(1250);

	// Nastavenie globalneho locale nefunguje... ale ked ho poslem do funkcie tolower ako parameter locale tak funguje bez chyby...
	/*setlocale(LC_ALL, "en_US.UTF-8");*/

	initHeapMonitor();

	SearchData* data = new SearchData();

	auto it = ds::amt::MultiWayExplicitHierarchy<CSVElement*>::PreOrderHierarchyIterator(data->hierarchy, data->hierarchy->accessSon(*data->hierarchy->accessRoot(), 0));

	data->searcher.search("brat", data->search_from_beginning, &CSVElement::get_short_title, it, data->hierarchy->end());
	auto output = data->searcher.getOutput();

	for (auto el: output)
	{
		std::cout << el->get_official_title() << " " << el->get_medium_title() << " " <<
			el->get_short_title() << " " << el->get_code() << " " << el->get_note() << '\n';
	}

	delete data;

	//std::function<void(const ds::amt::MultiWayExplicitHierarchyBlock<CSVElement*>*)> print_tree = [&](auto el) {
	//	std::cout << el->data_->get_official_title() << " " << el->data_->get_medium_title() << " " <<
	//		el->data_->get_short_title() << " " << el->data_->get_code() << " " << el->data_->get_note() << '\n';
	//};

	//data->hierarchy->processPreOrder(data->hierarchy->accessRoot(), print_tree);




	//auto begin = data->kraje->begin();
	//auto end = data->kraje->end();


	//for (auto it = begin; it != end; ++it)
	//{
	//	std::cout << (*it)->get_short_title() << '\n';
	//}


	// Spustenie GUI
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	//Gui::main_form^ form = gcnew Gui::main_form();
	//Application::Run(form);
}

