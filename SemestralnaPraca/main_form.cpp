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

	// Nastavenie globalneho locale nefunguje... ale ked ho poslem do funkcie tolower tak funguje bez chyby...
	/*setlocale(LC_ALL, "en_US.UTF-8");*/

	SearchData* data = new SearchData();
	// Spustenie GUI
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Gui::main_form form(data);
	Application::Run(% form);
}

