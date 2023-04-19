/* Implementation of Recursive-Descent Parser
 * parser.cpp
 * Programming Assignment 2
 * Spring 2023
 */

#include "parser.h"

map<string, bool> defVar;
map<string, Token> SymTable;

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

// WritelnStmt:= WRITELN (ExpreList)
bool WritelnStmt(istream &in, int &line)
{
	LexItem t;
	// cout << "in Writeln Stmt" << endl;

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
		return false;
	}

	t = Parser::GetNextToken(in, line);
	if (t != RPAREN)
	{

		ParseError(line, "Missing Right Parenthesis of Writeln Statement");
		return false;
	}
	// Evaluate: print out the list of expressions values

	return true;
} // End of WritelnStmt

// ExprList:= Expr {,Expr}
bool ExprList(istream &in, int &line)
{

	bool status = false;
	// cout << "in ExprList and before calling Expr" << endl;
	status = Expr(in, line);
	if (!status)
	{

		ParseError(line, "Missing Expression");
		return false;
	}

	LexItem tok = Parser::GetNextToken(in, line);

	if (tok == COMMA)
	{
		// cout << "before calling ExprList" << endl;
		status = ExprList(in, line);
		// cout << "after calling ExprList" << endl;
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
bool Prog(istream &in, int &line)
{
	// line = line - 1;
	// line = line - 1;
	// line = line - 1;

	LexItem t;

	bool status = true;
	while ((t = Parser::GetNextToken(in, line)) != DONE)
	{

		// cout << t.GetLexeme() << endl;
		Parser::PushBackToken(t);
		status = StmtList(in, line);

		if (status == false)
		{
			t = Parser::GetNextToken(in, line);
			if (t != DONE)
			{
				Parser::PushBackToken(t);
				ParseError(line, "Missing prog");
				return false;
			}
			else
			{
				int i = ErrCount();
				if (i == 0)
				{
					break;
				}
				else
				{
					ParseError(line, "Missing prog");
					return false;
				}
			}
		}
	}

	cout << "(DONE)" << endl;
	return true;
}
bool StmtList(istream &in, int &line)
{

	if (!Stmt(in, line))
	{
		if (ErrCount() > 0)
		{

			ParseError(line, "Syntactic Erorr bnody");
			return false;
		}
	}
	else
	{

		LexItem t;
		t = Parser::GetNextToken(in, line);
		if (t == SEMICOL)
		{
			StmtList(in, line);
		}
		else
		{
			ParseError(line, "Missing semicolon at end of Statement.");
			return false;
		}
	}

	// ParseError(line, "stmt list error");
	return false;
}
bool Stmt(istream &in, int &line)
{
	LexItem t;
	t = Parser::GetNextToken(in, line);

	if (t == WRITELN)
	{
		// cout << t.GetLexeme() << endl;
		// Parser::PushBackToken(t);
		if (WritelnStmt(in, line))
		{
			return true;
		}
		else
		{
			ParseError(line, "Incorrect WriteLnSTMST.");

			return false;
		}
	}
	else if (t == IF)
	{
		// Parser::PushBackToken(t);
		if (IfStmt(in, line))
		{
			return true;
		}
		else
		{
			ParseError(line, "Incorrect if statement.");

			return false;
		}

		// legacy return IFstmt(in,line);
	}
	else if (t == SIDENT || t == NIDENT)
	{

		Parser::PushBackToken(t);
		if (AssignStmt(in, line))
		{
			return true;
		}
		else
		{
			// ParseError(line, "Incorrect assignment statement.");

			return false;
		}
	}

	Parser::PushBackToken(t);
	// ParseError(line, "Syntactic error in Program Body.");
	return false; // issue test prog2 and 4
}
bool IfStmt(istream &in, int &line) // needs fixing
{
	LexItem t;
	t = Parser::GetNextToken(in, line);
	if (t != LPAREN)
	{
		ParseError(line, "Missing right parenthesis if statment");
		return false;
	}
	else
	{
		if (!Expr(in, line))
		{
			ParseError(line, "Missing expression if statement");
			return false;
		}
		else
		{
			t = Parser::GetNextToken(in, line);
			if (t != RPAREN)
			{
				ParseError(line, "Missing right parenthesis after expression if statement");
				return false;
			}
			else
			{
				t = Parser::GetNextToken(in, line);
				if (t != LBRACES)
				{
					ParseError(line, "Missing left brace after if statement");
					return false;
				}
				else
				{

					StmtList(in, line);

					t = Parser::GetNextToken(in, line);
					if (t != RBRACES)
					{
						ParseError(line, "Missing right brace after if statement");
						return false;
					}
					else
					{
						t = Parser::GetNextToken(in, line);
						if (t != ELSE)
						{
							return true;
						}
						else
						{
							t = Parser::GetNextToken(in, line);
							if (t != LBRACES)
							{
								ParseError(line, "Missing left brace after else statement");
								return false;
							}
							else
							{
								StmtList(in, line);
								t = Parser::GetNextToken(in, line);
								if (t != RBRACES)
								{
									ParseError(line, "Missing right brace after else statement");
									return false;
								}
								else
								{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
}
bool AssignStmt(istream &in, int &line)
{

	LexItem t;

	if (Var(in, line))
	{

		t = Parser::GetNextToken(in, line);

		if (t == ASSOP)
		{

			if (Expr(in, line)) // EXPR does not consider )
			{
				t = Parser::GetNextToken(in, line);
				if (!(t == RPAREN))
				{
					Parser::PushBackToken(t);
				}
				return true;
			}
			ParseError(line, "Incorrect Assignment Statement.");
			// ParseError(line, "something went wrong with assignment");
			return false;
		}
		else
		{
			ParseError(line, "Missing assignment op.");
			// Parser::PushBackToken(t);
			// return false; // might revert back to true
		}
	}

	ParseError(line, "Incorrect Assignment Statement.");
	return false;
}
bool Var(istream &in, int &line)
{

	// map<string, bool> defVar
	LexItem t;
	t = Parser::GetNextToken(in, line);

	if (t == NIDENT || t == SIDENT)
	{

		if (defVar[t.GetLexeme()] == false)
		{
			defVar[t.GetLexeme()] = true;
		}
		return true;
	}
	ParseError(line, "something went wrong with var");
	return false;
}
bool Expr(istream &in, int &line)
{

	if (RelExpr(in, line)) // ISSUE WITH FOLLOWS
	{
		LexItem t;

		t = Parser::GetNextToken(in, line);

		if (t == SEQ || t == NEQ)
		{
			if (RelExpr(in, line))
			{

				return true;
			}
			ParseError(line, "Expression is wrong");
			return false;
		}

		Parser::PushBackToken(t);
		return true;
	}
	ParseError(line, "missing expression");
	return false;
}
bool RelExpr(istream &in, int &line) // STOPPED HERE ON 03/16, FOLLOW LINE 7 $y_1 = (7.5);
{
	// debug

	if (AddExpr(in, line)) // folow
	{
		LexItem t;

		t = Parser::GetNextToken(in, line);

		if (t == SGTHAN || t == SLTHAN || t == NGTHAN || t == NLTHAN)
		{
			if (AddExpr(in, line))
			{

				return true;
			}

			ParseError(line, "Missing operand after operator");
			return false;
		}

		Parser::PushBackToken(t);
		return true;
	}

	// ParseError(line, "something went wrong with RELEXPR");
	return false;
}
bool AddExpr(istream &in, int &line)
{
	LexItem t;

	if (MultExpr(in, line))
	{
		LexItem t;
		t = Parser::GetNextToken(in, line);

		if (t == PLUS || t == MINUS || t == CAT)
		{

			if (MultExpr(in, line))
			{
				return true;
			}

			ParseError(line, "Missing operand after operator");
			return false;
		}
		Parser::PushBackToken(t);
		return true;
	}

	// ParseError(line,"something went wrong with Addexpr");
	return false;
}
bool MultExpr(istream &in, int &line)
{

	if (ExponExpr(in, line))
	{
		LexItem t;
		t = Parser::GetNextToken(in, line);

		if (t == DIV || t == MULT || t == SREPEAT)
		{
			t = Parser::GetNextToken(in, line);
			if (t == SEMICOL)
			{
				ParseError(line, "Missing operand after operator");
				return false;
			}
			else
			{
				Parser::PushBackToken(t);
			}
			if (ExponExpr(in, line))
			{

				return true;
			}
			// t = Parser::GetNextToken(in, line);

			ParseError(line, "Missing operand after operator");
			return false;
		}

		Parser::PushBackToken(t);

		return true;
	}
	// ParseError(line,"something went wrong with MULTEXP");
	return false;
}
bool ExponExpr(istream &in, int &line)
{

	if (UnaryExpr(in, line))
	{

		LexItem t;
		t = Parser::GetNextToken(in, line);

		if (t == EXPONENT)
		{
			if (UnaryExpr(in, line))
			{
				return true;
			}
			ParseError(line, "Missing operand after operator");
			return false;
		}
		Parser::PushBackToken(t);
		return true;
	}

	// ParseError(line,"something went wrong with EXP");
	return false;
}
bool UnaryExpr(istream &in, int &line)
{

	if (PrimaryExpr(in, line, -1))
	{

		LexItem t;

		t = Parser::GetNextToken(in, line);

		if (t == PLUS)
		{
			if (PrimaryExpr(in, line, 1))
			{

				return true;
			}

			ParseError(line, "Missing operand after operator");
			return false;
		}
		else if (t == MINUS)
		{
			if (PrimaryExpr(in, line, 0))
			{

				return true;
			}

			// ParseError(line, "Not A UnaryExpr");
			return false;
		}

		Parser::PushBackToken(t);
		return true;
	}

	return false;
}
bool PrimaryExpr(istream &in, int &line, int sign) // MINUS = 0 PLUS = 1

{

	LexItem t;

	t = Parser::GetNextToken(in, line);

	if (t == SIDENT || t == NIDENT)
	{
		if (defVar[t.GetLexeme()] == false)
		{
			ParseError(line, "variable is unknown");
			return false;
		}
		return true;
	}

	else if (t == IDENT || t == ICONST || t == RCONST ||
					 t == SCONST)
	{

		return true;
	}
	else
	{

		if (Expr(in, line))
		{

			return true;
		}

		// Parser::PushBackToken(t);
	}

	// ParseError(line, "Not A PrimaryExpr");

	return false;
}
