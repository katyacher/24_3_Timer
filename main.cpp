#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>


void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    // std::cout << u8"\033[2J\033[1;1H";
    system("clear");
}

int main() {
    std::cout << "24.3 Timer" << std::endl;

    std::tm time_tm{};
    std::cout << "Enter the time (format 00:00): ";
    std::cin >> std::get_time(&time_tm, "%M:%S");

    if (std::cin.fail()) {
        std::cout << "Incorrect format. ";
        return (int) std::cin.fail();
    }

    std::time_t now_t = time(nullptr);
    std::tm* stop_tm = std::localtime(&now_t);
    stop_tm->tm_sec += time_tm.tm_sec;
    stop_tm->tm_min += time_tm.tm_min;

    std::time_t stop_t = mktime(stop_tm);
    clear();
    while(now_t != stop_t) {
        double d = std::difftime(stop_t,now_t);
        std::time_t diff = (std::time_t)d;
        std::tm *timer = std::localtime(&diff);
        std::cout << std::put_time(timer,"%M:%S") << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        now_t = time(nullptr);
        clear();
    }
    std::cout << "DING!DING!DING!" << std::endl;
    return 0;
}