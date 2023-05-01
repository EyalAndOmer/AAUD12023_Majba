#include "main_form.h"
#include <Windows.h>
#include <locale>

using namespace System;
using namespace System::Windows::Forms;

void main()
{
	initHeapMonitor();

	// Spustenie GUI
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Gui::main_form^ form = gcnew Gui::main_form();
	Application::Run(form);

}

