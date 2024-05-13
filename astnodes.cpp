#include<vector>
#include<memory>
#include"lexer.cpp"

class ExprAST {
public:
	virtual ~ExprAST() = default;

	virtual Value* codegen() = 0;
};

class  NumberExprAST : public ExprAST {
	double Val;

public:
	NumberExprAST(double V) : Val(V) {}
	Value* codegen() override;
};

class VariableExprAST : public ExprAST {
	std::string Name;

public:
	VariableExprAST(const std::string &N) : Name(N) {}
	Value* codegen() override;
};

class BinaryExprAST : public ExprAST {
	char Op;
	std::unique_ptr<ExprAST> LHS, RHS;

public:
	BinaryExprAST(
		char Op,
		std::unique_ptr<ExprAST> LHS,
		std::unique_ptr<ExprAST> RHS
		) : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
	Value* codegen() override;
};

class CallExprAST : public ExprAST {
	std::string Callee;
	std::vector<std::unique_ptr<ExprAST>> Args;

public:
	CallExprAST(const std::string &Callee,
				std::vector<std::unique_ptr<ExprAST>> Args
	) : Callee(Callee), Args(std::move(Args)) {}
	Value* codegen() override;
};

class PrototypeAST {
	std::string Name;
	std::vector<std::string> Args;
	
public:
	PrototypeAST(const std::string& name, std::vector<std::string> Args)
		: Name(name), Args(std::move(Args)) {}
	Function* codegen();
	const std::string& getName() const { return Name; }
};

class FunctionAST {
	std::unique_ptr<PrototypeAST> Proto;
	std::unique_ptr<ExprAST> Body;

public:
	FunctionAST(std::unique_ptr<PrototypeAST> Proto,
		std::unique_ptr<ExprAST> Body)
		: Proto(std::move(Proto)), Body(std::move(Body)) {}
	Function* codegen();
};