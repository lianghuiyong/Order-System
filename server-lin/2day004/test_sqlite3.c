#include "sqlite.h"
int main()
{
	sqlite3 *db;
	int ret;
	ret=sqlite3_open(argv[1],&db);
	return 0;
}
