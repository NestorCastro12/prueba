#include<iostream> 
#include<stdlib.h>

#include <ctime>
#include <iomanip>

#include <thread>
#include <chrono>
#include <vector>
#include <list>

class OrdersManager{
	private:
        std::list<std::string> orders;
		int orders_processed = 0;
		time_t last_printed_log = time(0);
        std::list<std::thread> threads;

		void generate_fake_orders(int quantity){
			log("Generating fake orders");
            for (int i = 0; i < quantity; i++)
            {
                orders.push_back("3a551c03-fc2b-47fd-976c-da634898d"+std::to_string(rand() % 999));
            }
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
			/*
			 * constructor, genera 1000 ordenes
			 */
			generate_fake_orders(1000); 
		}

        void process_order(std::string order, int id){
			/*
			 * procesa una unica orden (order) y recibe el numero de orden (id)
			 */
            fake_save_on_db(id,order);
            orders_processed++;
        }

        void process_orders(){
			/*
             * realiza un while hasta que la lista de ordenes esté vacia
             * guarda la orden en una variable, crea un hilo que se encargue de procesarla y elimina la orden de la lista
             * cuando toda la lista de ordenes se encuentre vacia se espera que los hilos terminen para poder terminar el proceso
			 */
            int idTh = 0;
            while (!orders.empty())
            {
                std::string order = orders.front();
                threads.push_back(std::thread(&OrdersManager::process_order, this, order,idTh));
                idTh++;
                orders.pop_front();
            }
            for (auto& t: threads) t.join();
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
