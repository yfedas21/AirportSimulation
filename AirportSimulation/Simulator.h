#ifndef SIMULATE_H_
#define SIMULATE_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <vector>
#include "LandingQueue.h"
#include "ServiceQueue.h"
#include "DepartureQueue.h"
#include "Random.h"

using std::vector;

Random my_random;  // Global variable 

class Simulator
{
private:
	int total_time;  // total time to run simulation
	int clock;       // current time
	//int number_of_gates;
					 
	// landing queue --> service queue --> departure queue
	LandingQueue *landing_queue;
	ServiceQueue *service_queue;
	DepartureQueue *departure_queue;

	// Remember me!
	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:

	Simulator() {
		landing_queue = new LandingQueue();
		service_queue = new ServiceQueue();
		departure_queue = new DepartureQueue();
	}

	void enter_data()
	{
		std::cout << "Welcome CS273 to the Simple Airport Simulator.\n\n";
		std::cout << "We are CS273ville, a small but feisty airport!\n";
		std::cout << "Remember to re-read section 6.5 of the text book\n\n";

		int rate = read_int("Please enter the plane arrival rate (planes/hour): ", 1, 59);
		double arrival_rate = rate / 60.0;

		int min_service = read_int("Please enter the minimum service time (mins): ", 0, INT_MAX);
		int max_service = read_int("Please enter the maximum service time (mins): ", 0, INT_MAX);
		int departure_time = read_int("Please enter the departure time (mins): ", 1, INT_MAX);
		//number_of_gates = read_int("Please enter the number of gates at the airport: ", 1, INT_MAX);

		total_time = read_int("Please enter the simulation time (hours): ", 1, INT_MAX);
		total_time *= 60;

		// set the arrival_rate for the landing queue
		landing_queue->set_arrival_rate(arrival_rate);

		// set the service times for the service queue 
		service_queue->set_service_times(min_service, max_service);
		// pass references to the landing and departure queue to the service queue
		service_queue->set_landing_queue(landing_queue);
		service_queue->set_departure_queue(departure_queue);

		//// if the number of gates is greater than 1, 
		//// create a gate vector and add the first 
		//// ServiceQueue object to this vector. 
		//if (number_of_gates > 1) {
		//	// create a vector that holds service queues 
		//	vector<ServiceQueue *> service_queue_vector;
		//	// add the first service queue to the vector
		//	service_queue_vector.push_back(service_queue);

		//	// Make the correct number of service queues
		//	for (int i = 1; i < number_of_gates; i++) {
		//		ServiceQueue *addl_gates = new ServiceQueue(min_service, max_service,
		//			landing_queue, departure_queue);
		//		service_queue_vector.push_back(addl_gates));
		//	}

		//	landing_queue->set_service_queue_vector(service_queue_vector);
		//}

		// set the departure time for the departure queue
		departure_queue->set_departure_time(departure_time);

	}

	void run_simulation()
	{
		// run the simulation
		for (clock = 0; clock < total_time; ++clock)
		{
			// for each time interval ...
			landing_queue->update(clock);

			//// if there is more than one service queue
			//// in the function (number of gates > 1), 
			//// run the update function on each service queue
			//if (number_of_gates > 1) {
			//	vector<ServiceQueue *> sqv = landing_queue->get_service_queue_vector();
			//	for (auto service_queue: sqv)
			//		service_queue->update(clock);
			//}
			
			service_queue->update(clock);

			departure_queue->update(clock);
		}
	}

	void show_stats()
	{
		/*int num_planes_served_total;
		int total_planes_service_time;

		vector<ServiceQueue *> sqv = landing_queue->get_service_queue_vector();
		for (auto s : sqv) {
			num_planes_served_total += s->get_number_of_planes_served();
			total_planes_service_time += s->get_total_planes_service_time();
		}*/

		std::cout << " -- THE ARRIVAL QUEUE -- " << std::endl;
		std::cout << "Number of planes served in the arrival queue: " << landing_queue->get_num_served() << std::endl;
		std::cout << "Total wait time for all planes in arrival queue: " << landing_queue->get_total_wait() << std::endl;
		std::cout << "The average wait time for the arrival queue: " <<
			landing_queue->get_total_wait() / landing_queue->get_num_served() << std::endl << std::endl;

		/*std::cout << " -- THE SERVICE QUEUES -- " << std::endl;
		std::cout << "Number of planes served in all service queues: " << num_planes_served_total << std::endl;
		std::cout << "Total time spent servicing planes on all gates: " << total_planes_service_time << std::endl;
		std::cout << "The average servicing time was " << total_planes_service_time / num_planes_served_total << std::endl;*/

		std::cout << " -- THE DEPARTURE QUEUE -- " << std::endl;
		std::cout << "Number of planes served in the departure queue: " << departure_queue->get_num_served() << std::endl;
		std::cout << "Total wait time for all planes in departure queue: " << departure_queue->get_total_wait() << std::endl;
		std::cout << "The average wait for the departure queue: " <<
			departure_queue->get_total_wait() / departure_queue->get_num_served() << std::endl;

		std::cout << std::endl;

	}


};

#endif