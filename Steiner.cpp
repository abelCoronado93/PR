
//------------------PR----------------------

/* Pablo Arag�n Moreno, Abel Coronado L�pez */

#include <gecode/int.hh>
#include <gecode/gist.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;

class Steiner : public Space {

protected:

	int n = 7;
	int nb = n * (n - 1) / 6;
	int numElem = 3;

	IntVarArray sets;

public:

	Steiner(void) : sets(*this, nb, 1, n){

		for (int i = 0; i < nb; i+=numElem){
			for (int j = 0; j < nb; j+=numElem){

				for (int k = 0; k < numElem; k++){
					for (int l = 0; l < numElem; l++){
						if (sets[i + k] == sets[j + l]){

						}
					}
				}
			}
		}
	}

	Steiner(bool share, Steiner& s) : Space(share, s) {
		sets.update(*this, share, s.sets);
	}

	virtual Space* copy(bool share) {
		return new Steiner(share, *this);
	}

	void print(std::ostream& os) const {

		os << sets << std::endl;
	}
};

int main(int argc, char* argv[]) {

	Steiner* m = new Steiner;
	Gist::Print<Steiner> p("Print solution");
	Gist::Options o;
	o.inspect.click(&p);
	Gist::dfs(m, o);
	delete m;
	return 0;
}