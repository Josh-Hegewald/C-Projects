#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//memory check
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int main(int argc, char** argv)
{
	VS_MEM_CHECK
		int num_students;
	int num_exams;
	string firstName;
	string lastName;
	int totalScore;

	//making sure there are three arguments in command-line argument
	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream my_input_file(argv[1]);
	if (!my_input_file)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}

	cout << "Output file: " << argv[2] << endl;
	ofstream my_output_file(argv[2]);
	if (!my_output_file)
	{
		my_input_file.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	//extracting the first two numbers from first line of input file
	my_input_file >> num_students >> num_exams;
	//creating a two-dimensional array for exam scores
	int **examScores = new int*[num_students];
	string *studentNames = new string[num_students];

	for (int i = 0; i < num_students; ++i)
	{
		my_input_file >> firstName >> lastName;
		studentNames[i] = firstName + " " + lastName;
		examScores[i] = new int[num_exams];
		for (int j = 0; j < num_exams; ++j)
		{
			my_input_file >> examScores[i][j];
		}
	}

	my_output_file << "Student Scores:" << endl;
	for (int k = 0; k < num_students; ++k)
	{
		my_output_file << setw(20) << studentNames[k] << " ";
		for (int m = 0; m < num_exams; ++m)
		{
			my_output_file << fixed << setprecision(0) << setw(6) << examScores[k][m];
		}
		my_output_file << endl;
	}

	my_output_file << "Exam Averages:" << endl;
	double *examAvg = new double[num_exams];
	for (int p = 0; p < num_exams; ++p)
	{
		totalScore = 0;
		for (int q = 0; q < num_students; ++q)
		{
			totalScore += examScores[q][p];
		}
		examAvg[p] = (double(totalScore) / num_students);
	}
	for (int z = 0; z < num_exams; ++z)
	{
		my_output_file << setprecision(1) << setw(9) << "Exam " << z + 1 << " Average =    " << examAvg[z] << endl;
	}


	char **letterGrades = new char*[num_students];
	for (int b = 0; b < num_students; ++b)
	{
		letterGrades[b] = new char[num_exams];
		for (int d = 0; d < num_exams; ++d)
		{
			if (examScores[b][d] >= examAvg[d] + 15) //A
			{
				letterGrades[b][d] = 'A';
			}
			else if (examScores[b][d] > examAvg[d] + 5) //B
			{
				letterGrades[b][d] = 'B';
			}
			else if (examScores[b][d] >= examAvg[d] - 5) //C
			{
				letterGrades[b][d] = 'C';
			}
			else if (examScores[b][d] > examAvg[d] - 15) //D
			{
				letterGrades[b][d] = 'D';
			}
			else //E
			{
				letterGrades[b][d] = 'E';
			}
		}
	}

	my_output_file << "Student Exam Grades:" << endl;
	for (int i = 0; i < num_students; ++i)
	{
		my_output_file << fixed << setprecision(0) << setw(20) << studentNames[i];
		for (int n = 0; n < num_exams; ++n)
		{
			my_output_file << setw(6) << examScores[i][n] << " (" << letterGrades[i][n] << ")";
		}
		my_output_file << endl;
	}

	my_output_file << "Exam Grades:" << endl;
	for (int r = 0; r < num_exams; ++r)
	{
		int aGradeCounter = 0;
		int bGradeCounter = 0;
		int cGradeCounter = 0;
		int dGradeCounter = 0;
		int eGradeCounter = 0;
		for (int a = 0; a < num_students; ++a)
		{
			if (letterGrades[a][r] == 'A')
			{
				aGradeCounter++;
			}
			else if (letterGrades[a][r] == 'B')
			{
				bGradeCounter++;
			}
			else if (letterGrades[a][r] == 'C')
			{
				cGradeCounter++;
			}
			else if (letterGrades[a][r] == 'D')
			{
				dGradeCounter++;
			}
			else
			{
				eGradeCounter++;
			}
		}
		my_output_file << setw(10) << "Exam  " << r + 1;
		my_output_file << setw(8) << aGradeCounter << "(A)";
		my_output_file << setw(8) << bGradeCounter << "(B)";
		my_output_file << setw(8) << cGradeCounter << "(C)";
		my_output_file << setw(8) << dGradeCounter << "(D)";
		my_output_file << setw(8) << eGradeCounter << "(E)" << endl;
	}

	double *finalGrades = new double[num_students];
	for (int i = 0; i < num_students; ++i)
	{
		double totalScore = 0.0;
		for (int j = 0; j < num_exams; ++j)
		{
			totalScore += examScores[i][j];
		}
		finalGrades[i] = (totalScore / num_exams);
	}

	double totalClassScore = 0.0;
	for (int i = 0; i < num_students; ++i)
	{
		totalClassScore += finalGrades[i];
	}
	double totalClassAverage = totalClassScore / num_students;


	string *finalLetterGrade = new string[num_students];
	for (int i = 0; i < num_students; ++i)
	{
		if (finalGrades[i] >= totalClassAverage + 15) //A
		{
			finalLetterGrade[i] = 'A';
		}
		else if (finalGrades[i] >= totalClassAverage + 5) //B
		{
			finalLetterGrade[i] = 'B';
		}
		else if (finalGrades[i] >= totalClassAverage - 5) //C
		{
			finalLetterGrade[i] = 'C';
		}
		else if (finalGrades[i] >= totalClassAverage - 15) //D
		{
			finalLetterGrade[i] = 'D';
		}
		else //E
		{
			finalLetterGrade[i] = 'E';
		}
	}

	my_output_file << "Student Final Grades:" << endl;
	for (int i = 0; i < num_students; ++i)
	{
		my_output_file << setw(20) << studentNames[i] << setw(6)
			<< setprecision(1) << finalGrades[i] << "(" << finalLetterGrade[i] << ")" << endl;
	}
	my_output_file << setw(20) << fixed << setprecision(1) << "Class Average Score = " << totalClassAverage;


	//Deletion of dynamic arrays		
	delete[] studentNames;

	for (int i = 0; i < num_students; ++i)
		{
			delete[] examScores[i];
		}
	delete[]examScores;

	delete[]finalGrades;

	delete[]examAvg;

	for (int i = 0; i < num_students; ++i)
	{
		delete[] letterGrades[i];
	}
	delete[]letterGrades;

	delete[]finalLetterGrade;


	return 0;
}
