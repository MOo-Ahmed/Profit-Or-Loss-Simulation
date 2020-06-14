#include <iostream>
#include <Vector>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

void simulate_model(int number_of_trails);
int generate_c1(unsigned long long);
double generate_c2(unsigned long long);
int generate_x(unsigned long long);
void print_c1(vector<int>, int);
void print_c2(vector<double>, int);
void print_x(vector<int>, int);
void print_profit(vector<double>, int);

int main()
{
	simulate_model(100);
	//simulate_model(100);
	system("Pause");
	return 0;
}

void simulate_model(int number_of_trails)
{
	const int fixed_cost = 1'000'000;
	const int price	= 249;

	vector<int> c1(number_of_trails);
	vector<double> c2(number_of_trails);
	vector<int> x(number_of_trails);
	vector<double> profit(number_of_trails);

	int num_of_losses = 0;
	double maximum_profit = INT_MIN;
	double maximum_loss = INT_MAX;
	long double average_profit = 0;

	for (int i = 0; i < number_of_trails; i++)
	{
		c1.at(i) = generate_c1(i);
		c2.at(i) = generate_c2(i);
		x.at(i) = generate_x(i);
		profit.at(i) = (price - c1[i] - c2[i]) * x[i] - fixed_cost;
		if (profit[i] > maximum_profit)
		{
			maximum_profit = profit[i];
		}
		if (profit[i] < maximum_loss)
		{
			maximum_loss = profit[i];
		}
		if (profit[i] < 0)
		{
			num_of_losses++;
		}
		average_profit += profit[i];
	}
	average_profit = average_profit / number_of_trails;
	double prob_of_loss = static_cast<double>(num_of_losses) / number_of_trails;

	cout << "The Maximum Profit :" << maximum_profit << endl;
	cout << "The Maximum Loss :" << maximum_loss << endl;
	cout << "The Average(Base) Profit :" << average_profit << endl;
	cout << "The Probabilitiy of Loss :" << prob_of_loss << endl;

	cout << endl << "The Histograms." << endl;
	print_c1(c1, number_of_trails);
	print_c2(c2, number_of_trails);
	print_x(x, number_of_trails);
	print_profit(profit, number_of_trails);
}
int generate_c1(unsigned long long num_of_skips)
{
	default_random_engine generator;
	generator.seed(time(0));
	generator.discard(num_of_skips);

	uniform_real_distribution<double> dist(0, 1);
	while (true)
	{
		double random = dist(generator);
		if (random >= 0 && random < 0.1)
		{
			return 43;
		}
		else if (random >= 0.1 && random < 0.3)
		{
			return 44;
		}
		else if (random >= 0.3 && random < 0.7)
		{
			return 45;
		}
		else if (random >= 0.7 && random < 0.9)
		{
			return 46;
		}
		else if (random >= 0.9 && random < 1)
		{
			return 47;
		}
	}
}
double generate_c2(unsigned long long num_of_skips)
{
	default_random_engine generator;
	generator.seed(time(0));
	generator.discard(num_of_skips);

	uniform_real_distribution<double> dist(80, 100);
	double random = dist(generator);

	return random;
}
int generate_x(unsigned long long num_of_skips)
{
	default_random_engine generator;
	generator.seed(time(0));
	generator.discard(num_of_skips);

	//The Standard Deviation ~ Range / 4.
	const int sd = 6750;
	//The mean is the value that divide the data into two equal halves.
	const int mean = 15000;
	normal_distribution<double> dist(mean, sd);
	while(true)
	{
		int random = dist(generator);
		if (random >= 1500 && random <= 28500)
		{
			return random;
		}
	}
}
void print_c1(vector<int> sent_vector, int number_of_trails)
{
	cout << "C1 Histogram." << endl;
	int scalar = 1;
	if (number_of_trails > 100)
	{
		scalar = number_of_trails / 100;
	}
	int const c1_range = 5;
	int freq[c1_range] = { 0 };
	for (int i = 0; i < number_of_trails; i++)
	{
		if (sent_vector[i] == 43)
		{
			freq[0]++;
		}
		else if (sent_vector[i] == 44)
		{
			freq[1]++;
		}
		else if (sent_vector[i] == 45)
		{
			freq[2]++;
		}
		else if (sent_vector[i] == 46)
		{
			freq[3]++;
		}
		else
		{
			freq[4]++;
		}
	}
	for (int print_number = 43; print_number <= 47; print_number++)
	{
		cout << print_number << " :";
		for (int i = 0; i < freq[print_number - 43] / scalar; i++)
		{
			cout << '*';
		}
		cout << endl;
	}
	cout << endl;
}
void print_c2(vector<double> sent_vector, int number_of_trails)
{
	cout << "C2 Histogram." << endl;
	int scalar = 1;
	if (number_of_trails > 100)
	{
		scalar = number_of_trails / 100;
	}
	int const c2_range = 5;
	int freq[c2_range] = { 0 };
	for (int i = 0; i < number_of_trails; i++)
	{
		if (sent_vector[i] >= 80 && sent_vector[i] < 84)
		{
			freq[0]++;
		}
		else if (sent_vector[i] >= 84 && sent_vector[i] < 88)
		{
			freq[1]++;
		}
		else if (sent_vector[i] >= 88 && sent_vector[i] < 92)
		{
			freq[2]++;
		}
		else if (sent_vector[i] >= 92 && sent_vector[i] < 96)
		{
			freq[3]++;
		}
		else
		{
			freq[4]++;
		}
	}
	int min_number = 80;
	int max_number = 84;
	for (int i = 0; i < c2_range; i++)
	{
		cout << min_number << " - " << setw(4) << max_number << " :";
		for (int index = 0; index < freq[i] / scalar; index++)
		{
			cout << '*';
		}
		cout << endl;
		min_number += 4;
		max_number += 4;
	}
	cout << endl;
}
void print_x(vector<int> sent_vector, int number_of_trails)
{
	cout << "X Histogram." << endl;
	int scalar = 1;
	if (number_of_trails > 100)
	{
		scalar = number_of_trails / 100;
	}
	const int x_range = 18;
	int freq[x_range] = { 0 };

	for (int i = 0; i < number_of_trails; i++)
	{
		if (sent_vector[i] >= 1500 && sent_vector[i] < 3000)
		{
			freq[0]++;
		}
		else if (sent_vector[i] >= 3000 && sent_vector[i] < 4500)
		{
			freq[1]++;
		}
		else if (sent_vector[i] >= 4500 && sent_vector[i] < 6000)
		{
			freq[2]++;
		}
		else if (sent_vector[i] >= 6000 && sent_vector[i] < 7500)
		{
			freq[3]++;
		}
		else if (sent_vector[i] >= 7500 && sent_vector[i] < 9000)
		{
			freq[4]++;
		}
		else if (sent_vector[i] >= 9000 && sent_vector[i] < 10500)
		{
			freq[5]++;
		}
		else if (sent_vector[i] >= 10500 && sent_vector[i] < 12000)
		{
			freq[6]++;
		}
		else if (sent_vector[i] >= 12000 && sent_vector[i] < 13500)
		{
			freq[7]++;
		}
		else if (sent_vector[i] >= 13500 && sent_vector[i] < 15000)
		{
			freq[8]++;
		}
		else if (sent_vector[i] >= 15000 && sent_vector[i] < 16500)
		{
			freq[9]++;
		}
		else if (sent_vector[i] >= 16500 && sent_vector[i] < 18000)
		{
			freq[10]++;
		}
		else if (sent_vector[i] >= 18000 && sent_vector[i] < 19500)
		{
			freq[11]++;
		}
		else if (sent_vector[i] >= 19500 && sent_vector[i] < 21000)
		{
			freq[12]++;
		}
		else if (sent_vector[i] >= 21000 && sent_vector[i] < 22500)
		{
			freq[13]++;
		}
		else if (sent_vector[i] >= 22500 && sent_vector[i] < 24000)
		{
			freq[14]++;
		}
		else if (sent_vector[i] >= 24000 && sent_vector[i] < 25500)
		{
			freq[15]++;
		}
		else if (sent_vector[i] >= 25500 && sent_vector[i] < 27000)
		{
			freq[16]++;
		}
		else
		{
			freq[17]++;
		}
	}

	int min_number = 1500;
	int max_number = 3000;

	for(int i = 0; i < x_range; i++)
	{
		cout << setw(5) << min_number << " - " << setw(5) << max_number << " :";
		for (int index = 0; index < freq[i] / scalar; index++)
		{
			cout << '*';
		}
		cout << endl;
		min_number += 1500;
		max_number += 1500;
	}
	cout << endl;
}
void print_profit(vector<double> sent_vector, int number_of_trails)
{
	cout << "Profit Histogram." << endl;
	int scalar = 1;
	if (number_of_trails > 100)
	{
		scalar = number_of_trails / 100;
	}
	const int max_profit = 2'591'000;
	const int max_loss = -847'000;

	const int profit_range = 10;
	int freq[profit_range] = { 0 };
	int int_diff = 343800;

	for (int i = 0; i < number_of_trails; i++)
	{
		for (int j = 0; j < profit_range; j++) 
		{
			if (sent_vector[i] >= -847'000 + int_diff * j &&
				sent_vector[i] < -847'000 + int_diff * (j + 1))
			{
				freq[j]++;
				break;
			}
		}
	}
	for (int i = 0; i < profit_range; i++) 
	{
		cout << setw(7) << (max_loss + int_diff * i) << " - " 
			 << setw(7) <<(max_loss + int_diff * (i + 1)) << " :";
		for (int j = 0; j < freq[i] / scalar; j++) 
		{
			cout << '*';
		}
		cout << endl;
	}
	cout << endl;
}
