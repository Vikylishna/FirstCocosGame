#include <vector>
#include <string>

void fill_arr_filename(std::vector<std::string> & filename){
	filename.resize(4);
	filename[0] = "grass1.jpg";
	filename[1] = "grass2.jpg";
	filename[2] = "wall1.jpg";
	filename[3] = "wall2.jpg";
}