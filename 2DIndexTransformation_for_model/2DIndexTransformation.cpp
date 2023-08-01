#include "2DIndexTransformation.h"

bool isInteger(const std::string& s)
{
	try
	{
		size_t pos = 0;
		std::stoi(s, &pos);
		return pos == s.length(); // �T�O��Ӧr�곣�ഫ�����
	}
	catch (const std::exception& e)
	{
		return false; // �ഫ���ѡA���O���
	}
}

bool isFloat(const std::string& s)
{
	try
	{
		size_t pos = 0;
		std::stof(s, &pos);
		return pos == s.length(); // �T�O��Ӧr�곣�ഫ���B�I��
	}
	catch (const std::exception& e)
	{
		return false; // �ഫ���ѡA���O�B�I��
	}
}

void IndexTrans()
{
	vector <element> ELEMENT;
	vector <element_2D> ELEMENT_2D;
	vector <string> elements;
	vector <float> element_x2;	//rightmost ,�����u��LINE, edge survival method
	vector <float> element_y2;	//�����u��LINE, edge survival method
	string temp_line;

	ifstream file(inputfile_path);			//read file
	if (!file.is_open())
	{
		cout << "�L�k�}���ɮסG" << inputfile_path << endl;
		return;
	}
	ofstream output_file(outputfile_path);	//write file
	ofstream output_file2(outputfile_path2);	//write file

	while (getline(file, temp_line))
	{
		elements.clear();

		stringstream ss(temp_line);
		string item;
		while (getline(ss, item, '@'))		//�H@�Ÿ����j����
			elements.push_back(item);
		/*
		if (elements.size() == 5 && item.empty())				//�O�I����
			if (isInteger(elements[0]) && isFloat(elements[1]) && isFloat(elements[2]) && isFloat(elements[3]) && isFloat(elements[4]))
				ELEMENT.push_back(element(atoi(elements[0].c_str()), stof(elements[1]), stof(elements[2]), stof(elements[3]), stof(elements[4]), ""));
		*/
		if (elements.size() == 6)								//�O�I����
			if (isInteger(elements[0]) && isFloat(elements[1]) && isFloat(elements[2]) && isFloat(elements[3]) && isFloat(elements[4]) && elements[5] != "(null)")
				ELEMENT.push_back(element(atoi(elements[0].c_str()), stof(elements[1]), stof(elements[2]), stof(elements[3]), stof(elements[4]), elements[5]));

	}

	for (int i = 0; i < ELEMENT.size(); i++)
	{
		element_x2.push_back(ELEMENT[i].x2);		//�����u
		element_y2.push_back(ELEMENT[i].y2);		//�����u
		ELEMENT_2D.push_back(element_2D());			//�ഫ��2D
	}

	sort(element_x2.begin(), element_x2.end());	//�H�p��j(����k)
	sort(element_y2.begin(), element_y2.end());	//�H�p��j(�W��U)
	element_x2.erase(unique(element_x2.begin(), element_x2.end()), element_x2.end());	//�R�����Ƥ���
	element_y2.erase(unique(element_y2.begin(), element_y2.end()), element_y2.end());	//�R�����Ƥ���

	int coordinate_x = 1;
	bool* placed_ELEMENT = new bool[ELEMENT.size() + 5];		//�w��m/����m
	for (int i = 0; i < ELEMENT.size() + 5; i++)
		placed_ELEMENT[i] = false;
	for (int i = 0; i < element_x2.size(); i++)					//�����u
	{
		bool have_element = false;
		for (int j = 0; j < ELEMENT.size(); j++)
			if (ELEMENT[j].middle_x <= element_x2[i] && placed_ELEMENT[j] == false)		//�p�G�Ӥ��󪺤����I�b�u������A�B�٨S��x(���Q��m)
			{
				ELEMENT_2D[j].sequence = ELEMENT[j].sequence;
				ELEMENT_2D[j].x = coordinate_x;
				ELEMENT_2D[j].word = ELEMENT[j].word;
				placed_ELEMENT[j] = true;						//�w��m
				have_element = true;
			}
		if (have_element == true)
			coordinate_x++;
	}

	int coordinate_y = 1;
	for (int i = 0; i < ELEMENT.size() + 5; i++)
		placed_ELEMENT[i] = false;
	for (int i = 0; i < element_y2.size(); i++)					//�����u
	{
		bool have_element = false;
		for (int j = 0; j < ELEMENT.size(); j++)
			if (ELEMENT[j].middle_y <= element_y2[i] && placed_ELEMENT[j] == false)		//�p�G�Ӥ��󪺤����I�b�u���W���A�B�٨S��y(���Q��m)
			{
				ELEMENT_2D[j].y = coordinate_y;
				placed_ELEMENT[j] = true;
				have_element = true;
			}
		if (have_element == true)
			coordinate_y++;
	}

	for (int i = 0; i < ELEMENT_2D.size(); i++)
		output_file << ELEMENT_2D[i].sequence << "@" << ELEMENT_2D[i].x << "@" << ELEMENT_2D[i].y << "@" << ELEMENT_2D[i].word << endl;

	for (int i = 0; i < ELEMENT.size(); i++)
		output_file2 << ELEMENT[i].sequence << "@" << ELEMENT[i].x1 << "@" << ELEMENT[i].y1 << "@" << ELEMENT[i].x2 << "@" << ELEMENT[i].y2 << "@" << ELEMENT[i].word << endl;

	file.close();
	output_file.close();
	output_file2.close();
}

