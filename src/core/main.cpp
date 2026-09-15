#include "Application.h"

int main() {
	Application application;
	application.initialize();
	application.createShaders();
	application.run();
	application.destroy();
}