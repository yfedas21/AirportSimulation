#ifndef LANDING_Q_H_
#define LANDING_Q_H_

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Plane.h"
#include "Random.h"

extern Random my_random;  // Enables us to access the global variable declared in Simulator.h

class LandingQueue
{
private:
	double arrival_rate;            // plane arrival rate per minute (set in Simulator.h)
	std::queue<Plane *> the_queue;  // queue of planes in the landing queue
	int total_wait;  // total accumulated wait time in the landing queue
	int num_served;  // number of planes served through the landing queue
	std::vector<ServiceQueue*> service_queue_vector;

public:
	LandingQueue() : total_wait(0), num_served(0) {}

	void set_arrival_rate(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}

	int get_total_wait() {
		return total_wait;
	}

	int get_num_served() {
		return num_served;
	}

	void set_service_queue_vector(vector<ServiceQueue *> &sqv) {
		this->service_queue_vector = sqv;
	}

	vector<ServiceQueue *> get_service_queue_vector() {
		return service_queue_vector;
	}

	void update(int clock)
	{
		/* add a new plane into the landing queue based on the arrival_rate
		HINT: my_random.next_double() returns a random value between 0 and 1.
		Read how the the simulation described in the book does this
		(section 6.5 pages. 392-393).
		Look at the Passenger_Queue::check_new_arrival() method
		*/
		if (my_random.next_double() < arrival_rate) {
			the_queue.push(new Plane(clock));
		}

		if (service_queue_vector.size() > 1) {
			// check if any service queues are empty...
			for (int i = 0; i < service_queue_vector.size(); i++) {
				ServiceQueue *sq = service_queue_vector.at(i);

				// if an empty queue is found, push the first plane
				// in the_queue to the empty service queue 
				if (sq->get_the_queue().empty()) {
					sq->get_the_queue().push(the_queue.front());
					// remove the plane from the_queue once it 
					// is added to the service queue
					the_queue.pop();
				}
			}
		}
	}

	

	friend class ServiceQueue;
};

#endif