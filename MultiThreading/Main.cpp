#include<iostream>
#include<thread>
#include<vector>
#include<chrono>

using namespace std;
using namespace chrono;

void sum(vector <int> &vector, int &tempsum)
{
	for (auto& n : vector)
		tempsum += n;
};

int main()
{
	setlocale(LC_CTYPE, "rus");
	int result{}, n{}, res1{}, res2{}, res3{}, res4{};
	cout << "Введите число элементов: " << endl;
	cin >> n;
	vector <int> vct;
	srand(time(NULL));	
	for (size_t i = 0; i < n; i++)
	{
		vct.push_back(rand() % 100 + 1);
	}
	const size_t m = 4;
	const size_t num_vect = vct.size() / m;
	auto current = begin(vct);
	const auto finish = end(vct);
	vector<vector<int>> vectors(num_vect);
	for (auto& c : vectors)
	{
		auto distance = finish - current;
		auto step = distance < num_vect ? distance : num_vect;
		c.assign(current, current + step);
		current += step;
	}	
	auto start1 = high_resolution_clock::now();
	thread t(sum, ref(vct), ref(result));
	t.join();
	auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	cout << "Время выполнения в одном потоке: " << duration1.count() << " микросекунд" << endl;
	cout << "Сумма элементов: " << result << endl;
	auto start2 = high_resolution_clock::now();
	thread t1(sum, ref(vectors[0]), ref(res1));
	t1.join();
	thread t2(sum, ref(vectors[1]), ref(res2));
	t2.join();
	thread t3(sum, ref(vectors[2]), ref(res3));
	t3.join();
	thread t4(sum, ref(vectors[3]), ref(res4));
	t4.join();
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	cout << "Время выполнения в нескольких потоках: " << duration2.count() << " микросекунд" << endl;	
	cout << "Сумма элементов: " << res1 + res2 + res3 + res4 << endl;
	return 0;
}