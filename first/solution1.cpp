#include<iostream> 
#include<stdlib.h>

#include <ctime>
#include <iomanip>

#include <thread>
#include <chrono>
#include <vector>

class OrdersManager{
	private:
		std::string orders;
		int orders_processed = 0;
		time_t last_printed_log = time(0);
        std::vector<std::thread> threads;

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
			log("Order ["+ id +"] "+std::to_string(orders_processed)+" was successfully prosecuted.");
			std::this_thread::sleep_for(std::chrono::milliseconds( rand() % 1000));
		}
	
	public:
		OrdersManager(){
			generate_fake_orders(1000); 
		}

        void process_orders(int nT, int nThreads){
			/*
			 * recibe el numero total de hilos que se van a usar(nThreads)  y el numero del hilo en cuestion (nT)
			 * a través de dicha información encuentra el rango de datos a operar, siendo (1000/nThreads)*nT el primer numero
			 * y ((1000*(nT+1))/nThreads) el ultimo. se dejó 1000 como el numero de datos constante, falta que sea un valor variable.
			 */
			for (int i = (1000/nThreads)*nT; i < ((1000*(nT+1))/nThreads); i++)
			{
				fake_save_on_db(i,orders);
				orders_processed++;
			}

        }

		void process_orders_threads(int nThreads){
			/*
			 * Distribuye el trabajo entre el numero de hilos seleccionados (nThreads) a través de un ciclo for
			 * espera a que todos los hilos terminen para poder terminar el proceso
			 */
            for (int i = 0; i < nThreads; ++i){
                threads.push_back(std::thread(&OrdersManager::process_orders, this, i, nThreads));
            }
            for (auto& t: threads) t.join();

		}
};



int main(int argc, char** argv) {     
	OrdersManager orders_manager = OrdersManager();
	auto begin = std::chrono::high_resolution_clock::now();
	// se usa process_orders_threads para procesar los datos con hilos, en este caso con 500
	orders_manager.process_orders_threads(500);
	auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	
    printf("Time measured: %.6f seconds.\n", elapsed.count() * 1e-9);
	return 0;                    
}