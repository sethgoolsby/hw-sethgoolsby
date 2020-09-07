#include <iostream>
#include <string>

using namespace std;

// Implement below
bool are_paren_balanced(string& expression);

// We have suggested a helper method, but feel free to write whatever you see fit
bool are_paren_balanced(string& expression, size_t i, string expected_closing);

// Do not change this method
int main(int argc, char* argv[]) {

    // Check if an expression has been passed to the program
    if (argc != 2) {
        cerr << "error: expected expression to check!" << endl;
        return -1;
    }

    // The second argument is the expression string in the format specified and
    // promised in the assignment page. You do not need to do any error checking
    // except for checking the parentheses.
    string expression(argv[1]);
    if (are_paren_balanced(expression)) {
        cout << "correct" << endl;
    } else {
        cout << "incorrect" << endl;
    }

    return 0;
}

// Some notes:
// - This method must be implemented recursively.
// - When debugging, make sure to output to cerr rather than cout. This will
//   prevent any leftover debug statements from confusing the automated
//   grading and will make sure output is guaranteed to be written to the
//   terminal in case your program crashes.
bool are_paren_balanced(string& expression) {
    // TODO: your code here
	if (expression.length() < 2)
	{
		if(expression != "(" && expression != ")" && expression != "{" && expression != "}" && expression != "[" && expression != "]")
		{
			return true;
		}	
		else
		{
			return false;
		}
	}
	else
	{
		if(expression[0] != '(' && expression[0] != '{' && expression[0] != '[' && expression[0] != ')'&& expression[0] != '}' && expression[0] != ']')
		{
			string newExpression = expression.substr(1);
			//cout<< "Simple Skip: Simple Expression = "<<newExpression<<endl;
			return are_paren_balanced(newExpression);
		}
		else
		{
			if(expression.compare(0,1,"(") == 0)
			{

				string newExpression = expression.substr(1);
				//cout<<"I found a '(' newExpression ="<<newExpression<<endl;
				return are_paren_balanced(newExpression, size_t(newExpression.length()) ,")");
			}
			else if(expression.compare(0,1,"{") == 0)
			{
				string newExpression = expression.substr(1);
				//cout<<"I found a '{' newExpression ="<<newExpression<<endl;
				return are_paren_balanced(newExpression, newExpression.length(),"}");
			}
			else if(expression.compare(0,1,"[") == 0)
			{
				string newExpression = expression.substr(1);
				//cout<<"I found a '[' newExpression ="<<newExpression<<endl;
				return are_paren_balanced(newExpression, newExpression.length(),"]");
			}
			else
			{
				return false; // a close paren should never come first!!!
			}
		}
	}
}

bool are_paren_balanced(string& expression, size_t i, string expected_closing)
{
	bool flag = true;
	for(size_t x = 0; x < i; x ++)
	{
		if(expression.compare(x,1,expected_closing) == 0)
		{
			string newExpression = expression.substr(0,x) + expression.substr(x+1);
			cout<< "I found a match!! new Expression = "<<newExpression<<endl;
			flag = false;
			return are_paren_balanced(newExpression); //this skips the character ')'
		}
		
	}
	if (flag)
	{
		return false;
	}
}

// Add any additional function implementations here.
//
// If you want to use the suggested helper method, you'll have to write its
// definition here.
