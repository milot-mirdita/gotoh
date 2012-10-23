#include "gotoh.h"
#include "a_matrix.h"
#include "d_matrix.h"
#include "i_matrix.h"

gotoh::gotoh(std::string sequence1, std::string sequence2) : sequence1(sequence1), sequence2(sequence2)
{
	substitution_matrix matrix("C:\\Users\\Milot\\Documents\\Visual Studio 2010\\Projects\\gotoh\\Debug\\matrices\\dayhoff.mat");
	auto dm = d_matrix(sequence1, sequence2, &matrix, -12, -1);
	auto im = i_matrix(sequence1, sequence2, &matrix, -12, -1);
	auto am = a_matrix(sequence1, sequence2, &matrix, -12, -1, &dm, &im);

	dm.init();
	im.init();
	am.init();

	dm.set_a_matrix(&am);
	im.set_a_matrix(&am);

	for(int i = 0; i < am.rows; i++) {
		for(int j = 0; j < am.cols; j++) {
			dm.fill_in(i, j);
			im.fill_in(i, j);
			am.fill_in(i, j);
		}
	}
}


gotoh::~gotoh(void)
{
}
