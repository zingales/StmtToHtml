#ifndef STMT_TO_HTML
#define STMT_TO_HTML

#include <iostream>
#include <fstream>
#include "Halide.h"

using namespace Halide;
using namespace Halide::Internal;
using std::string;

static const string FOLDER = ".";

/*
	Please note you need to compile this file with the -fno-rtti flag. 
	to use please include like so
	#include "stmt_to_html/StmtToHtml.h"

*/

class StmtToHtml : public IRVisitor {


private:
	std::ofstream stream;

	string open_span(string cls, string data="") {
		return "<span class="+cls+" "+data+">";
	}

	string close_span() {
		return "</span>";
	}

	string open_div(string cls, string data="") {
		return "<div class="+cls+" "+data+">";
	}

	string close_div() {
		return "</div>\n";
	}

	string generate_data(string name, string content) {
		return "data-"+name+"="+'"'+content+'"';
	}

	void print(Expr ir) {
	    ir.accept(this);
	}

	void print(Stmt ir) {
	    ir.accept(this);
	}

public: 
	void visit(const IntImm *op){
		stream <<  open_span("IntImm") << op->value << close_span();
	}
    void visit(const FloatImm *op){
		stream <<  open_span("FloatImm") << op->value << 'f' << close_span();
    }
    void visit(const StringImm *op){
    	//TODO sanitize the stirng so it doesn't mess with the html
    	stream << open_span("StringImm");
    	  stream << '"';
	    for (size_t i = 0; i < op->value.size(); i++) {
	        unsigned char c = op->value[i];
	        if (c >= ' ' && c <= '~' && c != '\\' && c != '"') {
	            stream << c;
	        } else {
	            stream << '\\';
	            switch (c) {
	            case '"':
	                stream << '"';
	                break;
	            case '\\':
	                stream << '\\';
	                break;
	            case '\t':
	                stream << 't';
	                break;
	            case '\r':
	                stream << 'r';
	                break;
	            case '\n':
	                stream << 'n';
	                break;
	            default:
	                string hex_digits = "0123456789ABCDEF";
	                stream << 'x' << hex_digits[c >> 4] << hex_digits[c & 0xf];
	            }
	        }
   		}
    	stream << '"' << close_span();	
    }

    void visit(const Variable *op){
    	stream << open_span("Variable") << op->name << close_span();
    }

    void visit(const Cast *op){
    	stream << open_span("Cast");
    	// , generate_data("type", op->type));
	    stream << op->type << '(';
	    print(op->value);
	    stream << ')' << close_span();
    }

    void visit(const Add *op) {
    	stream << open_span("Add");
    	stream << '(';
	    print(op->a);
	    stream << " + ";
	    print(op->b);
	    stream << ')';
	    stream << ')' << close_span();
    }
    void visit(const Sub *op) {
    	stream << open_span("Sub");
    	 stream << '(';
	    print(op->a);
	    stream << " - ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const Mul *op) {
    	stream << open_span("Mul");
    	stream << '(';
	    print(op->a);
	    stream << "*";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const Div *op) {
    	stream << open_span("Div");
        stream << '(';
	    print(op->a);
	    stream << "/";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const Mod *op) {
    	stream << open_span("Mod");
    	stream << '(';
	    print(op->a);
	    stream << " % ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const Min *op) {
    	stream << open_span("Min");
	    stream << "min(";
	    print(op->a);
	    stream << ", ";
	    print(op->b);
	    stream << ")";	
	    stream << close_span();
    }
    void visit(const Max *op) {
    	stream << open_span("Max");
        stream << "max(";
	    print(op->a);
	    stream << ", ";
	    print(op->b);
	    stream << ")";
	    stream << close_span();
    }
    void visit(const EQ *op) {
    	stream << open_span("EQ");
    	stream << '(';
	    print(op->a);
	    stream << " == ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const NE *op) {
    	stream << open_span("NE");
        stream << '(';
	    print(op->a);
	    stream << " != ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const LT *op) {
    	stream << open_span("LT");
        stream << '(';
	    print(op->a);
	    stream << " < ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const LE *op) {
    	stream << open_span("LE");
        stream << '(';
	    print(op->a);
	    stream << " <= ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const GT *op) {
    	stream << open_span("GT");
	    stream << '(';
	    print(op->a);
	    stream << " > ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const GE *op) {
    	stream << open_span("GE");
	    stream << '(';
	    print(op->a);
	    stream << " >= ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
	}
    
