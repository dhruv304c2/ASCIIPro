#include <cstdlib>
#include <iostream>
#include <ostream>
#include <thread>
#include <chrono>


void waitTime(int seconds){
	auto now = std::chrono::steady_clock::now();
	std::this_thread::sleep_until(now + std::chrono::seconds(seconds));
}

int main() {
	std::cout << "\033[?25l";
	int maxSeconds = 60;
	int secondsPassed = 0;
	while(secondsPassed <= maxSeconds){
		system("cls");
		std::cout<< secondsPassed << std::endl;
		waitTime(1);
		secondsPassed++;
	}
}

