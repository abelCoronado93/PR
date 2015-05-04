
//------------------PR----------------------

/* Pablo Arag�n Moreno, Abel Coronado L�pez */

#include <gecode/int.hh>
#include <gecode/gist.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Planificacion : public Space {

protected:

	int n = 6;
	const int nDependencias = 4;
	int nRecursos = 2;
	int totalDias = 19;

	IntVarArray inicioTareas;
	IntVarArray finTareas;

public:

	Planificacion(void) : inicioTareas(*this, n, 1, totalDias), finTareas(*this, n, 1, totalDias) {

		int duraciones[] = { 3, 8, 8, 6, 3, 4 };
		int recursos[] = { 1, 1, 1, 2, 2, 2};
		int depIni[] = { 1, 1, 4, 5 };
		int depFin[] = { 5, 6, 3, 3 };
		
		//PRECEDENCIA
		for (int i = 0; i < nDependencias; i++){
			rel(*this, finTareas[depIni[i] - 1] < inicioTareas[depFin[i] - 1]);
		}

		//DEPENDENCIA	
		for (int i = 0; i < n - 1; i++){
			for (int j = i + 1; j < n; j++){
				if (recursos[i] == recursos[j])
					rel(*this, finTareas[i] < inicioTareas[j] || inicioTareas[j] > finTareas[i]);
			}
		}

		for (int i = 0; i < n; i++){
			rel(*this, finTareas[i] == inicioTareas[i] + duraciones[i] - 1);
		}
		

		branch(*this, finTareas, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		branch(*this, inicioTareas, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
	}

	Planificacion(bool share, Planificacion& s) : Space(share, s) {
		finTareas.update(*this, share, s.finTareas);
		inicioTareas.update(*this, share, s.inicioTareas);
	}

	virtual Space* copy(bool share) {
		return new Planificacion(share, *this);
	}

	void print(std::ostream& os) const {

		os << "Planificacíon de las tareas: " << std::endl;
		for (int i = 0; i < n; i++){
			os << "Tarea " << i << ":" << std::endl;
			os << "    Inicio: " << inicioTareas[i] << std::endl;
			os << "    Fin: " << finTareas[i] << std::endl;
		}
	}
};

int main(int argc, char* argv[]) {

	Planificacion* m = new Planificacion;
	Gist::Print<Planificacion> p("Print solution");
	Gist::Options o;
	o.inspect.click(&p);
	Gist::dfs(m, o);
	delete m;
	return 0;
}