    void visit(const And *op) {
    	stream << open_span("And");
	    stream << '(';
	    print(op->a);
	    stream << " && ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const Or *op) {
    	stream << open_span("Or");
	    stream << '(';
	    print(op->a);
	    stream << " || ";
	    print(op->b);
	    stream << ')';
	    stream << close_span();
    }
    void visit(const Not *op) {
    	stream << open_span("Not");
	    stream << '!';
	    print(op->a);
	    stream << close_span();
    }
    void visit(const Select *op) {
    	stream << open_span("Select");
	    stream << "select(";
	    print(op->condition);
	    stream << ", ";
	    print(op->true_value);
	    stream << ", ";
	    print(op->false_value);
	    stream << ")";
	    stream << close_span();
    }
    void visit(const Load *op) {
    	stream << open_span("Load");
	    stream << op->name << "[";
	    print(op->index);
	    stream << "]";
	    stream << close_span();
    }
    void visit(const Ramp *op) {
    	stream << open_span("Ramp");
	    stream << "ramp(";
	    print(op->base);
	    stream << ", ";
	    print(op->stride);
	    stream << ", " << op->width << ")";
	    stream << close_span();
    }
    void visit(const Broadcast *op) {
    	stream << open_span("Broadcast");
	    stream << "x" << op->width << "(";
	    print(op->value);
	    stream << ")";
	    stream << close_span();
    }
    void visit(const Call *op) {
    	stream << open_span("Call");
	    if (op->call_type == Call::Intrinsic) {
	        if (op->name == Call::extract_buffer_min) {
	            print(op->args[0]);
	            stream << ".min[" << op->args[1] << "]";
			    stream << close_span();
	            return;
	        } else if (op->name == Call::extract_buffer_max) {
	            print(op->args[0]);
	            stream << ".max[" << op->args[1] << "]";
	    		stream << close_span();
	            return;
	        }
	    }

	    stream << op->name << "(";
	    stream << open_span("CallArgs");
	    for (size_t i = 0; i < op->args.size(); i++) {
	        print(op->args[i]);
	        if (i < op->args.size() - 1) {
	            stream << ", ";
	        }
	    }
	    stream << close_span();
    	stream << ")";
	    stream << close_span();
    }
    void visit(const Let *op) {
    	stream << open_span("Let");
	    stream << "(let " << op->name << " = ";
	    print(op->value);
	    stream << " in ";
	    print(op->body);
	    stream << ")";
	    stream << close_span();
    }

