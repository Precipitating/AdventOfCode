#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>  
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Present
{
public:
	Present() : length(0), width(0), height(0),
				smallestSide(0), total(0), bowLength(0),
				ribbonLength(0), totalRibbon(0) {};

	Present(int t_length, int t_width, int t_height) :	length(t_length), width(t_width), height(t_height),
														smallestSide(0), total(0), bowLength(0), ribbonLength(0),
														totalRibbon(0) {}

	int CalculateSurfaceArea()
	{

		return (2 * length * width + 2 * width * height + 2 * height * length);

	};

	/* extra paper is just the smallest side */
	void CalculateExtraPaper()
	{
		int sideA = length * width;
		int sideB = width * height;
		int sideC = height * length;

		std::array<int, 3> areaArray = { sideA, sideB, sideC };
		smallestSide = *std::min_element(std::begin(areaArray), std::end(areaArray));



	}

	int CalculateTotal()
	{
		CalculateExtraPaper();
		total = CalculateSurfaceArea() + smallestSide;
		return total;

	}

	void SetDimensions(int l, int w, int h)
	{
		length = l;
		width = w;
		height = h;

	}

	int CalculateRibbon()
	{
		int largestNumber = 0;
		std::vector<int> presentDimensionArray = { length, width, height };
		
		/* we only want the smallest perimeter face,
		   so delete the largest number so we dont get 
		   the largest face perimeter
		 */
		presentDimensionArray.erase(std::max_element(std::begin(presentDimensionArray), std::end(presentDimensionArray)));

		/* get the perimeter by doubling each side (each side has 2 edges since is a cube) */
		for (const int& num : presentDimensionArray)
		{
			largestNumber += num * 2;
		}

		/* also add up the ribbon requirement */
		largestNumber += CalculateBow();

		return largestNumber;
	}

	/* get volume of cube */
	int CalculateBow()
	{
		bowLength = length * width * height;

		return bowLength;
	}

private:
	int length, width, height;
	int smallestSide;
	int total;

	int totalRibbon;
	int bowLength;
	int ribbonLength;



};




int main()
{
	int total = 0;
	std::ifstream file;
	std::string currentLine;
	file.open("input.txt", std::ios::in);

	Present x;

	/*	loop each line of txt, extract the 'x' char into a dummy variable (not used)
		so we can get the correct L/W/D dimensions in its proper variables (a b and c)
		via stringstream
	*/
	while (std::getline(file, currentLine))
	{
		std::istringstream iss(currentLine);
		int a, b, c;
		char discard1, discard2;


		iss >> a >> discard1 >> b >> discard2 >> c;

		x.SetDimensions(a, b, c);

		/* part 2 */
		total += x.CalculateRibbon();

		/* part 1 */ 
		//total += x.CalculateTotal();


	}

	std::cout << total;


	





	return 0;
}