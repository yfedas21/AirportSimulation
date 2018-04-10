#ifndef DEPARTURE_Q_H_
#define DEPARTURE_Q_H_

#include <queue>
#include "Plane.h"

class DepartureQueue
{
private:
	std::queue<Plane *> the_queue;  // the queue of planes in the departure queue
	int departure_time;  // the time a plane has to wait when it reaches the front of the queue before it can take-off
	int total_wait;   // total accumulated wait time in the departure queue
	int num_served;   // number of planes served through the departure queue
public:
	DepartureQueue() : total_wait(0), num_served(0) {}

	void set_departure_time(int departure_time) {
		this->departure_time = departure_time;
	}

	int get_num_served() {
		return num_served;
	}

	int get_total_wait() {
		return total_wait;
	}

	void update(int clock)
	{
		// are there planes waiting in the departure queue?
		if (!the_queue.empty()) {
			Plane *plane = the_queue.front();
			if (plane->ready_takeoff_time == -1) { // new plane has arrived at the front
												   // update the ready_takeoff_time attribute of the plane
				plane->ready_takeoff_time = clock;
			}
			else {
				// compute the time the plane has been waiting at the front
				if (clock - plane->ready_takeoff_time > departure_time) {
					// plane has waited long enough
					// FIXME: remove plane from departure queue


					// FIXME: calculate the wait time


					// FIXME: update total_wait and num_served



					// take off!   goodbye plane
					delete plane;
				}
			}
		}

	}

	friend class ServiceQueue;

};

#endif
