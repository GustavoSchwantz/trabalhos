import java.util.*;
import java.io.*;

class PrettyPrinter {
    LUGOSI tree;

    public PrettyPrinter (LUGOSI tree)
    {
	    this.tree = tree;
    }

    public void pprint ()
    {
	    System.out.print ("main");
	    System.out.println ();
	    System.out.println ("{");

	    for (VARDECL vd : tree.main.varDecls)
		    printVarDecls (vd);
            
	    for (COMANDO c : tree.main.comandos)
		    printComandos (c);

	    System.out.println ("}");

	    for (FUNC f : tree.funcs)
		    printFuncoes (f);
    }

    private void printVarDecls (VARDECL vd)
    {
	    System.out.print ("\t");
	    System.out.print ("var");
	    System.out.print (" ");
	    System.out.print (

			   (vd.tipo instanceof INT) ?  
			    (((INT) vd.tipo).valor) :
                            (((BOOL) vd.tipo).valor)

			    );
	    System.out.print (" ");
	    System.out.print (vd.id.id);
	    System.out.println (";");
    }

    private void printComandos (COMANDO c)
    {
	    if (c instanceof ATR_OU_CHA) {
		    System.out.print ("\t");
		    System.out.print ( ((ATR_OU_CHA) c).id.id );
		    System.out.print (" ");

		    if ( ((ATR_OU_CHA) c).comando2 instanceof ATRIBUICAO ) {
			    System.out.print (":=");
			    System.out.print (" ");

                            printExp ( ((ATRIBUICAO) ((ATR_OU_CHA) c).comando2).exp );

                            System.out.println (";");
		    }
		    else {
			    System.out.print ("(");
			   
			    printListExp ( ((CHAMADA) ((ATR_OU_CHA) c).comando2).listaExp );
                     
                            System.out.print (")");
			    System.out.println (";");
		    }
	    }
	    else if (c instanceof IF) {
		    System.out.print ("\t");
		    System.out.print ("if");
		    System.out.print (" ");
                    System.out.print ("(");

		    printExp (( (IF) c).exp);

		    System.out.print (")");
                    System.out.print (" ");
                    System.out.println ("{");
                    
                    for (COMANDO cmd : ( (IF) c).comandos)
			    printComandos (cmd);

                    System.out.print ("}");
		    System.out.println (";");
	    }
	    else if (c instanceof WHILE) {
		    System.out.print ("\t");
		    System.out.print ("while");
	            System.out.print (" ");
                    System.out.print ("(");
		   
		    printExp (( (WHILE) c).exp);

                    System.out.print (")");
		    System.out.print (" ");
		    System.out.print ("do");
		    System.out.print (" ");
		    System.out.println ("{");
		    
		    for (COMANDO cmd : ( (WHILE) c).comandos)
			    printComandos (cmd);
		   
		    System.out.print ("}");
		    System.out.println (";");
	    }
	    else if (c instanceof DO) {
		    System.out.print ("\t");
                    System.out.print ("do");
		    System.out.print (" ");
                    System.out.println ("{");
		    
		    for (COMANDO cmd : ( (DO) c).comandos)
			    printComandos (cmd);

		    System.out.print ("}");
		    System.out.print (" ");
		    System.out.print ("while");
		    System.out.print (" ");
		    System.out.print ("(");

		    printExp (( (DO) c).exp);

		    System.out.print (")");
		    System.out.println (";");
	    }
            else if (c instanceof RETURN) {
                    System.out.print ("\t");
		    System.out.print ("return");
		    System.out.print (" ");

		    printExp (( (RETURN) c).exp);

		    System.out.println (";");
	    }
	    else {
                    System.out.print ("\t");
		    System.out.print ("print");
		    System.out.print (" ");
		    System.out.print ("(");

		    printExp (( (PRINT) c).exp);

                    System.out.print (")");
		    System.out.println (";");
	    }
    }

    private void printExp (EXP exp) 
    {
	    if (exp instanceof EXPS) 
		    printFator ( ((EXPS) exp).fator);
	    else {
                    System.out.print ("(");

		    printExp ( ((EXPC) exp).exp1);
                    
		    System.out.print (" ");

		    printOp ( ((EXPC) exp).op);

		    System.out.print (" ");

		    printExp ( ((EXPC) exp).exp2);

		    System.out.print (")");
	    }
    }

    private void printFator (FATOR f)
    {
	    if (f instanceof ID_OU_CHA) {
		    System.out.print ( ((ID_OU_CHA) f).id.id );

		    if (((ID_OU_CHA) f).fator2 != null) {
			    System.out.print ("(");

                            printListExp (((ID_OU_CHA) f).fator2.listaExp);

                            System.out.print (")");
		    }
	    }
	    else if (f instanceof NUM) {
		    System.out.print ( ((NUM) f).num );
	    }
	    else if (f instanceof TRUE) {
		    System.out.print ( ((TRUE) f).t );
	    }
	    else {
		    System.out.print ( ((FALSE) f).f ); 
	    }
    }

    private void printListExp (ArrayList<EXP> le)
    {
	    for (int i = 0; i < le.size (); ++i) {
		    if (i == 0)
		            printExp (le.get (i));
		    else {
			    System.out.print (", ");
			    printExp (le.get (i));
		    }
	    }
    }

    private void printOp (OP op)
    {
	    if (op instanceof SOMA)
		    System.out.print (((SOMA) op).soma);
	    else if (op instanceof MENOS)
		    System.out.print (((MENOS) op).menos);
	    else if (op instanceof MULT)
		    System.out.print (((MULT) op).mult);
	    else if (op instanceof DIV)
		    System.out.print (((DIV) op).div);
            else if (op instanceof AND)
		    System.out.print (((AND) op).and);
	    else if (op instanceof OR)
		    System.out.print (((OR) op).or);
	    else if (op instanceof MENOR)
		    System.out.print (((MENOR) op).menor);
	    else if (op instanceof MAIOR)
		    System.out.print (((MAIOR) op).maior);
            else
		    System.out.print (((IGUAL) op).igual);
    }

    private void printFuncoes (FUNC f)
    {
	    System.out.print ("function");
	    System.out.print (" ");
            
	    System.out.print ( 

			     (f.tipo instanceof INT) ?
			         (((INT) f.tipo).valor) : 
				     (((BOOL) f.tipo).valor) 

				     );
	    System.out.print (" ");

            System.out.print (f.id.id);

            System.out.print (" ");
	    System.out.print ("(");

	    if (f.listaArg != null) 
		    printListaDeArgs (f.listaArg);

	    System.out.println (")");
	    System.out.println ("{");

            for (VARDECL vd : f.varDecls)
		    printVarDecls (vd);
	   
	    for (COMANDO c : f.comandos) 
		    printComandos (c);

	     System.out.println ("}");
    }

    private void printListaDeArgs (LISTAARG la)
    {
	    System.out.print ( 

			    (la.tipo instanceof INT) ? 
			        (((INT) la.tipo).valor) :
				    (((BOOL) la.tipo).valor)
				    
				    );

            System.out.print (" ");
	    System.out.print (la.id.id);

	    for (int i = 0; i < la.listaArg2.size (); ++i) { 
		    System.out.print (", ");

		    LISTAARG2 la2 = la.listaArg2.get (i);

		    System.out.print (

				    (la2.tipo instanceof INT) ? 
				        (((INT) la2.tipo).valor) : 
					    (((BOOL) la2.tipo).valor)

					    );

		    System.out.print (" ");
		    System.out.print (la2.id.id);
            }
    }
}

