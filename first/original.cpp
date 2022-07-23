#include<iostream> 
#include<stdlib.h>

#include <ctime>
#include <iomanip>

#include <thread>
#include <chrono>

class OrdersManager{
	private:
		std::string orders;
		int orders_processed = 0;
		time_t last_printed_log = time(0);;

		void generate_fake_orders(int quantity){
			log("Generating fake orders");
			orders = "3a551c03-fc2b-47fd-976c-da634898d337";

			log(std::to_string(quantity)+" generated...");
		}
		void log(std::string message){
			auto t = std::time(nullptr);
			auto tm = *std::localtime(&t);
			std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " > " << message << std::endl;
		}
		void fake_save_on_db(int number, std::string id){
			log("Order ["+ id +"] "+std::to_string(number)+" was successfully prosecuted.");
			std::this_thread::sleep_for(std::chrono::milliseconds( rand() % 1000));
		}
	
	public:
		OrdersManager(){
			generate_fake_orders(1000); 
		}
		void process_orders(){
			for (int i = 0; i < 1000; i++)
			{
				fake_save_on_db(i,orders);
				orders_processed++;
				
				time_t time_now = time(0);
				if (time_now > last_printed_log)
				{
					time(&last_printed_log);
					last_printed_log += 5; 
					log("Total orders executed: "+std::to_string(orders_processed)+"/1000");
				}
			}
			
		}
};



int main(int argc, char** argv) {     
	OrdersManager orders_manager = OrdersManager();
	auto begin = std::chrono::high_resolution_clock::now();
	orders_manager.process_orders();
	auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	
    printf("Time measured: %.6f seconds.\n", elapsed.count() * 1e-9);
	
	return 0;                    
}
