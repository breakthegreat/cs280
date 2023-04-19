/* Implementation of Recursive-Descent Parser
 * parse.cpp
 * Programming Assignment 2
 * Spring 2023
 */

#include "parserInt.h"
using namespace std;
map<string, bool> defVar;
map<string, Token> SymTable;
map<string, Value> TempsResults; // Container of temporary locations of Value objects for results of expressions, variables values and constants
queue<Value> *ValQue;						 // declare a pointer variable to a queue of Value objects

namespace Parser
{
	bool pushed_back = false;
	LexItem pushed_token;

	static LexItem GetNextToken(istream &in, int &line)
	{
		if (pushed_back)
		{
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem &t)
	{
		if (pushed_back)
		{
			abort();
		}
		pushed_back = true;
		pushed_token = t;
	}

}

static int error_count = 0;

int ErrCount()
{
	return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << error_count << ". Line # " << line << ": " << msg << endl;
}

// bool IdentList(istream& in, int& line);

// Program is: Prog ::= StmtList
bool Prog(istream &in, int &line)
{
	bool f1;
	LexItem tok = Parser::GetNextToken(in, line);

	if (tok.GetToken() == DONE && tok.GetLinenum() <= 1)
	{
		ParseError(line, "Empty File");
		return true;
	}
	Parser::PushBackToken(tok);
	f1 = StmtList(in, line);

	if (!f1)
	{
		ParseError(line, "Missing Program");
		return false;
	}
	else
		return true;
} // End of Prog

// StmtList ::= Stmt; { Stmt; }
bool StmtList(istream &in, int &line)
{
	bool status;

	LexItem tok;

	status = Stmt(in, line);
	while (status)
	{
		tok = Parser::GetNextToken(in, line);
		if (tok == DONE)
		{
			cout << endl;
			cout << "("
					 << "DONE"
					 << ")" << endl;
			Parser::PushBackToken(tok);
			return true;
		}
		else if (tok == RBRACES)
		{
			Parser::PushBackToken(tok);
			return true;
		}

		if (tok != SEMICOL)
		{
			ParseError(line, "Missing semicolon at end of Statement.");
			return false;
		}

		status = Stmt(in, line);
	}

	tok = Parser::GetNextToken(in, line);
	if (tok == ELSE)
	{
		ParseError(line, "Missing right brace.");
		return false;
	}
	else if (tok == RBRACES)
	{
		Parser::PushBackToken(tok);
		return true;
	}

	else
	{
		ParseError(line, "Syntactic error in Program Body.");
		return false;
	}

} // End of StmtList function

// Stmt ::= AssignStme | WriteLnStmt | IfStmt
bool Stmt(istream &in, int &line)
{
	bool status = false;

	LexItem t = Parser::GetNextToken(in, line);

	switch (t.GetToken())
	{
	case SIDENT:
	case NIDENT:
		Parser::PushBackToken(t);
		status = AssignStmt(in, line);
		if (!status)
		{
			ParseError(line, "Incorrect Assignment Statement.");
			return status;
		}
		break;
	case WRITELN:

		status = WritelnStmt(in, line);

		if (!status)
		{
			ParseError(line, "Incorrect Writeln Statement.");
			return status;
		}
		break;
	case IF:
		status = IfStmt(in, line);

		if (!status)
		{
			ParseError(line, "Incorrect If-Statement.");
			return status;
		}
		break;
	case ELSE:
		Parser::PushBackToken(t);
		return false;
		break;
	case IDENT:
		ParseError(line, "Invalid variable name");

		Parser::PushBackToken(t);
		return false;
		break;
	default:
		Parser::PushBackToken(t);
		return true;
	}
	return status;
} // End of Stmt function

// WritelnStmt:= WRITELN (ExpreList)
bool WritelnStmt(istream &in, int &line)
{
	LexItem t;
	ValQue = new queue<Value>;

	t = Parser::GetNextToken(in, line);
	if (t != LPAREN)
	{

		ParseError(line, "Missing Left Parenthesis of Writeln Statement");
		return false;
	}

	bool ex = ExprList(in, line);

	if (!ex)
	{
		ParseError(line, "Missing expression list after Print");
		while (!(*ValQue).empty())
		{
			ValQue->pop();
		}
		delete ValQue;
		return false;
	}

	// Evaluate: writeln by printing out the list of expressions' values
	while (!(*ValQue).empty())
	{
		Value nextVal = (*ValQue).front();
		cout << nextVal;
		ValQue->pop();
	}
	cout << endl;

	t = Parser::GetNextToken(in, line);
	if (t != RPAREN)
	{

		ParseError(line, "Missing Right Parenthesis of Writeln Statement");
		return false;
	}
	// cout << endl;
	return true;
} // End of WritelnStmt

// IfStmt:= IF (Expr) '{' StmtList '}' [ Else '{' StmtList '}' ]
bool IfStmt(istream &in, int &line)
{
	bool ex = false, status;
	LexItem t;

	t = Parser::GetNextToken(in, line);
	if (t != LPAREN)
	{

		ParseError(line, "Missing Left Parenthesis of If condition");
		return false;
	}

	Value retVal;
	ex = Expr(in, line, retVal);
	if (retVal.GetType() != VBOOL)
	{
		ParseError(line, "Illegal expresison if statement");
		return false;
	}

	if (!ex)
	{
		ParseError(line, "Missing if statement Logic Expression");
		return false;
	}

	t = Parser::GetNextToken(in, line);
	if (t != RPAREN)
	{

		ParseError(line, "Missing Right Parenthesis of If condition");
		return false;
	}

	if (retVal.GetBool() == true)
	{
		t = Parser::GetNextToken(in, line);
		if (t != LBRACES)
		{
			ParseError(line, "If Statement Syntax Error: Missing left brace");
			return false;
		}

		status = StmtList(in, line);
		if (!status)
		{
			ParseError(line, "Missing Statement for If-Stmt Clause");
			return false;
		}
		t = Parser::GetNextToken(in, line);
		if (t != RBRACES)
		{
			ParseError(line, "If Statement Syntax Error: Missing right brace.");
			return false;
		}
		do
		{
			t = Parser::GetNextToken(in, line);
		} while (t != RBRACES);
	}
	else
	{
		do
		{
			t = Parser::GetNextToken(in, line);
		} while (t != ELSE);

		// t = Parser::GetNextToken(in, line);

		if (t == ELSE)
		{
			t = Parser::GetNextToken(in, line);
			if (t != LBRACES)
			{
				ParseError(line, "If Statement Syntax Error: Missing left brace");
				return false;
			}
			status = StmtList(in, line);
			if (!status)
			{
				ParseError(line, "Missing Statement for Else-Clause");
				return false;
			}
			t = Parser::GetNextToken(in, line);
			if (t != RBRACES)
			{
				Parser::PushBackToken(t);
				ParseError(line, "If Statement Syntax Error: Missing right brace.");
				return false;
			}
			// Parser::PushBackToken(t);
		}
		else
		{
			Parser::PushBackToken(t);
			return true;
		}
	}
	return true;
} // End of IfStmt function

// Var ::= NIDENT | SIDENT
bool Var(istream &in, int &line, LexItem &idtok)
{
	string identstr;

	LexItem tok = Parser::GetNextToken(in, line);

	if (tok == NIDENT || tok == SIDENT)
	{
		identstr = tok.GetLexeme();

		if (!(defVar.find(identstr)->second))
		{
			defVar[identstr] = true;
			SymTable[identstr] = tok.GetToken();
		}
		return true;
	}
	else if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");

		return false;
	}

