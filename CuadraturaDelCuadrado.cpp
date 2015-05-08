
//-------------------PR----------------------//

/* Pablo Aragón Moreno, Abel Coronado López */

#include <gecode/int.hh>
#include <gecode/gist.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;

class CuadraturaDelCuadrado : public Space {

protected:

	const static int N_CUADRADOS = 10;
	const static int size = 4;

	IntVarArray x;
	IntVarArray y;

public:

	CuadraturaDelCuadrado(void){

		//int baldosas[N_CUADRADOS] = { 50, 42, 37, 35, 33, 29, 27, 25, 24, 19, 18, 17, 16, 15, 11, 9, 8, 7, 6, 4, 2 };
		int baldosas[N_CUADRADOS] = {2, 2, 1, 1, 1, 1, 1, 1, 1, 1};

		x = IntVarArray(*this, N_CUADRADOS);
		y = IntVarArray(*this, N_CUADRADOS);

		//Inicialización del dominio de los Arrays
		for (int i = 0; i < N_CUADRADOS; i++){
			x[i] = IntVar(*this, 0, size - baldosas[i]);
			y[i] = IntVar(*this, 0, size - baldosas[i]);
		}

		//No solape de cuadrados
		for (int i = 0; i < N_CUADRADOS; i++)
			for (int j = i + 1; j < N_CUADRADOS; j++)
				rel(*this, (x[i] + baldosas[i] <= x[j] || y[i] + baldosas[i] <= y[j]) || (x[i] >= x[j] + baldosas[j] || y[i] >= y[j] + baldosas[j]));
			
		
		branch(*this, x, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		branch(*this, y, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
	}

	CuadraturaDelCuadrado(bool share, CuadraturaDelCuadrado& s) : Space(share, s) {
		x.update(*this, share, s.x);
		y.update(*this, share, s.y);
	}

	virtual Space* copy(bool share) {
		return new CuadraturaDelCuadrado(share, *this);
	}

	void print(std::ostream& os) const {
		os << x << std::endl;
		os << y << std::endl;
	}
};

int main(int argc, char* argv[]) {

	CuadraturaDelCuadrado* m = new CuadraturaDelCuadrado;
	Gist::Print<CuadraturaDelCuadrado> p("Print solution");
	Gist::Options o;
	o.inspect.click(&p);
	Gist::dfs(m, o);
	delete m;
	return 0;
}