    // Divs
    void visit(const LetStmt *op) {
    	stream << open_div("LetStmt");
	    stream << "let " << op->name << " = ";
	    print(op->value);
	    stream << close_div();
    }
    void visit(const AssertStmt *op) {
    	stream << open_div("AssertStmt");
	    stream << "assert(";
	    print(op->condition);
	    stream << ", ";
	   	stream << open_span("AssertMsg");
	    stream << '"' << op->message << '"';
	    stream << close_span();
	    for (size_t i = 0; i < op->args.size(); i++) {
	        stream << ", ";
	        print(op->args[i]);
	    }
	    stream << ')';
	    stream << close_div();
    }
    void visit(const Pipeline *op) {
    	stream << open_div("Produce");
	    stream << "produce " << op->name << " {";
	    stream << open_div("ProduceBody");
	   	print(op->produce); 
	   	stream << close_div();
	   	stream << '}';
	    stream << close_div();
	    if (op->update.defined()) {
	    	stream << open_div("Update");
	        stream << "update " << op->name << " {";
	        stream << open_div("UpdateBody");
	        print(op->update);
	        stream << close_div();
	        stream << '}';
	        stream << close_div();
	    }

    }
    void visit(const For *op) {
    	stream << open_div("For");
	    stream << op->for_type << " (" << op->name << ", ";
	    print(op->min);
	    stream << ", ";
	    print(op->extent);
	    stream << ") {";
		stream << open_div("ForBody");
	    print(op->body);
		stream << close_div();
		stream << '}';
	    stream << close_div();
    }
    void visit(const Store *op) {
    	stream << open_div("Store");
   	    stream << op->name << "[";
    	stream << open_span("StoreIndex");
	    print(op->index);
    	stream << close_span();
	    stream << "] = ";
		stream << open_span("StoreValue");
	    print(op->value);
		stream << close_span();
	    stream << close_div();
    }
    void visit(const Provide *op) {
    	stream << open_div("Provide");
		stream << op->name << "(";
	    for (size_t i = 0; i < op->args.size(); i++) {
	        print(op->args[i]);
	        if (i < op->args.size() - 1) stream << ", ";
	    }
	    stream << ") = ";
	    if (op->values.size() > 1) {
	        stream << "{";
	        stream << open_span("ProvideValues");
	    }
	    for (size_t i = 0; i < op->values.size(); i++) {
	        if (i > 0) {
	            stream << ", ";
	        }
	        print(op->values[i]);
	    }
	    if (op->values.size() > 1) {
	    	stream << close_span();
	        stream << "}";
	    }
	    stream << close_div();
    }
    void visit(const Allocate *op) {
    	stream << open_div("Allocate");
    	stream << "allocate " << op->name << "[" << op->type;
	    for (size_t i = 0; i < op->extents.size(); i++) {
	        stream  << " * ";
	        print(op->extents[i]);
	    }
	    stream << "]";
	    if (!is_one(op->condition)) {
	        stream << " if ";
	        print(op->condition);
	    }
	    stream << open_div("AllocateBody");
	    print(op->body);
	    stream << close_div();
	    stream << close_div();
    }
    void visit(const Free *op) {
    	stream << open_div("Free");
	    stream << "free " << op->name;
	    stream << close_div();
    }
    void visit(const Realize *op) {
    	stream << open_div("Realize");
	    stream << "realize " << op->name << "(";
	    stream << open_span("RealizeArgs");
	    for (size_t i = 0; i < op->bounds.size(); i++) {
	        stream << "[";
	        print(op->bounds[i].min);
	        stream << ", ";
	        print(op->bounds[i].extent);
	        stream << "]";
	        if (i < op->bounds.size() - 1) stream << ", ";
	    }
	    stream << ")";
		stream << close_span();
		if (!is_one(op->condition)) {
	        stream << " if ";
	        print(op->condition);
    	}
        stream << " {";
        stream << open_div("RealizeBody");
        print(op->body);
        stream << close_div();
	    stream << close_div();
    }
    void visit(const Block *op) {
    	stream << open_div("Block");
	    print(op->first);
	    if (op->rest.defined()) print(op->rest);
	    stream << close_div();
    }
    void visit(const IfThenElse *op) {
    	stream << open_div("IfThenElse");
    	while (1) {
    	stream << "if (";	
    	stream << open_span("IfStmt");
    	print(op->condition);
        stream << ")";
        stream << close_span() << "{";
        stream << open_div("ThenBody");
        print(op->then_case);
        stream << close_div();

        if (!op->else_case.defined()) {
            break;
        }

        if (const IfThenElse *nested_if = op->else_case.as<IfThenElse>()) {
            // do_indent();
            stream << "} else ";
            op = nested_if;
        } else {
            // do_indent();
            stream << "} else {\n";
            // indent += 2;
            print(op->else_case);
            // indent -= 2;
            break;
        }
    }
     stream << close_div();
    }

    void visit(const Evaluate *op) {
    	stream << open_div("Evaluate");
   	    print(op->value);
	    stream << close_div();
    }

	StmtToHtml(string filename){
		stream.open(filename);
		stream << "<head>";
		stream <<"<link rel=\"stylesheet\" type=\"text/css\" href=\""+FOLDER+"/stmt_to_html.css\">";
		stream << "<script language=\"javascript\" type=\"text/javascript\" src=\""+FOLDER+"/stmt_to_html.js\"></script>";
		stream << "</head>\n <body>\n";
	}

	void genereate(Stmt s){
		print(s);	
		stream << "</body>";
		stream.close();
	}

	~StmtToHtml(){}
};



/*
	All files will be stored in stmt_to_html
*/
void print_to_html(string filename, Stmt s) {
	StmtToHtml sth(FOLDER+"/"+filename);
	sth.genereate(s);
}


#endif