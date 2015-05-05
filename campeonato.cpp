
//------------------PR----------------------

/* Pablo Aragón Moreno, Abel Coronado López */

#include <gecode/int.hh>
#include <gecode/gist.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Campeonato : public Space {

protected:

	const static int NUM_EQUIPOS = 8;
	
	IntVarArray rivales[NUM_EQUIPOS];
	IntVarArray sedes[NUM_EQUIPOS];

public:
	
	Campeonato(void) {

		for (int i = 0; i < NUM_EQUIPOS; i++){

			rivales[i] = IntVarArray(*this, NUM_EQUIPOS - 1, 1, NUM_EQUIPOS);
			sedes[i] = IntVarArray(*this, NUM_EQUIPOS - 1, 1, NUM_EQUIPOS);
		}

		for (int i = 0; i < NUM_EQUIPOS; i++){

			distinct(*this, rivales[i]);

			for (int j = 0; j < NUM_EQUIPOS - 1; j++){

				//CONSISTENCIA ENTRE SEDES Y RIVALES
				rel(*this, sedes[i][j] == sedes[rivales[i][j] - 1][j]); //NECESITAMOS CAST (INTVAR A INT) 

				//NO PUEDE JUGAR CONTRA SI MISMO
				rel(*this, rivales[i][j] != i + 1);

				//CONSISTENCIA ENTRE RIVALES
				rel(*this, rivales[rivales[i][j] - 1][j] == i + 1); //NECESITAMOS CAST (INTVAR A INT) 

				//NO SE REPITEN LAS COLUMNAS
				for (int k = j + 1; k < NUM_EQUIPOS - 1; k++){
					rel(*this, sedes[i][j] != sedes[i][k]);
					rel(*this, rivales[i][j] != rivales[i][k]);
				}	
			}
		}

		for (int i = 0; i < NUM_EQUIPOS; i++){
			branch(*this, rivales[i], INT_VAR_SIZE_MIN(), INT_VAL_MIN());
			branch(*this, sedes[i], INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		}
	}

	Campeonato(bool share, Campeonato& s) : Space(share, s) {
		for (int i = 0; i < NUM_EQUIPOS; i++){
			sedes[i].update(*this, share, s.sedes[i]);
			rivales[i].update(*this, share, s.rivales[i]);
		}
	}

	virtual Space* copy(bool share) {
		return new Campeonato(share, *this);
	}

	void print(std::ostream& os) const {

		os << "Campeonato: " << std::endl;
		for (int i = 0; i < NUM_EQUIPOS; i++){
			os << "Equipo " << i + 1 << ":" << std::endl;
			os << "    Sede: " << sedes[i] << std::endl;
			os << "    Rival: " << rivales[i] << std::endl;
		}
	}
};

int main(int argc, char* argv[]) {

	Campeonato* m = new Campeonato;
	Gist::Print<Campeonato> p("Print solution");
	Gist::Options o;
	o.inspect.click(&p);
	Gist::dfs(m, o);
	delete m;
	return 0;
}