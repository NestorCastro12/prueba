#include<iostream> 
#include<stdlib.h>

#include <ctime>
#include <iomanip>

#include <thread>
#include <chrono>
#include <vector>
#include <list>
#include <mutex>


class OrdersManager{
	private:
        std::list<std::string> orders;
		int orders_processed = 0;
		time_t last_printed_log = time(0);
        std::vector<std::thread> threads;
        std::mutex m;

		void generate_fake_orders(int quantity){
			log("Generating fake orders");
            for (int i = 0; i < quantity; i++)
            {
                //orders.push_back("3a551c03-fc2b-47fd-976c-da634898d"+std::to_string(rand() % 999));
                orders.push_back(std::to_string(i));
            }
			log(std::to_string(quantity)+" generated...");
		}

		void log(std::string message){
			auto t = std::time(nullptr);
			auto tm = *std::localtime(&t);
			std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " > " << message << std::endl;
		}

		void fake_save_on_db(int number, std::string id){
			log("Order ["+ id +"] "+std::to_string(orders_processed)+" was successfully prosecuted.");
			std::this_thread::sleep_for(std::chrono::milliseconds( rand() % 1000));
		}
	
	public:
		OrdersManager(){
			generate_fake_orders(1000); 
		}

        void procesadasCn(){
            log("se han procesado "+std::to_string(orders_processed));
        }

        void

        void process_orders(int nT, int nThreads){
            while (!orders.empty())
            {
                std::string asd = orders.front();
                orders.pop_front();
				fake_save_on_db(5,asd);
				orders_processed++;
            }
            
        }
		void process_orders_threads(int nThreads){
            for (int i = 0; i < nThreads; ++i){
                threads.push_back(std::thread(&OrdersManager::process_orders, this, i, nThreads));

            }
            for (auto& t: threads) t.join();

		}
};



int main(int argc, char** argv) {     
	time_t start, finish;
	OrdersManager orders_manager = OrdersManager();
	time(&start);
	orders_manager.process_orders_threads(500);
	time(&finish);


	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " > Tiempo de ejecucion: "+std::to_string(difftime(finish, start))+" segundos..."<< std::endl;
    orders_manager.procesadasCn();
	return 1;                    
}