	return false;
} // End of Var

// AssignStmt:= Var = Expr
bool AssignStmt(istream &in, int &line)
{
	bool varstatus = false, status = false;
	LexItem t;
	Value retVal;
	LexItem temp = Parser::GetNextToken(in, line);
	string var = temp.GetLexeme();
	Parser::PushBackToken(temp);
	varstatus = Var(in, line, t);

	if (varstatus)
	{

		Token type =SymTable[var]; 
		// 
		t = Parser::GetNextToken(in, line);


		if (t == ASSOP)
		{

			status = Expr(in, line, retVal);

			if (!status)
			{
				ParseError(line, "Missing Expression in Assignment Statement");
				return status;
			}
		}
		else if (t.GetToken() == ERR)
		{
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << t.GetLexeme() << ")" << endl;
			return false;
		}
		else
		{
			ParseError(line, "Missing Assignment Operator");
			return false;
		}
		//
		ValType type2 = retVal.GetType();
		if(type == NIDENT){
			if(type2 != VREAL && type2 != VINT){
				ParseError(line,"illegal assignment");
				return false;
			}
	}
	if(type == SIDENT){
		if(type2 == VBOOL){
			ParseError(line,"illegal assignment");
				return false;
		}

	}

		
		TempsResults[var] = retVal;
	}
	else
	{
		ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
		return false;
	}

	return status;
} // End of AssignStmt

