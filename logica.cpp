//------------------PR----------------------

/* Pablo Aragón Moreno, Abel Coronado López */

#include <gecode/int.hh>
#include <gecode/gist.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Logica : public Space {

protected:

	IntVarArray color;
	IntVarArray mascota;
	IntVarArray nacionalidad;
	IntVarArray bebida;
	IntVarArray coche;

public:

	Logica(void) : color(*this, 5, 1, 5), mascota(*this, 5, 1, 5), nacionalidad(*this, 5, 1, 5),
		bebida(*this, 5, 1, 5), coche(*this, 5, 1, 5){

		distinct(*this, color);
		distinct(*this, mascota);
		distinct(*this, nacionalidad);
		distinct(*this, bebida);
		distinct(*this, coche);

		rel(*this, nacionalidad[0] == color[0]);
		rel(*this, nacionalidad[1] == mascota[0]);
		rel(*this, color[1] == bebida[0]);
		rel(*this, nacionalidad[2] == bebida[1]);
		rel(*this, color[1] == color[2] + 1);
		rel(*this, coche[0] == mascota[1]);
		rel(*this, coche[1] == color[3]);
		rel(*this, bebida[2] == 3);
		rel(*this, nacionalidad[3] == 1);
		rel(*this, coche[2] == mascota[2] + 1 || coche[2] == mascota[2] - 1);
		rel(*this, coche[1] == mascota[3] + 1 || coche[1] == mascota[3] - 1);
		rel(*this, coche[3] == bebida[3]);
		rel(*this, nacionalidad[4] == coche[4]);
		rel(*this, nacionalidad[3] == color[4] + 1 || nacionalidad[3] == color[4] - 1);

		branch(*this, nacionalidad, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		branch(*this, color, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		branch(*this, bebida, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		branch(*this, mascota, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		branch(*this, coche, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
		branch(*this, coche, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
	}

	Logica(bool share, Logica& s) : Space(share, s) {
		coche.update(*this, share, s.coche);
		nacionalidad.update(*this, share, s.nacionalidad);
		mascota.update(*this, share, s.mascota);
		bebida.update(*this, share, s.bebida);
		color.update(*this, share, s.color);
	}

	virtual Space* copy(bool share) {
		return new Logica(share, *this);
	}

	void print(std::ostream& os) const {

		os << "Coches: ";
		os << coche << std::endl;
		os << "Nacionalidades: ";
		os << nacionalidad << std::endl;
		os << "Bebidas: ";
		os << bebida << std::endl;
		os << "Mascotas: ";
		os << mascota << std::endl;
		os << "Colores: ";
		os << color << std::endl;

		os << "Solucion: " << std::endl;
		os << "Hiena en la casa : ";
		os << mascota[4] << std::endl;
		os << "Agua en la casa : ";
		os << bebida[4] << std::endl;
	}
};

int main(int argc, char* argv[]) {

	Logica* m = new Logica;
	Gist::Print<Logica> p("Print solution");
	Gist::Options o;
	o.inspect.click(&p);
	Gist::dfs(m, o);
	delete m;
	return 0;
}