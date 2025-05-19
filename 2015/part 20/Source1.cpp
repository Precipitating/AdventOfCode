#include <iostream>
using namespace std;

typedef long long ll;

const ll IN = 34000000;
const ll SQRT = 2000; //approximate sqrt of (IN/10)

ll house[4000000];

int main()
{
	for (ll i = 1; i <= SQRT; i++)
	{
		for (ll j = i * i; j <= IN / 10; j += i)
		{
			// part 2
			//if (j / i <= 50) house[j] += i * 11;
			//if (j != i * i && i <= 50) house[j] += j / i * 11;

			// part 1
			house[j] += i*10;
			if (j != i*i) house[j] += j/i*10;

		}
	}
	ll ans;
	for (ans = 1; ans < IN / 10; ans++)
	{
		if (house[ans] >= IN) break;
	}
	cout << ans << '\n';


	//debug stuff
	return 0;
}