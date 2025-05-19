#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
	fstream file; file.open("input.txt");
	string line;
	int validTriangle = 0;

	int currentLine = 0;
	vector<vector<int>> triangleSet;
	while (getline(file, line))
	{
		int input1, input2, input3;
		stringstream stream(line);

		while (stream >> input1 >> input2 >> input3)
		{
			vector<int> tempVector = { input1, input2,input3 };
			triangleSet.push_back(tempVector);
			++currentLine;

		}

		/*put the first three lines into a vector, and do same calculations but in a row */
		/* once currentLine is 3, then three potential triangles will be calculated and repeat */
		if (currentLine == 3)
		{
			int currentRow = 0;

			/*
				how tempVector is processed:
				->121 673 121 | 121 ->673 777 | 121  673 ->777 |
				->153 253 153 | 153 ->253 231 | 153  253 ->231 |
				->234 523 234 | 234 ->523 359 | 234  523 ->359 |

				same as part one but we grab the first three lines in file,
				put in a vector, and then process each row, meaning three 'triangles'
				get processed per 3 lines.
				
			*/
			do
			{
				vector<int> tempVector = { triangleSet[0][currentRow], triangleSet[1][currentRow],triangleSet[2][currentRow] };

				/* first smallest element*/
				input1 = *min_element(tempVector.begin(), tempVector.end());
				tempVector.erase(remove(tempVector.begin(), tempVector.end(), *min_element(tempVector.begin(), tempVector.end())));
				/* second smallest element*/
				input2 = *min_element(tempVector.begin(), tempVector.end());
				tempVector.erase(remove(tempVector.begin(), tempVector.end(), *min_element(tempVector.begin(), tempVector.end())));
				
				/* last element should be the highest*/
				input3 = tempVector[0];

				if ((input1 + input2) > input3)
				{
					++validTriangle;
				}

				++currentRow;
			} while (currentRow < 3);
			triangleSet.clear();
			currentLine = 0;
		}
		
	}

	cout << validTriangle;
	return 0;
}