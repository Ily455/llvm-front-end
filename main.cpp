#include"tlparse.cpp"
int main() {
	BinopPrecedence['<'] = 10;
	BinopPrecedence['+'] = 20;
	BinopPrecedence['-'] = 20;
	BinopPrecedence['*'] = 40;

	fprintf(stderr, "ready> ");
	getNextToken();

	InitializeModule();

	MainLoop();

	TheModule->print(errs(), nullptr);

	return 0;
}