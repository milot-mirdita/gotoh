#include "gotoh.h"
#include "a_matrix.h"
#include "d_matrix.h"
#include "i_matrix.h"
#include "alignment_type.h"

gotoh::gotoh(std::string sequence1, std::string sequence2) : sequence1(sequence1), sequence2(sequence2)
{
	substitution_matrix matrix("C:\\Users\\Milot\\Documents\\Visual Studio 2010\\Projects\\gotoh\\Debug\\matrices\\dayhoff.mat");
	d_matrix dm(sequence1, sequence2, &matrix, -10, -2);
	i_matrix im(sequence1, sequence2, &matrix, -10, -2);
	a_matrix am(sequence1, sequence2, &matrix, -10, -2, &dm, &im);

	dm.init();
	im.init();
	am.init();

	dm.set_a_matrix(&am);
	im.set_a_matrix(&am);

	for(int i = 0; i < am.rows; i++) {
		for(int j = 0; j < am.cols; j++) {
			if(j != 0)
				dm.fill_in(i, j);
			if(i != 0)
				im.fill_in(i, j);
			if(i != 0 && j != 0)
				am.fill_in(i, j);
		}
	}

	dm.print();
	im.print();
	am.print();

	std::pair<std::string, std::string> alignment = am.get_traceback();

	system("pause");
}


gotoh::~gotoh(void)
{
}
