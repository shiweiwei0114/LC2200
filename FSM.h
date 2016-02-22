/*
 * FSM.h
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */

#ifndef FSM_H_
#define FSM_H_

enum macro_state {
	FETCH,
	DECODE,
	EXECUTE
};
enum micro_state {

};
typedef struct macro_state State;



struct FSM {
	State macro_state;

};

#endif /* FSM_H_ */
