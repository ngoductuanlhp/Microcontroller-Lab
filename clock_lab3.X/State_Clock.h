#ifndef STATE_CLOCK_H
#define	STATE_CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc.h"

    
void disp_Clock (void);
void handle_Time (void);
void disp_Clock_Hide(unsigned char state);

#ifdef	__cplusplus
}
#endif

#endif	/* STATE_CLOCK_H */