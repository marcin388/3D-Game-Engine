#include <Engine/App/Application.h>

int main()
{
	Application app;
	app.create_Window(1980, 1080);
	//app.run("Game");
	app.run("Editor");
	return 0;
}