// ExprList:= Expr {,Expr}
bool ExprList(istream &in, int &line)
{
	bool status = false;
	Value retVal;

	status = Expr(in, line, retVal);
	if (!status)
	{
		ParseError(line, "Missing Expression");
		return false;
	}
	ValQue->push(retVal);
	LexItem tok = Parser::GetNextToken(in, line);

	if (tok == COMMA)
	{
		status = ExprList(in, line);
	}
	else if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else
	{
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
} // End of ExprList

// Expr ::= EqualExpr ::= RelExpr [(-EQ|==) RelExpr ]
bool Expr(istream &in, int &line, Value &retVal)
{
	LexItem tok;
	bool t1 = RelExpr(in, line, retVal);
	Value leftHand = retVal;
	if (!t1)
	{
		return false;
	}

	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if (tok == NEQ || tok == SEQ)
	{
		t1 = RelExpr(in, line, retVal);
		if (!t1)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

		if (tok == NEQ)
		{
			retVal = (leftHand == retVal);
		}
		if (tok == SEQ)
		{
			retVal = (leftHand.SEqual(retVal));
		}
		if (retVal.GetType() == VERR)
		{
			ParseError(line, "error");
			return false;
		}

		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR)
		{
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
} // End of Expr/EqualExpr

// RelExpr ::= AddExpr [ ( -LT | -GT | < | > )  AddExpr ]
bool RelExpr(istream &in, int &line, Value &retVal)
{
	LexItem tok;
	bool t1 = AddExpr(in, line, retVal);

	if (!t1)
	{
		return false;
	}
	Value leftHand = retVal;
	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if (tok == NGTHAN || tok == NLTHAN || tok == SGTHAN || tok == SLTHAN)
	{
		t1 = AddExpr(in, line, retVal);
		if (!t1)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

		if (tok == NGTHAN)
		{
			retVal = leftHand > retVal;
		}
		if (tok == NLTHAN)
		{

			retVal = leftHand < retVal;
		}
		if (tok == SGTHAN)
		{

			retVal = leftHand.SGthan(retVal);
		}
		if (tok == SLTHAN)
		{
			retVal = leftHand.SLthan(retVal);
		}
		if (retVal.GetType() == VERR)
		{

			ParseError(line, "error illegal operand type");
			return false;
		}

		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR)
		{
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}

	Parser::PushBackToken(tok);
	return true;
} // End of RelExpr

// AddExpr :: MultExpr { ( + | - | .) MultExpr }
bool AddExpr(istream &in, int &line, Value &retVal)
{

	bool t1 = MultExpr(in, line, retVal);
	LexItem tok;

	if (!t1)
	{
		return false;
	}
	Value leftHand = retVal;

	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while (tok == PLUS || tok == MINUS || tok == CAT)
	{
		t1 = MultExpr(in, line, retVal);
		if (!t1)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

		if (tok == PLUS)
		{
			retVal = leftHand + retVal;
			leftHand = retVal;
		}
		if (tok == MINUS)
		{
			retVal = leftHand - retVal;
			leftHand = retVal;
		}

		if (tok == CAT)
		{
			retVal = leftHand.Catenate(retVal);
			leftHand = retVal;
		}
		if (retVal.GetType() == VERR)
		{
			// cout << leftHand << endl;
			ParseError(line, "illegal operand type in AddExpr");
			return false;
		}

		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR)
		{
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
} // End of AddExpr

// MultExpr ::= ExponExpr { ( * | / | **) ExponExpr }
bool MultExpr(istream &in, int &line, Value &retVal)
{

	bool t1 = ExponExpr(in, line, retVal);

	LexItem tok;

	if (!t1)
	{
		return false;
	}
	Value leftHand = retVal;

	tok = Parser::GetNextToken(in, line);
	if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while (tok == MULT || tok == DIV || tok == SREPEAT)
	{

		t1 = ExponExpr(in, line, retVal);

		if (!t1)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

		if (tok == MULT)
		{

			retVal = leftHand * retVal;
			leftHand = retVal;
		}
		if (tok == DIV)
		{

			retVal = leftHand / retVal;
			leftHand = retVal;
		}
		if (tok == SREPEAT)
		{

			retVal = leftHand.Repeat(retVal);
			leftHand = retVal;
		}

		if (retVal.GetType() == VERR)
		{

			ParseError(line, "illegal  operand type in MULTEXPR");
			return false;
		}

		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR)
		{
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
} // End of MultExpr

// ExponExpr ::= UnaryExpr { ^ UnaryExpr }
// enforcing right associativity using right recursiveness
bool ExponExpr(istream &in, int &line, Value &retVal)
{
	bool status;

	status = UnaryExpr(in, line, retVal);
	if (!status)
	{
		return false;
	}
	Value leftHand = retVal;
	LexItem tok = Parser::GetNextToken(in, line);
	if (tok == EXPONENT)
	{
		status = ExponExpr(in, line, retVal);
		if (!status)
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}

		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == ERR)
		{
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}

		retVal = leftHand.operator^(retVal);

		if (retVal.GetType() == VERR)
		{
			ParseError(line, "Illegal operand type for operation");
			return false;
		}
	}
	else if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	Parser::PushBackToken(tok);
	return true;
} // End of ExponExpr

// UnaryExpr ::= ( - | + ) PrimaryExpr | PrimaryExpr
bool UnaryExpr(istream &in, int &line, Value &retVal)
{
	LexItem t = Parser::GetNextToken(in, line);
	bool status;
	int sign = 0;

	
	if (t == MINUS)
	{
		
		 t = Parser::GetNextToken(in, line);
		 if(t.GetToken() == SCONST){
			Parser::PushBackToken(t);
			ParseError(line,"illegal string in front of minus ");
			return false;
		 }
		 Parser::PushBackToken(t);

		sign = -1;
	
		
	}

	else if (t == PLUS)
	{
		sign = 1;
	}
	else
		Parser::PushBackToken(t);

	status = PrimaryExpr(in, line, sign, retVal);
	return status;
}
// End of UnaryExpr

// PrimaryExpr ::= IDENT | NIDENT | SIDENT | ICONST | RCONST | SCONST | ( Expr )
bool PrimaryExpr(istream &in, int &line, int sign, Value &retVal)
{
	// assign retVal a value.
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == NIDENT || tok == SIDENT)
	{

		string lexeme = tok.GetLexeme();
		if (!(defVar.find(lexeme)->second))
		{
			ParseError(line, "Using Undefined Variable");
			return false;
		}
		if (tok == SIDENT)
		{
			
			retVal = TempsResults[tok.GetLexeme()];
			
			
		}
		else if (tok == NIDENT)
		{

			retVal = TempsResults[tok.GetLexeme()];
			if(sign == -1){
			double value = retVal.GetReal();
			value *= -1;
			retVal.SetReal(value);
			}

		}

		return true;
	}
	else if (tok == ICONST)
	{
		
		retVal.SetType(VREAL);
		double value = stod(tok.GetLexeme());
		if (sign == -1)
		{
			value *= -1;
		}
		retVal.SetReal(value);
		return true;
	}
	else if (tok == SCONST)
	{ // STRING
		


		retVal.SetType(VSTRING);
		retVal.SetString(tok.GetLexeme());

		return true;
	}
	else if (tok == RCONST)
	{
		string lex = tok.GetLexeme();
		int size = lex.size() - 1;
		if (lex[size] == '.')
		{
			retVal.SetType(VINT);
			int value = stoi(lex);
			if (sign == -1)
			{
				value *= -1;
			}
			retVal.SetInt(value);
			return true;
		}

		retVal.SetType(VREAL);
		double value = stod(tok.GetLexeme());
		if (sign == -1)
		{
			value *= -1;
		}

		retVal.SetReal(value);
		return true;
	}
	else if (tok == LPAREN)
	{

		bool ex = Expr(in, line, retVal);
		if (!ex)
		{
			ParseError(line, "Missing expression after Left Parenthesis");
			return false;
		}
		if (Parser::GetNextToken(in, line) == RPAREN)
			return ex;
		else
		{
			Parser::PushBackToken(tok);
			ParseError(line, "Missing right Parenthesis after expression");
			return false;
		}
	}
	else if (tok.GetToken() == ERR)
	{
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}

	return false;
}
