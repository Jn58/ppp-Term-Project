/*
 * statem.h
 *
 *  Created on: Nov 28, 2015
 *      Author: jung
 */

#ifndef STATEM_H_
#define STATEM_H_

typedef enum { initial, starting, closed, stopped, closing, stopping, reqsent, ackrcvd, acksent, opened } STATE;
typedef enum { up, down, open, close, top, tom, rcrp, rcrm, rca, rcn, rtr, rta, ruc, rxjp, rxjm, rxr } EVENT;
STATE statemc[10][16];


#endif /* STATEM_H_ */

